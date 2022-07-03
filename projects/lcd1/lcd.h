/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

void Lcd_Port(char a){
    if(a & 1){// 1 = 0000 0001
        D4 = 1;
    }
    else{
        D4 = 0;
    }
    if(a & 2){// 2 = 0000 0010
        D5 = 1;
    }
    else{
        D5 = 0;
    }
    if(a & 4){// 4 = 0000 0100
        D6 = 1;
    }
    else{
        D6 = 0;
    }
    if(a & 8){// 8 = 0000 1000
        D7 = 1;
    }
    else{
        D7 = 0;
    }
}
void Lcd_Cmd(char a){// truyen 4 bit
    RS = 0;
    Lcd_Port(a);
    E = 1;
    __delay_us(50);
    E = 0;
}
void Lcd_Clear(){
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}
void Lcd_Gotoxy(unsigned char x, unsigned char y){
    if(y == 1){
        Lcd_Cmd(((0x80 + x - 1) & 0xF0) >> 4);// truyen 4 bit cao
        Lcd_Cmd((0x80 + x - 1) & 0x0F);// truyen 4 bit thap
    }
    if(y == 2){
        Lcd_Cmd(((0xC0 + x - 1) & 0xF0) >> 4);// truyen 4 bit cao
        Lcd_Cmd((0xC0 + x - 1) & 0x0F);// truyen 4 bit thap
    }
}
void Lcd_Init(){
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(1);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}
void Lcd_Char(char a){// tung ki tu
    RS = 1;
    Lcd_Port((a & 0xF0) >> 4);
    E = 1;
    __delay_us(50);
    E = 0;
    Lcd_Port(a & 0x0F);
    E = 1;
    __delay_us(50);
    E = 0;
}
void Lcd_String(char *a){// chuoi ki tu
    for(unsigned int i = 0; a[i] != '\0'; i++){
        Lcd_Char(a[i]);
    }
}
