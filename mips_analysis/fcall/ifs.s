	.file	1 "ifs.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	function
	.set	nomips16
	.set	nomicromips
	.ent	function
	.type	function, @function
function:
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
	slt	$2,$3,$2
	beq	$2,$0,$L2
	nop



	lw	$2,8($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,8($fp)
	lw	$3,8($fp)
	lw	$2,12($fp)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$L3
	nop

	lw	$2,12($fp)
	nop
	addiu	$2,$2,3
	sw	$2,12($fp)
	lw	$3,8($fp)
	lw	$2,12($fp)
	nop
	bne	$3,$2,$L3
	nop

	lw	$3,8($fp)
	lw	$2,12($fp)
	nop
	mult	$3,$2
	mflo	$2
	b	$L4
	nop

$L3:
	lw	$2,12($fp)
	b	$L4
	nop

$L2:
	li	$2,13			# 0xd
$L4:
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	function
	.size	function, .-function
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	sw	$16,28($sp)
	move	$fp,$sp
	move	$5,$0
	move	$4,$0
	.option	pic0
	jal	function
	nop

	.option	pic2
	move	$16,$2
	li	$5,2			# 0x2
	li	$4,1			# 0x1
	.option	pic0
	jal	function
	nop

	.option	pic2
	addu	$16,$16,$2
	li	$5,3			# 0x3
	li	$4,4			# 0x4
	.option	pic0
	jal	function
	nop

	.option	pic2
	addu	$16,$16,$2
	li	$5,7			# 0x7
	li	$4,6			# 0x6
	.option	pic0
	jal	function
	nop

	.option	pic2
	addu	$2,$16,$2
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$16,28($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
