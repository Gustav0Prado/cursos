.section .data
   A: .quad 0
   B: .quad 0
.section .text
.globl _start
troca:
   pushq %rbp
   movq %rsp, %rbp
   subq $8, %rsp           #aloca variavel local

   movq 16(%rbp), %rax     #move primeiro param para rax
   movq (%rax), %rbx       #move conteudo do end de rax para rbx
   movq %rbx, -8(%rbp)     #move conteudo de rbx para a var local

   movq 24(%rbp), %rax     #pega o conteudo do segundo parametro
   movq (%rax), %rbx       #pega o conteudo do endereco apontado por rax
   movq 16(%rbp), %rax
   movq %rbx, (%rax)       #move o conteudo de rbx para o end em rax

   movq 24(%rbp), %rax     #pega o conteudo do segundo parametro
   movq -8(%rbp), %rbx     #pega o conteudo do var local
   movq %rbx, (%rax)

   addq $8, %rsp           #desaloca vars locais
   popq %rbp
   ret
_start:
   movq $1, A
   movq $2, B

   subq $16, %rsp          #aloca espaco dos params
   pushq $B                #empilha B
   pushq $A                #empilha A
   call troca

   addq $16, %rsp          #desaloca espaco dos params
   movq $0, %rdi
   movq $60, %rax
   syscall
   