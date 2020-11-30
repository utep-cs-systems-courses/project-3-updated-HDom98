.text
	.balign 2
	.text
	
jt:	.word option0
	.word option1
	.word default
	
	.text
	

	.extern up
up:	.byte
	.global sum
	.global siren_advance
siren_advance:
	cmp #3, &up		;jumping to default if its over 2
	jhs default
	mov #0, r12		; state = 0
	mov jt(r12), r0
option0:
	mov #0, &red_on		;red_on = 0
	mov #1, &up		;up = 1
	add #1, r12		;state++
	CALL #led_update
	jmp end			;break
option1:	
	mov #1, &red_on		;red_on = 1
	mov #0, &up		;up = 0
	mov #0, r12		;state = 0
	CALL #led_update
	jmp end
default:jmp end
end:	pop r0

sum:
	sub #2, r1
	mov #-5,2(r1) 		;i = -5
loop:	
	cmp #0,2(r1)		;if i >= 0
	jge endL
	add #1,r12		;sum++
	add #1,2(r1)		;i++
	jmp loop
	
endL:	mov 2(r1), r12
	add #2, r1
	pop r0
	
