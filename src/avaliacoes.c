#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// --- INCLUDES LOCAIS ---
#include "filmes.h"   
#include "usuarios.h"  
#include "avaliacoes.h" 
#include "utils.h"     

// Struct auxiliar para o k-NN
typedef struct {
    char titulo[100];
    int nota;
} RegistroNota;


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
            printf("\n                   ---------------- AVALIAÇÃO %d ----------------", qtAvaliacaoPorUser + 1);
            printf("\n                             FILME: %s\n", avUser.titulo);
            printf("\n                             USUARIOS: %s\n", avUser.usuario);
            printf("\n                             COMENTARIO: %s", avUser.comentario);
            switch (avUser.avaliacao)
            {
            case 1:
                
                printf("\n                             NOTA: %d ⭐\n", avUser.avaliacao);
                break;
            case 2:
                printf("\n                             NOTA: %d ⭐⭐\n", avUser.avaliacao);
                break;
            case 3:
                printf("\n                             NOTA: %d ⭐⭐⭐\n", avUser.avaliacao);
                break;
            case 4:
                printf("\n                             NOTA: %d ⭐⭐⭐⭐\n", avUser.avaliacao);
                break;
            case 5:
                printf("\n                             NOTA: %d ⭐⭐⭐⭐⭐\n", avUser.avaliacao);
                break;           
            default:
                break;
            }
            

            qtAvaliacaoPorUser++;
        }
    }

    if (qtAvaliacaoPorUser == 0)
    {
        printf("\nNão foram encontradas avaliações desse usuario\n");
    }
    printf(ORANGE"\n                     =========================================\n" RESET);
    printf("Pressione ENTER para voltar...");
    getchar();
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
        printf("\n                   ---------------- AVALIAÇÃO %d ----------------", qtAvaliacaoPorFilme + 1);
            printf("\n                             FILME: %s\n", avFilme.titulo);
            printf("\n                             USUARIOS: %s\n", avFilme.usuario);
            printf("\n                             COMENTARIO: %s", avFilme.comentario);
            switch (avFilme.avaliacao)
            {
            case 1:
                
                printf("\n                             NOTA: %d ⭐\n", avFilme.avaliacao);
                break;
            case 2:
                printf("\n                             NOTA: %d ⭐⭐\n", avFilme.avaliacao);
                break;
            case 3:
                printf("\n                             NOTA: %d ⭐⭐⭐\n", avFilme.avaliacao);
                break;
            case 4:
                printf("\n                             NOTA: %d ⭐⭐⭐⭐\n", avFilme.avaliacao);
                break;
            case 5:
                printf("\n                             NOTA: %d ⭐⭐⭐⭐⭐\n", avFilme.avaliacao);
                break;           
            default:
                break;
            }

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
        printf("\n               -------------- AVALIAÇÃO %d --------------\n", qtAvaliacaoTotal);
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



