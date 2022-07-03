/*
 * File:   spi_slave.c
 * Author: hoang
 *
 * Created on January 24, 2022, 10:17 PM
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

void main(void) {
    // THIET LAP SPI CHO SLAVE
    SSPCONbits.SSPEN = 1;// cho phep giao tiep noi tiep mssp
    SSPCONbits.CKP = 0;// trang thai nghi o muc thap
    SSPCONbits.SSPM = 0b0101;// che do slave, cham SS khong dung
    SSPSTATbits.SMP = 0;// phai duoc xoa
    SSPSTATbits.CKE = 0;// truyen khi tu trang thai nghi sang trang thai hoat dong
    // thiet lap io cho slave
    TRISCbits.TRISC3 = 1;// sck input
    TRISCbits.TRISC4 = 1;// sdi input
    TRISCbits.TRISC5 = 0;// sdo output
    while(SSPCONbits.SSPOV){
        SSPCONbits.SSPOV = 0;
    }
    while(!SSPSTATbits.BF);
    if((SSPSTATbits.BF)&&(SSPBUF == 'a')){
        TRISDbits.TRISD0 = 0;
        PORTDbits.RD0 = 1;
    }
    return;
}
