	.text
	.file	"handwrite.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	movl	$1, -12(%rsp)
	movl	$1, -16(%rsp)
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	b,@object                       # @b
	.data
	.globl	b
	.p2align	2
b:
	.long	1                               # 0x1
	.size	b, 4

	.type	d,@object                       # @d
	.section	.rodata,"a",@progbits
	.globl	d
	.p2align	2
d:
	.long	1                               # 0x1
	.size	d, 4

	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	2
a:
	.long	0                               # 0x0
	.size	a, 4

	.type	c,@object                       # @c
	.section	.rodata,"a",@progbits
	.globl	c
	.p2align	2
c:
	.long	0                               # 0x0
	.size	c, 4

	.section	".note.GNU-stack","",@progbits
