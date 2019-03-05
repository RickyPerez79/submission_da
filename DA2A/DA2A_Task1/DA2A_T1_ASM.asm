;
; DA2A_1_Assembly.asm
;
; Created: 3/4/2019 6:28:10 PM
; Author : perezr1
;
.org	0x00
 ;;;;;;;;;;;;;;;;;;;;;;;;Initialize Port & TCCR1B ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ldi r16, 0x24	;setting pd2 & pd5
out DDRB, r16	; enableing pd2 & pd5 as output
ldi r16, 0x04	; loads 4 in r16
ldi r17, 0x20	; used to set/reset pd2 & pd5
ldi r20, 0x05   ; prescalar 1024
sts TCCR1B,	r20 ; setting up TCCR1B = 00000101 for 1024 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LetsBegin:
	Ldi r20, 0	; setting up timer counter to 0

;;;;;;;;;Timer Counter needs two registers since its a 16 bit ;;;;;;;;;;;;;;;;;;;;;;;;

	sts	TCNT1H, r20 	; high byte of the TCNT
	sts	TCNT1L, r20 	; low byte of the TNCT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rjmp delay_on_low 	; will check the low byte of the TCNT for the 60% DC
ImBack:
	eor r17, r16	; xor to toggle LED
	out PORTB, r17	; enable pd2 & pd5

	ldi r20, 0; ; setting up timer counter back to 0 to check for the 40% DC that it is off
	sts TCNT1H, r20 ; high byte of the TNCT
	sts TCNT1L, r20 ; low byte of the TNCT

	rjmp	delay_off_low 	; will check the low byte of the TCNT for the 40% DC
ImBackAgain:
	eor r17, r16	; xor to toggle LED
	out PORTB, r17	; enable pd2 & pd5

	rjmp	LetsBegin	; repeats all over again

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	delay_off_low:
	lds r29, TCNT1H	; load upper bytes of timer counter to r29
	lds r28, TCNT1L ; load lower bytes of timer counter to r28

	cpi r28, 0xB2	; check to see if lower 8 bits of timer counter is 0x12
	brsh delay_off_high ; if lower 8 bits of timer counter is 0x12 then jump label
	rjmp	delay_off_low ; otherwise keep checking lower bytes

delay_off_high:
	cpi r29, 0x11	; check if upper timer counter is 0x4F
	brlt delay_off_low; otherwise recheck the lower bytes
	rjmp ImBackAgain	; finished checking 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_on_low:
	lds	r29, TCNT1H	; load upper bytes of timer counter to r29
	lds	r28, TCNT1L 	; load lower bytes of timer counter to r28

	cpi	r28, 0x8C	; check to see if lower 8 bits of timer counter are 0x08
	brsh delay_on_high
	rjmp delay_on_low		; otherwise keep checking lower bytes

delay_on_high:
	cpi	r29, 0x1A	; check if upper timer counter have reached desired value
	brlt delay_on_low		; otherwise recheck the lower bytes
	rjmp ImBack
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
