#ifndef __X5045_H__
#define __X5045_H__

void X5045_Init();
//复位看门狗
void X5045_RstWDT();
#ifndef X5045_MorePage
//向X5045写入单字节数据,输入：x,待写数据,address,写入数据的地址
void X5045_WriteByte(uint8_t address,uint8_t x);
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount);

//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
uint8_t X5045_ReadByte(uint8_t address);
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount);
#else
//向X5045写入单字节数据,输入：x,待写数据,address,写入数据的地址
void X5045_WriteByte(uint8_t address,uint8_t x,uint8_t page);
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount,uint8_t page);

//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
uint8_t X5045_ReadByte(uint8_t address,uint8_t page);
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount,uint8_t page);
#endif

//5045状态寄存器读出程序
uint8_t X5045_RDSR();

//5045状态寄存器写入程序
void X5045_WRSR(uint8_t x);

#endif
