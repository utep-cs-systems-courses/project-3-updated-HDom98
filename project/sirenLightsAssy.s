.text
	.balign 2
	.text
	
jt:	.word option0
	.word option1
	.word default
	
	.text
	

	.extern up
up:	.byte
	.global siren_advance
siren_advance:
	cmp #3, &up
	jhs default

	mov #0, r12		; state = 0
	mov jt(r12), r0
option0:
	mov #0, &red_on		;red_on = 0
	CALL #led_update
	mov #1, &up		;up = 0
	add #1, r12		;state++
	jmp end			;break
option1:	
	mov #1, &red_on		;red_on = 1
	CALL #led_update
	mov #0, &up		;up = 0
	mov #0, r12		;state = 0
default:
	jmp end
end:	pop r0
