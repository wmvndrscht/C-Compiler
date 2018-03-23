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

	li $3,1
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
	b $L2
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
$L2:

	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop

