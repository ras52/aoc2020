	# Funnction:  imul( unsigned a, unsigned b );
	# 
	# computes hi:low *= val;
.globl imul
imul:
	PUSH	%ebp
	MOVL	%esp, %ebp

	XORL	%edx, %edx
	MOVL	8(%ebp), %eax
	IMULL	12(%ebp)		# implicitly acts on %edx:%eax

	POP	%ebp
	RET
