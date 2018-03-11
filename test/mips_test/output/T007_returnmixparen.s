.global f
.align 2
f:
	addiu $sp,$sp,-8
	sw $fp,4($sp)
	move $fp,$sp

	li $2,6
	li $3,3
	multu $2,$3
	mflo $2
	li $3,3
	li $8,1
	subu $3,$3,$8
	multu $2,$3
	mflo $2


	move $sp,$fp
	lw $fp,4($sp)
	addiu $sp,$sp,8
	j $31
	nop
