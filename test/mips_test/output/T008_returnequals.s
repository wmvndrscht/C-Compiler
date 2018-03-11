.global f
.align 2
f:
	addiu $sp,$sp,-8
	sw $fp,4($sp)
	move $fp,$sp

	li $2,5
	li $3,5
	beq $2,$3,L1
	nop
	li $2,0
	b L2
L1:
	li $2,1
L2:


	move $sp,$fp
	lw $fp,4($sp)
	addiu $sp,$sp,8
	j $31
	nop
