SECTION .text
jmp Print
jmp Scan
tmp_byte: db '0'
Print:
	mov r9, 10
	mov rcx, 0
	cmp rax, 0
		je .zero
		jge .Loop
	mov dl, '-'
	push rax
	call PrintChar
	pop rax
	neg rax
	.Loop:
		cmp rax, 0
			je .print
		xor rdx, rdx
		div r9
		add dl, '0'
		push rdx
		inc rcx
		jmp .Loop

	.zero:
		mov dl, '0'
		call PrintChar
		jmp .end

	.print:
		.Output:
			cmp rcx, 0
				je .end
			pop rdx
			call PrintChar
			dec rcx
			jmp .Output
	.end:
		mov dl, 10	;\n
		call PrintChar
		ret

PrintChar:
	mov [tmp_byte], dl
	mov rsi, tmp_byte
	mov rax, 1
	mov rdi, 0
	mov rdx, 1
	push rcx
	syscall

	pop rcx
	ret

Scan:
	xor r8, r8
	.Loop:
	    mov eax, 3
	    mov ebx, 2
	    mov ecx, tmp_byte
	    mov edx, 1
	    int 80h
	    cmp byte [tmp_byte], 10
	    	je .end
	    imul r8, 10	
	    xor rax, rax
	    mov al, [tmp_byte]
	    sub al, '0'
	    add r8, rax
	    jmp .Loop
	.end:
		ret