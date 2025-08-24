#include<lpc21xx.h>
#include "types.h"
#include "can.h"
#include "can_defines.h"
#include "delay.h"
#include "interrupt.h"
#include "interrupt_defines.h"
#include "pin_connect_block_defines.h"
#include "pin_connect_block.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "i2c.h"
#include "i2c_defines.h"

#define MMA7660 0x4C
#define rled 1<<16
#define gled 1<<17
#define FUEL 1
#define FUEL_BAR 0
#define THS +19
#define NTHS -19


u32 flag;
s32 i;
u32 current=0;
void eint0_isr(void) __irq;
void eint1_isr(void) __irq ;
u8 cgramLUT[]={0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
               0x1f,0x11,0x11,0x1f,0x1f,0x1f,0x1f,0x1f};

main()
{
        u32 percentage,i;
        signed char x,y,z;
        struct CAN_Frame rxFrame,txFrame;
        IODIR1 = rled|gled;
        //cfg p0.16 as EINT0 input pin
        CfgPortPinFunc(0,1,EINT0_INPUT_PIN);
        //cfg p0.3 as EINT1 input pin
        CfgPortPinFunc(0,7,EINT1_INPUT_PIN);

    VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO;
    VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
    VICVectAddr0=(u32 )eint0_isr;

    VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;
    VICVectAddr1=(u32 )eint1_isr;

        EXTMODE=1<<1|1<<0;
        //IODIR0|=1<<EINT0_STATUS_LED|1<<EINT1_STATUS_LED;

        InitLCD();
//      StrLCD("v");
//      delay_ms(1000);
        Init_CAN1();
        init_i2c();
        i2c_device_write(MMA7660,0x07,0x01);
        delay_ms(100);
        //IODIR1 = rled|gled;
        init_MMA7660();
        BuildCGRAM(cgramLUT,16);
        /*CharLCD(1);
        for(i=0;i<5;i++){
              CmdLCD(GOTO_LINE1_POS0+(2+i));
                  CharLCD(0);
        }*/
        while(1)
                {
                x = read_MMA7660(0x00);
                y = read_MMA7660(0X01);
                z = read_MMA7660(0X02);

                if(((x>THS||y>THS||z>THS)||(x<(NTHS)||y<(NTHS)||z<(NTHS))))
                {
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("AIRBAGS OPEN    ");
                }
                else
                {

                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("SAFE            ");
                        
                }
                if(((C1GSR>>RBS_BIT_READ)&1))
                {
                     //      if(((C1GSR>>0)&1)){
                        CAN1_Rx(&rxFrame);
                        if(rxFrame.ID == 50 && rxFrame.vbf.DLC==1)
                        {
                                percentage = rxFrame.Data1;
                                //BuildCGRAM(cgramLUT,16);
                                CmdLCD(GOTO_LINE1_POS0);
                                CharLCD(FUEL);
                                for(i=2;i<7;i++)
                                {
                                        CmdLCD(GOTO_LINE1_POS0+i);
                                        CharLCD(FUEL_BAR);
                                }

                                if(percentage>0 && percentage<=20)
                                                {
                                        CmdLCD(GOTO_LINE1_POS0+3);
                                        StrLCD("    ");
                                }
                                else if(percentage>20 && percentage<=40)
                                                                {
                                        CmdLCD(GOTO_LINE1_POS0+4);
                                        StrLCD("   ");
                                }
                                else if(percentage>40 && percentage<=60)
                                                                {
                                        CmdLCD(GOTO_LINE1_POS0+5);
                                        StrLCD("  ");
                                }
                                else if(percentage>60 && percentage<=80)
                                                                {
                                        CmdLCD(GOTO_LINE1_POS0+6);
                                        StrLCD(" ");
                                }
                                else if(percentage>80 && percentage<=100)
                                                                {
                                        CmdLCD(GOTO_LINE1_POS0+2);
                                                                //charLCD(FUEL_BAR);
                                 }
                                 else if(percentage>100)
                                 {
                                    percentage = 100;
                                    CmdLCD(GOTO_LINE1_POS0+2);
                                  }
                                   else
                                   {
                                      CmdLCD(GOTO_LINE1_POS0+2);
                                      StrLCD("     ");
                                    }

                                    CmdLCD(GOTO_LINE1_POS0 + 8);
                                    StrLCD("    ");
                                    CmdLCD(GOTO_LINE1_POS0 + 8);
                                    U32LCD(percentage);
                                    CharLCD(0x25);
													}
												}

                                

												txFrame.ID = 55;
												if(flag!=0)
												{
																if(flag==current)
																{
																		txFrame.Data1='X';
																		txFrame.vbf.DLC=1;
																		CAN1_Tx(txFrame);
																		current=0;
																}
																else
																{

																			if(flag==1)
																			{
																					txFrame.Data1='L';
																			}
																			else if(flag==2)
																			{
																					txFrame.Data1='R';
																			}
																			CAN1_Tx(txFrame);
																			current=flag;
																	}
																}
																flag=0;

        }
}
								
void eint0_isr(void) __irq
{
        flag = 1;
        //clear EINT0 status flag in Ext Int Peripheral
        EXTINT=1<<0;
        //clear EINT0 status in VIC Peripheral
        VICVectAddr=0;

}

void eint1_isr(void) __irq
{
        flag=2;
        //clear EINT1 status flag in Ext Int Peripheral
        EXTINT=1<<1;
        //clear EINT1 status in VIC Peripheral
        VICVectAddr=0;
}
