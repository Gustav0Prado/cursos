.section .data
    topoInicialHeap:    .quad 0
    topoHeap:           .quad 0
    inicioHeap:         .quad 0
    numBytes:           .quad 0
    topoAux:            .quad 0
    teste1:             .quad 0
    teste2:             .quad 0
    teste3:             .quad 0
    TAM_HEADER:             .quad 16

.section .text
.globl iniciaAlocador
.globl finalizaAlocador
.globl liberaMem
.globl alocaMem
.globl imprimeMapa

iniciaAlocador:
    pushq %rbp                      # informacoes gerenciais
    movq %rsp, %rbp

    movq $12, %rax                  # chamada de sistema do brk
    movq $0, %rdi                   # pega valor inicial da heap
    syscall
    movq %rax, topoInicialHeap
    movq %rax, topoHeap
    movq %rax, inicioHeap

    popq %rbp                       # retorno do procedimento
    ret

finalizaAlocador:
    pushq %rbp                      # informacoes gerenciais
    movq %rsp, %rbp

    movq $12, %rax                  # chamada do sistema do brk
    movq topoInicialHeap, %rdi      # retorna heap ao estado original
    syscall

    popq %rbp                       # retorno do procedimento
    ret

liberaMem:
    pushq %rbp                      # informacoes gerenciais
    movq %rsp, %rbp

    movq %rdi, %rax                 # salva endereco do bloco em %rax
    subq $16, %rax                   # Faz endereço apontar para o primeiro byte
    movq $0, (%rax)                 # escreve 0 na informacao gerencial

    popq %rbp                       # retorno do procedimento
    ret

alocaMem:
    pushq %rbp                      # informacoes gerenciais
    movq %rsp, %rbp

    movq %rdi, %rax                 # %rax <- num_bytes
    movq $4096, %rbx                # num_bytes/4096
    idiv %rbx                       # resultado da divisao no %rax
    addq $1, %rax                   # (num_bytes/4096)+1
    imul $4096, %rax                # %rax <- ((num_bytes/4096)+1)*4096

    addq $16, %rax                 # espaco para infos gerenciais
    movq %rax, numBytes            # numBytes <- %rax
    addq topoHeap, %rax            # altura nova da brk
    movq %rax, topoAux             # topo auxiliar

    movq $12, %rax                 # chamada do sistema do brk
    movq topoAux, %rdi             # %rdi <- num_bytes
    syscall

    # addq $1, topoHeap               # aponta para o novo bloco
    movq topoHeap, %rbx             # %rbx <- endereco do topo antigo da pilha
    movq $1, (%rbx)                 # marca bloco como ocupado
    subq $16, numBytes
    movq numBytes, %rcx
    movq %rcx, 8(%rbx)              # marca tamanho do bloco
    addq $16, %rbx               
    movq %rbx, %rax                 # retorna endereco do bloco livre
    addq %rcx, topoHeap             # atualiza topo da heap

    popq %rbp                       # retorno do procedimento
    ret

# IMPRIME MAPA
imprimeMapa:
    pushq %rbp                       # Empilha informacoes da funcao
    movq %rsp, %rbp
    movq inicioHeap, %r12            # Endereco do inicio da heap
    movq topoHeap, %r13              # Endereco do topo da heap
    
    initWhileImprime:
    cmpq %r13, %r12
    jge fimWhileImprime
    call imprimeHeader
    
    movq (%r12), %r10                # %r10 := Conteudo de %r12 (flag de ocupado)
    movq 8(%r12), %r11               # %r11 := Conteudo de %r12 + 8 bytes (tamanho do bloco)
    cmpq $1, %r10
    je imprimeOcupado
    
    movq %r11, %rdi                  # %rdi eh o primeiro parametro da funcao seguinte
    call imprimeBlocoLivre           # Imprime bytes do bloco livre
    jmp incrementaAtual

    imprimeOcupado:
    movq %r11, %rdi                  # %rdi eh o primeiro parametro da funcao seguinte
    call imprimeBlocoOcupado         # Imprime bytes do bloco ocupado

    incrementaAtual:             
    addq 8(%r12), %r12               # Aumenta o endereco apontado pelo inicio da heap
    addq TAM_HEADER, %r12            
    jmp initWhileImprime          

    fimWhileImprime:
    movq $10, %rdi                   # 10 igual a \n em ascii
    call putchar
    movq $10, %rdi
    call putchar
    popq %rbp                        # Retorna funcao
    ret


imprimeHeader:
    pushq %rbp
    movq %rsp, %rbp
    movq $0, %r14 		             # Inicializa contador
    initWhileHeader:
    cmpq TAM_HEADER, %r14
    jge fimWhileHeader
    movq $35, %rdi                   # 35 igual a # em ascii
    call putchar
    addq $1, %r14
    jmp initWhileHeader
    fimWhileHeader:
    popq %rbp
    ret


imprimeBlocoOcupado:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rbx                  # %rbx := Tamanho do bloco (1o parametro passado)
    movq $0, %r14 		             # Inicializa contador
    initWhileOcupado:
    cmpq %rbx, %r14
    jge fimWhileOcupado
    movq $43, %rdi                   # 43 igual a + em ascii
    call putchar
    addq $1, %r14
    jmp initWhileOcupado
    fimWhileOcupado:
    popq %rbp
    ret


imprimeBlocoLivre:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rbx                  # %rbx := Tamanho do bloco (1o parametro passado)
    movq $0, %r14 		             # Inicializa contador
    initWhileLivre:
    cmpq %rbx, %r14
    jge fimWhileLivre
    movq $45, %rdi                   # 45 igual a - em ascii
    call putchar
    addq $1, %r14
    jmp initWhileLivre
    fimWhileLivre:
    popq %rbp
    ret
