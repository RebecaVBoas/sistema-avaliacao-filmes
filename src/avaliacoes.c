#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- INCLUDES LOCAIS ---
#include "filmes.h"   
#include "usuarios.h"  
#include "avaliacoes.h" 
#include "utils.h"     


void exibirAvaliacoesPorUsuario(char user[], FILE *arqavaliacoes)
{
    system("clear");

    fseek(arqavaliacoes, 0, SEEK_SET);

    int qtAvaliacaoPorUser = 0;

    Avaliar avUser;
    while (fread(&avUser, sizeof(Avaliar), 1, arqavaliacoes) == 1)
    {
        if (strcmp(avUser.usuario, user) == 0)
        {
            printf("--------------AVALIAÇÃO %d--------------", qtAvaliacaoPorUser + 1);
            printf("\nFILME: %s\n", avUser.titulo);
            printf("\nUSUARIOS: %s\n", avUser.usuario);
            printf("\nCOMENTARIO: %s", avUser.comentario);
            printf("\nNOTA: %d\n", avUser.avaliacao);

            qtAvaliacaoPorUser++;
        }
    }

    if (qtAvaliacaoPorUser == 0)
    {
        printf("\nNão foram encontradas avaliações desse usuario\n");
    }
}

void exibirAvaliacoesPorFilme(char filme[], FILE *arqavaliacoes)
{
    system("clear");

    fseek(arqavaliacoes, 0, SEEK_SET);

    int qtAvaliacaoPorFilme = 0;

    Avaliar avFilme;
    while (fread(&avFilme, sizeof(Avaliar), 1, arqavaliacoes) == 1)
    {
        if (strcmp(avFilme.titulo, filme) == 0)
        {
            printf("--------------AVALIAÇÃO %d--------------", qtAvaliacaoPorFilme + 1);
            printf("\nFILME: %s\n", avFilme.titulo);
            printf("\nUSUARIOS: %s\n", avFilme.usuario);
            printf("\nCOMENTARIO: %s", avFilme.comentario);
            printf("\nNOTA: %d\n", avFilme.avaliacao);

            qtAvaliacaoPorFilme++;
        }
    }

    if (qtAvaliacaoPorFilme == 0)
    {
        printf("\nNão foram encontradas avaliações desse filmes\n");
    }
}

void exibirTodasAvaliacoes(FILE *avaliacoes)
{
    if (avaliacoes == NULL)
    {
        printf("\nERRO: O arquivo de avaliações não está aberto ou é NULL.\n");
        return;
    }

    // 1. Volta para o início do arquivo para garantir que a leitura comece do zero
    fseek(avaliacoes, 0, SEEK_SET);

    int qtAvaliacaoTotal = 0;
    Avaliar avAtual;

    printf("\n=======================================================");
    printf("\n========= EXIBINDO TODAS AS AVALIAÇÕES SALVAS =========");
    printf("\n=======================================================\n");

    // 2. Loop de leitura: continua enquanto fread conseguir ler 1 struct (retorna 1)
    while (fread(&avAtual, sizeof(Avaliar), 1, avaliacoes) == 1)
    {
        qtAvaliacaoTotal++;

        // 3. Exibição dos dados do registro
        printf("\n-------------- AVALIAÇÃO %d --------------\n", qtAvaliacaoTotal);
        printf("FILME:      %s\n", avAtual.titulo);
        printf("USUÁRIO:    %s\n", avAtual.usuario);
        printf("NOTA:       %d/5\n", avAtual.avaliacao);
        printf("COMENTÁRIO: %s\n", avAtual.comentario);
        printf("-----------------------------------------\n");
    }

    // 4. Mensagem de resumo
    if (qtAvaliacaoTotal == 0)
    {
        printf("\nO arquivo 'avaliacoes.dat' está vazio ou não foram encontradas avaliações.\n");
    }
    else
    {
        printf("\n=======================================================");
        printf("\n%d avaliações exibidas com sucesso.", qtAvaliacaoTotal);
        printf("\n=======================================================\n");
    }

}
