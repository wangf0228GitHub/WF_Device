#include <htc.h>
#include "HardwareProfile.h"
#if	_FLASH_WRITE_SIZE

extern void initiate_write(void);

/* Most flash devices write in 8 byte widths,
 * newer parts can write 32 or 64 bytes at a time.
 * If these haven't been defined by user, use defaults. */
#ifndef _FLASH_WRITE_SIZE
	#define _FLASH_WRITE_SIZE 8
#endif
#ifndef _FLASH_ERASE_SIZE
	#define _FLASH_ERASE_SIZE 64
#endif

// If the device erases in larger blocks than it writes, then the destination sector
// should be copied to a buffer in RAM before erasure.
// For those chips whose flash write size is the same as their erasure size,
// data can be copied directly into the flash holding registers. (don't maintain a
// separate buffer in RAM)
#if _FLASH_WRITE_SIZE != _FLASH_ERASE_SIZE
	#define _BUFFERED_WRITE
#endif

// Check to see that legitimate values have been entered
#define _POW2(a)	(((a)&((a)-1))==0)
#define _NOT_POW2(a)	(! _POW2(a))

#if _NOT_POW2(_FLASH_WRITE_SIZE)
 #error Invalid definition of _FLASH_WRITE_SIZE, must be a power of two
#endif
#if _NOT_POW2(_FLASH_ERASE_SIZE)
 #error Invalid definition of _FLASH_ERASE_SIZE, must be a power of two
#endif

// 18Fxxjxx parts have a slightly different mechanism for writing to flash
#ifdef __J_PART
// This buffer must align on a 1024 address boundary
// This cannot exist in the final block of 1024 as this contains config stuff
volatile const uint8_t _flash_buffer_j[_FLASH_ERASE_SIZE] @ FlashWriteBakAddr;

/* Simple helper function as this sequence is repeated through flash_write for J-parts */
void transfer(uint16_t ix){
	asm("tblwt*");			// transfer a byte to flash holding regs
	ix &= (_FLASH_WRITE_SIZE-1);
	if(ix==0)
		initiate_write();	// commit what we have to temp buffer
}
	
void wf_flash_write(const uint8_t * source, uint16_t length, far uint8_t * dest){
	uint16_t ix, offset;
	volatile const uint8_t * ptr;
#ifdef _OMNI_CODE_
	uint8_t	saved_tblptrh;
	uint8_t	saved_tblptru;

	saved_tblptrh = TBLPTRH;
	saved_tblptru = TBLPTRU;
#endif
	
	offset = ((int)(dest)) & (_FLASH_ERASE_SIZE-1);
	dest = (uint8_t *)((uint32_t)dest & ~(_FLASH_ERASE_SIZE-1)); // point to start of destination erase buffer

	while(length){
		// align at start of erase block
		ptr = dest;

		TBLPTR = (uint8_t *)_flash_buffer_j;	// first erase the holding buffer
		FREE=1;
		initiate_write();
	
		for(ix=0; ix != _FLASH_ERASE_SIZE; ){
			if(offset || (length==0)){	// not reading from source, read backup from dest
				if(offset)
					offset--;
				TBLPTR=(uint8_t *)ptr;
				asm("tblrd*");
			}else{
				TABLAT=*source++;	// reading from source
				length--;
			}
			ptr++;

			// TABLAT has byte of data, transfer to flash buffer
			TBLPTR = (uint8_t *)&_flash_buffer_j[ix];
			transfer(++ix);	// commit what we have to temp buffer
		}

		TBLPTR = (uint8_t *)dest;	// first erase the destination sector
		FREE=1;
		initiate_write();
		ptr = _flash_buffer_j;	// already linked to start of erase block

		// transfer temporary buffer in flash to final destination.
		for(ix=0; ix != _FLASH_ERASE_SIZE; ){
			TABLAT = _flash_buffer_j[ix];	// read this byte from buffer
			TBLPTR = (uint8_t *)dest++;	// point to destination
			transfer(++ix);	// move from flash buffer to final destination
		}
	}
#ifdef _OMNI_CODE_
	TBLPTRH = saved_tblptrh;
	TBLPTRU = saved_tblptru;
#endif
}

