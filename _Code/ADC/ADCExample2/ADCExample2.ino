/******************************************************************
 * This program Demonstrates the operation of the Analog to Digital converter
 * operating in Alternate AutoSample mode.
 *
 * The Hardware setup consist of a PIC32 pim on an Explorer16 board
 * Analog input 4 (the temperature sensor) and Analog input 5 (the pot) are converted
 * The ADC Alternate mode is used to automatically sample the
 * 2 channels without CPU intervention. The most current results can be
 * read from the channel4 and channel5 variables
 *
 *
 ********************************************************************/
// Master header file for all peripheral library includes
//#include <plib.h>
#include "adc10.h"

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz (80MHz / 1)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT off 
// Other options are don't care
//

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FPBDIV = DIV_1
#pragma config POSCMOD = HS, FNOSC = PRIPLL 
#pragma config FWDTEN = OFF

#define SYS_FREQ (80000000L)

unsigned int channel4;  // conversion result as read from result buffer
unsigned int channel5;  // conversion result as read from result buffer
unsigned int offset;  // buffer offset to point to the base of the idle buffer

int main(void)
{
  // Configure the device for maximum performance but do not change the PBDIV
  // Given the options, this function will change the flash wait states and
  // enable prefetch cache but will not change the PBDIV. The PBDIV value
  // is already set via the pragma FPBDIV option above..
 // SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

  // configure and enable the ADC
  CloseADC10(); // ensure the ADC is off before setting the configuration

  // define setup parameters for OpenADC10
  //        Turn module on | ouput in integer | trigger mode auto | enable autosample
  #define PARAM1  ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

  // define setup parameters for OpenADC10
  //        ADC ref external    | disable offset test    | disable scan mode | perform 2 samples | use dual buffers | use alternate mode
  #define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON

  // define setup parameters for OpenADC10
  //          use ADC internal clock | set sample time
  #define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15


  // define setup parameters for OpenADC10
  //               set AN4 and AN5 as analog inputs
  #define PARAM4  ENABLE_AN4_ANA | ENABLE_AN5_ANA


  // define setup parameters for OpenADC10
  // do not assign channels to scan
  #define PARAM5  SKIP_SCAN_ALL
  
  // use ground as neg ref for A | use AN4 for input A      |  use ground as neg ref for A | use AN5 for input B

  // configure to sample AN4 & AN5
  SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 |  ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN5); // configure to sample AN4 & AN5
  OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above

  EnableADC10(); // Enable the ADC

  while (1)
  {
    while ( ! mAD1GetIntFlag() ) 
        { 
            // wait for the first conversion to complete so there will be vaild data in ADC result registers
        }
  
    // the results of the conversions are available in channel4 and channel5

    offset = 8 * ((~ReadActiveBufferADC10() & 0x01));  // determine which buffer is idle and create an offset
    
    channel4 = ReadADC10(offset);     // read the result of channel 4 conversion from the idle buffer
    channel5 = ReadADC10(offset + 1);   // read the result of channel 5 conversion from the idle buffer
    
    mAD1ClearIntFlag();
  }

  return 0;
}


