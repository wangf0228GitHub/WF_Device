#ifndef __SX1276_LORA_H__
#define __SX1276_LORA_H__


#include "sx1276_LoRa_Conf.h"

typedef enum
{
	RFLR_STATE_IDLE,
	RFLR_STATE_RX_INIT,
	RFLR_STATE_RX_RUNNING,
	RFLR_STATE_RX_DONE,
	RFLR_STATE_RX_TIMEOUT,
	RFLR_STATE_TX_INIT,
	RFLR_STATE_TX_RUNNING,
	RFLR_STATE_TX_DONE,
	RFLR_STATE_TX_TIMEOUT,
	RFLR_STATE_CAD_INIT,
	RFLR_STATE_CAD_RUNNING,
}tRFLRStates;
extern uint8_t RFLRState;

typedef struct sLoRaSettings
{
    uint32_t RFFrequency;
    int8_t Power;
    uint8_t SignalBw;                   
                                         
    uint8_t SpreadingFactor;            
    uint8_t ErrorCoding;                
    bool CrcOn;                         
    bool ImplicitHeaderOn;              
    bool RxSingleOn;                   
    bool FreqHopOn;                     
    uint8_t HopPeriod;                 
    uint32_t TxPacketTimeout;
    uint32_t RxPacketTimeout;
    uint8_t PayloadLength;
}tLoRaSettings;
extern tLoRaSettings LoRaSettings;

/*!
 * RF packet definition
 */
#define RF_BUFFER_SIZE_MAX                          256
#define RF_BUFFER_SIZE                              256
extern uint8_t RFBuffer[RF_BUFFER_SIZE];

extern double RxPacketRssiValue;
extern uint16_t RxPacketSize;
extern int8_t RxPacketSnrEstimate;
extern uint16_t TxPacketSize;
extern uint8_t RxGain;
extern uint8_t TxRxFlag;

typedef struct sSX1276LR
{
    uint8_t RegFifo;                                // 0x00 
    // Common settings
    uint8_t RegOpMode;                              // 0x01 
    uint8_t RegRes02;                               // 0x02 
    uint8_t RegRes03;                               // 0x03 
    uint8_t RegBandSetting;                         // 0x04 
    uint8_t RegRes05;                               // 0x05 
    uint8_t RegFrfMsb;                              // 0x06 
    uint8_t RegFrfMid;                              // 0x07 
    uint8_t RegFrfLsb;                              // 0x08 
    // Tx settings
    uint8_t RegPaConfig;                            // 0x09 
    uint8_t RegPaRamp;                              // 0x0A 
    uint8_t RegOcp;                                 // 0x0B 
    // Rx settings
    uint8_t RegLna;                                 // 0x0C 
    // LoRa registers
    uint8_t RegFifoAddrPtr;                         // 0x0D 
    uint8_t RegFifoTxBaseAddr;                      // 0x0E 
    uint8_t RegFifoRxBaseAddr;                      // 0x0F 
    uint8_t RegFifoRxCurrentAddr;                   // 0x10 
    uint8_t RegIrqFlagsMask;                        // 0x11 
    uint8_t RegIrqFlags;                            // 0x12 
    uint8_t RegNbRxBytes;                           // 0x13 
    uint8_t RegRxHeaderCntValueMsb;                 // 0x14 
    uint8_t RegRxHeaderCntValueLsb;                 // 0x15 
    uint8_t RegRxPacketCntValueMsb;                 // 0x16 
    uint8_t RegRxPacketCntValueLsb;                 // 0x17 
    uint8_t RegModemStat;                           // 0x18 
    uint8_t RegPktSnrValue;                         // 0x19 
    uint8_t RegPktRssiValue;                        // 0x1A 
    uint8_t RegRssiValue;                           // 0x1B 
    uint8_t RegHopChannel;                          // 0x1C 
    uint8_t RegModemConfig1;                        // 0x1D 
    uint8_t RegModemConfig2;                        // 0x1E 
    uint8_t RegSymbTimeoutLsb;                      // 0x1F 
    uint8_t RegPreambleMsb;                         // 0x20 
    uint8_t RegPreambleLsb;                         // 0x21 
    uint8_t RegPayloadLength;                       // 0x22 
    uint8_t RegMaxPayloadLength;                    // 0x23 
    uint8_t RegHopPeriod;                           // 0x24 
    uint8_t RegFifoRxByteAddr;                      // 0x25
    uint8_t RegModemConfig3;                        // 0x26
    uint8_t RegTestReserved27[0x30 - 0x27];         // 0x27-0x30
    uint8_t RegTestReserved31;                      // 0x31
    uint8_t RegTestReserved32[0x40 - 0x32];         // 0x32-0x40
    // I/O settings                
    uint8_t RegDioMapping1;                         // 0x40 
    uint8_t RegDioMapping2;                         // 0x41 
    // Version
    uint8_t RegVersion;                             // 0x42
    // Additional settings
    uint8_t RegAgcRef;                              // 0x43
    uint8_t RegAgcThresh1;                          // 0x44
    uint8_t RegAgcThresh2;                          // 0x45
    uint8_t RegAgcThresh3;                          // 0x46
    // Test
    uint8_t RegTestReserved47[0x4B - 0x47];         // 0x47-0x4A
    // Additional settings
    uint8_t RegPllHop;                              // 0x4B
    uint8_t RegTestReserved4C;                      // 0x4C
    uint8_t RegPaDac;                               // 0x4D
    // Test
    uint8_t RegTestReserved4E[0x58-0x4E];           // 0x4E-0x57
    // Additional settings
    uint8_t RegTcxo;                                // 0x58
    // Test
    uint8_t RegTestReserved59;                      // 0x59
    // Test
    uint8_t RegTestReserved5B;                      // 0x5B
    // Additional settings
    uint8_t RegPll;                                 // 0x5C
    // Test
    uint8_t RegTestReserved5D;                      // 0x5D
    // Additional settings
    uint8_t RegPllLowPn;                            // 0x5E
    // Test
    uint8_t RegTestReserved5F[0x6C - 0x5F];         // 0x5F-0x6B
    // Additional settings
    uint8_t RegFormerTemp;                          // 0x6C
    // Test
    uint8_t RegTestReserved6D[0x71 - 0x6D];         // 0x6D-0x70
}tSX1276LR;

extern tSX1276LR* SX1276LR;

void SX1276Write( uint8_t addr, uint8_t data );
void SX1276Read( uint8_t addr, uint8_t *data );
void SX1276ReadFifo( uint8_t *buffer, uint8_t size );
void SX1276WriteFifo( uint8_t *buffer, uint8_t size );
void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );
void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );


void SX1276LoRaSetOpMode( uint8_t opMode );
/*!
 * SX1276 definitions
 */
// #define XTAL_FREQ                                   26000000
// #define FREQ_STEP                                   49.59106445
#define XTAL_FREQ                                   32000000
#define FREQ_STEP                                   61.03515625

/*!
 * SX1276 Internal registers Address
 */
#define REG_LR_FIFO                                 0x00 
// Common settings
#define REG_LR_OPMODE                               0x01 
#define REG_LR_BANDSETTING                          0x04
#define REG_LR_FRFMSB                               0x06 
#define REG_LR_FRFMID                               0x07
#define REG_LR_FRFLSB                               0x08 
// Tx settings
#define REG_LR_PACONFIG                             0x09 
#define REG_LR_PARAMP                               0x0A 
#define REG_LR_OCP                                  0x0B 
// Rx settings
#define REG_LR_LNA                                  0x0C 
// LoRa registers
#define REG_LR_FIFOADDRPTR                          0x0D 
#define REG_LR_FIFOTXBASEADDR                       0x0E 
#define REG_LR_FIFORXBASEADDR                       0x0F 
#define REG_LR_FIFORXCURRENTADDR                    0x10 
#define REG_LR_IRQFLAGSMASK                         0x11 
#define REG_LR_IRQFLAGS                             0x12 
#define REG_LR_NBRXBYTES                            0x13 
#define REG_LR_RXHEADERCNTVALUEMSB                  0x14 
#define REG_LR_RXHEADERCNTVALUELSB                  0x15 
#define REG_LR_RXPACKETCNTVALUEMSB                  0x16 
#define REG_LR_RXPACKETCNTVALUELSB                  0x17 
#define REG_LR_MODEMSTAT                            0x18 
#define REG_LR_PKTSNRVALUE                          0x19 
#define REG_LR_PKTRSSIVALUE                         0x1A 
#define REG_LR_RSSIVALUE                            0x1B 
#define REG_LR_HOPCHANNEL                           0x1C 
#define REG_LR_MODEMCONFIG1                         0x1D 
#define REG_LR_MODEMCONFIG2                         0x1E 
#define REG_LR_SYMBTIMEOUTLSB                       0x1F 
#define REG_LR_PREAMBLEMSB                          0x20 
#define REG_LR_PREAMBLELSB                          0x21 
#define REG_LR_PAYLOADLENGTH                        0x22 
#define REG_LR_PAYLOADMAXLENGTH                     0x23 
#define REG_LR_HOPPERIOD                            0x24 
#define REG_LR_FIFORXBYTEADDR                       0x25
#define REG_LR_MODEMCONFIG3                         0x26
// end of documented register in datasheet
// I/O settings
#define REG_LR_DIOMAPPING1                          0x40
#define REG_LR_DIOMAPPING2                          0x41
// Version
#define REG_LR_VERSION                              0x42
// Additional settings
#define REG_LR_PLLHOP                               0x44
#define REG_LR_TCXO                                 0x4B
#define REG_LR_PADAC                                0x4D
#define REG_LR_FORMERTEMP                           0x5B
#define REG_LR_BITRATEFRAC                          0x5D
#define REG_LR_AGCREF                               0x61
#define REG_LR_AGCTHRESH1                           0x62
#define REG_LR_AGCTHRESH2                           0x63
#define REG_LR_AGCTHRESH3                           0x64

#define RFLR_OPMODE_LONGRANGEMODE_MASK              0x7F 
#define RFLR_OPMODE_LONGRANGEMODE_OFF               0x00 // Default
#define RFLR_OPMODE_LONGRANGEMODE_ON                0x80 

#define RFLR_OPMODE_ACCESSSHAREDREG_MASK            0xBF 
#define RFLR_OPMODE_ACCESSSHAREDREG_ENABLE          0x40 
#define RFLR_OPMODE_ACCESSSHAREDREG_DISABLE         0x00 // Default

#define RFLR_OPMODE_FREQMODE_ACCESS_MASK            0xF7
#define RFLR_OPMODE_FREQMODE_ACCESS_LF              0x08 // Default
#define RFLR_OPMODE_FREQMODE_ACCESS_HF              0x00 

#define RFLR_OPMODE_MASK                            0xF8 
#define RFLR_OPMODE_SLEEP                           0x00 
#define RFLR_OPMODE_STANDBY                         0x01 // Default
#define RFLR_OPMODE_SYNTHESIZER_TX                  0x02 
#define RFLR_OPMODE_TRANSMITTER                     0x03 
#define RFLR_OPMODE_SYNTHESIZER_RX                  0x04 
#define RFLR_OPMODE_RECEIVER                        0x05 
// LoRa specific modes
#define RFLR_OPMODE_RECEIVER_SINGLE                 0x06 
#define RFLR_OPMODE_CAD                             0x07 
/*!
 * RegBandSetting 
 */
#define RFLR_BANDSETTING_MASK                    0x3F 
#define RFLR_BANDSETTING_AUTO                    0x00 // Default
#define RFLR_BANDSETTING_DIV_BY_1                0x40
#define RFLR_BANDSETTING_DIV_BY_2                0x80
#define RFLR_BANDSETTING_DIV_BY_6                0xC0