void recomendarFilmes(char *usuario_logado, FILE *arqavaliacoes) {
    // 1. Definições e Variáveis
    RegistroNota minhasNotas[100]; 
    int qtdMinhasNotas = 0;
    
    // --- NOVO: Variáveis para guardar os candidatos à recomendação ---
    RegistroNota candidatos[100];
    int qtdCandidatos = 0;
    // ----------------------------------------------------------------
    
    char usuarioAtual[25];
    char melhorVizinho[25];
    strcpy(melhorVizinho, "");
    
    float menorDistancia = 100000.0; 
    int encontrouVizinho = 0;

    Avaliar avLeitura;
    
    system("clear"); // Use "cls" se estiver no Windows
    printf("               CALCULANDO RECOMENDACOES BASEADAS EM SEU GOSTO...\n");

    // ---------------------------------------------------------
    // PASSO 1: Carregar as notas do usuário logado (IGUAL AO ANTERIOR)
    // ---------------------------------------------------------

    rewind(arqavaliacoes); 
    while(fread(&avLeitura, sizeof(Avaliar), 1, arqavaliacoes) == 1) {
        if(strcmp(avLeitura.usuario, usuario_logado) == 0) {
            strcpy(minhasNotas[qtdMinhasNotas].titulo, avLeitura.titulo);
            minhasNotas[qtdMinhasNotas].nota = avLeitura.avaliacao;
            qtdMinhasNotas++;
        }
    }

    if (qtdMinhasNotas == 0) {
        printf("\n[INFO] Voce precisa avaliar alguns filmes antes de receber recomendacoes!\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    // ---------------------------------------------------------
    // PASSO 2: Encontrar o Vizinho (IGUAL AO ANTERIOR)
    // ---------------------------------------------------------
    rewind(arqavaliacoes);
    while(fread(&avLeitura, sizeof(Avaliar), 1, arqavaliacoes) == 1) {
        if(strcmp(avLeitura.usuario, usuario_logado) != 0) {
            strcpy(usuarioAtual, avLeitura.usuario);
            
            float somaDiferencas = 0;
            int filmesEmComum = 0;
            long posAtual = ftell(arqavaliacoes); 
            
            FILE *arqTemp = abrirAvaliacoes(); 
            Avaliar avVizinho;
            
            while(fread(&avVizinho, sizeof(Avaliar), 1, arqTemp) == 1) {
                if(strcmp(avVizinho.usuario, usuarioAtual) == 0) {
                    for(int i = 0; i < qtdMinhasNotas; i++) {
                        if(strcmp(minhasNotas[i].titulo, avVizinho.titulo) == 0) {
                            somaDiferencas += pow(minhasNotas[i].nota - avVizinho.avaliacao, 2);
                            filmesEmComum++;
                            break;
                        }
                    }
                }
            }
            fclose(arqTemp); 

            if (filmesEmComum > 0) {
                float distanciaEuclidiana = sqrt(somaDiferencas);
                if (distanciaEuclidiana < menorDistancia) {
                    menorDistancia = distanciaEuclidiana;
                    strcpy(melhorVizinho, usuarioAtual);
                    encontrouVizinho = 1;
                }
            }
            fseek(arqavaliacoes, posAtual, SEEK_SET);
        }
    }

    // ---------------------------------------------------------
    // PASSO 3: MODIFICADO - Coletar, Ordenar e Exibir Top 5
    // ---------------------------------------------------------
    
    if (!encontrouVizinho) {
        printf("\n                    [INFO] Nao encontramos usuarios com gostos similares.\n");
    } else {
        printf("\n               Encontramos um perfil compativel: "); 
        printf(ORANGE"%s (Distancia: %.2f)\n" RESET, melhorVizinho, menorDistancia);
        
        // 3.1 COLETAR FILMES CANDIDATOS
        rewind(arqavaliacoes);
        while(fread(&avLeitura, sizeof(Avaliar), 1, arqavaliacoes) == 1) {
            // Se for nota do vizinho e nota boa (>=4)
            if(strcmp(avLeitura.usuario, melhorVizinho) == 0 && avLeitura.avaliacao >= 4) {
                
                // Verifica se eu já vi
                int jaVi = 0;
                for(int i = 0; i < qtdMinhasNotas; i++) {
                    if(strcmp(minhasNotas[i].titulo, avLeitura.titulo) == 0) {
                        jaVi = 1;
                        break;
                    }
                }
                
                // Se eu não vi, adiciona à lista de candidatos
                if (!jaVi) {
                    strcpy(candidatos[qtdCandidatos].titulo, avLeitura.titulo);
                    candidatos[qtdCandidatos].nota = avLeitura.avaliacao;
                    qtdCandidatos++;
                }
            }
        }

        // 3.2 ORDENAR CANDIDATOS (Bubble Sort - Maior nota para menor)
        // Isso garante que o "Top 5" sejam realmente os melhores filmes
        for (int i = 0; i < qtdCandidatos - 1; i++) {
            for (int j = 0; j < qtdCandidatos - i - 1; j++) {
                if (candidatos[j].nota < candidatos[j+1].nota) {
                    // Troca de posição
                    RegistroNota temp = candidatos[j];
                    candidatos[j] = candidatos[j+1];
                    candidatos[j+1] = temp;
                }
            }
        }

        // 3.3 EXIBIR TOP 5 (ou menos, se não tiver 5)
        if(qtdCandidatos == 0) {
            printf("\nO seu 'vizinho' nao tem filmes novos bons para te indicar.\n");
        } else {
            printf(GREEN"\n               --- TOP 5 FILMES RECOMENDADOS PARA VOCE ---\n" RESET);
            
            // Define limite: o menor valor entre 5 e a quantidade que achamos
            int limite = (qtdCandidatos < 5) ? qtdCandidatos : 5;
            
            for(int i = 0; i < limite; i++) {
                printf("               %d. %s (Nota dele: %d)\n", i+1, candidatos[i].titulo, candidatos[i].nota);
            }
        }
    }
    
    printf("\n               -----------------------------------------------------\n");
    printf("               Pressione ENTER para voltar ao menu...");
    getchar();
}