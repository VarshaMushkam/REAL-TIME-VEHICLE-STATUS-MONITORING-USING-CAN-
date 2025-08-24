//i2c.h
#include "types.h"
void init_i2c(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
void i2c_write(u8);
u8 i2c_nack(void);
u8 i2c_mack(void);
void i2c_device_write(u8 , u8 , u8);
u8 i2c_device_read(u8 , u8 );
void init_MMA7660(void);
u8 read_MMA7660(u8 );
