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


	move $sp,$fp
	lw $fp,4($sp)
	addiu $sp,$sp,8
	j $31
	nop
