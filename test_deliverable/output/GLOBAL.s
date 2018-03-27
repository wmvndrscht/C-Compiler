	.globl a
	.data
	.align 2
	.type a,@object
	.size a,4
a:
	.word 2
	.globl b
	.data
	.align 2
	.type a,@object
	.size b,4
b:
	.word 1
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

	lui $3,%hi(a)
	lw $3,%lo(a)($3)
	lui $8,%hi(b)
	lw $8,%lo(b)($8)
	lui $3,%hi(a)
	sw $8,%lo(a)($3)
	lui $3,%hi(a)
	lw $3,%lo(a)($3)
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

