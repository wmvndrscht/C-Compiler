	.file	1 "arraylocal.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,56,$31		# vars= 24, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	lw	$2,%got(__stack_chk_guard)($28)
	nop
	lw	$2,0($2)
	nop
	sw	$2,44($fp)
	li	$2,1			# 0x1
	sw	$2,24($fp)
	li	$2,2			# 0x2
	sw	$2,28($fp)
	li	$2,3			# 0x3
	sw	$2,32($fp)
	li	$2,4			# 0x4
	sw	$2,36($fp)
	li	$2,5			# 0x5
	sw	$2,40($fp)
	lw	$3,24($fp)
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
	addu	$2,$3,$2
	lw	$3,%got(__stack_chk_guard)($28)
	lw	$4,44($fp)
	lw	$3,0($3)
	nop
	beq	$4,$3,$L3
	nop

	lw	$2,%call16(__stack_chk_fail)($28)
	nop
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__stack_chk_fail
1:	jalr	$25
	nop

$L3:
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
