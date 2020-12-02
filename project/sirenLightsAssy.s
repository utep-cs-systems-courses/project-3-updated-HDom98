.file 	"siren_advance.c"
	.text
	.balign 2
	.text
	
jt:	.word option0
	.word option1
	.word default

	.text
	

	.extern up
	.extern led_update
up:	.byte
	.global siren_advance
siren_advance:
	cmp #3, &up		;jumping to default if its over 2
	jge default
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

	.global dim
dim:	cmp -1, r12		;r12 is the dim mode
	jl dimEnd
	add #1, r12 		;add 1 to the dime mode
dimEnd: pop r0
	
