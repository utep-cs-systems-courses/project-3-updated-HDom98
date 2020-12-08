	.text
	.balign 2
	.data
up:	.byte
	
jt:	.word option0
	.word option1
	.word default

	.text
	

	.extern green_on
	.extern led_update
			
	.global siren_advance
siren_advance:
	cmp #3, r12		;jumping to default if its over 2
	jhs default
	mov jt(r12), r0
option0:			;state 0 siren has a higher pitch, green LED is off 
	mov #1, &green_on		;green_on = 1
	mov #1, &up		;up = 1
	CALL #led_update
	jmp end			;break
option1:			;state 1 siren has a lower pitch, green LED is on
	mov #0, &green_on		;green_on = 0
	mov #0, &up		;up = 0
	CALL #led_update
	jmp end
default:jmp end	
end:	mov &up,r12
	pop r0

	.global dim
dim:	cmp -1, r12		;r12 is the dim mode
	jl dimEnd
	add #1, r12 		;add 1 to the dime mode
dimEnd: pop r0
	
