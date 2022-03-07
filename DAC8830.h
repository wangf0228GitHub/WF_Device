#ifndef __DAC8830_h__
#define __DAC8830_h__


void DAC8830_Init(void);
void DAC8830_Setting(uint16_t set);

#ifdef DAC8830_2
void DAC8830_2_Init(void);
void DAC8830_2_Setting(uint16_t set);
#endif

#ifdef DAC8830_3
void DAC8830_3_Init(void);
void DAC8830_3_Setting(uint16_t set);
#endif

#endif // __SimSPI_h__
