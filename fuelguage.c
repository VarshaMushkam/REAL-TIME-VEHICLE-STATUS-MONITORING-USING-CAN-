#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "adc.h"
#include "adc_defines.h"
#include "types.h"
#include "interrupt.h"
#include "can.h"
#include "can_defines.h"
//Define the minimum and maximum voltage levels from the sensor
#define MINI 0.49
#define MAX 2.72
//Define the channel
#define CHNO 1
//Declare variable for ADC,eAR, and Fuel percentage
u32 adcDVal;
f32 eAR;
u32 percentage;

main(){
	      //Declare a CAN frame structure for transmission
        struct CAN_Frame txFrame;
	      // Initialise CAN1 interface and ADC(Analog to Digital Converter)
        Init_CAN1();
        Init_ADC();
	      //set up the CAN Fraame ID, Data Length Code(DLC) and Remote Transmission Request(RTR)
        txFrame.ID=55;
        txFrame.vbf.RTR=0;
        txFrame.vbf.DLC=1;
        while(1){
					      // Read ADC value from Channel and calculate the corresponding voltage
                Read_ADC(CHNO,&adcDVal,&eAR);
					      // Calculate the fuel percentage based on the eAR voltage
                percentage = ((eAR-MINI)/(MAX-MINI))*100;
					      // Introduce a delay of 500 milliseconds
                delay_ms(500);
					      //Assigning the fuel percentage to the CAN data frame
                txFrame.Data1=percentage;
                txFrame.Data2=0;
					      //To Transmit the CAN frame
                CAN1_Tx(txFrame);
					      //Invert the fuel percentage value for the next transmission
                txFrame.Data1=((~txFrame.Data1)&0x0);
        }
}
