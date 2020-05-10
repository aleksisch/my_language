global      _start                              ;must be declared for linker (ld)

msg     db  'Hello, world!',0xa                 ;our dear string
len     equ $ - msg      

_start:                                         ;tell linker entry point
    mov     edx,0xffff
    push rax
    push rbx
    push r8
    push 5