/*!
 * RegFrf (MHz)
 */
#define RFLR_FRFMSB_434_MHZ                         0x6C // Default
#define RFLR_FRFMID_434_MHZ                         0x80 // Default
#define RFLR_FRFLSB_434_MHZ                         0x00 // Default

#define RFLR_FRFMSB_863_MHZ                         0xD7
#define RFLR_FRFMID_863_MHZ                         0xC0
#define RFLR_FRFLSB_863_MHZ                         0x00
#define RFLR_FRFMSB_864_MHZ                         0xD8
#define RFLR_FRFMID_864_MHZ                         0x00
#define RFLR_FRFLSB_864_MHZ                         0x00
#define RFLR_FRFMSB_865_MHZ                         0xD8
#define RFLR_FRFMID_865_MHZ                         0x40
#define RFLR_FRFLSB_865_MHZ                         0x00
#define RFLR_FRFMSB_866_MHZ                         0xD8
#define RFLR_FRFMID_866_MHZ                         0x80
#define RFLR_FRFLSB_866_MHZ                         0x00
#define RFLR_FRFMSB_867_MHZ                         0xD8
#define RFLR_FRFMID_867_MHZ                         0xC0
#define RFLR_FRFLSB_867_MHZ                         0x00
#define RFLR_FRFMSB_868_MHZ                         0xD9
#define RFLR_FRFMID_868_MHZ                         0x00
#define RFLR_FRFLSB_868_MHZ                         0x00
#define RFLR_FRFMSB_869_MHZ                         0xD9
#define RFLR_FRFMID_869_MHZ                         0x40
#define RFLR_FRFLSB_869_MHZ                         0x00
#define RFLR_FRFMSB_870_MHZ                         0xD9
#define RFLR_FRFMID_870_MHZ                         0x80
#define RFLR_FRFLSB_870_MHZ                         0x00

#define RFLR_FRFMSB_902_MHZ                         0xE1
#define RFLR_FRFMID_902_MHZ                         0x80
#define RFLR_FRFLSB_902_MHZ                         0x00
#define RFLR_FRFMSB_903_MHZ                         0xE1
#define RFLR_FRFMID_903_MHZ                         0xC0
#define RFLR_FRFLSB_903_MHZ                         0x00
#define RFLR_FRFMSB_904_MHZ                         0xE2
#define RFLR_FRFMID_904_MHZ                         0x00
#define RFLR_FRFLSB_904_MHZ                         0x00
#define RFLR_FRFMSB_905_MHZ                         0xE2
#define RFLR_FRFMID_905_MHZ                         0x40
#define RFLR_FRFLSB_905_MHZ                         0x00
#define RFLR_FRFMSB_906_MHZ                         0xE2
#define RFLR_FRFMID_906_MHZ                         0x80
#define RFLR_FRFLSB_906_MHZ                         0x00
#define RFLR_FRFMSB_907_MHZ                         0xE2
#define RFLR_FRFMID_907_MHZ                         0xC0
#define RFLR_FRFLSB_907_MHZ                         0x00
#define RFLR_FRFMSB_908_MHZ                         0xE3
#define RFLR_FRFMID_908_MHZ                         0x00
#define RFLR_FRFLSB_908_MHZ                         0x00
#define RFLR_FRFMSB_909_MHZ                         0xE3
#define RFLR_FRFMID_909_MHZ                         0x40
#define RFLR_FRFLSB_909_MHZ                         0x00
#define RFLR_FRFMSB_910_MHZ                         0xE3
#define RFLR_FRFMID_910_MHZ                         0x80
#define RFLR_FRFLSB_910_MHZ                         0x00
#define RFLR_FRFMSB_911_MHZ                         0xE3
#define RFLR_FRFMID_911_MHZ                         0xC0
#define RFLR_FRFLSB_911_MHZ                         0x00
#define RFLR_FRFMSB_912_MHZ                         0xE4
#define RFLR_FRFMID_912_MHZ                         0x00
#define RFLR_FRFLSB_912_MHZ                         0x00
#define RFLR_FRFMSB_913_MHZ                         0xE4
#define RFLR_FRFMID_913_MHZ                         0x40
#define RFLR_FRFLSB_913_MHZ                         0x00
#define RFLR_FRFMSB_914_MHZ                         0xE4
#define RFLR_FRFMID_914_MHZ                         0x80
#define RFLR_FRFLSB_914_MHZ                         0x00
#define RFLR_FRFMSB_915_MHZ                         0xE4  
#define RFLR_FRFMID_915_MHZ                         0xC0  
#define RFLR_FRFLSB_915_MHZ                         0x00 
#define RFLR_FRFMSB_916_MHZ                         0xE5
#define RFLR_FRFMID_916_MHZ                         0x00
#define RFLR_FRFLSB_916_MHZ                         0x00
#define RFLR_FRFMSB_917_MHZ                         0xE5
#define RFLR_FRFMID_917_MHZ                         0x40
#define RFLR_FRFLSB_917_MHZ                         0x00
#define RFLR_FRFMSB_918_MHZ                         0xE5
#define RFLR_FRFMID_918_MHZ                         0x80
#define RFLR_FRFLSB_918_MHZ                         0x00
#define RFLR_FRFMSB_919_MHZ                         0xE5
#define RFLR_FRFMID_919_MHZ                         0xC0
#define RFLR_FRFLSB_919_MHZ                         0x00
#define RFLR_FRFMSB_920_MHZ                         0xE6
#define RFLR_FRFMID_920_MHZ                         0x00
#define RFLR_FRFLSB_920_MHZ                         0x00
#define RFLR_FRFMSB_921_MHZ                         0xE6
#define RFLR_FRFMID_921_MHZ                         0x40
#define RFLR_FRFLSB_921_MHZ                         0x00
#define RFLR_FRFMSB_922_MHZ                         0xE6
#define RFLR_FRFMID_922_MHZ                         0x80
#define RFLR_FRFLSB_922_MHZ                         0x00
#define RFLR_FRFMSB_923_MHZ                         0xE6
#define RFLR_FRFMID_923_MHZ                         0xC0
#define RFLR_FRFLSB_923_MHZ                         0x00
#define RFLR_FRFMSB_924_MHZ                         0xE7
#define RFLR_FRFMID_924_MHZ                         0x00
#define RFLR_FRFLSB_924_MHZ                         0x00
#define RFLR_FRFMSB_925_MHZ                         0xE7
#define RFLR_FRFMID_925_MHZ                         0x40
#define RFLR_FRFLSB_925_MHZ                         0x00
#define RFLR_FRFMSB_926_MHZ                         0xE7
#define RFLR_FRFMID_926_MHZ                         0x80
#define RFLR_FRFLSB_926_MHZ                         0x00
#define RFLR_FRFMSB_927_MHZ                         0xE7
#define RFLR_FRFMID_927_MHZ                         0xC0
#define RFLR_FRFLSB_927_MHZ                         0x00
#define RFLR_FRFMSB_928_MHZ                         0xE8
#define RFLR_FRFMID_928_MHZ                         0x00
#define RFLR_FRFLSB_928_MHZ                         0x00

/*!
 * RegPaConfig
 */
#define RFLR_PACONFIG_PASELECT_MASK                 0x7F 
#define RFLR_PACONFIG_PASELECT_PABOOST              0x80 
#define RFLR_PACONFIG_PASELECT_RFO                  0x00 // Default

#define RFLR_PACONFIG_MAX_POWER_MASK                0x8F

#define RFLR_PACONFIG_OUTPUTPOWER_MASK              0xF0 
 
/*!
 * RegPaRamp
 */
#define RFLR_PARAMP_TXBANDFORCE_MASK                0xEF 
#define RFLR_PARAMP_TXBANDFORCE_BAND_SEL            0x10 
#define RFLR_PARAMP_TXBANDFORCE_AUTO                0x00 // Default

#define RFLR_PARAMP_MASK                            0xF0 
#define RFLR_PARAMP_3400_US                         0x00 
#define RFLR_PARAMP_2000_US                         0x01 
#define RFLR_PARAMP_1000_US                         0x02
#define RFLR_PARAMP_0500_US                         0x03 
#define RFLR_PARAMP_0250_US                         0x04 
#define RFLR_PARAMP_0125_US                         0x05 
#define RFLR_PARAMP_0100_US                         0x06 
#define RFLR_PARAMP_0062_US                         0x07 
#define RFLR_PARAMP_0050_US                         0x08 
#define RFLR_PARAMP_0040_US                         0x09 // Default
#define RFLR_PARAMP_0031_US                         0x0A 
#define RFLR_PARAMP_0025_US                         0x0B 
#define RFLR_PARAMP_0020_US                         0x0C 
#define RFLR_PARAMP_0015_US                         0x0D 
#define RFLR_PARAMP_0012_US                         0x0E 
#define RFLR_PARAMP_0010_US                         0x0F 

/*!
 * RegOcp
 */
#define RFLR_OCP_MASK                               0xDF 
#define RFLR_OCP_ON                                 0x20 // Default
#define RFLR_OCP_OFF                                0x00   

#define RFLR_OCP_TRIM_MASK                          0xE0
#define RFLR_OCP_TRIM_045_MA                        0x00
#define RFLR_OCP_TRIM_050_MA                        0x01   
#define RFLR_OCP_TRIM_055_MA                        0x02 
#define RFLR_OCP_TRIM_060_MA                        0x03 
#define RFLR_OCP_TRIM_065_MA                        0x04 
#define RFLR_OCP_TRIM_070_MA                        0x05 
#define RFLR_OCP_TRIM_075_MA                        0x06 
#define RFLR_OCP_TRIM_080_MA                        0x07  
#define RFLR_OCP_TRIM_085_MA                        0x08
#define RFLR_OCP_TRIM_090_MA                        0x09 
#define RFLR_OCP_TRIM_095_MA                        0x0A 
#define RFLR_OCP_TRIM_100_MA                        0x0B  // Default
#define RFLR_OCP_TRIM_105_MA                        0x0C 
#define RFLR_OCP_TRIM_110_MA                        0x0D 
#define RFLR_OCP_TRIM_115_MA                        0x0E 
#define RFLR_OCP_TRIM_120_MA                        0x0F 
#define RFLR_OCP_TRIM_130_MA                        0x10
#define RFLR_OCP_TRIM_140_MA                        0x11   
#define RFLR_OCP_TRIM_150_MA                        0x12 
#define RFLR_OCP_TRIM_160_MA                        0x13 
#define RFLR_OCP_TRIM_170_MA                        0x14 
#define RFLR_OCP_TRIM_180_MA                        0x15 
#define RFLR_OCP_TRIM_190_MA                        0x16 
#define RFLR_OCP_TRIM_200_MA                        0x17  
#define RFLR_OCP_TRIM_210_MA                        0x18
#define RFLR_OCP_TRIM_220_MA                        0x19 
#define RFLR_OCP_TRIM_230_MA                        0x1A 
#define RFLR_OCP_TRIM_240_MA                        0x1B

/*!
 * RegLna
 */
#define RFLR_LNA_GAIN_MASK                          0x1F 
#define RFLR_LNA_GAIN_G1                            0x20 // Default
#define RFLR_LNA_GAIN_G2                            0x40 
#define RFLR_LNA_GAIN_G3                            0x60 
#define RFLR_LNA_GAIN_G4                            0x80 
#define RFLR_LNA_GAIN_G5                            0xA0 
#define RFLR_LNA_GAIN_G6                            0xC0 

