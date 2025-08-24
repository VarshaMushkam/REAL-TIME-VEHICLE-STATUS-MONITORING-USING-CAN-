//i2c_defines.h
#include "adc_defines.h"
//define pin functions
#define FUNC2 1
#define SCL_PIN_0_2   FUNC2
#define SDA_PIN_0_3   FUNC2

//defines for I2C_SPEED Configuration
#define I2C_SPEED 100000    //Hz
#define BITRATE   ((PCLK/I2C_SPEED)/2)

//bit defines for I2CONSET sfr
#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6

//bit defines for I2CONCLR sfr
#define   AAC_BIT 2
#define   SIC_BIT 3
#define  STAC_BIT 5
#define I2ENC_BIT 6

#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr
