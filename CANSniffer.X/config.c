#include "config.h"

void initPins(void) {
    // All pins as output
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    
    // All pins low
    LATA = 0;
    LATB = 0;
    LATC = 0;
    
    // Disable analog inputs and ADC
    ADCON1bits.PCFG = 0b1111;
    ADCON0bits.ADON = 0;
    
    // Disable PORTB pullups
    INTCON2bits.RBPU = 1;
}

void initInterrupt(void) {
    // Disable interrupts
    INTCONbits.GIE = 0;
}