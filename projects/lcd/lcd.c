/*
 * File:   main.c
 * Author: hoang
 *
 * Created on January 30, 2022, 8:04 PM
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
#include"lcd.h"
void main(void) {
    TRISD = 0x00;
    TRISC = 0X00;
    RC6 = 0;
    Lcd_Init();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("chao 2022");
    __delay_ms(2000);
    while(1);
    return;
}
