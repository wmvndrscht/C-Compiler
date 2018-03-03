	.file	1 "f.c"
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
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8    #allocate 8 bytes on the stack
	sw	$fp,4($sp)    #store previous frame pointer
	move	$fp,$sp       #create new frame pointer
	move	$2,$0         #move 0 into register 2 for return val
	move	$sp,$fp       # get back base stack-pointer
	lw	$fp,4($sp)    # load the old frame-pointer
	addiu	$sp,$sp,8     #release 8 bytes from the stack
	j	$31           #return
	nop

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
