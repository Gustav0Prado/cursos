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
    movq $A, %r11
    movq $B, %rbx
    subq %r11, %rbx
    movq $str1, %rdi
    movq %r11, %rsi
    call printf

    movq $_c, %r11
    movq $_d, %rbx
    subq %r11, %rbx
    movq $str2, %rdi
    movq %r11, %rsi
    call printf

    movq $0, %rdi
    movq $60, %rax
    syscall
    _d:
