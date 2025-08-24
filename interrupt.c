//interrupt.c
#include"types.h"
#include"interrupt_defines.h"
#include"interrupt.h"
#include<lpc21xx.h>
void Enable_EINT0(void)
{
 PINSEL0|=PINSEL0&~(3<<2)|(3<<2);
 VICIntEnable=1<<EINT0_VIC_CHNO;
 VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
 VICVectAddr0=(u32)eint0_isr;
 EXTMODE=1<<0;
 //EXTPOLAR=0<<1;
 }
 void Enable_EINT1(void)
{
 PINSEL0|=PINSEL0&~(3<<28)|(2<<28);
 VICIntEnable=1<<EINT1_VIC_CHNO;
 VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;
 VICVectAddr1=(u32)eint1_isr;
 EXTMODE=1<<1;
 //EXTPOLAR=0<<1;

 }
