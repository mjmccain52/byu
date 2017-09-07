#include <p24F16KA301.h>

double ROSS_MESSAGE = 0.0;

_FOSCSEL(FNOSC_FRC);

void _ISR _INT0Interrupt(void)
{
    _INT0IF = 0;

    if(_RA0){
        ROSS_MESSAGE += 360/256.0;
    }
    else{
        ROSS_MESSAGE -= 360/256.0;
    }
    if (ROSS_MESSAGE < 0){
        ROSS_MESSAGE += 360;
    } else if (ROSS_MESSAGE > 360){
        ROSS_MESSAGE -= 360;
    }

}
int main() {
    _TRISA0 = 1;//configured to input
    _TRISA1 = 1;//configured to input
    ANSA = 0;//set analog to off
    _RA0 = 0;//set RA0 pin to 0

    _INT0IP = 4;//interrupt priority set to 4
    _INT0IE = 1;//Enables INT0 pin
    _INT0IF = 0;//Set flag
    _INT0EP = 0;//Set Edge detection to positive edge (goes to positive)

    T2CONbits.TON = 1; //Turn timer on
    T2CONbits.TCKPS = 1; //no prescaler
    T2CONbits.T32 = 0; //This choice does not combine timer 2 with timer 3
    T2CONbits.TCS = 0; //internal clock

    OC1CON1bits.OCTSEL = 0; //Timer select to timer 2
    OC1CON1bits.OCM = 6; //Edge-aligned PWM mode on OCX
    OC1CON2bits.SYNCSEL = 0b01100; //Set to timer 2

    PR2 = 9999; //
    
    while(1){
        OC1R = (ROSS_MESSAGE/360)*PR2;
    }

    return 0;
}