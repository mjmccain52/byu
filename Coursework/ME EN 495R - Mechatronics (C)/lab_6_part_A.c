//Include Header File
#include <p24F16KA301.h>

//Select Oscillator
_FOSCSEL(FNOSC_FRC);//8MHz oscillator

void config_ad(void)
{
    // AD1CHS register
    _CH0NA = 0;         // AD1CHS<7:5> -- Use VDD as negative input
    _CH0SA = 1;         // AD1CHS<4:0> -- Use AN1 as positive input
    //_CH0NB = 0;         // AD2CHS -- Use VDD as negative input
    //_CH0SB = 0b01111;   //AN15 is positive input

    // AD1CON1 register
    _ADON = 1;          // AD1CON1<15> -- Turn on A/D
    _ADSIDL = 0;        // AD1CON1<13> -- A/D continues while in idle mode
    _MODE12 = 1;        // AD1CON1<10> -- 12-bit A/D operation
    _FORM = 0;          // AD1CON1<9:8> -- Unsigned integer output
    _SSRC = 7;          // AD1CON1<7:4> -- Auto conversion (internal counter)
    _ASAM = 1;          // AD1CON1<2> -- Auto sampling

    // AD1CSSL register
    _CSS1 = 1;          //AN1
    //_CSS15 = 1;         //AN15

    // AD1CON2 register
    _PVCFG = 0;         // AD1CON2<15:14> -- Use VDD as positive ref voltage
    _NVCFG = 0;         // AD1CON2<13> -- Use VSS as negative ref voltage
    _CSCNA = 1;         // AD1CON2<10> -- Does not scan inputs specified in
                        // AD1CSSx registers (instead uses channels specified
                        // by CH0SA bits in AD1CHS register) -- Selecting '0'
                        // here probably makes writing to the AD1CSSL register
                        // unnecessary.
    _ALTS = 0;          // AD1CON2<0> -- Sample MUXA only
    _BUFREGEN = 1;      //Sets buffer to corresponding active channels
    _SMPI = 1;          //Sets the interrupt select bits to every other (2 channels now)

    // AD1CON3 register
    _ADRC = 0;          // AD1CON3<15> -- Use system clock
    _SAMC = 0;          // AD1CON3<12:8> -- Auto sample every A/D period TAD
    _ADCS = 0x3F;       // AD1CON3<7:0> -- A/D period TAD = 64*TCY
}

//Main Function
int main()
{
    //Configure timer 2
    T2CONbits.TON = 1; //Turn timer on
    T2CONbits.TCKPS = 1; //no prescaler
    T2CONbits.T32 = 0; //This choice does not combine timer 2 with timer 3
    T2CONbits.TCS = 0; //internal clock

    //Configure PWM
    OC1CON1bits.OCTSEL = 0; //Timer select to timer 2
    OC1CON1bits.OCM = 6; //Edge-aligned PWM mode on OCX
    OC1CON2bits.SYNCSEL = 0b01100; //Set to timer 2

    //OC2CON1bits.OCTSEL = 0; //Timer select to timer 2
    //OC2CON1bits.OCM = 6; //Edge-aligned PWM mode on OCX
    //OC2CON2bits.SYNCSEL = 0b01100; //Set to timer 2

    //Select period and duty cycle
    PR2 = 9999; //

    // Configure pins
    _TRISA1 = 1;
    //_TRISB4 = 1;
    _ANSA1 = 1;
    //_ANSB15 = 1;


    // Configure A/D
    config_ad();
    OC1R = 5000;
    // Loop
    while(1)
    {
        // Read from the A/D buffer and do something useful with it. The A/D
        // buffer is being updated continuously behind the scenes.
        // WRITE CODE TO DO SOMETHING INTERESTING WITH THE VALUE IN THE
        // A/D BUFFER HERE
        if (ADC1BUF1 > 2048){
            T2CONbits.TON = 0;
        } else {
            T2CONbits.TON = 1;
            //450+ADC1BUF1/6;// set duty cycle to a/d converted signal
        //OC2R = ADC1BUF15;
        }
    }

    return 0;
}
