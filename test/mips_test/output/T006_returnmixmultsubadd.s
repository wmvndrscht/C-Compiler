.global f
.align 2
f:
	addiu $sp,$sp,-8
	sw $fp,4($sp)
	move $fp,$sp

	li $2,1
	li $3,2
	multu $2,$3
	mflo $2
	li $3,3
	multu $2,$3
	mflo $2
	li $3,1
	li $8,5
	multu $3,$8
	mflo $3
	subu $2,$2,$3
	li $8,2
	addu $2,$2,$8
	li $9,1
	subu $2,$2,$9
	li $10,4
	subu $2,$2,$10
	li $11,5
	addu $2,$2,$11


	move $sp,$fp
	lw $fp,4($sp)
	addiu $sp,$sp,8
	j $31
	nop
