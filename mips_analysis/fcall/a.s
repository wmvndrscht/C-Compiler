.align 2
	.global function
	.type function, @function
function:
	addiu $sp,$sp,-32
	sw $31,28($sp)
	sw $fp,24($sp)
	move $fp,$sp



	sw $4,32($fp) #store parameter at offset of sp
	sw $5,36($fp) #store parameter at offset of sp

	lw $3,32($fp) #load variables in for comparison
	lw $8,36($fp)


	slt $3,$3,$8 #if a < b set 3 to one
	beq $3,$0,$L1
	nop
	lw $3,32($fp)
	lw $8,32($fp)
	li $9,1
	subu $8,$8,$9
	move $3,$8
	sw $3,32($fp)
	lw $3,32($fp)
	lw $8,36($fp)
	slt $3,$8,$3
	beq $3,$0,$L2
	nop
	lw $3,36($fp)
	lw $8,36($fp)
	li $9,3
	addu $8,$8,$9
	move $3,$8
	sw $3,36($fp)
	lw $3,32($fp)
	lw $8,36($fp)
	beq $3,$8,L4
	nop
	li $3,0
	b L5
L4:
	li $3,1
L5:
	beq $3,$0,$L3
	nop
	lw $3,32($fp)
	lw $8,36($fp)
	multu $3,$8
	mflo $3
	move $2,$3
	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop
$L3:
$L2:
	lw $3,36($fp)
	move $2,$3
	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop
$L1:
	li $3,13
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
	.align 2
	.global main
	.type main, @function
main:
	addiu $sp,$sp,-32
	sw $31,28($sp)
	sw $fp,24($sp)
	move $fp,$sp

	li $3,0
	move $4,$3
	li $3,0
	move $5,$3

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
	jal function
	nop
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
	move $3,$2
	li $8,1
	move $4,$3
	li $8,2
	move $5,$3

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
	jal function
	nop
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
	li $8,4
	move $4,$3
	li $8,3
	move $5,$3

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
	jal function
	nop
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
	li $8,6
	move $4,$3
	li $8,7
	move $5,$3

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
	jal function
	nop
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

	move $sp,$fp
	lw $31,28($sp)
	lw $fp,24($sp)
	addiu $sp,$sp,32
	j $31
	nop
