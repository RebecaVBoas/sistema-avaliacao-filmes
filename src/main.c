#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "filmes.h"
#include "usuarios.h"
#include "avaliacoes.h"
#include "utils.h"

/* modo de uso
    printf(ORANGE "Cor 1 (#ff8000)\n" RESET);
    printf(GREEN  "Cor 2 (#00e054)\n" RESET);
    printf(BLUE   "Cor 3 (#40bcf4)\n" RESET);
    return 0;
*/

// Funções de Abertura de Arquivo
// MODIFICAR TIPO DO ARQUIVO E PARAMETRO DO fopen()
FILE *abrirFilme();
FILE *abrirUsuarios();
FILE *abrirAvaliacoes();

// Funções do Menu
int menuPrincipal(int *op);
int menuAdmin(int *op);

int main()
{

    FILE *filme = abrirFilme();
    FILE *usuarios = abrirUsuarios();
    FILE *avaliacoes = abrirAvaliacoes();

    long contarTotalFilmes(FILE * arqfilme);
    
    Usuarios usuerLogado = validarLogin(usuarios);
    int op = 0;

    // VARIAVEIS CASE 6
    char userPesquisa[20];

    // VARIAVEIS CASE 7
    char filmePesquisa[100];

    if (strcmp(usuerLogado.nome, "admin") != 0)
    {
        // menupPrincipal;

        while (op != 8)
        {
            menuPrincipal(&op);
            // limpa o buffer para a próxima leitura
            while ((getchar()) != '\n')
                ;

            switch (op)
            {
            case 1:
                // cadastrarFilme(filme);
                system("clear");
                listar_avaliarFilmes(filme, avaliacoes, usuerLogado.nome);

                break;
            case 2:
                /* 2 - Estastísticas */
                break;
            case 3:
                // Ver filmes avaliados
                break;
            case 4:
                // ver melhores filmes
                melhoresfilmes(filme);
                break;
            case 5:
                // ver piores filmes
                pioresfilmes(filme);

                break;
            case 6:
                // ver avaliações por usuario
                printf("Informe o nome do usuário que deseja pesquisar: ");
                fgets(userPesquisa, sizeof(userPesquisa), stdin);
                remover_quebra_linha(userPesquisa);

                system("clear");

                exibirAvaliacoesPorUsuario(userPesquisa, avaliacoes);
                break;
            case 7:

                // ver avaliações por filme
                printf("Informe o nome do filme que deseja pesquisar: ");
                fgets(filmePesquisa, sizeof(filmePesquisa), stdin);
                remover_quebra_linha(filmePesquisa);

                system("clear");

                exibirAvaliacoesPorFilme(filmePesquisa, avaliacoes);
                break;
            case 8:
                /* 8 - Recomendação k-NN */
                // Precisamos passar o ponteiro do arquivo de avaliações e o nome do usuário
                recomendarFilmes(usuerLogado.nome, avaliacoes);
                break;
            case 9: // saiu
                system("clear");
                // fechando arquivos para salvar
                printf("\nEncerrando e fechando arquivos...\n");
                fclose(filme);
                fclose(usuarios);
                fclose(avaliacoes);
                printf("Arquivos fechados. Ate mais!\n");
                printf("Saindo do programa...\n");
                exit(0);
                break;

            default:
                printf("\n \n                            [ERRO] - Digite algo valido, entre 1 e 7!! \n \n");
                break;
            }
        }
    }
    else
    {
        while (op != 5)
        {
            menuAdmin(&op);
            // limpa o buffer para a próxima leitura
            while ((getchar()) != '\n')
                ;

            switch (op)
            {
            case 1:
                // cadastrarFilme(filme);
                system("clear");
                cadastrarFilme(filme);

                break;
            case 2:
                // Cadastrar usuario
                system("clear");
                cadastrarUsuario(usuarios);

                break;
            case 3:
                /* 3- Estastísticas */
                system("clear");
                exibirTodasAvaliacoes(avaliacoes);

                break;
            case 4:
                // Ver usuarios cadastrados
                imprimirUsuarios(usuarios);
                break;
            case 5: // saiu
                system("clear");
                // fechando arquivos para salvar
                printf("\nEncerrando e fechando arquivos...\n");
                fclose(filme);
                fclose(usuarios);
                fclose(avaliacoes);
                printf("Arquivos fechados. Ate mais!\n");
                printf("Saindo do programa...\n");
                exit(0);
                break;

            default:
                printf("\n \n                            [ERRO] - Digite algo valido, entre 1 e 4!! \n \n");
                break;
            }
        }
    }

    return 0;
}

int menuPrincipal(int *op)
{
    // system("clear"); utilizar cls no windows

    // 38 espaços
    printf(ORANGE "                                      ⬤ " RESET); // ⬤ é Unicode, que é um padrão universal que define números (códigos) para representar todos os caracteres que existem
    printf(GREEN "⬤ " RESET);
    printf(BLUE "⬤ " RESET "\n");

    //  28 espaços
    printf("                 ---------- BEM VINDO AO LETTERBOXD LP1 ----------           \n");
    printf("                            1 - Ver/Avaliar filmes                     \n");
    printf("                            2 - Estastísticas                  \n");
    printf("                            3 - Ver Filmes avaliados                         \n");
    printf("                            4 - Ver melhores filmes                           \n");
    printf("                            5 - Ver piores filmes                       \n");
    printf("                            6 - Ver avaliações por usuário                       \n");
    printf("                            7 - Ver avaliações por filmes                       \n");
    printf("                            8 - Recomendações (IA k-NN) ✨             \n"); 
    printf("                            9 - Sair                           \n");
    printf("                            Escolha sua opção: ");
    scanf("%d", op);
    return *op;
}

int menuAdmin(int *op)
{
    // system("clear"); utilizar cls no windows

    // 38 espaços
    printf(ORANGE "                                      ⬤ " RESET); // ⬤ é Unicode, que é um padrão universal que define números (códigos) para representar todos os caracteres que existem
    printf(GREEN "⬤ " RESET);
    printf(BLUE "⬤ " RESET "\n");

    //  28 espaços
    printf("                 ---------- BEM VINDO AO LETTERBOXD LP1 ADMIN----------           \n");
    printf("                            1 - Cadastar novo filme                  \n");
    printf("                            2 - Cadastrar Usuario                  \n");
    printf("                            3 - Ver avaliações                 \n");
    printf("                            4 - Ver usuarios cadastrados                \n");
    printf("                            5 - Sair                           \n");
    printf("                            Escolha sua opção: ");
    scanf("%d", op);
    return *op;
}

