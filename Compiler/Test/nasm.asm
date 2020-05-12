global _start
_start:

	pop rax
	pop rbx
	
	mov rax, 280
	mov rbx, 10
	mov rdx, 0x0100000000000000
	cvtsi2sd xmm1, rax


	sub     rsp, 16
	movdqu  [rsp], xmm0

	movdqu xmm0, [rsp]
	add rsp, 16

	movdqu xmm1, [rsp]
	add rsp, 16

	addsd xmm0, xmm1

	cvttsd2si rax, xmm0

	mulsd xmm0, xmm1

	cvttsd2si rax, xmm0

	divsd xmm0, xmm1

	cvttsd2si rax, xmm0

	subsd xmm0, xmm1

	cvttsd2si rax, xmm0


	add     esp, 16
	mov     eax, 0 
	mov     ebx, 1 
	int     0x80