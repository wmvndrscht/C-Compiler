.global f
.align 2
f:
	addiu $sp,$sp,-8
	sw $fp,4($sp)
	move $fp,$sp

	li $2,7
	li $3,6
	subu $2,$2,$3
	li $3,9
	addu $2,$2,$3
	li $3,0
	addu $2,$2,$3


	move $sp,$fp
	lw $fp,4($sp)
	addiu $sp,$sp,8
	j $31
	nop