#define RFLR_LNA_BOOST_LF_MASK                      0xE7 
#define RFLR_LNA_BOOST_LF_DEFAULT                   0x00 // Default
#define RFLR_LNA_BOOST_LF_GAIN                      0x08 
#define RFLR_LNA_BOOST_LF_IP3                       0x10 
#define RFLR_LNA_BOOST_LF_BOOST                     0x18 

#define RFLR_LNA_RXBANDFORCE_MASK                   0xFB 
#define RFLR_LNA_RXBANDFORCE_BAND_SEL               0x04
#define RFLR_LNA_RXBANDFORCE_AUTO                   0x00 // Default

#define RFLR_LNA_BOOST_HF_MASK                      0xFC 
#define RFLR_LNA_BOOST_HF_OFF                       0x00 // Default
#define RFLR_LNA_BOOST_HF_ON                        0x03 

/*!
 * RegFifoAddrPtr
 */
#define RFLR_FIFOADDRPTR                            0x00 // Default

/*!
 * RegFifoTxBaseAddr
 */
#define RFLR_FIFOTXBASEADDR                         0x80 // Default

/*!
 * RegFifoTxBaseAddr
 */
#define RFLR_FIFORXBASEADDR                         0x00 // Default

/*!
 * RegFifoRxCurrentAddr (Read Only)
 */

/*!
 * RegIrqFlagsMask
 */
#define RFLR_IRQFLAGS_RXTIMEOUT_MASK                0x80 
#define RFLR_IRQFLAGS_RXDONE_MASK                   0x40 
#define RFLR_IRQFLAGS_PAYLOADCRCERROR_MASK          0x20 
#define RFLR_IRQFLAGS_VALIDHEADER_MASK              0x10 
#define RFLR_IRQFLAGS_TXDONE_MASK                   0x08 
#define RFLR_IRQFLAGS_CADDONE_MASK                  0x04 
#define RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL_MASK       0x02 
#define RFLR_IRQFLAGS_CADDETECTED_MASK              0x01 

/*!
 * RegIrqFlags
 */
#define RFLR_IRQFLAGS_RXTIMEOUT                     0x80 
#define RFLR_IRQFLAGS_RXDONE                        0x40 
#define RFLR_IRQFLAGS_PAYLOADCRCERROR               0x20 
#define RFLR_IRQFLAGS_VALIDHEADER                   0x10 
#define RFLR_IRQFLAGS_TXDONE                        0x08 
#define RFLR_IRQFLAGS_CADDONE                       0x04 
#define RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL            0x02 
#define RFLR_IRQFLAGS_CADDETECTED                   0x01 

 /*!
 * RegModemStat (Read Only)    //
 */
#define RFLR_MODEMSTAT_RX_CR_MASK                   0x1F 
#define RFLR_MODEMSTAT_MODEM_STATUS_MASK            0xE0 
 /*!
 * RegModemConfig1
 */
#define RFLR_MODEMCONFIG1_BW_MASK                   0x0F 

#define RFLR_MODEMCONFIG1_BW_7_81_KHZ               0x00 
#define RFLR_MODEMCONFIG1_BW_10_41_KHZ              0x10 
#define RFLR_MODEMCONFIG1_BW_15_62_KHZ              0x20 
#define RFLR_MODEMCONFIG1_BW_20_83_KHZ              0x30 
#define RFLR_MODEMCONFIG1_BW_31_25_KHZ              0x40 
#define RFLR_MODEMCONFIG1_BW_41_66_KHZ              0x50 
#define RFLR_MODEMCONFIG1_BW_62_50_KHZ              0x60 
#define RFLR_MODEMCONFIG1_BW_125_KHZ                0x70 // Default
#define RFLR_MODEMCONFIG1_BW_250_KHZ                0x80 
#define RFLR_MODEMCONFIG1_BW_500_KHZ                0x90 
                                                    
#define RFLR_MODEMCONFIG1_CODINGRATE_MASK           0xF1 
#define RFLR_MODEMCONFIG1_CODINGRATE_4_5            0x02
#define RFLR_MODEMCONFIG1_CODINGRATE_4_6            0x04 // Default
#define RFLR_MODEMCONFIG1_CODINGRATE_4_7            0x06 
#define RFLR_MODEMCONFIG1_CODINGRATE_4_8            0x08 
                                                    
#define RFLR_MODEMCONFIG1_IMPLICITHEADER_MASK       0xFE 
#define RFLR_MODEMCONFIG1_IMPLICITHEADER_ON         0x01 
#define RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF        0x00 // Default

 /*!
 * RegModemConfig2
 */
#define RFLR_MODEMCONFIG2_SF_MASK                   0x0F 
#define RFLR_MODEMCONFIG2_SF_6                      0x60 
#define RFLR_MODEMCONFIG2_SF_7                      0x70 // Default
#define RFLR_MODEMCONFIG2_SF_8                      0x80 
#define RFLR_MODEMCONFIG2_SF_9                      0x90 
#define RFLR_MODEMCONFIG2_SF_10                     0xA0 
#define RFLR_MODEMCONFIG2_SF_11                     0xB0 
#define RFLR_MODEMCONFIG2_SF_12                     0xC0 

#define RFLR_MODEMCONFIG2_TXCONTINUOUSMODE_MASK     0xF7 
#define RFLR_MODEMCONFIG2_TXCONTINUOUSMODE_ON       0x08 
#define RFLR_MODEMCONFIG2_TXCONTINUOUSMODE_OFF      0x00 

#define RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK         0xFB 
#define RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON           0x04 
#define RFLR_MODEMCONFIG2_RXPAYLOADCRC_OFF          0x00 // Default
 
#define RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK       0xFC 
#define RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB            0x00 // Default
                                                    
                                                    
/*!                                                 
 * RegHopChannel (Read Only)                        
 */                                                 
#define RFLR_HOPCHANNEL_PLL_LOCK_TIMEOUT_MASK       0x7F 
#define RFLR_HOPCHANNEL_PLL_LOCK_FAIL               0x80 
#define RFLR_HOPCHANNEL_PLL_LOCK_SUCCEED            0x00 // Default
                                                    
#define RFLR_HOPCHANNEL_PAYLOAD_CRC16_MASK          0xBF
#define RFLR_HOPCHANNEL_PAYLOAD_CRC16_ON            0x40
#define RFLR_HOPCHANNEL_PAYLOAD_CRC16_OFF           0x00 // Default

#define RFLR_HOPCHANNEL_CHANNEL_MASK                0x3F 


/*!
 * RegSymbTimeoutLsb
 */
#define RFLR_SYMBTIMEOUTLSB_SYMBTIMEOUT             0x64 // Default

/*!
 * RegPreambleLengthMsb
 */
#define RFLR_PREAMBLELENGTHMSB                      0x00 // Default

/*!
 * RegPreambleLengthLsb
 */
#define RFLR_PREAMBLELENGTHLSB                      0x08 // Default

/*!
 * RegPayloadLength
 */
#define RFLR_PAYLOADLENGTH                          0x0E // Default

/*!
 * RegPayloadMaxLength
 */
#define RFLR_PAYLOADMAXLENGTH                       0xFF // Default

/*!
 * RegHopPeriod
 */
#define RFLR_HOPPERIOD_FREQFOPPINGPERIOD            0x00 // Default


/*!
 * RegDioMapping1
 */
#define RFLR_DIOMAPPING1_DIO0_MASK                  0x3F
#define RFLR_DIOMAPPING1_DIO0_00                    0x00  // Default
#define RFLR_DIOMAPPING1_DIO0_01                    0x40
#define RFLR_DIOMAPPING1_DIO0_10                    0x80
#define RFLR_DIOMAPPING1_DIO0_11                    0xC0

#define RFLR_DIOMAPPING1_DIO1_MASK                  0xCF
#define RFLR_DIOMAPPING1_DIO1_00                    0x00  // Default
#define RFLR_DIOMAPPING1_DIO1_01                    0x10
#define RFLR_DIOMAPPING1_DIO1_10                    0x20
#define RFLR_DIOMAPPING1_DIO1_11                    0x30

#define RFLR_DIOMAPPING1_DIO2_MASK                  0xF3
#define RFLR_DIOMAPPING1_DIO2_00                    0x00  // Default
#define RFLR_DIOMAPPING1_DIO2_01                    0x04
#define RFLR_DIOMAPPING1_DIO2_10                    0x08
#define RFLR_DIOMAPPING1_DIO2_11                    0x0C

#define RFLR_DIOMAPPING1_DIO3_MASK                  0xFC
#define RFLR_DIOMAPPING1_DIO3_00                    0x00  // Default
#define RFLR_DIOMAPPING1_DIO3_01                    0x01
#define RFLR_DIOMAPPING1_DIO3_10                    0x02
#define RFLR_DIOMAPPING1_DIO3_11                    0x03

/*!
 * RegDioMapping2
 */
#define RFLR_DIOMAPPING2_DIO4_MASK                  0x3F
#define RFLR_DIOMAPPING2_DIO4_00                    0x00  // Default
#define RFLR_DIOMAPPING2_DIO4_01                    0x40
#define RFLR_DIOMAPPING2_DIO4_10                    0x80
#define RFLR_DIOMAPPING2_DIO4_11                    0xC0

#define RFLR_DIOMAPPING2_DIO5_MASK                  0xCF
#define RFLR_DIOMAPPING2_DIO5_00                    0x00  // Default
#define RFLR_DIOMAPPING2_DIO5_01                    0x10
#define RFLR_DIOMAPPING2_DIO5_10                    0x20
#define RFLR_DIOMAPPING2_DIO5_11                    0x30

#define RFLR_DIOMAPPING2_MAP_MASK                   0xFE
#define RFLR_DIOMAPPING2_MAP_PREAMBLEDETECT         0x01
#define RFLR_DIOMAPPING2_MAP_RSSI                   0x00  // Default
/*!
 * RegPllHop
 */
#define RFLR_PLLHOP_FASTHOP_MASK                    0x7F
#define RFLR_PLLHOP_FASTHOP_ON                      0x80
#define RFLR_PLLHOP_FASTHOP_OFF                     0x00 // Default

/*!
 * RegTcxo
 */
#define RFLR_TCXO_TCXOINPUT_MASK                    0xEF
#define RFLR_TCXO_TCXOINPUT_ON                      0x10
#define RFLR_TCXO_TCXOINPUT_OFF                     0x00  // Default

/*!
 * RegPaDac
 */
#define RFLR_PADAC_20DBM_MASK                       0xF8
#define RFLR_PADAC_20DBM_ON                         0x07
#define RFLR_PADAC_20DBM_OFF                        0x04  // Default

/*!
 * RegPll
 */
#define RFLR_PLL_BANDWIDTH_MASK                     0x3F
#define RFLR_PLL_BANDWIDTH_75                       0x00
#define RFLR_PLL_BANDWIDTH_150                      0x40
#define RFLR_PLL_BANDWIDTH_225                      0x80
#define RFLR_PLL_BANDWIDTH_300                      0xC0  // Default

/*!
 * RegPllLowPn
 */
#define RFLR_PLLLOWPN_BANDWIDTH_MASK                0x3F
#define RFLR_PLLLOWPN_BANDWIDTH_75                  0x00
#define RFLR_PLLLOWPN_BANDWIDTH_150                 0x40
#define RFLR_PLLLOWPN_BANDWIDTH_225                 0x80
#define RFLR_PLLLOWPN_BANDWIDTH_300                 0xC0  // Default

/*!
 * RegModemConfig3
 */
#define RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_MASK  0xF7 
#define RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_ON    0x08 
#define RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_OFF   0x00 // Default

#define RFLR_MODEMCONFIG3_AGCAUTO_MASK              0xFB 
#define RFLR_MODEMCONFIG3_AGCAUTO_ON                0x04 // Default 
#define RFLR_MODEMCONFIG3_AGCAUTO_OFF               0x00 


