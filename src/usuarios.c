#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- INCLUDES LOCAIS ---
#include "usuarios.h" // Traz a struct Usuarios
#include "utils.h"    // Traz as Cores e remover_quebra_linha

void cadastrarUsuario(FILE *arqusuario)
{
    Usuarios user, arquser;

    // Garante que o arquivo está aberto
    if (arqusuario == NULL)
    {
        printf(ORANGE "\n[ERRO] Arquivo de usuários não está aberto!\n" RESET);
        return;
    }

    printf(ORANGE "                                     ⬤ " RESET);
    printf(GREEN "⬤ " RESET);
    printf(BLUE "⬤ " RESET "\n");
    printf("\n                 ---------- CADASTRANDO NOVO USUARIO ----------           \n");

    printf("\n                            Login: ");
    fgets(user.nome, sizeof(user.nome), stdin);
    remover_quebra_linha(user.nome);

    printf("\n                            Senha (max 8 chars): ");
    fgets(user.senha, sizeof(user.senha), stdin);
    remover_quebra_linha(user.senha);

    // --- VERIFICAÇÃO DE DUPLICIDADE ---
    fseek(arqusuario, 0, SEEK_SET); // Vai para o início
    int existe = 0;

    while (fread(&arquser, sizeof(arquser), 1, arqusuario) == 1)
    {
        if (strcmp(arquser.nome, user.nome) == 0)
        {
            printf(ORANGE "\n                            [ERRO] Nome indisponivel!                            \n" RESET);
            existe = 1;
            break;
        }
    }

    if (!existe)
    {
        fseek(arqusuario, 0, SEEK_END); // Vai para o fim para gravar
        fwrite(&user, sizeof(user), 1, arqusuario);
        fflush(arqusuario); // Garante a gravação
        printf(GREEN "\n                            Usuario cadastrado com sucesso!                            \n" RESET);
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

Usuarios validarLogin(FILE *arqusuario)
{
    Usuarios arquser;
    Usuarios login;
    char opcao_menu; // Variável para armazenar a escolha do usuário ('s' ou 'n')

    if (arqusuario == NULL)
    {
        printf("\nNão foi possivel abrir o arquivo!\n");
        exit(1);
    }

    // Loop infinito: permite tentativas de login até sucesso ou saída explícita
    while (1)
    {
        system("clear"); // Limpa a tela a cada nova tentativa

        printf(ORANGE "                                     ⬤ " RESET);
        printf(GREEN "⬤ " RESET);
        printf(BLUE "⬤ " RESET "\n");
        printf("\n                          ---------- LOGIN ----------           \n");

        // 1. Coleta de credenciais
        printf("                                     LOGIN: ");
        // Se estiver em Linux/macOS, pode ser omitido, mas é mais seguro.
        fflush(stdin);
        fgets(login.nome, sizeof(login.nome), stdin);
        remover_quebra_linha(login.nome);

        printf("                                     SENHA: ");
        fgets(login.senha, sizeof(login.senha), stdin);
        remover_quebra_linha(login.senha);

        // 2. Busca no arquivo
        fseek(arqusuario, 0, SEEK_SET);

        while (fread(&arquser, sizeof(arquser), 1, arqusuario) == 1)
        {
            // Compara Nome E Senha
            if ((strcmp(arquser.nome, login.nome) == 0) && (strcmp(arquser.senha, login.senha) == 0))
            {
                printf(GREEN "\nLogin realizado com sucesso!\n" RESET);
                return arquser; // Sai da função retornando o usuário logado
            }
        }

        // 3. Se a busca falhou: Oferecer nova tentativa ou sair
        printf(ORANGE "\nUsuário ou senha incorretos.\n" RESET);

        do
        {
            printf("\n(s) Nova tentativa de login | (n) Sair do programa\n");
            printf("Opção: ");

            // Leitura de um único caractere e limpeza do buffer
            if (scanf(" %c", &opcao_menu) != 1 )
            {
               
            }
            while (getchar() != '\n')
                ; // Limpa o buffer de entrada

            opcao_menu = tolower(opcao_menu); // Padroniza para 's' ou 'n'

        } while (opcao_menu != 's' && opcao_menu != 'n'); // Repete até que 's' ou 'n' seja digitado

        if (opcao_menu == 'n')
        {
            printf("Encerrando o login...\n");
            exit(1); // FALHA: Retorna o usuário nulo, permitindo que a main lide com a saída ou prosseguimento.
        }
        // Se for 's', o loop 'while(1)' recomeça para uma nova tentativa de login.
    }
}

void atualizarSenha(FILE *arqusuario, Usuarios user)
{
    Usuarios arqUser;
    int encontrado = 0;

    if (arqusuario == NULL)
        return;

    fseek(arqusuario, 0, SEEK_SET);

    while (fread(&arqUser, sizeof(arqUser), 1, arqusuario) == 1)
    {
        if (strcmp(arqUser.nome, user.nome) == 0)
        {
            printf(BLUE "\nAlterando senha para: %s\n" RESET, user.nome);
            printf("Informe a nova senha: ");
            fgets(arqUser.senha, sizeof(arqUser.senha), stdin);
            remover_quebra_linha(arqUser.senha);

            // Volta o ponteiro para o início desse registro para sobrescrever
            fseek(arqusuario, -((long)sizeof(arqUser)), SEEK_CUR);

            fwrite(&arqUser, sizeof(arqUser), 1, arqusuario);
            fflush(arqusuario);
            encontrado = 1;
            printf(GREEN "Senha atualizada com sucesso!\n" RESET);
            break;
        }
    }

    if (!encontrado)
    {
        printf(ORANGE "Erro: Usuário não encontrado no arquivo.\n" RESET);
    }
    getchar();
}

void imprimirUsuarios(FILE *arqusuario)
{
    Usuarios user;
    int contador = 0;

    if (arqusuario == NULL)
        return;

    // volta o ponteiro do arquivo para o início
    fseek(arqusuario, 0, SEEK_SET);

    printf("\n---------- LISTA DE USUÁRIOS CADASTRADOS ----------\n");

    while (fread(&user, sizeof(user), 1, arqusuario))
    {
        printf("Usuário %d:\n", ++contador);
        printf("   Nome:  %s\n", user.nome);
        // printf("   Senha: %s\n\n", user.senha); // Opcional: mostrar senha
        printf("---------------------------------------------------\n");
    }

    if (contador == 0)
        printf("Nenhum usuário cadastrado ainda.\n");

    printf("\nPressione ENTER para voltar...");
    getchar();
}