/*
 * source: https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
 * Código do exercicio baseado no FloatType.c
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define erro 1.4012984643248170709237296e-45

typedef union
{
    int32_t i;
    float f;
    struct
    {   // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        uint32_t mantissa : 23; // primeiros 23 bits (da direita para a esquerda)
        uint32_t exponent : 8;  // próximos 8 bits
        uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

/* imprime a union Float_t como ponto flutuante, hexadecimal e 
 * suas partes na forma de inteiros */
void printFloat_t( Float_t num )
{
   printf("f:%1.9e, ix:0x%08X, s:%d, e:%d, mx:0x%06X\n",
            num.f, num.i,
            num.parts.sign, num.parts.exponent, num.parts.mantissa); 
}

int main()
{
    Float_t a;
    float orig;
    float prox;
    float ant;
    float nant;
    float npos;

    printf("Digite um numero float: ");
    scanf("%f", &a.f);
    orig = a.f;
    printf("Inicio:    %.25e\n", a.f);
    printf("------------------------------------------\n");

    /* ao olhar para o numero como inteiro e diminuir/aumentar, ele se tornará o proximo/anterior */
    if(a.f >= erro ){
        a.i--;
        ant = a.f;
        printf("Anterior:  %.25e\n", a.f);

        a.i += 2;
        prox = a.f;
        printf("Posterior: %.25e\n", a.f);

        nant = nextafterf(orig, orig-(orig*10));
        npos = nextafterf(orig, orig+(orig*10));        
    }
    //caso o numero seja 0, o proximo e anterior sao iguais, mas com sinal invertido
    else if(fabs(a.f) < erro){
        a.parts.sign = 1;
        a.i++;
        ant = a.f;
        printf("Anterior: %.25e\n", a.f);

        a.parts.sign = 0;
        prox = a.f;
        printf("Posterior: %.25e\n", a.f);
        a.i--;

        nant = nextafterf(orig, orig-1);
        npos = nextafterf(orig, orig+1);
    }
    //numero negativo, inverte maior/menor (ou prox/ant)
    else{
        a.i++;
        ant = a.f;
        printf("Anterior:  %.25e\n", a.f);

        a.i -= 2;
        prox = a.f;
        printf("Posterior: %.25e\n", a.f);

        nant = nextafterf(orig, orig+(orig*10));
        npos = nextafterf(orig, orig-(orig*10));
    }

    printf("--------------------vs--------------------\n");

    /* nextafter anterior -> num atual na direcao "negativa" (para tras)
     * nextafter posterior -> num atual na direcao "postiva" (para frente)
     * obs: o (orig*10) se deve ao aumento na distancia entre um número e outro a medida que aumentam (vide ex. 2)
     * logo calcula-se o nextafter de um numero 10x maior que atual para garantir que seja representado um numero realmente maior
     */
    
    printf("Nextafter Anterior:  %.25e\n", nant);
    printf("Nextafter Posterior: %.25e\n", npos);

    /* diferenca entre os numeros calculados */
    printf("----------------Resultado-----------------\n");
    printf("Diferenca de: %e e %e\n", fabs(ant-nant), fabs(prox-npos));

   return 0;
}