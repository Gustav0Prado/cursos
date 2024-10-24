.section .data
   A: .quad 0
   B: .quad 0
.section .text
.globl _start
soma:
   pushq %rbp
   movq %rsp, %rbp
   #aloca espaco na pilha
   subq $8, %rsp
   #soma os parametros e move o resultado para a var na pilha
   movq 16(%rbp), %rax
   addq 24(%rbp), %rax
   movq %rax, -8(%rbp)
   #desaloca espaco
   addq $8, %rsp
   popq %rbp
   ret
_start:
   movq $4, A
   movq $5, B
   pushq B
   pushq A
   call soma
   movq %rax, %rdi
   movq $60, %rax
   syscall
