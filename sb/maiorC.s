.section .data
   I:          .quad 0 #Mapeado em %rdi
   MAIOR:      .quad 0 #Mapeado em %rbx
   DATA_ITEMS: .quad 3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0
                     #Mapeado em %rax
.section .text
.globl _start
_start:
   movq $0, %rdi
   movq DATA_ITEMS(, %rdi, 8), %rbx
   movq $1, %rdi
   while:
      movq DATA_ITEMS(, %rdi, 8), %rax
      cmpq $0, %rax
      je fim_while
      cmpq %rbx, %rax
      jle fim_if
      movq %rax, %rbx
      fim_if:
         addq $1, %rdi
      jmp while
   fim_while:
      movq %rbx, %rdi
      movq $60, %rax
      syscall
      