	.file	1 "arrayglobal.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls

	#this is all that happens with global arrays.......
	.comm	a,20,4


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
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	lw	$2,%got(a)($28)
	li	$3,1			# 0x1
	sw	$3,0($2)
	lw	$2,%got(a)($28)
	li	$3,2			# 0x2
	sw	$3,4($2)
	lw	$2,%got(a)($28)
	li	$3,3			# 0x3
	sw	$3,8($2)
	lw	$2,%got(a)($28)
	li	$3,4			# 0x4
	sw	$3,12($2)
	lw	$2,%got(a)($28)
	li	$3,5			# 0x5
	sw	$3,16($2)
	lw	$2,%got(a)($28)
	nop
	lw	$3,0($2)
	lw	$2,%got(a)($28)
	nop
	lw	$2,4($2)
	nop
	addu	$3,$3,$2
	lw	$2,%got(a)($28)
	nop
	lw	$2,8($2)
	nop
	addu	$3,$3,$2
	lw	$2,%got(a)($28)
	nop
	lw	$2,12($2)
	nop
	addu	$3,$3,$2
	lw	$2,%got(a)($28)
	nop
	lw	$2,16($2)
	nop
	addu	$2,$3,$2
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
