#include <p24F16KA301.h>
_FOSCSEL(FNOSC_LPRC);

//configure pin for output

void delay(int s) {
    int k = 0;
    while (k < s)
        k++;
}
// Timer1 interrupt service routine
// This function executes every time the micro receives an interrupt
// originating from Timer1. The micro knows the interrupt is from Timer1
// when the Timer1 interrupt flag (T1IF) is set.
void _ISR _T1Interrupt(void)
{
    // Remember to clear the Timer1 interrupt flag when this ISR is entered.
    _T1IF = 0;
    if (_RB1){
        if (PR1 == 7750){
            _RA0 = ~_RA0;
            if (_RA0 == 1){
                PR1 = 3875;
            }
        } else{
            _RB2 = ~_RB2;
            if (_RB2 == 1){
                PR1 = 7750;
            }
        }
    } else{
        _RA0 = 0;
        _RB2 = 0;
    }

    // Place in this ISR whatever code should be executed when the timer
    // reaches the period (PR1) that you specify
    // PLACE CUSTOM CODE HERE

}
int main() {
    //_RCDIV = 0b011; //Postscaler
    // Configure the digital I/O ports
    _TRISA0 = 0;
    _TRISB2 = 0;
    _TRISB1 = 1;
    ANSB = 0;
    ANSA = 0;
    _RA0 = 0;
    _RB2 = 0;

    // Configure Timer1 using T1CON register
    // Remember to enable Timer1, select its prescale value, and set the timer
    // source to the internal clock (FOSC/2)
    _TON = 1;
    _TCS = 0;
    _TCKPS = 0;


    // Configure Timer1 interrupt
    // Remember to enable the Timer1 interrupt source (IEC0 register) and
    // set the Timer1 interrupt priority to 4 (IPC0) register

    _T1IP = 4;
    _T1IE = 1;
    _T1IF = 0;
    PR1 = 7750;

    // Clear Timer1 interrupt flag (IFS0 register)
    // PLACE CODE TO CLEAR THE TIMER1 INTERRUPT FLAG HERE

    // Other initialization stuff
    // PLACE OTHER INITIALIZATION CODE HERE

    // Loop and wait - Note that it's empty because the only time anything is
    // done is when the Timer1 interrupt occurs, sending the code to the ISR
    // (see above) where all the action happens
    while(1);
// Timer
//    _TON = 1;
//    _TCS = 0;
//    _TCKPS = 0b10;
//
//    while (1) {
//        while (_RB1) {
//            TMR1 = 0;
//            _RB2 = ~_RB2;
//            while (TMR1 < 15259);
//            _RB2 = ~_RB2;
//            TMR1 = 0;
//            _RA0 = 1;
//            while (TMR1 < 30518);
//            _RA0 = 0;
//
//        }
//    }
    //Oscillator with postscaling
    //    int delay_time_short = 1302; //(62500/2 = 31250, 31250/6 = 5208.3, 5208.3*.25 = 1302 instruction cycles)
    //    int delay_time_long = 2604;
    //
    //    //create while loop that contains delay
    //    while(1)
    //    {
    //        while(_RB1){
    //            //set delay to equal 0.25 seconds
    //            _RB2 = ~_RB2;
    //            delay(delay_time_short);
    //            _RB2 = ~_RB2;
    //
    //            //set delay time to equal .5 seconds
    //            _RA0 = 1;
    //            delay(delay_time_long);
    //            _RA0 = 0;
    //        }
    //
    //    }

};



