#ifndef FILMES_H
#define FILMES_H

#include <stdio.h>
#include "utils.h" // Para usar as cores (ORANGE, GREEN...)

// --- AQUI MORA A STRUCT FILMES ---
typedef struct {
    char titulo[100];
    char resumo[500];
    int soma_notas;
    float avaliacao_media;
    int qtdAvalia;
    int qtdComent;
} Filmes;

// Protótipos
void cadastrarFilme(FILE *arqfilme);
void listar_avaliarFilmes(FILE *arqfilme, FILE *arqavaliacao, char *usuario_logado);
long contarTotalFilmes(FILE *arqfilme);
void pioresfilmes(FILE *arqfilme);
void melhoresfilmes(FILE *arqfilme);

#endif