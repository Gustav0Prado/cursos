#pragma once

void iniciaAlocador();
void finalizaAlocador();
void liberaMem(void* bloco);
void* alocaMem(long int num_bytes);
void imprimeMapa();