/*!
 * RF packet definition
 */
#define RF_BUFFER_SIZE_MAX                          256
#define RF_BUFFER_SIZE                              256
/*!
 * SX1276 definitions
 */
// #define XTAL_FREQ                                   26000000
// #define FREQ_STEP                                   49.59106445
#define XTAL_FREQ                                   32000000
#define FREQ_STEP                                   61.03515625
/*!
 * SX1276 Internal registers Address
 */
#define REG_FIFO                                    0x00
// Common settings
#define REG_OPMODE                                  0x01
#define REG_BITRATEMSB                              0x02
#define REG_BITRATELSB                              0x03
#define REG_FDEVMSB                                 0x04 
#define REG_FDEVLSB                                 0x05
#define REG_FRFMSB                                  0x06
#define REG_FRFMID                                  0x07
#define REG_FRFLSB                                  0x08
// Tx settings
#define REG_PACONFIG                                0x09
#define REG_PARAMP                                  0x0A
#define REG_OCP                                     0x0B 
// Rx settings
#define REG_LNA                                     0x0C
#define REG_RXCONFIG                                0x0D
#define REG_RSSICONFIG                              0x0E
#define REG_RSSICOLLISION                           0x0F
#define REG_RSSITHRESH                              0x10
#define REG_RSSIVALUE                               0x11
#define REG_RXBW                                    0x12 
#define REG_AFCBW                                   0x13
#define REG_OOKPEAK                                 0x14
#define REG_OOKFIX                                  0x15
#define REG_OOKAVG                                  0x16
#define REG_RES17                                   0x17
#define REG_RES18                                   0x18
#define REG_RES19                                   0x19
#define REG_AFCFEI                                  0x1A
#define REG_AFCMSB                                  0x1B
#define REG_AFCLSB                                  0x1C
#define REG_FEIMSB                                  0x1D
#define REG_FEILSB                                  0x1E
#define REG_PREAMBLEDETECT                          0x1F
#define REG_RXTIMEOUT1                              0x20
#define REG_RXTIMEOUT2                              0x21
#define REG_RXTIMEOUT3                              0x22
#define REG_RXDELAY                                 0x23
// Oscillator settings
#define REG_OSC                                     0x24
// Packet handler settings
#define REG_PREAMBLEMSB                             0x25
#define REG_PREAMBLELSB                             0x26
#define REG_SYNCCONFIG                              0x27
#define REG_SYNCVALUE1                              0x28
#define REG_SYNCVALUE2                              0x29
#define REG_SYNCVALUE3                              0x2A
#define REG_SYNCVALUE4                              0x2B
#define REG_SYNCVALUE5                              0x2C
#define REG_SYNCVALUE6                              0x2D
#define REG_SYNCVALUE7                              0x2E
#define REG_SYNCVALUE8                              0x2F
#define REG_PACKETCONFIG1                           0x30
#define REG_PACKETCONFIG2                           0x31
#define REG_PAYLOADLENGTH                           0x32
#define REG_NODEADRS                                0x33
#define REG_BROADCASTADRS                           0x34
#define REG_FIFOTHRESH                              0x35
// SM settings
#define REG_SEQCONFIG1                              0x36
#define REG_SEQCONFIG2                              0x37
#define REG_TIMERRESOL                              0x38
#define REG_TIMER1COEF                              0x39
#define REG_TIMER2COEF                              0x3A
// Service settings
#define REG_IMAGECAL                                0x3B
#define REG_TEMP                                    0x3C
#define REG_LOWBAT                                  0x3D
// Status
#define REG_IRQFLAGS1                               0x3E
#define REG_IRQFLAGS2                               0x3F
// I/O settings
#define REG_DIOMAPPING1                             0x40
#define REG_DIOMAPPING2                             0x41
// Version
#define REG_VERSION                                 0x42
// Additional settings
#define REG_PLLHOP                                  0x44
#define REG_TCXO                                    0x4B
#define REG_PADAC                                   0x4D
#define REG_FORMERTEMP                              0x5B
#define REG_BITRATEFRAC                             0x5D
#define REG_AGCREF                                  0x61
#define REG_AGCTHRESH1                              0x62
#define REG_AGCTHRESH2                              0x63
#define REG_AGCTHRESH3                              0x64


/*!
 * SX1276 FSK bit control definition
 */

/*!
 * RegFifo
 */

/*!
 * RegOpMode
 */
#define RF_OPMODE_LONGRANGEMODE_MASK                0x7F
#define RF_OPMODE_LONGRANGEMODE_OFF                 0x00  // Default
#define RF_OPMODE_LONGRANGEMODE_ON                  0x80

#define RF_OPMODE_MODULATIONTYPE_MASK               0x9F
#define RF_OPMODE_MODULATIONTYPE_FSK                0x00  // Default
#define RF_OPMODE_MODULATIONTYPE_OOK                0x20

#define RF_OPMODE_FREQMODE_ACCESS_MASK              0xF7
#define RF_OPMODE_FREQMODE_ACCESS_LF                0x08  // Default
#define RF_OPMODE_FREQMODE_ACCESS_HF                0x00 

#define RF_OPMODE_MASK                              0xF8
#define RF_OPMODE_SLEEP                             0x00
#define RF_OPMODE_STANDBY                           0x01  // Default
#define RF_OPMODE_SYNTHESIZER_TX                    0x02
#define RF_OPMODE_TRANSMITTER                       0x03
#define RF_OPMODE_SYNTHESIZER_RX                    0x04
#define RF_OPMODE_RECEIVER                          0x05

/*!
 * RegBitRate (bits/sec)
 */
#define RF_BITRATEMSB_1200_BPS                      0x68
#define RF_BITRATELSB_1200_BPS                      0x2B
#define RF_BITRATEMSB_2400_BPS                      0x34
#define RF_BITRATELSB_2400_BPS                      0x15
#define RF_BITRATEMSB_4800_BPS                      0x1A  // Default
#define RF_BITRATELSB_4800_BPS                      0x0B  // Default
#define RF_BITRATEMSB_9600_BPS                      0x0D
#define RF_BITRATELSB_9600_BPS                      0x05
#define RF_BITRATEMSB_15000_BPS                     0x08
#define RF_BITRATELSB_15000_BPS                     0x55
#define RF_BITRATEMSB_19200_BPS                     0x06
#define RF_BITRATELSB_19200_BPS                     0x83
#define RF_BITRATEMSB_38400_BPS                     0x03
#define RF_BITRATELSB_38400_BPS                     0x41
#define RF_BITRATEMSB_76800_BPS                     0x01
#define RF_BITRATELSB_76800_BPS                     0xA1
#define RF_BITRATEMSB_153600_BPS                    0x00
#define RF_BITRATELSB_153600_BPS                    0xD0
#define RF_BITRATEMSB_57600_BPS                     0x02
#define RF_BITRATELSB_57600_BPS                     0x2C
#define RF_BITRATEMSB_115200_BPS                    0x01
#define RF_BITRATELSB_115200_BPS                    0x16
#define RF_BITRATEMSB_12500_BPS                     0x0A
#define RF_BITRATELSB_12500_BPS                     0x00
#define RF_BITRATEMSB_25000_BPS                     0x05
#define RF_BITRATELSB_25000_BPS                     0x00
#define RF_BITRATEMSB_50000_BPS                     0x02
#define RF_BITRATELSB_50000_BPS                     0x80
#define RF_BITRATEMSB_100000_BPS                    0x01
#define RF_BITRATELSB_100000_BPS                    0x40
#define RF_BITRATEMSB_150000_BPS                    0x00
#define RF_BITRATELSB_150000_BPS                    0xD5
#define RF_BITRATEMSB_200000_BPS                    0x00
#define RF_BITRATELSB_200000_BPS                    0xA0
#define RF_BITRATEMSB_250000_BPS                    0x00
#define RF_BITRATELSB_250000_BPS                    0x80
#define RF_BITRATEMSB_32768_BPS                     0x03
#define RF_BITRATELSB_32768_BPS                     0xD1

/*!
 * RegFdev (Hz)
 */
 
#define RF_FDEVMSB_BANDREG_MASK                     0x3F 
#define RF_FDEVMSB_BANDREG_AUTO                     0x00 // Default
#define RF_FDEVMSB_BANDREG_DIV_BY_1                 0x40
#define RF_FDEVMSB_BANDREG_DIV_BY_2                 0x80
#define RF_FDEVMSB_BANDREG_DIV_BY_6                 0xC0
 
#define RF_FDEVMSB_FDEV_MASK                        0xC0

#define RF_FDEVMSB_2000_HZ                          0x00
#define RF_FDEVLSB_2000_HZ                          0x21
#define RF_FDEVMSB_5000_HZ                          0x00  // Default
#define RF_FDEVLSB_5000_HZ                          0x52  // Default
#define RF_FDEVMSB_10000_HZ                         0x00
#define RF_FDEVLSB_10000_HZ                         0xA4
#define RF_FDEVMSB_15000_HZ                         0x00
#define RF_FDEVLSB_15000_HZ                         0xF6
#define RF_FDEVMSB_20000_HZ                         0x01
#define RF_FDEVLSB_20000_HZ                         0x48
#define RF_FDEVMSB_25000_HZ                         0x01
#define RF_FDEVLSB_25000_HZ                         0x9A
#define RF_FDEVMSB_30000_HZ                         0x01
#define RF_FDEVLSB_30000_HZ                         0xEC
#define RF_FDEVMSB_35000_HZ                         0x02
#define RF_FDEVLSB_35000_HZ                         0x3D
#define RF_FDEVMSB_40000_HZ                         0x02
#define RF_FDEVLSB_40000_HZ                         0x8F
#define RF_FDEVMSB_45000_HZ                         0x02
#define RF_FDEVLSB_45000_HZ                         0xE1
#define RF_FDEVMSB_50000_HZ                         0x03
#define RF_FDEVLSB_50000_HZ                         0x33
#define RF_FDEVMSB_55000_HZ                         0x03
#define RF_FDEVLSB_55000_HZ                         0x85
#define RF_FDEVMSB_60000_HZ                         0x03
#define RF_FDEVLSB_60000_HZ                         0xD7
#define RF_FDEVMSB_65000_HZ                         0x04
#define RF_FDEVLSB_65000_HZ                         0x29
#define RF_FDEVMSB_70000_HZ                         0x04
#define RF_FDEVLSB_70000_HZ                         0x7B
#define RF_FDEVMSB_75000_HZ                         0x04
#define RF_FDEVLSB_75000_HZ                         0xCD
#define RF_FDEVMSB_80000_HZ                         0x05
#define RF_FDEVLSB_80000_HZ                         0x1F
#define RF_FDEVMSB_85000_HZ                         0x05
#define RF_FDEVLSB_85000_HZ                         0x71
#define RF_FDEVMSB_90000_HZ                         0x05
#define RF_FDEVLSB_90000_HZ                         0xC3
#define RF_FDEVMSB_95000_HZ                         0x06
#define RF_FDEVLSB_95000_HZ                         0x14
#define RF_FDEVMSB_100000_HZ                        0x06
#define RF_FDEVLSB_100000_HZ                        0x66
#define RF_FDEVMSB_110000_HZ                        0x07
#define RF_FDEVLSB_110000_HZ                        0x0A
#define RF_FDEVMSB_120000_HZ                        0x07
#define RF_FDEVLSB_120000_HZ                        0xAE
#define RF_FDEVMSB_130000_HZ                        0x08
#define RF_FDEVLSB_130000_HZ                        0x52
#define RF_FDEVMSB_140000_HZ                        0x08
#define RF_FDEVLSB_140000_HZ                        0xF6
#define RF_FDEVMSB_150000_HZ                        0x09
#define RF_FDEVLSB_150000_HZ                        0x9A
#define RF_FDEVMSB_160000_HZ                        0x0A
#define RF_FDEVLSB_160000_HZ                        0x3D
#define RF_FDEVMSB_170000_HZ                        0x0A
#define RF_FDEVLSB_170000_HZ                        0xE1
#define RF_FDEVMSB_180000_HZ                        0x0B
#define RF_FDEVLSB_180000_HZ                        0x85
#define RF_FDEVMSB_190000_HZ                        0x0C
#define RF_FDEVLSB_190000_HZ                        0x29
#define RF_FDEVMSB_200000_HZ                        0x0C
#define RF_FDEVLSB_200000_HZ                        0xCD

