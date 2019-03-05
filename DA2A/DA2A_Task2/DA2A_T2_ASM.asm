;
; DA2A_Task2_Assembly.asm
;
; Created: 3/4/2019 3:08:27 PM
; Author : perezr1
;

.org 0
;;;;;;;;;;;;;;;;;;;;;;;; Initializing Ports ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ldi r16,0 ; loads 0 in r16
out ddrc, r16 ; will clear 
ldi r16, 0xff ; loads 0xff in r16
out ddrb, r16 ; data direction register b
out portb, r16 ; outputs r16 to portb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Start:	
		sbic	PINC, 2	; If bit of PC2 is high, then it will skip	
		rjmp	Start ; will keep looping until it push buttom is pushed
		rcall	Light_LED_UP ; Call subroutine to light up LED
LED_Done:
		rjmp Start; will go back to read for push button	
;;;;;;;;;;;;;;;; Will Keep LED on for 1.25 seconds;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Light_LED_UP:
		cbi		portb, 2	; pb2 = 0 ==> its ON
		ldi		R20, 5; Prescalar 1024
		sts		TCCR1B, R20 ; Set timer
		ldi		R20, 0	; set timer to zero
		sts		TCNT1H, R20	; sets upper byte to zero
		sts		TCNT1L, R20 ; sets lower byte to zero
		rjmp	Delay_Low	; subroute for delay
;;;;;;;;;;;;;;;;;;;;;;;;;;; Delay Starts here;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Delay_Low:
		lds		R29, TCNT1H		; load upper bytes of timer counter to r29
		lds		R28, TCNT1L 	; load lower bytes of timer counter to r28
		cpi		R28, 0x4A		; check to see if lower 8 bits of timer counter is 0x4A
		brsh	Delay_High      ; if lower 8 bits of timer counter is 0x4A than jumps to label
		rjmp	Delay_Low		; otherwise keep checking lower bytes
Delay_High:	
		cpi		R29, 0x4C		; check if upper timer counter have reached desired value
		brlt	Delay_Low		; otherwise recheck the lower bytes
		sbi		portb, 2		; TURN OFF LED
		ret						; returns back from subroutine
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
