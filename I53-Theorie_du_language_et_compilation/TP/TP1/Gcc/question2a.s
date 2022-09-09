	.file	"main.c"
	.text
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$2, 12(%esp)
	movl	$1, 4(%esp)
	movl	$0, 8(%esp)
	jmp	L2
L3:
	addl	$1, 12(%esp)
	addl	$1, 8(%esp)
L2:
	cmpl	$9, 8(%esp)
	jle	L3
	addl	$1, 12(%esp)
	movl	12(%esp), %eax
	addl	%eax, 4(%esp)
	movl	12(%esp), %edx
	movl	4(%esp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%esp), %edx
	movl	4(%esp), %eax
	addl	%edx, %eax
	movl	%ecx, %edx
	imull	%eax, %edx
	movl	12(%esp), %eax
	subl	4(%esp), %eax
	movl	%eax, %ecx
	movl	12(%esp), %eax
	subl	4(%esp), %eax
	imull	%eax, %ecx
	movl	12(%esp), %eax
	subl	4(%esp), %eax
	imull	%ecx, %eax
	addl	%edx, %eax
	movl	%eax, (%esp)
	movl	(%esp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC Build-2) 9.2.0"
