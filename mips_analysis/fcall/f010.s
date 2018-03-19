	.file	1 "f010.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
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
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	li	$2,2			# 0x2
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

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
	.frame	$fp,40,$31		# vars= 0, regs= 4/0, args= 16, gp= 8
	.mask	0xc0030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	move	$fp,$sp
	.option	pic0
	jal	f
	nop

	.option	pic2
	sll	$16,$2,1
	.option	pic0
	jal	f
	nop

	.option	pic2
	mult	$16,$2
	mflo	$2
	addiu	$16,$2,6
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$17,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$2,$17,$2
	subu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	sll	$2,$2,1
	addu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$16,$16,$2
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$2,$16,$2
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
