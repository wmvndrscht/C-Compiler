	.file	1 "global2.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls

	#start b
	.globl	b
	.data
	.align	2
	.type	b, @object
	.size	b, 4
b:
	.word	5

	#start a
	.globl	a
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.word	5

#start function
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	lui	$2,%hi(a)
	lw	$3,%lo(a)($2)
	lui	$2,%hi(b)
	lw	$2,%lo(b)($2)
	nop
	addu	$2,$3,$2
	addiu	$2,$2,5
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
