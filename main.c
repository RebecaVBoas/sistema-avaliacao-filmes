#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORANGE "\033[38;5;208m"
#define GREEN "\033[38;5;41m"
#define BLUE "\033[38;5;75m"
#define RESET "\033[0m"

/* modo de uso
    printf(ORANGE "Cor 1 (#ff8000)\n" RESET);
    printf(GREEN  "Cor 2 (#00e054)\n" RESET);
    printf(BLUE   "Cor 3 (#40bcf4)\n" RESET);
    return 0;
*/

/*-------------------MODULO DE FUNÇÕES DEFINIÇÃO DAS STRUCTS-------------------*/

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

/*------------------- MÓDULO DE LISTAGEM DAS FUNÇÕES -------------------*/

// Funções de Abertura de Arquivo
// MODIFICAR TIPO DO ARQUIVO E PARAMETRO DO fopen()
FILE *abrirFilme();
FILE *abrirUsuarios();
FILE *abrirAvaliacoes();

// Funções do Menu
int menuPrincipal(int *op);

// Funções de Filmes
void cadastrarFilme(FILE *arqfilme);
void listarFilmes(FILE *arqfilme);

// Funções de Usuários
void cadastrarUsuario(FILE *arqusuario);
void validarLogin(FILE *arqusuario);
void atualizarSenha(FILE *arqusuario, Usuarios user);
void imprimirUsuarios(FILE *arqusuario);

// Funções Utilitárias
void remover_quebra_linha(char *str);

int main()
{

    FILE *filme = abrirFilme();
    FILE *usuarios = abrirUsuarios();
    FILE *avaliacoes = abrirAvaliacoes();

    // TESTE

    // cadastrarUsuario(usuarios);
    // validarLogin(usuarios);
    // imprimirUsuarios(usuarios);

    /*
    CADASTRAR 20 FILMES
     int i = 0;
     while (i < 20)
     {
         cadastrarFilme(filme);
         i++;
     }

    incluir validações de usuario antes de ir para o menu principal

    menuPrincipal();
    cadastrarUsuario(usuarios);

    atualizarSenha();
    */

    int op = 0;
    while (op != 4)
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
            listarFilmes(filme);

            break;
        case 2:
            /* 2 - Estastísticas */
            break;
        case 3:

            /* 3 - ADM */

            break;
        case 4: // saiu
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
    printf("                            1 - Ver filmes                     \n");
    printf("                            2 - Estastísticas                  \n");
    printf("                            3 - ADM                            \n");
    printf("                            4 - Sair                           \n");
    printf("                            Escolha sua opção: ");
    scanf("%d", op);
    return *op;
}

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
    avaliacoes = fopen("avaliacoes.dat", "r+w");

    {
        avaliacoes = fopen("avaliacoes .dat", "w+b");

        if (avaliacoes == NULL)
        {
            printf("\n ERRO NÃO FOI POSSIVEL ABRIR O ARQUIVO USUARIOS.DATA \n");
            return NULL;
        }
    }

    printf("\nARQUIVO USUARIOS.DATA ABERTO\n");
    return avaliacoes;
}

/*-------------------MODULO DE FUNÇÕES DE FILMES-------------------*/

