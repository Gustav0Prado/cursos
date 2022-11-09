.section .data
.section .text
.globl _start
_start:
   movq $0, %rax     #rax contem a
   movq $0, %rdi     #rdi contem i
   while:
      cmpq $10, %rdi
      jge fim_loop
      addq %rdi, %rax
      addq $1, %rdi
      jmp while
   fim_loop:
      movq %rax, %rdi
      movq $60, %rax
      syscall
