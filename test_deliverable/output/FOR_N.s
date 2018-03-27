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
	sw $4,32($fp)
	sw $5,36($fp)

	li $3,0

	addiu $sp,$sp,-4
	move $fp,$sp
	sw $3,0($fp)
	b $L2
	nop
$L1:
	lw $3,36($fp)
	lw $8,36($fp)
	li $9,1
	addu $8,$8,$9
	move $3,$8
	sw $3,36($fp)

	lw $3,0($fp)
	move $8,$3
	addiu $8,$8,1
	sw $8,0($fp)
$L2:
	lw $3,0($fp)
	li $8,10
	slt $3,$3,$8

	bne $3,$0,$L1
	nop
	lw $3,36($fp)
	lw $8,40($fp)
	addu $3,$3,$8
	move $2,$3
	move $sp,$fp
	lw $31,32($sp)
	lw $fp,28($sp)
	addiu $sp,$sp,36
	j $31
	nop

	move $sp,$fp
	lw $31,32($sp)
	lw $fp,28($sp)
	addiu $sp,$sp,36
	j $31
	nop

