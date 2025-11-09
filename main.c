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

void menuPrincipal()
{
    system("clear"); // utilizar cls no windows
    // 28 espaços
    printf("                 ---------- BEM VINDO AO LETTERBOXD LP1 ----------           \n");
    printf("                            1 - Ver filmes                     \n");
    printf("                            2 - Estastísticas                  \n");
    printf("                            3 - ADM                            \n");
    printf("                            4 - Sair                           \n");
}

int main()
{
    usuarios login;
    /*
        declarações das variaveis
    */

    printf("                 ---------- BEM VINDO AO LETTERBOXD LP1 ----------           \n");
    printf("                            Faça seu login:                     \n");
    printf("                            Login: ");
    fgets(login.nome, sizeof(login.nome), stdin);
    printf("                            Senha: ");
    fgets(login.senha, sizeof(login.senha), stdin);

    // incluir validações de usuario antes de ir para o menu principal

    menuPrincipal();

    return 0;
}