.ORG 0;location for reset
JMP Lets_Begin
.ORG 0x02;location for external interrupt 0
JMP EX0_ISR ; jumps to interrupt label
Lets_Begin:
LDI R20,HIGH(RAMEND)
OUT SPH,R20; initialize upper stack
LDI R20,LOW(RAMEND)
OUT SPL,R20; initialize lower stack
LDI R20,0x02;make INT0 falling edge triggered
STS EICRA,R20
SBI DDRB,2;PORTB.2 = output

SBI PORTD,2;pull-up activated
LDI R20,1<<INT0;enable INT0
OUT EIMSK,R20
SEI;enable interrupts
LETS_WAIT:
	JMP LETS_WAIT

EX0_ISR:
	IN R21,PORTB ; readas PORTB
;;;;;;;;;;;;;;;;;; Toggles The LED;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LDI R22,(1<<2)|(1<<5) ; 
	EOR R21,R22
	OUT PORTB,R21
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rcall Delay; will go to subroutine 
;;;;;;;;;;;;;;;;;; Toggles The LED;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LDI R22,(1<<2)|(1<<5)
	EOR R21,R22
	OUT PORTB,R21
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	RETI

;;;;;;;;;;; will delay the duration of the LED being on ;;;;;;;;;;;;;
Delay:
	ldi r20, 123
	nop
	nop
	nop
	nop
	nop
D1:
	ldi r21, 250
	nop
	nop
	nop
	D2:
	ldi r22, 107
	nop
	nop
Del_LP:
	nop
	nop
	nop
	dec  r22
    brne Del_lp
	nop
	nop
    dec  r21
    brne D2
	nop
    dec  r20
    brne D1	
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;