void cadastrarFilme(FILE *arqfilme)
{

    Filmes filme;
    fseek(arqfilme, 0, SEEK_END);

    /* ⬤ é Unicode, que é um padrão universal que define números (códigos)
    para representar todos os caracteres que existem */
    printf(ORANGE "                                     ⬤ " RESET);
    printf(GREEN "⬤ " RESET);
    printf(BLUE "⬤ " RESET "\n");
    printf("\n                 ---------- CADASTRANDO NOVO FILME ----------           \n");

    printf("\n                            Informe o título do filme: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    remover_quebra_linha(filme.titulo);

    printf("\n                            Adcione o resumo: ");
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
void listarFilmes(FILE *arqfilme)
{

    Filmes filme;

    if (arqfilme == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    // antes de ler os filmes, mova o ponteiro de leitura para o início do arquivo
    fseek(arqfilme, 0, SEEK_SET);

    printf(ORANGE "                                     ⬤ " RESET);
    printf(GREEN "⬤ " RESET);
    printf(BLUE "⬤ " RESET "\n");
    printf("\n                    ---------- FILMES CADASTRADOS ----------           \n");

    // Lê os filmes do arquivo enquanto não atingir o final
    while (fread(&filme, sizeof(filme), 1, arqfilme) == 1)
    {
        printf("\n                               Título: %s\n", filme.titulo);
        printf("                               Resumo: %s\n", filme.resumo);
        printf("                    ----------------------------------------\n");
    }

    if (ferror(arqfilme))
    {
        printf("Erro ao ler o arquivo.\n");
    }
}

/*-------------------MODULO DE FUNÇÕES DE USUARIOS-------------------*/

void cadastrarUsuario(FILE *arqusuario)
{

    Usuarios user;

    printf("\n                 ---------- CADASTRANDO NOVO USUARIO ----------           \n");

    printf("\n                            Login: ");
    fgets(user.nome, sizeof(user.nome), stdin);
    remover_quebra_linha(user.nome);

    printf("\n                            Senha: ");
    fgets(user.senha, sizeof(user.senha), stdin);
    remover_quebra_linha(user.senha);

    fwrite(&user, sizeof(user), 1, arqusuario);
    printf("\n                            Usuario cadastrado com sucesso!                            \n");
}

void validarLogin(FILE *arqusuario)
{

    Usuarios arquser;
    Usuarios login;

    printf("\n                 ---------- LOGIN ----------           \n");

    printf("                            LOGIN: ");
    fgets(login.nome, sizeof(login.nome), stdin);
    remover_quebra_linha(login.nome);

    printf("\n                            SENHA: ");
    fgets(login.senha, sizeof(login.senha), stdin);
    remover_quebra_linha(login.senha);

    while (fread(&arquser, sizeof(arquser), 1, arqusuario) == 1)
    {
        if ((strcmp(arquser.nome, login.nome) == 0) && (strcmp(arquser.senha, login.senha) == 0))
        {
            if (arquser.nome != "admin")
            {
                // IMPLEMENTAR CHAMADA PARA MENU DE USUARUO COMUM
                printf("VALIDADO COMUM");
                return;
            }
            else
            {
                // IMPLEMENTAR CHAMADA PARA MENU DE ADMINISTRADOR
                printf("VALIDADO ADMIN");
                return;
            }
        }
        else
        {
            printf("\nUsuario não encontrado\n");
        }
    }

    printf("\nUsuario não encontrado\n");
}

void atualizarSenha(FILE *arqusuario, Usuarios user)
{

    Usuarios arqUser;

    for (;;)
    {
        fread(&arqUser, sizeof(arqUser), 1, arqusuario);

        if (strcmp(arqUser.nome, user.nome) == 0)
        {
            printf("Informe a nova senha");
            fgets(arqUser.senha, sizeof(arqUser.senha), stdin);
            remover_quebra_linha(arqUser.senha);
            fseek(arqusuario, -sizeof(arqUser), SEEK_CUR);
            fwrite(&arqUser, sizeof(arqUser), 1, arqusuario);
            break;
        }

        // Verificar primeiro
        if (feof(arqusuario))
            break;
    }
}

/* NOVA FUNÇÃO: LÊ TODOS OS USUÁRIOS DO ARQUIVO E IMPRIME */
void imprimirUsuarios(FILE *arqusuario)
{
    Usuarios user;
    int contador = 0;

    // volta o ponteiro do arquivo para o início
    rewind(arqusuario);

    printf("\n---------- LISTA DE USUÁRIOS CADASTRADOS ----------\n");

    while (fread(&user, sizeof(user), 1, arqusuario))
    {
        printf("Usuário %d:\n", ++contador);
        printf("   Nome:  %s\n", user.nome);
        printf("   Senha: %s\n\n", user.senha);
    }

    if (contador == 0)
        printf("Nenhum usuário cadastrado ainda.\n");
}

/*-------------------MODULO DE FUNÇÕES DE AVALIAÇÕES-------------------*/

/*-------------------MODULO DE FUNÇÕES GÊNERICAS-------------------*/

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