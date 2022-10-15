	.text
	.file	"Test.c"
	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	2
a:
	.long	0                               # 0x0
	.size	a, 4

	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
