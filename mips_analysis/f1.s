	.file	1 "f1.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	li	$2,10			# 0xa
	sw	$2,0($fp)
	li	$2,12			# 0xc
	sw	$2,4($fp)
	li	$2,14			# 0xe
	sw	$2,8($fp)
	sw	$0,12($fp)
	lw	$3,0($fp)
	lw	$2,4($fp)
	mul	$3,$3,$2
	lw	$2,8($fp)
	mul	$3,$3,$2
	lw	$2,12($fp)
	mul	$2,$3,$2
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
