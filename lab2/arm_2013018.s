fib:
    push {r7, lr}
    sub sp, sp, #8
    add r7, sp, #0
    str r0, [r7, #4]
    ldr r3, [r7, #4]
    cmp r3, #1
    bne .L1
    b .L2

.L1:
    ldr r3, [r7, #4]
    subs r3, r3, #1
    mov r0, r3
    bl fib(PLT)		
    mov r2,r0
    ldr r3, [r7, #4]
    mul r3, r3, r2

.L2:
    mov	r0, r3
	adds r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	fib, .-fib
	.global	main
	.type	main, %function

main:
	push {r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	bl getint(PLT)
	bl fib(PLT)
	bl putint(PLT)
	adds r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	main, .-main
