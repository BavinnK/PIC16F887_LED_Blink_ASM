/*
 * File:   gpio.c
 * Author: Bavin
 *
 * Created on March 6, 2026, 2:43 AM
 */


#include <xc.h>
#pragma config LVP = OFF
#pragma config WDTE = OFF  
#pragma config LVP = OFF   
#pragma config FOSC = INTRC_NOCLKOUT 
void main(void) {
    
#asm
  
  BSF STATUS,6
  BSF STATUS,5
 
  CLRF ANSEL
  CLRF ANSELH
  BCF STATUS,6
  BSF TRISB,0
  CLRF TRISD
  BCF STATUS,5
  CLRF 0x20
  CLRF PORTD

  LOOP:
  BTFSC PORTB,0
  GOTO INC_CNTR
  GOTO LOOP

  INC_CNTR:
  INCF 0x20,F
  MOVLW 10
  SUBWF 0x20,W
  BTFSC STATUS,2
  GOTO INC_RESET
  MOVF 0x20,W
  MOVWF PORTD
  
  WAIT:
  BTFSC PORTB,0
  GOTO WAIT
  GOTO LOOP

  INC_RESET:
  CLRF 0x20
  GOTO LOOP
    
#endasm
    
    return;
}
