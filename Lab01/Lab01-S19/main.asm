; Created: 2/8/2019 5:40:30 PM
; Author : perezr1

.org 0x0000

start:
	ldi r16, 0	   ; holds a zero
	ldi r17, 0	   ; will hold a copy of the multiplier
	ldi r18, 0	   ; register for the product
	ldi r19, 0     ; register for the product
	ldi r20, 0     ; register for the product
	ldi r22, 0x05  ; multiplier
	ldi r24, 0x0D  ; low byte of the multiplicand
	ldi r25, 0x0A  ; high byte of the multiplicand 
	mov r17, r22   ; makes a copy of r22
	cpse r17, r16  ; if r17 equals zero then it will skip the next instruction
	jmp addlp      ; if r17 doesn't equal to zero then it will go to this instruction
	
	; condition for this loop is that it will keep looping the amount of times the multipier is set.
	jmp done ; will jump to the done label
	; loop to add both the low and high bytes
	addlp:
	add r18, r24   ; adds the low byte of the multiplicand into the register that holds the product
	adc r19, r25   ; will add (if there is a) carry to the next product register
	adc r20, r16   ; will add (if there is a) carry to the next product register
	dec r17        ; decrements the multiplier every time it loops
	brne addLp     ; will keep looping until the multiplier is zero
	; finished program 
	done:
		BREAK
