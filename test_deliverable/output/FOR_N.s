	.text
	.align 2
	.global f
	.set nomicromips
	.set nomips16
	.type f, @function
f:
	addiu $sp,$sp,-32
	sw $31,28($sp)
	sw $fp,24($sp)
	move $fp,$sp

	li $3,0

	addiu $sp,$sp,-4
	move $fp,$sp
	sw $3,0($fp)
	li $3,0

	addiu $sp,$sp,-4
	move $fp,$sp
	sw $3,0($fp)
	b $L2
	nop
$L1:
	lw $3,4($fp)
	lw $8,4($fp)
	li $9,1
	addu $8,$8,$9
	move $3,$8
	sw $3,4($fp)

	lw $3,0($fp)
	addiu $3,$3,1
	sw $3,0($fp)
$L2:
	lw $3,0($fp)
	li $8,10
	slt $3,$3,$8

	bne $3,$0,$L1
	nop
	lw $3,4($fp)
	move $2,$3
	move $sp,$fp
	lw $31,36($sp)
	lw $fp,32($sp)
	addiu $sp,$sp,40
	j $31
	nop

	move $sp,$fp
	lw $31,36($sp)
	lw $fp,32($sp)
	addiu $sp,$sp,40
	j $31
	nop

