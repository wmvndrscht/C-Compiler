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

	lw $3,32($fp)
	li $8,1
	multu $3,$8
	mflo $3
	beq $3,$0,$L1
	nop
	li $3,42
	move $2,$3
	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop
$L1:
	li $3,21
	move $2,$3
	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop

	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop

