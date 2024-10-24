.section .data
   A: .quad 0
   B: .quad 0
.section .text
.globl _start
soma:
   pushq %rbp
   movq %rsp, %rbp
   #aloca espaco na pilha
   subq $16, %rsp
   #inicializa valolres na pilha
   movq A, %rax
   movq %rax, -8(%rbp)
   movq B, %rax
   movq %rax, -16(%rbp)
   #puxa valores para os regs
   movq -8(%rbp), %rax
   movq -16(%rbp), %rbx
   addq %rbx, %rax
   #libera espaço
   addq $16, %rsp
   popq %rbp
   ret
_start:
   movq $4, A
   movq $5, B
   call soma
   movq %rax, %rdi
   movq $60, %rax
   syscall
