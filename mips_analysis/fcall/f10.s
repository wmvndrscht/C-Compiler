	.file	1 "f10.c"
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
	sw	$4,8($fp)
	sw	$5,12($fp)
	sw	$6,16($fp)
	sw	$7,20($fp)
	lw	$3,8($fp)
	lw	$2,12($fp)
	nop
	addu	$3,$3,$2
	lw	$2,16($fp)
	nop
	addu	$3,$3,$2
	lw	$2,20($fp)
	nop
	addu	$3,$3,$2
	lw	$2,24($fp)
	nop
	addu	$3,$3,$2
	lw	$2,28($fp)
	nop
	addu	$3,$3,$2
	lw	$2,32($fp)
	nop
	addu	$3,$3,$2
	lw	$2,36($fp)
	nop
	addu	$3,$3,$2
	lw	$2,40($fp)
	nop
	addu	$3,$3,$2
	lw	$2,44($fp)
	nop
	addu	$2,$3,$2
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
	.frame	$fp,56,$31		# vars= 0, regs= 2/0, args= 40, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	move	$fp,$sp
	li	$2,10			# 0xa
	sw	$2,36($sp)
	li	$2,9			# 0x9
	sw	$2,32($sp)
	li	$2,8			# 0x8
	sw	$2,28($sp)
	li	$2,7			# 0x7
	sw	$2,24($sp)
	li	$2,6			# 0x6
	sw	$2,20($sp)
	li	$2,5			# 0x5
	sw	$2,16($sp)
	li	$7,4			# 0x4
	li	$6,3			# 0x3
	li	$5,2			# 0x2
	li	$4,1			# 0x1
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	addiu	$sp,$sp,56
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
