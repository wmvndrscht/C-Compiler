	.file	1 "gb.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls

	##start global variable = 5
	.globl	a
	.data
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

	#a = 2;
	#start by loading upper half of a into 2
	lui	$2,%hi(a)
	#load 2 into $3
	li	$3,2			# 0x2
	#store $3 into low of a
	sw	$3,%lo(a)($2)


	#return a 
	lui	$2,%hi(a)
	lw	$2,%lo(a)($2)
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