/*!
 * RegFrf (MHz)
 */
#define RF_FRFMSB_863_MHZ                           0xD7
#define RF_FRFMID_863_MHZ                           0xC0
#define RF_FRFLSB_863_MHZ                           0x00
#define RF_FRFMSB_864_MHZ                           0xD8
#define RF_FRFMID_864_MHZ                           0x00
#define RF_FRFLSB_864_MHZ                           0x00
#define RF_FRFMSB_865_MHZ                           0xD8
#define RF_FRFMID_865_MHZ                           0x40
#define RF_FRFLSB_865_MHZ                           0x00
#define RF_FRFMSB_866_MHZ                           0xD8
#define RF_FRFMID_866_MHZ                           0x80
#define RF_FRFLSB_866_MHZ                           0x00
#define RF_FRFMSB_867_MHZ                           0xD8
#define RF_FRFMID_867_MHZ                           0xC0
#define RF_FRFLSB_867_MHZ                           0x00
#define RF_FRFMSB_868_MHZ                           0xD9
#define RF_FRFMID_868_MHZ                           0x00
#define RF_FRFLSB_868_MHZ                           0x00
#define RF_FRFMSB_869_MHZ                           0xD9
#define RF_FRFMID_869_MHZ                           0x40
#define RF_FRFLSB_869_MHZ                           0x00
#define RF_FRFMSB_870_MHZ                           0xD9
#define RF_FRFMID_870_MHZ                           0x80
#define RF_FRFLSB_870_MHZ                           0x00

#define RF_FRFMSB_902_MHZ                           0xE1
#define RF_FRFMID_902_MHZ                           0x80
#define RF_FRFLSB_902_MHZ                           0x00
#define RF_FRFMSB_903_MHZ                           0xE1
#define RF_FRFMID_903_MHZ                           0xC0
#define RF_FRFLSB_903_MHZ                           0x00
#define RF_FRFMSB_904_MHZ                           0xE2
#define RF_FRFMID_904_MHZ                           0x00
#define RF_FRFLSB_904_MHZ                           0x00
#define RF_FRFMSB_905_MHZ                           0xE2
#define RF_FRFMID_905_MHZ                           0x40
#define RF_FRFLSB_905_MHZ                           0x00
#define RF_FRFMSB_906_MHZ                           0xE2
#define RF_FRFMID_906_MHZ                           0x80
#define RF_FRFLSB_906_MHZ                           0x00
#define RF_FRFMSB_907_MHZ                           0xE2
#define RF_FRFMID_907_MHZ                           0xC0
#define RF_FRFLSB_907_MHZ                           0x00
#define RF_FRFMSB_908_MHZ                           0xE3
#define RF_FRFMID_908_MHZ                           0x00
#define RF_FRFLSB_908_MHZ                           0x00
#define RF_FRFMSB_909_MHZ                           0xE3
#define RF_FRFMID_909_MHZ                           0x40
#define RF_FRFLSB_909_MHZ                           0x00
#define RF_FRFMSB_910_MHZ                           0xE3
#define RF_FRFMID_910_MHZ                           0x80
#define RF_FRFLSB_910_MHZ                           0x00
#define RF_FRFMSB_911_MHZ                           0xE3
#define RF_FRFMID_911_MHZ                           0xC0
#define RF_FRFLSB_911_MHZ                           0x00
#define RF_FRFMSB_912_MHZ                           0xE4
#define RF_FRFMID_912_MHZ                           0x00
#define RF_FRFLSB_912_MHZ                           0x00
#define RF_FRFMSB_913_MHZ                           0xE4
#define RF_FRFMID_913_MHZ                           0x40
#define RF_FRFLSB_913_MHZ                           0x00
#define RF_FRFMSB_914_MHZ                           0xE4
#define RF_FRFMID_914_MHZ                           0x80
#define RF_FRFLSB_914_MHZ                           0x00
#define RF_FRFMSB_915_MHZ                           0xE4  // Default
#define RF_FRFMID_915_MHZ                           0xC0  // Default
#define RF_FRFLSB_915_MHZ                           0x00  // Default
#define RF_FRFMSB_916_MHZ                           0xE5
#define RF_FRFMID_916_MHZ                           0x00
#define RF_FRFLSB_916_MHZ                           0x00
#define RF_FRFMSB_917_MHZ                           0xE5
#define RF_FRFMID_917_MHZ                           0x40
#define RF_FRFLSB_917_MHZ                           0x00
#define RF_FRFMSB_918_MHZ                           0xE5
#define RF_FRFMID_918_MHZ                           0x80
#define RF_FRFLSB_918_MHZ                           0x00
#define RF_FRFMSB_919_MHZ                           0xE5
#define RF_FRFMID_919_MHZ                           0xC0
#define RF_FRFLSB_919_MHZ                           0x00
#define RF_FRFMSB_920_MHZ                           0xE6
#define RF_FRFMID_920_MHZ                           0x00
#define RF_FRFLSB_920_MHZ                           0x00
#define RF_FRFMSB_921_MHZ                           0xE6
#define RF_FRFMID_921_MHZ                           0x40
#define RF_FRFLSB_921_MHZ                           0x00
#define RF_FRFMSB_922_MHZ                           0xE6
#define RF_FRFMID_922_MHZ                           0x80
#define RF_FRFLSB_922_MHZ                           0x00
#define RF_FRFMSB_923_MHZ                           0xE6
#define RF_FRFMID_923_MHZ                           0xC0
#define RF_FRFLSB_923_MHZ                           0x00
#define RF_FRFMSB_924_MHZ                           0xE7
#define RF_FRFMID_924_MHZ                           0x00
#define RF_FRFLSB_924_MHZ                           0x00
#define RF_FRFMSB_925_MHZ                           0xE7
#define RF_FRFMID_925_MHZ                           0x40
#define RF_FRFLSB_925_MHZ                           0x00
#define RF_FRFMSB_926_MHZ                           0xE7
#define RF_FRFMID_926_MHZ                           0x80
#define RF_FRFLSB_926_MHZ                           0x00
#define RF_FRFMSB_927_MHZ                           0xE7
#define RF_FRFMID_927_MHZ                           0xC0
#define RF_FRFLSB_927_MHZ                           0x00
#define RF_FRFMSB_928_MHZ                           0xE8
#define RF_FRFMID_928_MHZ                           0x00
#define RF_FRFLSB_928_MHZ                           0x00

/*!
 * RegPaConfig
 */
#define RF_PACONFIG_PASELECT_MASK                   0x7F
#define RF_PACONFIG_PASELECT_PABOOST                0x80
#define RF_PACONFIG_PASELECT_RFO                    0x00 // Default

#define RF_PACONFIG_MAX_POWER_MASK                  0x8F

#define RF_PACONFIG_OUTPUTPOWER_MASK                0xF0
 
/*!
 * RegPaRamp
 */
#define RF_PARAMP_MODULATIONSHAPING_MASK            0x9F
#define RF_PARAMP_MODULATIONSHAPING_00              0x00 // Default
#define RF_PARAMP_MODULATIONSHAPING_01              0x20
#define RF_PARAMP_MODULATIONSHAPING_10              0x40
#define RF_PARAMP_MODULATIONSHAPING_11              0x60
 
#define RF_PARAMP_TXBANDFORCE_MASK                  0xEF 
#define RF_PARAMP_TXBANDFORCE_BAND_SEL              0x10 
#define RF_PARAMP_TXBANDFORCE_AUTO                  0x00 // Default

#define RF_PARAMP_MASK                              0xF0
#define RF_PARAMP_3400_US                           0x00
#define RF_PARAMP_2000_US                           0x01
#define RF_PARAMP_1000_US                           0x02
#define RF_PARAMP_0500_US                           0x03
#define RF_PARAMP_0250_US                           0x04
#define RF_PARAMP_0125_US                           0x05
#define RF_PARAMP_0100_US                           0x06
#define RF_PARAMP_0062_US                           0x07
#define RF_PARAMP_0050_US                           0x08
#define RF_PARAMP_0040_US                           0x09  // Default
#define RF_PARAMP_0031_US                           0x0A
#define RF_PARAMP_0025_US                           0x0B
#define RF_PARAMP_0020_US                           0x0C
#define RF_PARAMP_0015_US                           0x0D
#define RF_PARAMP_0012_US                           0x0E
#define RF_PARAMP_0010_US                           0x0F

/*!
 * RegOcp
 */
#define RF_OCP_MASK                                 0xDF
#define RF_OCP_ON                                   0x20  // Default
#define RF_OCP_OFF                                  0x00  

#define RF_OCP_TRIM_MASK                            0xE0
#define RF_OCP_TRIM_045_MA                          0x00
#define RF_OCP_TRIM_050_MA                          0x01   
#define RF_OCP_TRIM_055_MA                          0x02 
#define RF_OCP_TRIM_060_MA                          0x03 
#define RF_OCP_TRIM_065_MA                          0x04 
#define RF_OCP_TRIM_070_MA                          0x05 
#define RF_OCP_TRIM_075_MA                          0x06 
#define RF_OCP_TRIM_080_MA                          0x07  
#define RF_OCP_TRIM_085_MA                          0x08
#define RF_OCP_TRIM_090_MA                          0x09 
#define RF_OCP_TRIM_095_MA                          0x0A 
#define RF_OCP_TRIM_100_MA                          0x0B  // Default
#define RF_OCP_TRIM_105_MA                          0x0C 
#define RF_OCP_TRIM_110_MA                          0x0D 
#define RF_OCP_TRIM_115_MA                          0x0E 
#define RF_OCP_TRIM_120_MA                          0x0F 
#define RF_OCP_TRIM_130_MA                          0x10
#define RF_OCP_TRIM_140_MA                          0x11   
#define RF_OCP_TRIM_150_MA                          0x12 
#define RF_OCP_TRIM_160_MA                          0x13 
#define RF_OCP_TRIM_170_MA                          0x14 
#define RF_OCP_TRIM_180_MA                          0x15 
#define RF_OCP_TRIM_190_MA                          0x16 
#define RF_OCP_TRIM_200_MA                          0x17  
#define RF_OCP_TRIM_210_MA                          0x18
#define RF_OCP_TRIM_220_MA                          0x19 
#define RF_OCP_TRIM_230_MA                          0x1A 
#define RF_OCP_TRIM_240_MA                          0x1B

/*!
 * RegLna
 */
#define RF_LNA_GAIN_MASK                            0x1F
#define RF_LNA_GAIN_G1                              0x20  // Default
#define RF_LNA_GAIN_G2                              0x40
#define RF_LNA_GAIN_G3                              0x60
#define RF_LNA_GAIN_G4                              0x80
#define RF_LNA_GAIN_G5                              0xA0
#define RF_LNA_GAIN_G6                              0xC0

