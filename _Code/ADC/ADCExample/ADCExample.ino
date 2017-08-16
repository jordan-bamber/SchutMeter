void setup() {
  // put your setup code here, to run once:

  #include "p32mx795f512l.h"                  //include header file
  //#include "plib.h"
  #include "adc10.h"
  
  unsigned int channel4;// conversion result as read from result buffer
  unsigned int channel5;// conversion result as read from result buffer
  unsigned int offset; // points to the base of the idle buffer

  // configure and enable the ADC
  CloseADC10();// ensure the ADC is off before setting the configuration
  // define setup parameters for OpenADC10
  #define PARAM1 ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO |
  ADC_AUTO_SAMPLING_ON
  #define PARAM2 ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF
  | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON
  #define PARAM3 ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_12
  #define PARAM4SKIP_SCAN_ALL
  #define PARAM5ENABLE_AN4_ANA | ENABLE_AN5_ANA
  // configure to sample AN4 & AN5
  SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 |
  ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN5);
  // configure ADC and enable it
  OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 );
  // Now enable the ADC logic
  EnableADC10();
  // the results of the conversions are available in channel4 and channel5
}

void loop()
{
    // determine which buffer is idle and create an offset
    offset = 8 * ((~ReadActiveBufferADC10() & 0x01));
    // read the result of channel 4 conversion in the idle buffer
    channel4 = ReadADC10(offset);
    // read the result of channel 5 conversion in the idle buffer
    channel5 = ReadADC10(offset + 1);
 
}
