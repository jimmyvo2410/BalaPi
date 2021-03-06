#include "BalaPi_BoardConf.h"

// addresses of the device
// #define MS561101BA_ADDR_CSB_HIGH  0x76   //CBR=1 0x76 I2C address when CSB is connected to HIGH (VCC)
#define MS561101BA_ADDR_CSB_HIGH  0xEC   //CBR=1 0x76<<1 I2C address when CSB is connected to HIGH (VCC)
// #define MS561101BA_ADDR_CSB_LOW   0x77   //CBR=0 0x77 I2C address when CSB is connected to LOW (GND)
#define MS561101BA_ADDR_CSB_LOW   0xEE   //CBR=0 0x77<<1 I2C address when CSB is connected to LOW (GND)

// registers of the device
#define MS561101BA_D1 0x40
#define MS561101BA_D2 0x50
#define MS561101BA_RESET 0x1E

// D1 and D2 result size (bytes)
#define MS561101BA_D1D2_SIZE 3

// OSR (Over Sampling Ratio) constants
#define MS561101BA_OSR_256 0x00
#define MS561101BA_OSR_512 0x02
#define MS561101BA_OSR_1024 0x04
#define MS561101BA_OSR_2048 0x06
#define MS561101BA_OSR_4096 0x08

#define MS561101BA_PROM_BASE_ADDR 0xA2 // by adding ints from 0 to 6 we can read all the prom configuration values. 
// C1 will be at 0xA2 and all the subsequent are multiples of 2
#define MS561101BA_PROM_REG_COUNT 6 // number of registers in the PROM
#define MS561101BA_PROM_REG_SIZE 2 // size in bytes of a prom registry.

typedef enum 
{
    MS561101BA_STATUS_SUCCESS 						= 2,
    MS561101BA_STATUS_FAIL		 						= 3,
    MS561101BA_STATUS_TIMEOUT 						=	4,
}MS561101BA_Status;


typedef enum
{
    MS561101BA_STATUS_START_CONVERT = 0x01,
    MS561101BA_STATUS_CONVERTING,
    MS561101BA_STATUS_CONVERT_FINISH,
    MS561101BA_STATUS_CONVERT_FAIL
}MS561101BA_Status_Convert;

typedef enum
{
    MS561101BA_CONVERT_TEMPERATURE = 0x01,
    MS561101BA_CONVERT_PRESSURE,
    MS561101BA_CALCULATE
}MS561101BA_Convert_Object;

extern MS561101BA_Convert_Object g_MS561101BA_convert;

MS561101BA_Status MS561101BA_ResetChip(void);
MS561101BA_Status MS561101BA_ReadPROM(uint8_t *buffer);
MS561101BA_Status MS561101BA_StartConversion(uint8_t command);
MS561101BA_Status MS561101BA_SetConversion(uint8_t *buffer);



MS561101BA_Status_Convert  MS561101BA_RawTemperature(uint8_t OSR,uint8_t *buffer);
MS561101BA_Status_Convert  MS561101BA_RawPressure(uint8_t OSR,uint8_t *buffer);

void MS561101BA_process(void);
MS561101BA_Status_Convert MS561101BA_GgetData(void);
