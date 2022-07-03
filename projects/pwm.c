/*
 * File:   pwm.c
 * Author: hoang
 *
 * Created on May 18, 2022, 10:26 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <pic16f877a.h>

void main(void) {
    // thiet lap ngo ra
    TRISCbits.TRISC2 = 0;
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC3 = 0;
    PORTCbits.RC3 = 0;
    // thiet lap che do pwm
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;
    CCP2CONbits.CCP2M3 = 1;
    CCP2CONbits.CCP2M2 = 1;
    // thiet lap timer2
    T2CONbits.T2CKPS1 = 1;// bo chia truoc 16
    PR2 = 25;
    CCPR1L = 10;
    CCPR2L = 10;
    while(1){
        TMR2IF = 0;
        TMR2 = 0;
        T2CONbits.TMR2ON = 1;// cho phep timer2 hoat dong
        while(TMR2IF == 0);
    }
    return;
}
