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
	slt $3,$3,$8
	beq $3,$0,$L1
	nop
	li $3,2
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
	lw $3,32($fp)
	lw $8,32($fp)
	li $9,1
	subu $8,$8,$9
	move $4,$8

	addiu $sp,$sp,-92
	sw $25,16($sp)
	sw $24,20($sp)
	sw $23,24($sp)
	sw $22,28($sp)
	sw $21,32($sp)
	sw $20,36($sp)
	sw $19,40($sp)
	sw $18,44($sp)
	sw $17,48($sp)
	sw $16,52($sp)
	sw $15,56($sp)
	sw $14,60($sp)
	sw $13,64($sp)
	sw $12,68($sp)
	sw $11,72($sp)
	sw $10,76($sp)
	sw $9,80($sp)
	sw $8,84($sp)
	sw $3,88($sp)
	move $fp,$sp
	.option pic0
	jal f
	nop
	.option pic2
	lw $25,16($sp)
	lw $24,20($sp)
	lw $23,24($sp)
	lw $22,28($sp)
	lw $21,32($sp)
	lw $20,36($sp)
	lw $19,40($sp)
	lw $18,44($sp)
	lw $17,48($sp)
	lw $16,52($sp)
	lw $15,56($sp)
	lw $14,60($sp)
	lw $13,64($sp)
	lw $12,68($sp)
	lw $11,72($sp)
	lw $10,76($sp)
	lw $9,80($sp)
	lw $8,84($sp)
	lw $3,88($sp)

	addiu $sp,$sp,92
	move $fp,$sp
	move $8,$2
	addu $3,$3,$8
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

