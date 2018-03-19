	.file	1 "f2.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls


	#start f
	.text
	.align	2
	.globl	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	sw	$5,12($fp)
	lw	$3,8($fp)
	lw	$2,12($fp)
	nop
	addu	$2,$3,$2
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	#normal funtion up until this point

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro

	#allocate 32 for stack when there is only 2 parameters called
	addiu	$sp,$sp,-32
	#store the return address in 4 below the stackpointer
	sw	$31,28($sp)
	#store the framepointer 8 below the stackpointer
	sw	$fp,24($sp)
	#set fp = sp
	move	$fp,$sp

	#load function arguments into registers
	li	$5,4			# 0x4
	li	$4,2			# 0x2
	.option	pic0
	#jal to function call
	jal	f
	nop

	.option	pic2

	#
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32


	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
