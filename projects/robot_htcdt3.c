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
#include <stdlib.h>
#include <pic16f877a.h>
void work(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void gap(unsigned char, unsigned char, unsigned char, unsigned char);
void servo1(unsigned char);
void servo2(unsigned char);
void servo3(unsigned char);
void servo4(unsigned char);
void delayms(unsigned int);
void __interrupt() ISR_RB(void){
    if(INTCONbits.RBIF){
        if(PORTBbits.RB4){
            PORTBbits.RB1 = 1;
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
            
            for(unsigned int a = 0; a < 60000; a++){
                TMR2IF = 0;
                TMR2 = 0;
                T2CONbits.TMR2ON = 1;// cho phep timer2 hoat dong
                while(TMR2IF == 0);
            }
        
            CCP1CONbits.CCP1M = 0b0000;
            CCP2CONbits.CCP2M = 0b0000;
            T2CONbits.TMR2ON = 0;
            PIR1bits.TMR2IF = 0;
            PORTBbits.RB1 = 0;
            PORTCbits.RC1 = 0;
            PORTDbits.RD0 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
        }
        if(PORTBbits.RB5){
            for(unsigned char i = 0; i < 10; i++){
                servo1(150);// goc lam viec 1 ban dau
                servo2(120);// goc lam viec 2 ban dau
                servo3(165);// goc lam viec 3 ban dau
            }
            // goc cuoi, goc dau, thoi gian delay
            work(180, 120, 165, 150, 120, 165, 31);// servo 1 quay
            work(180, 140, 145, 180, 120, 165, 20);//servo 2 di xuong, servo3 di xuong
            gap(140, 170, 140, 145);
            work(180, 120, 165, 180, 140, 145, 20);// servo2 di len, servo3 di len
            work(110, 120, 165, 180, 120, 165, 71);// servo1 quay
            work(110, 140, 145, 110, 120, 165, 20);// servo2 di xuong, servo3 ha xuong
            gap(170, 140, 140, 145);
            work(150, 120, 165, 110, 140, 145, 41);// quay ve vi tri ban dau
        }
        INTCONbits.RBIF = 0;// xoa co ngat
    }
    return;
}
void main(void) {
    
    // led
    
    TRISBbits.TRISB1 = 0;
    PORTBbits.RB1 = 0;
    TRISBbits.TRISB2 = 0;
    PORTBbits.RB2 = 0;
    
    // servo
    
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    PORTDbits.RD7 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD4 = 0;
    
    // ngat portb
    
    TRISBbits.TRISB1 = 0;
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    
    // TIMER0
    
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;// bo chia 2
    OPTION_REGbits.PSA = 0;// bo chia dung cho timer0
    OPTION_REGbits.T0CS = 0;// nguon xung clock ben trong
    TMR0 = 235;
    
    // thiet lap ngo ra
    
    TRISCbits.TRISC2 = 0;
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC3 = 0;
    PORTCbits.RC3 = 0;
    
    while(1){
    }
    return;
}
void work(unsigned char angle1, unsigned char angle2, unsigned char angle3, unsigned char angl1, unsigned char angl2, unsigned char angl3, unsigned char dl){
    for(unsigned char i = 0; i < dl; i++){
        // servo1
        if(angle1 == angl1){
            servo1(angl1);
        }
        else if(angle1 < angl1){
            for(unsigned char j = 0; j < 3; j++){
                servo1(angl1);
            }
            angl1--;
        }
        else{
            for(unsigned char j = 0; j < 3; j++){
                servo1(angl1);
            }
            angl1++;
        }
        // servo2
        if(angle2 == angl2){
            servo2(angl2);
        }
        else if(angle2 < angl2){
            for(unsigned char j = 0; j < 3; j++){
                servo2(angl2);
            }
            angl2--;
        }
        else{
            for(unsigned char j = 0; j < 3; j++){
                servo2(angl2);
            }
            angl2++;
        }
        // servo3
        if(angle3 == angl3){
            servo3(angl3);
        }
        else if(angle3 < angl3){
            for(unsigned char j = 0; j < 3; j++){
                servo3(angl3);
            }
            angl3--;
        }
        else{
            for(unsigned char j = 0; j < 3; j++){
                servo3(angl3);
            }
            angl3++;
        }
    }
}
void gap(unsigned char glv4c, unsigned char glv4m, unsigned char glv2, unsigned char glv3){
    if(glv4c < glv4m){
        for(unsigned char a = glv4c; a < glv4m; a++){
            for(unsigned char b = 0; b < 3; b++){
                servo4(a);
            }
            servo2(glv2);
            servo3(glv3);
        }
    }
    else{
        for(unsigned char a = glv4c; a > glv4m; a--){
            for(unsigned char b = 0; b < 3; b++){
                servo4(a);
            }
            servo2(glv2);
            servo3(glv3);
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
