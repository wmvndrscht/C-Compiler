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


	addiu $sp,$sp,-4
	move $fp,$sp
	sw $0,0($fp)
#size of array is 5
	addiu $sp,$sp,-4
	move $fp,$sp

	addiu $sp,$sp,-4
	move $fp,$sp

	addiu $sp,$sp,-4
	move $fp,$sp

	addiu $sp,$sp,-4
	move $fp,$sp

	lw $2,16($fp)
	li $3,4
	move $2,$3
	sw $2,16($fp)
	lw $2,12($fp)
	li $3,8
	move $2,$3
	sw $2,12($fp)
	lw $2,8($fp)
	li $3,12
	move $2,$3
	sw $2,8($fp)
	lw $2,4($fp)
	li $3,16
	move $2,$3
	sw $2,4($fp)
	lw $2,0($fp)
	li $3,2
	move $2,$3
	sw $2,0($fp)
	lw $2,16($fp)
	lw $3,12($fp)
	addu $2,$2,$3
	lw $3,8($fp)
	addu $2,$2,$3
	lw $3,4($fp)
	addu $2,$2,$3
	lw $3,0($fp)
	addu $2,$2,$3
	move $2,$2
	move $sp,$fp
	lw $31,48($sp)
	lw $fp,44($sp)
	addiu $sp,$sp,52
	j $31
	nop

	move $sp,$fp
	lw $31,48($sp)
	lw $fp,44($sp)
	addiu $sp,$sp,52
	j $31
	nop