#define RF_LNA_BOOST_LF_MASK                        0xE7 
#define RF_LNA_BOOST_LF_DEFAULT                     0x00 // Default
#define RF_LNA_BOOST_LF_GAIN                        0x08 
#define RF_LNA_BOOST_LF_IP3                         0x10 
#define RF_LNA_BOOST_LF_BOOST                       0x18 

#define RF_LNA_RXBANDFORCE_MASK                     0xFB 
#define RF_LNA_RXBANDFORCE_BAND_SEL                 0x04
#define RF_LNA_RXBANDFORCE_AUTO                     0x00 // Default

#define RF_LNA_BOOST_HF_MASK                        0xFC 
#define RF_LNA_BOOST_HF_OFF                         0x00 // Default
#define RF_LNA_BOOST_HF_ON                          0x03 

/*!
 * RegRxConfig
 */
#define RF_RXCONFIG_RESTARTRXONCOLLISION_MASK       0x7F
#define RF_RXCONFIG_RESTARTRXONCOLLISION_ON         0x80
#define RF_RXCONFIG_RESTARTRXONCOLLISION_OFF        0x00 // Default

#define RF_RXCONFIG_RESTARTRXWITHOUTPLLLOCK         0x40 // Write only

#define RF_RXCONFIG_RESTARTRXWITHPLLLOCK            0x20 // Write only

#define RF_RXCONFIG_AFCAUTO_MASK                    0xEF
#define RF_RXCONFIG_AFCAUTO_ON                      0x10
#define RF_RXCONFIG_AFCAUTO_OFF                     0x00 // Default 

#define RF_RXCONFIG_AGCAUTO_MASK                    0xF7
#define RF_RXCONFIG_AGCAUTO_ON                      0x08 // Default
#define RF_RXCONFIG_AGCAUTO_OFF                     0x00

#define RF_RXCONFIG_RXTRIGER_MASK                   0xF8
#define RF_RXCONFIG_RXTRIGER_OFF                    0x00
#define RF_RXCONFIG_RXTRIGER_RSSI                   0x01
#define RF_RXCONFIG_RXTRIGER_PREAMBLEDETECT         0x06 // Default
#define RF_RXCONFIG_RXTRIGER_RSSI_PREAMBLEDETECT    0x07

/*!
 * RegRssiConfig
 */
#define RF_RSSICONFIG_OFFSET_MASK                   0x07
#define RF_RSSICONFIG_OFFSET_P_00_DB                0x00  // Default
#define RF_RSSICONFIG_OFFSET_P_01_DB                0x08
#define RF_RSSICONFIG_OFFSET_P_02_DB                0x10
#define RF_RSSICONFIG_OFFSET_P_03_DB                0x18
#define RF_RSSICONFIG_OFFSET_P_04_DB                0x20
#define RF_RSSICONFIG_OFFSET_P_05_DB                0x28
#define RF_RSSICONFIG_OFFSET_P_06_DB                0x30
#define RF_RSSICONFIG_OFFSET_P_07_DB                0x38
#define RF_RSSICONFIG_OFFSET_P_08_DB                0x40
#define RF_RSSICONFIG_OFFSET_P_09_DB                0x48
#define RF_RSSICONFIG_OFFSET_P_10_DB                0x50
#define RF_RSSICONFIG_OFFSET_P_11_DB                0x58
#define RF_RSSICONFIG_OFFSET_P_12_DB                0x60
#define RF_RSSICONFIG_OFFSET_P_13_DB                0x68
#define RF_RSSICONFIG_OFFSET_P_14_DB                0x70
#define RF_RSSICONFIG_OFFSET_P_15_DB                0x78
#define RF_RSSICONFIG_OFFSET_M_16_DB                0x80
#define RF_RSSICONFIG_OFFSET_M_15_DB                0x88
#define RF_RSSICONFIG_OFFSET_M_14_DB                0x90
#define RF_RSSICONFIG_OFFSET_M_13_DB                0x98
#define RF_RSSICONFIG_OFFSET_M_12_DB                0xA0
#define RF_RSSICONFIG_OFFSET_M_11_DB                0xA8
#define RF_RSSICONFIG_OFFSET_M_10_DB                0xB0
#define RF_RSSICONFIG_OFFSET_M_09_DB                0xB8
#define RF_RSSICONFIG_OFFSET_M_08_DB                0xC0
#define RF_RSSICONFIG_OFFSET_M_07_DB                0xC8
#define RF_RSSICONFIG_OFFSET_M_06_DB                0xD0
#define RF_RSSICONFIG_OFFSET_M_05_DB                0xD8
#define RF_RSSICONFIG_OFFSET_M_04_DB                0xE0
#define RF_RSSICONFIG_OFFSET_M_03_DB                0xE8
#define RF_RSSICONFIG_OFFSET_M_02_DB                0xF0
#define RF_RSSICONFIG_OFFSET_M_01_DB                0xF8

#define RF_RSSICONFIG_SMOOTHING_MASK                0xF8
#define RF_RSSICONFIG_SMOOTHING_2                   0x00
#define RF_RSSICONFIG_SMOOTHING_4                   0x01
#define RF_RSSICONFIG_SMOOTHING_8                   0x02  // Default
#define RF_RSSICONFIG_SMOOTHING_16                  0x03
#define RF_RSSICONFIG_SMOOTHING_32                  0x04
#define RF_RSSICONFIG_SMOOTHING_64                  0x05
#define RF_RSSICONFIG_SMOOTHING_128                 0x06
#define RF_RSSICONFIG_SMOOTHING_256                 0x07

/*!
 * RegRssiCollision
 */
#define RF_RSSICOLISION_THRESHOLD                   0x0A  // Default

/*!
 * RegRssiThresh
 */
#define RF_RSSITHRESH_THRESHOLD                     0xFF  // Default

/*!
 * RegRssiValue (Read Only)
 */

/*!
 * RegRxBw
 */
#define RF_RXBW_MANT_MASK                           0xE7
#define RF_RXBW_MANT_16                             0x00  
#define RF_RXBW_MANT_20                             0x08  
#define RF_RXBW_MANT_24                             0x10  // Default 

#define RF_RXBW_EXP_MASK                            0xF8 
#define RF_RXBW_EXP_0                               0x00 
#define RF_RXBW_EXP_1                               0x01 
#define RF_RXBW_EXP_2                               0x02 
#define RF_RXBW_EXP_3                               0x03 
#define RF_RXBW_EXP_4                               0x04 
#define RF_RXBW_EXP_5                               0x05  // Default
#define RF_RXBW_EXP_6                               0x06  
#define RF_RXBW_EXP_7                               0x07 

/*!
 * RegAfcBw
 */
#define RF_AFCBW_MANTAFC_MASK                       0xE7
#define RF_AFCBW_MANTAFC_16                         0x00
#define RF_AFCBW_MANTAFC_20                         0x08  // Default
#define RF_AFCBW_MANTAFC_24                         0x10  

#define RF_AFCBW_EXPAFC_MASK                        0xF8
#define RF_AFCBW_EXPAFC_0                           0x00 
#define RF_AFCBW_EXPAFC_1                           0x01 
#define RF_AFCBW_EXPAFC_2                           0x02  
#define RF_AFCBW_EXPAFC_3                           0x03  // Default
#define RF_AFCBW_EXPAFC_4                           0x04 
#define RF_AFCBW_EXPAFC_5                           0x05 
#define RF_AFCBW_EXPAFC_6                           0x06  
#define RF_AFCBW_EXPAFC_7                           0x07 

/*!
 * RegOokPeak
 */
#define RF_OOKPEAK_BITSYNC_MASK                     0xDF  // Default
#define RF_OOKPEAK_BITSYNC_ON                       0x20  // Default
#define RF_OOKPEAK_BITSYNC_OFF                      0x00

#define RF_OOKPEAK_OOKTHRESHTYPE_MASK               0xE7
#define RF_OOKPEAK_OOKTHRESHTYPE_FIXED              0x00
#define RF_OOKPEAK_OOKTHRESHTYPE_PEAK               0x08  // Default
#define RF_OOKPEAK_OOKTHRESHTYPE_AVERAGE            0x10

#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_MASK           0xF8
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_0_5_DB         0x00  // Default
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_1_0_DB         0x01
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_1_5_DB         0x02
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_2_0_DB         0x03
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_3_0_DB         0x04
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_4_0_DB         0x05
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_5_0_DB         0x06
#define RF_OOKPEAK_OOKPEAKTHRESHSTEP_6_0_DB         0x07

/*!
 * RegOokFix
 */
#define RF_OOKFIX_OOKFIXEDTHRESHOLD                 0x0C  // Default

/*!
 * RegOokAvg
 */
#define RF_OOKAVG_OOKPEAKTHRESHDEC_MASK             0x1F
#define RF_OOKAVG_OOKPEAKTHRESHDEC_000              0x00  // Default
#define RF_OOKAVG_OOKPEAKTHRESHDEC_001              0x20
#define RF_OOKAVG_OOKPEAKTHRESHDEC_010              0x40
#define RF_OOKAVG_OOKPEAKTHRESHDEC_011              0x60
#define RF_OOKAVG_OOKPEAKTHRESHDEC_100              0x80
#define RF_OOKAVG_OOKPEAKTHRESHDEC_101              0xA0
#define RF_OOKAVG_OOKPEAKTHRESHDEC_110              0xC0
#define RF_OOKAVG_OOKPEAKTHRESHDEC_111              0xE0

#define RF_OOKAVG_AVERAGEOFFSET_MASK                0xF3
#define RF_OOKAVG_AVERAGEOFFSET_0_DB                0x00  // Default
#define RF_OOKAVG_AVERAGEOFFSET_2_DB                0x04
#define RF_OOKAVG_AVERAGEOFFSET_4_DB                0x08
#define RF_OOKAVG_AVERAGEOFFSET_6_DB                0x0C

#define RF_OOKAVG_OOKAVERAGETHRESHFILT_MASK         0xFC
#define RF_OOKAVG_OOKAVERAGETHRESHFILT_00           0x00
#define RF_OOKAVG_OOKAVERAGETHRESHFILT_01           0x01
#define RF_OOKAVG_OOKAVERAGETHRESHFILT_10           0x02  // Default
#define RF_OOKAVG_OOKAVERAGETHRESHFILT_11           0x03

/*!
 * RegAfcFei
 */
#define RF_AFCFEI_AGCSTART                          0x10

#define RF_AFCFEI_AFCCLEAR                          0x02

#define RF_AFCFEI_AFCAUTOCLEAR_MASK                 0xFE
#define RF_AFCFEI_AFCAUTOCLEAR_ON                   0x01
#define RF_AFCFEI_AFCAUTOCLEAR_OFF                  0x00  // Default

/*!
 * RegAfcMsb (Read Only)
 */
 
/*!
 * RegAfcLsb (Read Only)
 */

/*!
 * RegFeiMsb (Read Only)
 */

/*!
 * RegFeiLsb (Read Only)
 */

/*!
 * RegPreambleDetect
 */
#define RF_PREAMBLEDETECT_DETECTOR_MASK             0x7F
#define RF_PREAMBLEDETECT_DETECTOR_ON               0x80  // Default
#define RF_PREAMBLEDETECT_DETECTOR_OFF              0x00

#define RF_PREAMBLEDETECT_DETECTORSIZE_MASK         0x9F
#define RF_PREAMBLEDETECT_DETECTORSIZE_1            0x00
#define RF_PREAMBLEDETECT_DETECTORSIZE_2            0x20  // Default
#define RF_PREAMBLEDETECT_DETECTORSIZE_3            0x40
#define RF_PREAMBLEDETECT_DETECTORSIZE_4            0x60

