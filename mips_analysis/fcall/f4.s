	.file	1 "f4.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls

	#starting f function
	.text
	.align	2
	.globl	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp) #store fp stack-4
	move	$fp,$sp

	sw	$4,16($fp) #get variables into r4,5,6,7
	sw	$5,20($fp)
	sw	$6,24($fp)
	sw	$7,28($fp)

	lw	$3,16($fp) #do the addition
	lw	$2,20($fp)
	nop
	addu	$3,$3,$2
	lw	$2,24($fp)
	nop
	addu	$3,$3,$2
	lw	$2,28($fp)
	nop
	addu	$2,$3,$2 #result in $2

	sw	$2,4($fp)
	lw	$2,4($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16 
	j	$31
	nop


	#start main function
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

	#allocate 32
	addiu	$sp,$sp,-32
	sw	$31,28($sp) #store return address stack size-4
	sw	$fp,24($sp) #store framepointer stacksize-8
	move	$fp,$sp
	li	$7,4			# 0x4
	li	$6,3			# 0x3
	li	$5,2			# 0x2
	li	$4,1			# 0x1
	.option	pic0
	jal	f
	nop

	.option	pic2
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
