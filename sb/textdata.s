.section .data
    A: .quad 0
    B: .quad 0
    C: .quad 0
.section .text
.globl _start

# main:
_start:
    pushq %rbp
    movq %rsp, %rbp
    movq A, %rdi
    movq $60, %rax
    syscall
