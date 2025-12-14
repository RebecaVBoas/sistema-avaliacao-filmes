#include <stdio.h>
#include <string.h>
#include "utils.h" 

/*-------------------MODULO DE FUNÇÕES DE ABERTURA DOS ARQUIVOS-------------------*/

FILE *abrirFilme()
{
    FILE *filmes;

    filmes = fopen("filmes.dat", "r+b");

    if (filmes == NULL)
    {
        filmes = fopen("filmes.dat", "w+b");

        if (filmes == NULL)
        {
            printf("ERRO, NÃO FOI POSÍVEL ABRIR O ARQUIVO FILMES");
            return NULL;
        }
    }

    printf("\nARQUIVO FILME ABERTO \n");
    return filmes;
}

FILE *abrirUsuarios()
{
    FILE *usuarios;

    usuarios = fopen("usuarios.dat", "r+b");
    if (usuarios == NULL)
    {
        usuarios = fopen("usuarios.dat", "w+b");

        if (usuarios == NULL)
        {
            printf("\n ERRO NÃO FOI POSSIVEL ABRIR O ARQUIVO USUARIOS.DATA \n");
            return NULL;
        }
    }

    printf("\nARQUIVO USUARIOS.DATA ABERTO\n");
    return usuarios;
}

FILE *abrirAvaliacoes()
{
    FILE *avaliacoes;
    avaliacoes = fopen("avaliacoes.dat", "r+b");

    {
        // avaliacoes = fopen("avaliacoes.dat", "w+b");

        if (avaliacoes == NULL)
        {
            printf("\n ERRO NÃO FOI POSSIVEL ABRIR O ARQUIVO AVALIACOES.DATA \n");
            return NULL;
        }
    }

    printf("\nARQUIVO AVALIACOES.DATA ABERTO\n");
    return avaliacoes;
}


// Implementação da função que remove o \n do fgets
void remover_quebra_linha(char *str)
{
    int i = 0;

    // Avança até o final da string
    // O loop para quando str[i] for o '\0' (terminador)
    while (str[i] != '\0')
    {
        i++;
    }

    /* agora, 'i' é o índice do '\0' (que é o comprimento da string)
    verifica se a string não está vazia (i > 0) e se o caractere ANTERIOR (i - 1) é o '\n'
    */
    if (i > 0 && str[i - 1] == '\n')
    {

        // se for, substitui o '\n' por um '\0', "cortando" a string um caractere antes
        str[i - 1] = '\0';
    }
}

