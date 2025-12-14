#ifndef AVALIACOES_H
#define AVALIACOES_H

#include <stdio.h>

// --- DEFINIÇÃO DA STRUCT (O filmes.c precisa ler isso aqui) ---
typedef struct
{
    char titulo[100];
    char usuario[25];
    int avaliacao;
    char comentario[80];
} Avaliar;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void exibirAvaliacoesPorUsuario(char user[], FILE *arqavaliacoes);
void exibirAvaliacoesPorFilme(char filme[], FILE *arqavaliacoes);
void exibirTodasAvaliacoes(FILE *avaliacoes);
void recomendarFilmes(char *usuario_logado, FILE *arqavaliacoes);

#endif