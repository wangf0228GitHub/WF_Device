#ifndef __X5045_H__
#define __X5045_H__

void X5045_Init();
//复位看门狗
void X5045_RstWDT();
#ifndef X5045_MorePage
//向X5045写入单字节数据,输入：x,待写数据,address,写入数据的地址
void X5045_WriteByte(unsigned char address,unsigned char x);
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount);

//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
unsigned char X5045_ReadByte(unsigned char address);
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount);
#else
//向X5045写入单字节数据,输入：x,待写数据,address,写入数据的地址
void X5045_WriteByte(unsigned char address,unsigned char x,unsigned char page);
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount,unsigned char page);

//从X5045读入单字节数据,输入：address,待读数据地址,返回：读出的数据
unsigned char X5045_ReadByte(unsigned char address,unsigned char page);
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount,unsigned char page);
#endif

//5045状态寄存器读出程序
unsigned char X5045_RDSR();

//5045状态寄存器写入程序
void X5045_WRSR(unsigned char x);

#endif
