#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char titulo[100];
    char usuario[25];
    int avaliacao;
    char comentario[80];

} avaliar;

typedef struct
{
    char titulo[100];
    char resumo[200];
    int soma_notas;
    float avaliacao_media;
    int qtdAvalia;
    int qtdComent;

} filmes;

typedef struct
{
    char nome[50];
    char senha[8];

} usuarios;

int main()
{

    return 0;
}