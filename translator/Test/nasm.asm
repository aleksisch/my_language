global _start
_start:
	mov rax, 9
	mov rbx, 16
	cvtsi2sd xmm0, rax
	cvtsi2sd xmm1, rbx
	sqrtsd xmm0, xmm1
	comisd xmm0, xmm1
	jb end


end:
	mov ax, ax