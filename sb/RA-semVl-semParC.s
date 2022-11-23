.section .data
   A: .quad 0  #Mapeado em %rax
   B: .quad 0  #Mapeado em %rbx
.section .text
.globl _start
soma:
   pushq %rbp
   movq %rsp, %rbp
   movq A, %rax
   movq B, %rbx
   addq %rbx ,%rax
   popq %rbp
   ret

_start:
   movq $5, A
   movq $5, B
   call soma
   movq %rax, %rdi
   movq $60, %rax
   syscall
