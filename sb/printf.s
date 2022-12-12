.section .data
    str1: .string "Imprimiu %d\n"
.section .text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movq $str1, %rdi
    movq $0, %r11      # i = 0
    movq %r11, %rsi
    call printf
    movq $1, %r11      # i++
    movq $str1, %rdi
    movq %r11, %rsi
    call printf
    movq $0, %rdi
    movq $60, %rax
    syscall
