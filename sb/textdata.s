.section .data
    A: .quad 0
    str1: .string ".data %d bytes\n"
    str2: .string ".text %d bytes\n"
    B: .quad 0

.section .text
.globl main

main:
    _c:
    pushq %rbp
    movq %rsp, %rbp

    # imprime tamanho da secao data
    movq $B, %rax
    movq $A, %rbx
    subq %rbx, %rax
    movq %rax, %rsi
    movq $str1, %rdi
    call printf

    # imprime tamanho da secao text
    movq $_d, %rax
    movq $_c, %rbx
    subq %rbx, %rax
    movq %rax, %rsi
    movq $str2, %rdi
    call printf

    movq $0, %rdi
    movq $60, %rax
    syscall
    _d:
