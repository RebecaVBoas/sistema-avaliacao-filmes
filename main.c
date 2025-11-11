#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char titulo[100];
    char usuario[25];
    int avaliacao;
    char comentario[80];

} Avaliar;

typedef struct
{
    char titulo[100];
    char resumo[500];
    int soma_notas;
    float avaliacao_media;
    int qtdAvalia;
    int qtdComent;

} Filmes;

typedef struct
{
    char nome[50];
    char senha[8];

} Usuarios;

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

// Remove o '\n' do final de uma string
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

FILE *abrirFilme()
{
    FILE *filmes;

    filmes = fopen("filmes.data", "a+b");

    if (filmes == NULL)
    {
        printf("ERRO, NÃO FOI POSÍVEL ABRIR O ARQUIVO FILMES");
        return NULL;
    }
    else
    {
        printf("\nARQUIVO FILME ABERTO \n");
        return filmes;
    }
}

FILE *abrirUsuarios()
{
    FILE *usuarios;

    usuarios = fopen("usuarios.data", "a+b");
    if (usuarios == NULL)
    {
        printf("\n ERRO NÃO FOI POSSIVEL ABRIR O ARQUIVO USUARIOS.DATA \n");
        return NULL;
    }
    else
    {
        printf("\nARQUIVO USUARIOS.DATA ABERTO\n");
        return usuarios;
    }
}

FILE *abrirAvaliacoes()
{
    FILE *avaliacoes;
    avaliacoes = fopen("avaliacoes.data", "a+b");

    if (avaliacoes == NULL)
    {
        printf("\nERRO. NÃO FOI POSSIVEL ABRIRO ARQUIVO AVALIACOES.DATA\n");
        return NULL;
    }
    else
    {
        printf("\nARQUIVO AVALIACOES.DATA ABERTO\n");
        return avaliacoes;
    }
}

void cadastrarFilme(FILE *arqfilme)
{

    Filmes filme;

    printf("\n----------------CADASTRANDO NOVO FILME----------------\n");

    printf("\nInforme o título do filme: \n");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    remover_quebra_linha(filme.titulo);

    printf("\nAdcione o resumo: \n");
    fgets(filme.resumo, sizeof(filme.resumo), stdin);
    remover_quebra_linha(filme.resumo);

    /*PENDENTE: IMPLEMENTAR NAS FUNÇÕES ENVOLVIDAS O CÁLCULO DESSES
    VALORES AUTOMATICAMENTE */

    filme.avaliacao_media = 0;

    filme.qtdAvalia = 0;

    filme.qtdComent = 0;

    fwrite(&filme, sizeof(filme), 1, arqfilme);
    printf("\nFilme cadastrado com sucesso!\n");
}

void cadastrarUsuario(FILE *arqusuario)
{

    Usuarios user;

    printf("\n----------------CADASTRANDO NOVO USUARIO----------------\n");

    printf("\nLogin:\n");
    fgets(user.nome, sizeof(user.nome), stdin);
    remover_quebra_linha(user.nome);

    printf("\nSenha:\n");
    fgets(user.senha, sizeof(user.senha), stdin);
    remover_quebra_linha(user.senha);

    fwrite(&user, sizeof(user), 1, arqusuario);
    printf("\nUsuario cadastrado com sucesso!\n");
}

int main()
{

    FILE *filme = abrirFilme();
    FILE *usuarios = abrirUsuarios();
    FILE *avaliacoes = abrirAvaliacoes();

    // TESTE

    Usuarios login;
    /*
        declarações das variaveis
    */
   
    // CADASTRAR 20 FILMES
    //  int i = 0;
    //  while (i < 20)
    //  {
    //      cadastrarFilme(filme);
    //      i++;
    //  }

    // incluir validações de usuario antes de ir para o menu principal

    menuPrincipal();

    // fechando arquivos para salvar
    printf("\nEncerrando e fechando arquivos...\n");
    fclose(filme);
    fclose(usuarios);
    fclose(avaliacoes);
    printf("Arquivos fechados. Ate mais!\n");

    return 0;
}