#define RF_PREAMBLEDETECT_DETECTORTOL_MASK          0xE0
#define RF_PREAMBLEDETECT_DETECTORTOL_0             0x00
#define RF_PREAMBLEDETECT_DETECTORTOL_1             0x01
#define RF_PREAMBLEDETECT_DETECTORTOL_2             0x02
#define RF_PREAMBLEDETECT_DETECTORTOL_3             0x03
#define RF_PREAMBLEDETECT_DETECTORTOL_4             0x04
#define RF_PREAMBLEDETECT_DETECTORTOL_5             0x05
#define RF_PREAMBLEDETECT_DETECTORTOL_6             0x06
#define RF_PREAMBLEDETECT_DETECTORTOL_7             0x07
#define RF_PREAMBLEDETECT_DETECTORTOL_8             0x08
#define RF_PREAMBLEDETECT_DETECTORTOL_9             0x09
#define RF_PREAMBLEDETECT_DETECTORTOL_10            0x0A  // Default
#define RF_PREAMBLEDETECT_DETECTORTOL_11            0x0B
#define RF_PREAMBLEDETECT_DETECTORTOL_12            0x0C
#define RF_PREAMBLEDETECT_DETECTORTOL_13            0x0D
#define RF_PREAMBLEDETECT_DETECTORTOL_14            0x0E
#define RF_PREAMBLEDETECT_DETECTORTOL_15            0x0F
#define RF_PREAMBLEDETECT_DETECTORTOL_16            0x10
#define RF_PREAMBLEDETECT_DETECTORTOL_17            0x11
#define RF_PREAMBLEDETECT_DETECTORTOL_18            0x12
#define RF_PREAMBLEDETECT_DETECTORTOL_19            0x13
#define RF_PREAMBLEDETECT_DETECTORTOL_20            0x14
#define RF_PREAMBLEDETECT_DETECTORTOL_21            0x15
#define RF_PREAMBLEDETECT_DETECTORTOL_22            0x16
#define RF_PREAMBLEDETECT_DETECTORTOL_23            0x17
#define RF_PREAMBLEDETECT_DETECTORTOL_24            0x18
#define RF_PREAMBLEDETECT_DETECTORTOL_25            0x19
#define RF_PREAMBLEDETECT_DETECTORTOL_26            0x1A
#define RF_PREAMBLEDETECT_DETECTORTOL_27            0x1B
#define RF_PREAMBLEDETECT_DETECTORTOL_28            0x1C
#define RF_PREAMBLEDETECT_DETECTORTOL_29            0x1D
#define RF_PREAMBLEDETECT_DETECTORTOL_30            0x1E
#define RF_PREAMBLEDETECT_DETECTORTOL_31            0x1F

/*!
 * RegRxTimeout1
 */
#define RF_RXTIMEOUT1_TIMEOUTRXRSSI                 0x00  // Default

/*!
 * RegRxTimeout2
 */
#define RF_RXTIMEOUT2_TIMEOUTRXPREAMBLE             0x00  // Default

/*!
 * RegRxTimeout3
 */
#define RF_RXTIMEOUT3_TIMEOUTSIGNALSYNC             0x00  // Default

/*!
 * RegRxDelay
 */
#define RF_RXDELAY_INTERPACKETRXDELAY               0x00  // Default

/*!
 * RegOsc
 */
#define RF_OSC_RCCALSTART                           0x08

#define RF_OSC_CLKOUT_MASK                          0xF8
#define RF_OSC_CLKOUT_32_MHZ                        0x00
#define RF_OSC_CLKOUT_16_MHZ                        0x01
#define RF_OSC_CLKOUT_8_MHZ                         0x02
#define RF_OSC_CLKOUT_4_MHZ                         0x03
#define RF_OSC_CLKOUT_2_MHZ                         0x04
#define RF_OSC_CLKOUT_1_MHZ                         0x05  // Default
#define RF_OSC_CLKOUT_RC                            0x06
#define RF_OSC_CLKOUT_OFF                           0x07  

/*!
 * RegPreambleMsb/RegPreambleLsb
 */
#define RF_PREAMBLEMSB_SIZE                         0x00  // Default
#define RF_PREAMBLELSB_SIZE                         0x03  // Default

/*!
 * RegSyncConfig
 */
#define RF_SYNCCONFIG_AUTORESTARTRXMODE_MASK        0x3F
#define RF_SYNCCONFIG_AUTORESTARTRXMODE_WAITPLL_ON  0x80  // Default
#define RF_SYNCCONFIG_AUTORESTARTRXMODE_WAITPLL_OFF 0x40
#define RF_SYNCCONFIG_AUTORESTARTRXMODE_OFF         0x00


#define RF_SYNCCONFIG_PREAMBLEPOLARITY_MASK         0xDF
#define RF_SYNCCONFIG_PREAMBLEPOLARITY_55           0x20
#define RF_SYNCCONFIG_PREAMBLEPOLARITY_AA           0x00  // Default

#define RF_SYNCCONFIG_SYNC_MASK                     0xEF
#define RF_SYNCCONFIG_SYNC_ON                       0x10  // Default
#define RF_SYNCCONFIG_SYNC_OFF                      0x00


#define RF_SYNCCONFIG_SYNCSIZE_MASK                 0xF8
#define RF_SYNCCONFIG_SYNCSIZE_1                    0x00
#define RF_SYNCCONFIG_SYNCSIZE_2                    0x01
#define RF_SYNCCONFIG_SYNCSIZE_3                    0x02  
#define RF_SYNCCONFIG_SYNCSIZE_4                    0x03  // Default
#define RF_SYNCCONFIG_SYNCSIZE_5                    0x04
#define RF_SYNCCONFIG_SYNCSIZE_6                    0x05
#define RF_SYNCCONFIG_SYNCSIZE_7                    0x06
#define RF_SYNCCONFIG_SYNCSIZE_8                    0x07

/*!
 * RegSyncValue1-8
 */
#define RF_SYNCVALUE1_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE2_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE3_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE4_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE5_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE6_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE7_SYNCVALUE                     0x01  // Default
#define RF_SYNCVALUE8_SYNCVALUE                     0x01  // Default

/*!
 * RegPacketConfig1
 */
#define RF_PACKETCONFIG1_PACKETFORMAT_MASK          0x7F
#define RF_PACKETCONFIG1_PACKETFORMAT_FIXED         0x00
#define RF_PACKETCONFIG1_PACKETFORMAT_VARIABLE      0x80  // Default

#define RF_PACKETCONFIG1_DCFREE_MASK                0x9F
#define RF_PACKETCONFIG1_DCFREE_OFF                 0x00  // Default
#define RF_PACKETCONFIG1_DCFREE_MANCHESTER          0x20
#define RF_PACKETCONFIG1_DCFREE_WHITENING           0x40

#define RF_PACKETCONFIG1_CRC_MASK                   0xEF
#define RF_PACKETCONFIG1_CRC_ON                     0x10  // Default
#define RF_PACKETCONFIG1_CRC_OFF                    0x00

#define RF_PACKETCONFIG1_CRCAUTOCLEAR_MASK          0xF7
#define RF_PACKETCONFIG1_CRCAUTOCLEAR_ON            0x00  // Default
#define RF_PACKETCONFIG1_CRCAUTOCLEAR_OFF           0x08

#define RF_PACKETCONFIG1_ADDRSFILTERING_MASK         0xF9
#define RF_PACKETCONFIG1_ADDRSFILTERING_OFF          0x00  // Default
#define RF_PACKETCONFIG1_ADDRSFILTERING_NODE         0x02
#define RF_PACKETCONFIG1_ADDRSFILTERING_NODEBROADCAST 0x04

#define RF_PACKETCONFIG1_CRCWHITENINGTYPE_MASK      0xFE
#define RF_PACKETCONFIG1_CRCWHITENINGTYPE_CCITT     0x00  // Default
#define RF_PACKETCONFIG1_CRCWHITENINGTYPE_IBM       0x01

/*!
 * RegPacketConfig2
 */
 
#define RF_PACKETCONFIG2_WMBUS_CRC_ENABLE_MASK      0x7F 
#define RF_PACKETCONFIG2_WMBUS_CRC_ENABLE           0x80
#define RF_PACKETCONFIG2_WMBUS_CRC_DISABLE          0x00  // Default

#define RF_PACKETCONFIG2_DATAMODE_MASK              0xBF
#define RF_PACKETCONFIG2_DATAMODE_CONTINUOUS        0x00
#define RF_PACKETCONFIG2_DATAMODE_PACKET            0x40  // Default

#define RF_PACKETCONFIG2_IOHOME_MASK                0xDF
#define RF_PACKETCONFIG2_IOHOME_ON                  0x20
#define RF_PACKETCONFIG2_IOHOME_OFF                 0x00  // Default

#define RF_PACKETCONFIG2_BEACON_MASK                0xF7
#define RF_PACKETCONFIG2_BEACON_ON                  0x08
#define RF_PACKETCONFIG2_BEACON_OFF                 0x00  // Default

#define RF_PACKETCONFIG2_PAYLOADLENGTH_MSB_MASK     0xF8

/*!
 * RegPayloadLength
 */
#define RF_PAYLOADLENGTH_LENGTH                     0x40  // Default

/*!
 * RegNodeAdrs
 */
#define RF_NODEADDRESS_ADDRESS                      0x00

/*!
 * RegBroadcastAdrs
 */
#define RF_BROADCASTADDRESS_ADDRESS                 0x00

/*!
 * RegFifoThresh
 */
#define RF_FIFOTHRESH_TXSTARTCONDITION_MASK         0x7F
#define RF_FIFOTHRESH_TXSTARTCONDITION_FIFOTHRESH   0x00  // Default
#define RF_FIFOTHRESH_TXSTARTCONDITION_FIFONOTEMPTY 0x80  

#define RF_FIFOTHRESH_FIFOTHRESHOLD_MASK            0xC0
#define RF_FIFOTHRESH_FIFOTHRESHOLD_THRESHOLD       0x0F  // Default

/*!
 * RegSeqConfig1
 */
#define RF_SEQCONFIG1_SEQUENCER_START               0x80

#define RF_SEQCONFIG1_SEQUENCER_STOP                0x40

#define RF_SEQCONFIG1_IDLEMODE_MASK                 0xDF
#define RF_SEQCONFIG1_IDLEMODE_SLEEP                0x20
#define RF_SEQCONFIG1_IDLEMODE_STANDBY              0x00  // Default

#define RF_SEQCONFIG1_FROMSTART_MASK                0xE7
#define RF_SEQCONFIG1_FROMSTART_TOLPS               0x00  // Default
#define RF_SEQCONFIG1_FROMSTART_TORX                0x08
#define RF_SEQCONFIG1_FROMSTART_TOTX                0x10
#define RF_SEQCONFIG1_FROMSTART_TOTX_ONFIFOLEVEL    0x18

#define RF_SEQCONFIG1_LPS_MASK                      0xFB
#define RF_SEQCONFIG1_LPS_SEQUENCER_OFF             0x00  // Default
#define RF_SEQCONFIG1_LPS_IDLE                      0x04

#define RF_SEQCONFIG1_FROMIDLE_MASK                 0xFD
#define RF_SEQCONFIG1_FROMIDLE_TOTX                 0x00  // Default
#define RF_SEQCONFIG1_FROMIDLE_TORX                 0x02

#define RF_SEQCONFIG1_FROMTX_MASK                   0xFE
#define RF_SEQCONFIG1_FROMTX_TOLPS                  0x00  // Default
#define RF_SEQCONFIG1_FROMTX_TORX                   0x01

/*!
 * RegSeqConfig2
 */
