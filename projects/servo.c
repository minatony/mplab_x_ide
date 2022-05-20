/*
 * File:   servo.c
 * Author: hoang
 *
 * Created on March 23, 2022, 9:43 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 16000000
#include <xc.h>
#include <stdint.h>
#include <pic16f877a.h>
void servo1(uint8_t);
void main(void) {
    TRISDbits.TRISD4 = 0;
    PORTDbits.RD4 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    // cau hinh timer0
    PORTBbits.RB1 = 1;
    PORTBbits.RB2 = 1;
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;// bo chia 2
    OPTION_REGbits.PSA = 0;// bo chia dung cho timer0
    OPTION_REGbits.T0CS = 0;// nguon xung clock ben trong
    TMR0 = 235;
    while(1){
        for(unsigned char i = 100; i < 198; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo1(i);
            }
        }
        for(unsigned char i = 198; i > 100; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo1(i);
            }
        }
    }
    return;
}
void servo1(uint8_t duty0){
    for(uint16_t count0 = 0; count0 < 2000; count0++){
        if(count0 < duty0){
            PORTDbits.RD4 = 1;
        }
        else{
            PORTDbits.RD4 = 0;
        }
        while(!INTCONbits.TMR0IF);
        INTCONbits.TMR0IF = 0;
        TMR0 = 235;
    }
}
