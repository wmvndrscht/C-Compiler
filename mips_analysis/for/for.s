	.file	1 "forloop.c"
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
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	li	$2,2			# 0x2
	sw	$2,4($fp)
	
#start for loop

	#stat1

	sw	$0,4($fp)
	b	$L2
	nop


$L3:
	#body
	lw	$2,4($fp)
	nop
	addiu	$2,$2,2
	sw	$2,4($fp)

	#stat3
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sw	$2,4($fp)


$L2:
	#stat2
	lw	$2,4($fp) #load in 
	nop
	slt	$2,$2,10	#

	#loop condition
	bne	$2,$0,$L3
	nop

	lw	$2,4($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
