#include "types.h"
#include "delay.h"
void delay_us(u32 dlyUS)
{
//XTAL = 12mhz,cclk =60mhz;
    dlyUS*=12;
    while(dlyUS--);
}
void delay_ms(u32 dlyMS){
//XTAL = 12mhz,cclk =60mhz;
    dlyMS*=12000;
    while(dlyMS--);
}
void delay_s(u32 dlyS){
//XTAL = 12mhz,cclk =60mhz;
    dlyS*=12000000;
    while(dlyS--);
}