#define RF_SEQCONFIG2_FROMRX_MASK                   0x1F
#define RF_SEQCONFIG2_FROMRX_TOUNUSED_000           0x00  // Default
#define RF_SEQCONFIG2_FROMRX_TORXPKT_ONPLDRDY       0x20
#define RF_SEQCONFIG2_FROMRX_TOLPS_ONPLDRDY         0x40
#define RF_SEQCONFIG2_FROMRX_TORXPKT_ONCRCOK        0x60
#define RF_SEQCONFIG2_FROMRX_TOSEQUENCEROFF_ONRSSI  0x80
#define RF_SEQCONFIG2_FROMRX_TOSEQUENCEROFF_ONSYNC  0xA0
#define RF_SEQCONFIG2_FROMRX_TOSEQUENCEROFF_ONPREAMBLE 0xC0
#define RF_SEQCONFIG2_FROMRX_TOUNUSED_111           0xE0

#define RF_SEQCONFIG2_FROMRXTIMEOUT_MASK            0xE7
#define RF_SEQCONFIG2_FROMRXTIMEOUT_TORXRESTART     0x00  // Default
#define RF_SEQCONFIG2_FROMRXTIMEOUT_TOTX            0x08
#define RF_SEQCONFIG2_FROMRXTIMEOUT_TOLPS           0x10
#define RF_SEQCONFIG2_FROMRXTIMEOUT_TOSEQUENCEROFF  0x18

#define RF_SEQCONFIG2_FROMRXPKT_MASK                0xF8
#define RF_SEQCONFIG2_FROMRXPKT_TOSEQUENCEROFF      0x00  // Default
#define RF_SEQCONFIG2_FROMRXPKT_TOTX_ONFIFOEMPTY    0x01
#define RF_SEQCONFIG2_FROMRXPKT_TOLPS               0x02
#define RF_SEQCONFIG2_FROMRXPKT_TOSYNTHESIZERRX     0x03
#define RF_SEQCONFIG2_FROMRXPKT_TORX                0x04

/*!
 * RegTimerResol
 */
#define RF_TIMERRESOL_TIMER1RESOL_MASK              0xF3
#define RF_TIMERRESOL_TIMER1RESOL_OFF               0x00  // Default
#define RF_TIMERRESOL_TIMER1RESOL_000064_US         0x04
#define RF_TIMERRESOL_TIMER1RESOL_004100_US         0x08
#define RF_TIMERRESOL_TIMER1RESOL_262000_US         0x0C

#define RF_TIMERRESOL_TIMER2RESOL_MASK              0xFC
#define RF_TIMERRESOL_TIMER2RESOL_OFF               0x00  // Default
#define RF_TIMERRESOL_TIMER2RESOL_000064_US         0x01
#define RF_TIMERRESOL_TIMER2RESOL_004100_US         0x02
#define RF_TIMERRESOL_TIMER2RESOL_262000_US         0x03

/*!
 * RegTimer1Coef
 */
#define RF_TIMER1COEF_TIMER1COEFFICIENT             0xF5  // Default

/*!
 * RegTimer2Coef
 */
#define RF_TIMER2COEF_TIMER2COEFFICIENT             0x20  // Default

/*!
 * RegImageCal
 */
#define RF_IMAGECAL_AUTOIMAGECAL_MASK               0x7F
#define RF_IMAGECAL_AUTOIMAGECAL_ON                 0x80
#define RF_IMAGECAL_AUTOIMAGECAL_OFF                0x00  // Default

#define RF_IMAGECAL_IMAGECAL_MASK                   0xBF
#define RF_IMAGECAL_IMAGECAL_START                  0x40

#define RF_IMAGECAL_IMAGECAL_RUNNING                0x20
#define RF_IMAGECAL_IMAGECAL_DONE                   0x00  // Default

#define RF_IMAGECAL_TEMPCHANGE_HIGHER               0x08
#define RF_IMAGECAL_TEMPCHANGE_LOWER                0x00

#define RF_IMAGECAL_TEMPTHRESHOLD_MASK              0xF9
#define RF_IMAGECAL_TEMPTHRESHOLD_05                0x00
#define RF_IMAGECAL_TEMPTHRESHOLD_10                0x02  // Default
#define RF_IMAGECAL_TEMPTHRESHOLD_15                0x04
#define RF_IMAGECAL_TEMPTHRESHOLD_20                0x06

#define RF_IMAGECAL_TEMPMONITOR_MASK                0xFE
#define RF_IMAGECAL_TEMPMONITOR_ON                  0x00 // Default
#define RF_IMAGECAL_TEMPMONITOR_OFF                 0x01

/*!
 * RegTemp (Read Only)
 */

/*!
 * RegLowBat
 */
#define RF_LOWBAT_MASK                              0xF7
#define RF_LOWBAT_ON                                0x08
#define RF_LOWBAT_OFF                               0x00  // Default

#define RF_LOWBAT_TRIM_MASK                         0xF8
#define RF_LOWBAT_TRIM_1695                         0x00
#define RF_LOWBAT_TRIM_1764                         0x01
#define RF_LOWBAT_TRIM_1835                         0x02  // Default
#define RF_LOWBAT_TRIM_1905                         0x03
#define RF_LOWBAT_TRIM_1976                         0x04
#define RF_LOWBAT_TRIM_2045                         0x05
#define RF_LOWBAT_TRIM_2116                         0x06
#define RF_LOWBAT_TRIM_2185                         0x07

/*!
 * RegIrqFlags1
 */
#define RF_IRQFLAGS1_MODEREADY                      0x80

#define RF_IRQFLAGS1_RXREADY                        0x40

#define RF_IRQFLAGS1_TXREADY                        0x20

#define RF_IRQFLAGS1_PLLLOCK                        0x10

#define RF_IRQFLAGS1_RSSI                           0x08

#define RF_IRQFLAGS1_TIMEOUT                        0x04

#define RF_IRQFLAGS1_PREAMBLEDETECT                 0x02

#define RF_IRQFLAGS1_SYNCADDRESSMATCH               0x01

/*!
 * RegIrqFlags2
 */
#define RF_IRQFLAGS2_FIFOFULL                       0x80

#define RF_IRQFLAGS2_FIFOEMPTY                      0x40

#define RF_IRQFLAGS2_FIFOLEVEL                      0x20

#define RF_IRQFLAGS2_FIFOOVERRUN                    0x10

#define RF_IRQFLAGS2_PACKETSENT                     0x08

#define RF_IRQFLAGS2_PAYLOADREADY                   0x04

#define RF_IRQFLAGS2_CRCOK                          0x02

#define RF_IRQFLAGS2_LOWBAT                         0x01

/*!
 * RegDioMapping1
 */
#define RF_DIOMAPPING1_DIO0_MASK                    0x3F
#define RF_DIOMAPPING1_DIO0_00                      0x00  // Default
#define RF_DIOMAPPING1_DIO0_01                      0x40
#define RF_DIOMAPPING1_DIO0_10                      0x80
#define RF_DIOMAPPING1_DIO0_11                      0xC0

#define RF_DIOMAPPING1_DIO1_MASK                    0xCF
#define RF_DIOMAPPING1_DIO1_00                      0x00  // Default
#define RF_DIOMAPPING1_DIO1_01                      0x10
#define RF_DIOMAPPING1_DIO1_10                      0x20
#define RF_DIOMAPPING1_DIO1_11                      0x30

#define RF_DIOMAPPING1_DIO2_MASK                    0xF3
#define RF_DIOMAPPING1_DIO2_00                      0x00  // Default
#define RF_DIOMAPPING1_DIO2_01                      0x04
#define RF_DIOMAPPING1_DIO2_10                      0x08
#define RF_DIOMAPPING1_DIO2_11                      0x0C

#define RF_DIOMAPPING1_DIO3_MASK                    0xFC
#define RF_DIOMAPPING1_DIO3_00                      0x00  // Default
#define RF_DIOMAPPING1_DIO3_01                      0x01
#define RF_DIOMAPPING1_DIO3_10                      0x02
#define RF_DIOMAPPING1_DIO3_11                      0x03

/*!
 * RegDioMapping2
 */
#define RF_DIOMAPPING2_DIO4_MASK                    0x3F
#define RF_DIOMAPPING2_DIO4_00                      0x00  // Default
#define RF_DIOMAPPING2_DIO4_01                      0x40
#define RF_DIOMAPPING2_DIO4_10                      0x80
#define RF_DIOMAPPING2_DIO4_11                      0xC0

#define RF_DIOMAPPING2_DIO5_MASK                    0xCF
#define RF_DIOMAPPING2_DIO5_00                      0x00  // Default
#define RF_DIOMAPPING2_DIO5_01                      0x10
#define RF_DIOMAPPING2_DIO5_10                      0x20
#define RF_DIOMAPPING2_DIO5_11                      0x30

#define RF_DIOMAPPING2_MAP_MASK                     0xFE
#define RF_DIOMAPPING2_MAP_PREAMBLEDETECT           0x01
#define RF_DIOMAPPING2_MAP_RSSI                     0x00  // Default
/*!
 * RegPllHop
 */
#define RF_PLLHOP_FASTHOP_MASK                      0x7F
#define RF_PLLHOP_FASTHOP_ON                        0x80
#define RF_PLLHOP_FASTHOP_OFF                       0x00 // Default

/*!
 * RegTcxo
 */
#define RF_TCXO_TCXOINPUT_MASK                      0xEF
#define RF_TCXO_TCXOINPUT_ON                        0x10
#define RF_TCXO_TCXOINPUT_OFF                       0x00  // Default

/*!
 * RegPaDac
 */
#define RF_PADAC_20DBM_MASK                         0xF8
#define RF_PADAC_20DBM_ON                           0x07
#define RF_PADAC_20DBM_OFF                          0x04  // Default

/*!
 * RegPll
 */
#define RF_PLL_BANDWIDTH_MASK                       0x3F
#define RF_PLL_BANDWIDTH_75                         0x00
#define RF_PLL_BANDWIDTH_150                        0x40
#define RF_PLL_BANDWIDTH_225                        0x80
#define RF_PLL_BANDWIDTH_300                        0xC0  // Default

/*!
 * RegPllLowPn
 */
#define RF_PLLLOWPN_BANDWIDTH_MASK                  0x3F
#define RF_PLLLOWPN_BANDWIDTH_75                    0x00
#define RF_PLLLOWPN_BANDWIDTH_150                   0x40
#define RF_PLLLOWPN_BANDWIDTH_225                   0x80
#define RF_PLLLOWPN_BANDWIDTH_300                   0xC0  // Default

#define MODULE_SX1276RF1IAS                         0
#define MODULE_SX1276RF1JAS                         0
#define MODULE_SX1276RF1KAS                         1

#define DIO0                                        SX1276ReadDio0( )
#define DIO1                                        SX1276ReadDio1( )
#define DIO2                                        SX1276ReadDio2( )
#define DIO3                                        SX1276ReadDio3( )
#define DIO4                                        SX1276ReadDio4( )
#define DIO5                                        SX1276ReadDio5( )
/*!
 * Constant values need to compute the RSSI value
 */
#define RSSI_OFFSET_LF                              -155.0
#define RSSI_OFFSET_HF                              -150.0

#define NOISE_ABSOLUTE_ZERO                         -174.0

#define NOISE_FIGURE_LF                                4.0
#define NOISE_FIGURE_HF                                6.0 


void SX1276Init(void);
void  SX1276StartRx(void);
uint32_t SX1276LoRaProcess(void);
void SX1276SetIdleState(void);
void SX1276GetRxPacket( void *buffer, uint16_t *size );
void SX1276SetTxPacket( const void *buffer, uint16_t size );
void SX1276LoRaSetRFFrequency( uint32_t freq );

#endif //__SX1276_LORA_H__

