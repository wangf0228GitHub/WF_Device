#ifndef __SHT25_h__
#define __SHT25_h__

#define SHT25_HoldT	0b11100011
#define SHT25_HoldRH 0b11100101
#define SHT25_NoHoldT 0b11110011
#define SHT25_NoHoldRH 0b11110101

#define SHT25_ADDR_W 0b10000000
#define SHT25_ADDR_R 0b10000001
extern uint16_t SHT25_T;//放大100倍后的温度
extern uint16_t SHT25_RH;//放大100倍后的湿度
uint8_t SHT25_bErrT;
uint8_t SHT25_bErrRH;
uint16_t SHT25_HoldRead(uint8_t cmd);
void SHT25_GetT(void);
void SHT25_GetRH(void);
uint8_t SHT25_GetUserReg(void);
uint8_t SHT25_Reset(void);
#endif // __SHT25_h__