#else	// non-J-parts use this implementation

 // further bounds checking required for non-J-parts
 #if (_FLASH_WRITE_SIZE > 128)
  #error Invalid _FLASH_WRITE_SIZE, must range from 1 to 128
 #endif
 #if (_FLASH_ERASE_SIZE > 128)
  #error Invalid _FLASH_ERASE_SIZE, must range from 1 to 128
 #endif


void wf_flash_write(const uint8_t * source_addr,uint16_t length,far uint8_t * dest_addr)
{
	/* variable declaration */
#ifdef _BUFFERED_WRITE
	uint8_t BUFFER[_FLASH_ERASE_SIZE];
#endif
	uint8_t index;
	uint8_t offset;
#if _ERRATA_TYPES & ERRATA_TBLWTINT
	uint8_t saved1,saved3;
#endif
#ifdef _OMNI_CODE_
	uint8_t	saved_tblptrh;
	uint8_t	saved_tblptru;

	saved_tblptrh = TBLPTRH;
	saved_tblptru = TBLPTRU;
#endif

	offset=(uint8_t)dest_addr & (_FLASH_ERASE_SIZE-1);	// find the index into the flash sector
	dest_addr-=offset;	// find the start address of the flash sector

	TBLPTR=dest_addr;	// initially point to destination sector
	asm("tblrd*-");		// dummy read to adjust TBLPTR
	while(length){
		// fill the data buffer either from ...
		index=0;
		do{
			asm("tblrd+*");	// get data from destination sector...
#ifdef _BUFFERED_WRITE
			BUFFER[index]=TABLAT;	// copy to RAM buffer
			if((index>=offset)&&(length)){	// or specifed data area
				BUFFER[index]=*(source_addr++);	// overwrite RAM buffer with new data
				TBLPTR=dest_addr + index;	// point back to destination sector
				length--;
			}
#else
			if((index>=offset)&&(length)){	// or specifed data area
				TABLAT=*(source_addr++);	// overwrite TABLAT with new data
				TBLPTR=dest_addr + index;	// point back to destination sector
				length--;
			}
			asm("tblwt*");	// unbuffered version - write directly to flash holding registers
#endif
		}while(++index<_FLASH_ERASE_SIZE);

// Erase destination sector before writing
#ifdef _BUFFERED_WRITE
		TBLPTRL=((uint8_t)dest_addr)&0xFF;  // start of erase section before erasure & short writes
#endif
		EECON1=0x94;
		initiate_write();
	
// now begin to copy the buffer to the destination area
#ifdef _BUFFERED_WRITE
		asm("\ttblrd*-");	// dummy read to adjust TBLPTR
		index=0;
		do{
			TABLAT=BUFFER[index];	// copy the data buffer to the
#if _ERRATA_TYPES & ERRATA_TBLWTINT
			/* Errata document (B3,B4,B5) advises that these devices need all *
			 * interrupt enable bits clear during TBLWT instruction.          *
			 * (That document mentions INTCON2 but it has no 'enable' bits.)  */
			saved1=INTCON; INTCON=0;	// Saving interrupt registers
			saved3=INTCON3; INTCON3=0;
			BUFFER[0]=PIE1; PIE1=0;		// Buffer[0] may be recycled
			offset=PIE2; PIE2=0;		// offset may be recycled
#endif
			asm("\ttblwt+*");	// load internal flash write registers
#if _ERRATA_TYPES & ERRATA_TBLWTINT
			PIE2=offset;	// restore the interrupt registers
			PIE1=BUFFER[0];
			INTCON3=saved3;
			INTCON=saved1;
#endif
			if((index & (_FLASH_WRITE_SIZE-1))==(_FLASH_WRITE_SIZE-1)){	// after every Nth byte...
				initiate_write();	// commit the holding registers to flash.
			}
		}while(++index<_FLASH_ERASE_SIZE);
#endif
		initiate_write();
		dest_addr+=_FLASH_ERASE_SIZE;
		offset=0;
	}
#ifdef _OMNI_CODE_
	TBLPTRH = saved_tblptrh;
	TBLPTRU = saved_tblptru;
#endif
}
#endif
#endif

