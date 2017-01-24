#============================================================================
# Example complete program written in IA-32 Assembly Language
# CS281 Fall 2015
# Professor Bressoud
#============================================================================
	# Global Data for the program
	.data
        # Move following allocation of memory to be 4-byte multiple aligned
	.align 4

	# Define global variable x
	.globl x
x:	.long	5

	# Define global variable y
	.globl	y
y:	.long	3

	# Define and initialize to 0 global variable result
result:	.long   0

pstr:	.string	"result = %d (0x%8.8x)\n"

# Code (text) for the program
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp           # Prologue begins
	movl	%esp, %ebp     #
	andl	$-16, %esp     #
	subl	$16, %esp      # Prologue ends

	# Body of main function
	movl	x, %edx        # %edx <- M[x]
	movl	y, %eax        # %eax <- M[y]
	subl	%edx, %eax     # %eax <- %eax + %edx
	movl	%eax, result   # M[result] <- %eax

	# Set up arguments and call printf
	movl	result, %eax   # %eax <- M[result]
	movl	%eax, 8(%esp)  # M[%esp + 8] <- %eax  ; arg3
	movl	%eax, 4(%esp)  # M[%esp + 4] <- %eax  ; arg2
	movl	$pstr, (%esp)  # M[%esp + 0] <- $pstr ; arg1
	call	printf         # printf(arg1, arg2, arg3)

	# 
	movl	$0, %eax
	leave
	ret

