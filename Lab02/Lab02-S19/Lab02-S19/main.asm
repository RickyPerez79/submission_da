;
; Lab02-S19.asm
; DA1B.asm
;
; Created: 2/20/2019 5:26:27 PM
; Author : perezr1
;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Initializing Registers/Variables ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.equ STARTADDS = 0x0200 			; STARTADDS will have the starting address
.equ count = 99						; count will begin at 99. This is the max numbers we will be storing
.equ begin_val = 11 				; begin_val will begin at 11. This is greater than 10
.org 0 								; program will begin at address 0

clr r20 							; clears r20
ldi XL, low(STARTADDS)				; stores lower byte address in XL
ldi XH, high(STARTADDS)				; stores high byte address XH
ldi YL, low(0x400)					; stores lower byte address YL
ldi YH, high(0x400)					; stores high byte address YH
ldi ZL, low(0x600)					; stores lower byte address ZL
ldi ZH, high(0x600)					; stores high byte address ZH

ldi r20, 3   						; r20 will have 3. will be used to compare if it is divisible by 3
ldi r21, count 						; r21 will have the value in count
ldi r22, begin_val					; r22 will have the value in begin_val

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; clear registers ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

clr r0
clr r16
clr r17
clr r18
clr r19

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;; Will store begin_val to X register address ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

start:
mov r3, r22				; copies the value in r22 into r3
st X+, r22				; stores the of r22 into the address of X. Afterwords X increments its address by 1.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;; Will check if the value is divisible by 3 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

divide_by_three:
cp r22, r20				; Will compare r22 and r20. 
brlo notDiv				; if the value in r22 is lower than 3 then it will go to the notDiv label
sub r22, r20			; if r22 is not lower than 3 ==> r22 = r22-3
cp r22, r20				; will compare again to see if it equals to zero.
breq isDiv 				; if it does equal to zero then it is divisible by 3 and will go to the isDiv label

rjmp divide_by_three	; if it doesnt equal to zero then it will repeat this label to see if its divisible by 3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Is divisible by 3 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

isDiv:
st Y+, r3 			; will store r3 in Y address and then Y will increment to the next address
add r16, r3 		; will add r3 to the lower byte of the sum register(r16) of the numbers that are divisable by 3
adc r17, r0 		; if there is a carry it will be added to the high byte of the sum register(r17) that are divisable by 3
rjmp done_adding    ; will jump to the done_adding label

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; if the value is not divisible by 3 will go to this label;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

notDiv:
st Z+, r3				; stores the of r3 into the address of Z. Afterwords Z increments its address by 1.
add r18, r3				; will add r3 to the lower byte of the sum register(r18) of the numbers that are not divisable by 3 
adc r19, r0				;if there is a carry it will be added to the high byte of the sum register(r17) that are not divisable by 3
rjmp done_adding		; will jump to the done_adding label

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Will go here once done adding ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

done_adding:
mov r22, r3		; reinitialize the value that was in r22 
inc r22			; increments r22 by 1
cp r21, r0 		; will check if the count is zero
breq Done		; if r21 equals zero then it will go to the Done label
dec r21			; will decrement r21 by 1
brne start 		; if r21 doesnt equal to zero then go to the start label 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; The Program has finished running ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Done: 
BREAK

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

