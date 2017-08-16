/* I can't seem to get plib.h stuff to work properly with chipKIT stuff unfortunately */
/*Possible explanation: http://chipkit.net/forum/viewtopic.php?t=2790 -Majenko response */





//#include <plib.h>
#include <peripheral/system.h>
#include <peripheral/timer.h>
/* This example assumes the CPU Core is operating at 80MHz
Note that Core Timer operates at FSYS/2 */
/* set the configuration fuse bits in software */
#pragma config FNOSC = FRCPLL, FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1, POSCMOD = OFF
#pragma config FWDTEN = OFF
#define FOSC 80000000
#define TICKS_PER_SEC 4
#define CORE_TICK_RATE (FOSC/2/TICKS_PER_SEC)
int main(void)
{

   Serial.print("Program init\n");
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STEP 1. configure the core timer
OpenCoreTimer(CORE_TICK_RATE);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STEP 2. set core timer interrupt level = 2
mConfigIntCoreTimer(CT_INT_ON | CT_INT_PRIOR_2);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STEP 3. enable multi-vector interrupts
INTEnableSystemMultiVectoredInt();
while(1)
{
//... do something useful here ...
};
}
void __ISR(_CORE_TIMER_VECTOR, ipl2) _CoreTimerHandler(void)
{
  // clear the interrupt flag
  mCTClearIntFlag();
  // update the period
  UpdateCoreTimer(CORE_TICK_RATE);

  Serial.print("Interrupt\n");
}
