/*
 * File:   robot.c
 * Author: hoang
 *
 * Created on May 7, 2022, 4:49 PM
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
#include <pic16f877a.h>
void work(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void servo1(unsigned char);
void servo2(unsigned char);
void servo3(unsigned char);
void servo4(unsigned char);
void delayms(unsigned int);
unsigned char glv1 = 149;
unsigned char glv2 = 135;
unsigned char glv3 = 155;
void main(void) {
    // led
    TRISBbits.TRISB1 = 0;
    PORTBbits.RB1 = 1;
    // servo
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    PORTDbits.RD7 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD4 = 0;
    // TIMER0
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;// bo chia 2
    OPTION_REGbits.PSA = 0;// bo chia dung cho timer0
    OPTION_REGbits.T0CS = 0;// nguon xung clock ben trong
    TMR0 = 235;
    
    while(1){
        for(unsigned char i = 0; i < 5; i++){
            servo1(glv1);// glv1 = 149
            servo2(glv2);// glv2 = 135
            servo3(glv3);// glv3 = 155
        }
        for(unsigned char i = 149; i < 180; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo1(i);
            }
        }
        for(unsigned char i = 135; i < 145; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo2(i);
            }
        }
        for(unsigned char i = 155; i > 130; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo3(i);
            }
        }
        delayms(5000);
        for(unsigned char i = 130; i < 155; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo3(i);
            }
        }
        for(unsigned char i = 145; i > 135; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo2(i);
            }
        }
        for(unsigned char i = 180; i > 110; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo1(i);
            }
        }
        for(unsigned char i = 135; i < 145; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo2(i);
            }
        }
        for(unsigned char i = 155; i > 130; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo3(i);
            }
        }
        delayms(5000);
        for(unsigned char i = 130; i < 155; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo3(i);
            }
        }
        for(unsigned char i = 145; i > 135; i--){
            for(unsigned char j = 0; j < 3; j++){
                servo2(i);
            }
        }
        for(unsigned char i = 110; i < 149; i++){
            for(unsigned char j = 0; j < 3; j++){
                servo1(i);
            }
        }
        while(1);
    }
    return;
}
void work(unsigned char angle1, unsigned char angle2, unsigned char angle3, unsigned char angl1, unsigned char angl2, unsigned char angl3){
    for(unsigned char i = 0; i < 250; i++){
        // servo1
        if(angle1 == angl1){
            servo1(angl1);
        }
        else if(angle1 < angl1){
            angl1--;
            for(unsigned char j = 0; j < 15; j++){
                servo1(angl1);
            }
        }
        else{
            angl1++;
            for(unsigned char j = 0; j <15; j++){
                servo1(angl1);
            }
        }
        // servo2
        if(angle2 == angl2){
            servo2(angl2);
        }
        else if(angle2 < angl2){
            angl2--;
            for(unsigned char j = 0; j < 15; j++){
                servo2(angl2);
            }
        }
        else{
            angl2++;
            for(unsigned char j = 0; j <15; j++){
                servo2(angl2);
            }
        }
        // servo3
        if(angle3 == angl3){
            servo3(angl3);
        }
        else if(angle3 < angl3){
            angl3--;
            for(unsigned char j = 0; j < 15; j++){
                servo3(angl3);
            }
        }
        else{
            angl3++;
            for(unsigned char j = 0; j <15; j++){
                servo3(angl3);
            }
        }
    }
}
void servo1(unsigned char duty){
    for(unsigned int count = 0; count < 2000; count++){
        if(count < duty){
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
void servo2(unsigned char duty){
    for(unsigned int count = 0; count < 2000; count++){
        if(count < duty){
            PORTDbits.RD5 = 1;
        }
        else{
            PORTDbits.RD5 = 0;
        }
        while(!INTCONbits.TMR0IF);
        INTCONbits.TMR0IF = 0;
        TMR0 = 235;
    }
}
void servo3(unsigned char duty){
    for(unsigned int count = 0; count < 2000; count++){
        if(count < duty){
            PORTDbits.RD6 = 1;
        }
        else{
            PORTDbits.RD6 = 0;
        }
        while(!INTCONbits.TMR0IF);
        INTCONbits.TMR0IF = 0;
        TMR0 = 235;
    }
}
void servo4(unsigned char duty){
    for(unsigned int count = 0; count < 2000; count++){
        if(count < duty){
            PORTDbits.RD7 = 1;
        }
        else{
            PORTDbits.RD7 = 0;
        }
        while(!INTCONbits.TMR0IF);
        INTCONbits.TMR0IF = 0;
        TMR0 = 235;
    }
}

 void delayms(unsigned int ms){
    for(unsigned int  msa = 0; msa < ms; msa ++){
        for(unsigned char msb = 0; msb < 10; msb++){
            while(!INTCONbits.TMR0IF);
            INTCONbits.TMR0IF = 0;
            TMR0 = 55;
        }
    }
}
