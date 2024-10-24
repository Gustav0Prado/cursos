.section .data
.section .text
.globl _start
_start:
   movq $4, %rax
   movq $5, %rbx
   cmpq %rax, %rbx
   jge else
   addq %rbx, %rax
   jmp fim_if
   else:
      subq %rbx, %rax
   fim_if:
      movq %rax, %rdi
      movq $60, %rax
      syscall