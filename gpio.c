/*
 * File:   gpio.c
 * Author: Bavin
 *
 * Created on March 6, 2026, 2:43 AM
 */
#include <xc.h>
#pragma config LVP = OFF
#pragma config WDTE = OFF  
#pragma config FOSC = INTRC_NOCLKOUT 
void main(void) {
    
#asm
    MAIN_INIT:
    BCF STATUS,6
    BCF STATUS,5        ;BANK0
    CLRF TMR0           ;clear the counter
    
    BSF STATUS,5        ;BANK1
    BCF OPTION_REG,5    ;we will use internal osc which is 4Mhz
    BCF OPTION_REG,3    ;the pcs is assigned to timer0 itself not the watchdog
    BSF OPTION_REG,0
    BSF OPTION_REG,1
    BSF OPTION_REG,2    ;now the pcs is 256 now each tick takes 256 us
   
    BCF TRISD,4         ;make RD4 as output, its a buildin led on my custom board
    BCF STATUS,5        ;BANK0
    CLRF 0x21
    
    MAIN_LOOP:
    BTFSC INTCON,2
    CALL DISPLAY
    GOTO MAIN_LOOP
   
    DISPLAY:
    BCF INTCON,2
    INCF 0x21,F
    MOVLW 15
    SUBWF 0x21,W
    BTFSC STATUS,2
    CALL INC_LOGIC
    RETURN
            
    INC_LOGIC:
    CLRF 0x21
    MOVLW 0b00010000
    XORWF PORTD,F
    RETURN        
#endasm
    return;
}
