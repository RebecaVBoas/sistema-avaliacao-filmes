#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILMES_POR_PAGINA 10 // paginação filmes

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
int menuAdmin(int *op);

// Funções de Filmes
void cadastrarFilme(FILE *arqfilme);
void listar_avaliarFilmes(FILE *arqfilme, FILE *arqavaliacao, char *usuario_logado);
long contarTotalFilmes(FILE *arqfilme);
void pioresfilmes(FILE *arqfilme);
void melhoresfilmes(FILE *arqfilme);

// Funções de Usuários
void cadastrarUsuario(FILE *arqusuario);
Usuarios validarLogin(FILE *arqusuario);
void atualizarSenha(FILE *arqusuario, Usuarios user);
void imprimirUsuarios(FILE *arqusuario);

// Funções de Avaliação

void adicionaravaliação(FILE *arqavaliacoes);
void exibirAvaliacoesPorUsuario(char user[], FILE *arqavaliacoes);
void exibirAvaliacoesPorFilme(char filme[], FILE *arqavaliacoes);
void exibirFilmesAvaliadosPorUsuario(char user[], FILE *arqavaliacoes);

// Funções Utilitárias
void remover_quebra_linha(char *str);

int main()
{

    FILE *filme = abrirFilme();
    FILE *usuarios = abrirUsuarios();
    FILE *avaliacoes = abrirAvaliacoes();

    long contarTotalFilmes(FILE * arqfilme);
    /*
    CADASTRAR 20 FILMES
     int i = 0;
     while (i < 20)
     {
         cadastrarFilme(filme);
         i++;
     }

    incluir validações de usuario antes de ir para o menu principal

    */

    Usuarios usuerLogado = validarLogin(usuarios);
    int op = 0;

    // VARIAVEIS CASE 6
    char userPesquisa[20];

    // VARIAVEIS CASE 7
    char filmePesquisa[100];

        if (strcmp(usuerLogado.nome, "nullLogin"))
    {
        printf("Usuario não encontrado");
    }

    else if (strcmp(usuerLogado.nome, "admin") != 0)
    {
        // menuAdmin;

        while (op != 6)
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

                remover_quebra_linha;

                exibirAvaliacoesPorUsuario(userPesquisa, avaliacoes);
                break;
            case 7:
                // ver avaliações por filme
                printf("Informe o nome do filme que deseja pesquisar: ");
                fgets(filmePesquisa, sizeof(filmePesquisa), stdin);

                remover_quebra_linha;

                exibirAvaliacoesPorUsuario(filmePesquisa, avaliacoes);
                break;
            case 8: // saiu
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
        while (op != 7)
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
                listar_avaliarFilmes(filme, avaliacoes, usuerLogado.nome);

                break;
            case 2:
                /* 2 - Estastísticas */
                break;
            case 3:

                break;
            case 7: // saiu
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
    printf("                            8 - Sair                           \n");
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
    printf("                            3 - Sair                           \n");
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
        avaliacoes = fopen("avaliacoes.dat", "w+b");

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
    filme.soma_notas = 0;
    filme.qtdAvalia = 0;
    filme.qtdComent = 0;

    fwrite(&filme, sizeof(filme), 1, arqfilme);
    printf("\nFilme cadastrado com sucesso!\n");
}

void listar_avaliarFilmes(FILE *arqfilme, FILE *arqavaliacoes, char *usuario_logado)
{

    Filmes buffer_filmes[FILMES_POR_PAGINA];

    long total_filmes;
    long total_paginas;
    char coment;

    int pagina_atual = 1;

    size_t tamanho_registro = sizeof(Filmes); // size_t tipo de dado sem sinal que recebe o tamanho em bytes da struct Filmes
    char opcao_nav;

    if (arqfilme == NULL)
    {
        printf("Erro: Arquivo de filmes não está aberto.\n");
    }

    // Calcula o total de filmes e o total de páginas
    total_filmes = contarTotalFilmes(arqfilme);
    if (total_filmes == 0)
    {
        printf("\n                            [INFO] - Nenhum filme cadastrado.\n");
    }

    // Calcula o total de páginas arredondando para cima.
    /*
        A expressão (total_filmes + FILMES_POR_PAGINA - 1) garante que,
        mesmo que haja filmes "sobrando" na última página, a divisão inteira
        ainda resultará em mais uma página necessária.
        ex: 31 + 9 = 40 | 31 filmes
        40 / 10 = 4 → correto (3 páginas não bastam)

    */
    total_paginas = (total_filmes + FILMES_POR_PAGINA - 1) / FILMES_POR_PAGINA;

    // loop principal de navegação do menu
    do
    {
        system("clear");

        // 1. Calcular o OFFSET (posição inicial em bytes)
        // (Página - 1) * Tamanho da Página * Tamanho do Registro
        long offset = (long)(pagina_atual - 1) * FILMES_POR_PAGINA * tamanho_registro;

        // 2. Posicionar o ponteiro do arquivo para a página correta
        fseek(arqfilme, offset, SEEK_SET); // fseek(arquivo_manipular, bytes_paraoponteiropular, define_pontodepartida)

        /* 3. Ler o bloco de filmes
        fread() -> retorna o número total de elementos lidos com sucesso do fluxo de arquivo, e sua tipagem em C é size_t
        */

        size_t filmes_lidos = fread(
            buffer_filmes,
            tamanho_registro,
            FILMES_POR_PAGINA,
            arqfilme);

        // Exibição do Cabeçalho
        printf(ORANGE "                                ⬤ " RESET);
        printf(GREEN "⬤ " RESET);
        printf(BLUE "⬤ " RESET "\n");
        printf("\n                 ---------- LISTA DE FILMES ----------           \n");
        printf(BLUE "Página %d de %ld (Total de %ld filmes)\n" RESET, pagina_atual, total_paginas, total_filmes);
        printf("--------------------------------------------------------------------\n");

        // Exibição dos Filmes da Página
        for (size_t i = 0; i < filmes_lidos; i++)
        {
            // Calcula o número de exibição do filme na lista total
            long indice_global = offset / tamanho_registro + i + 1;

            printf(GREEN "[%03ld] Título: %s\n" RESET, indice_global, buffer_filmes[i].titulo);
            printf("      Resumo: %s\n", buffer_filmes[i].resumo);
            printf("      Avaliação Média: %.1f\n", buffer_filmes[i].avaliacao_media);
            printf("--------------------------------------------------------------------\n");
        }

        // Navegação Atualizada
        printf("\nNavegação: (A)nterior | (P)róximo | (G)Ir Pag | (E)Avaliar | (S)air: ");
        scanf(" %c", &opcao_nav);
        while (getchar() != '\n')
            ; // Limpa buffer
        opcao_nav = toupper(opcao_nav);

        if (opcao_nav == 'P')
        {
            if (pagina_atual < total_paginas)
            {
                pagina_atual++;
            }
            else
            {
                printf(ORANGE "\n                                [INFO] - Você está na última página.\n" RESET);
                printf("Aperte ENTER para continuar...");
                getchar(); // espera o usuário pressionar ENTER
            }
        }
        else if (opcao_nav == 'A')
        {
            if (pagina_atual > 1)
            {
                pagina_atual--;
            }
            else
            {
                printf(ORANGE "\n                                [INFO] - Você está na primeira página.\n" RESET);
                printf("Aperte ENTER para continuar...");
                getchar(); // espera o usuário pressionar ENTER
            }
        }
        else if (opcao_nav == 'G')
        {
            int nova_pagina;
            printf("Ir para a página (1 a %ld): ", total_paginas);
            scanf("%d", &nova_pagina);
            while (getchar() != '\n')
                ; // Limpa o buffer após o scanf

            if (nova_pagina >= 1 && nova_pagina <= total_paginas)
            {
                pagina_atual = nova_pagina;
            }
            else if (nova_pagina < 1 || nova_pagina > total_paginas)
            {
                printf(ORANGE "\n                                [ERRO] - Número de página inválido.\n" RESET);
                printf("Aperte ENTER para continuar...");
                getchar(); // espera o usuário pressionar ENTER
            }
        }
        if (opcao_nav == 'E')
        {
            long id_escolhido;
            printf("\nInforme o ID do filme que deseja avaliar (ex: 1, 2...): ");
            scanf("%ld", &id_escolhido);
            while (getchar() != '\n')
                ;

            // Verifica se o ID é válido
            if (id_escolhido > 0 && id_escolhido <= total_filmes)
            {

                Filmes filme_edit;
                Avaliar nova_avaliacao;

                // Logica para achar o filme no arquivo
                // O ID 1 está no byte 0. O ID 2 está no byte sizeof(Filmes)...

                long offset_filme = (id_escolhido - 1) * sizeof(Filmes);

                fseek(arqfilme, offset_filme, SEEK_SET);
                fread(&filme_edit, sizeof(Filmes), 1, arqfilme);

                printf(BLUE "\n--- Avaliando: %s ---\n" RESET, filme_edit.titulo);

                // 2. PEDIR A NOTA E COMENTÁRIO
                int nota_temp;
                do
                {
                    printf("Nota (0 a 5[⭐⭐⭐⭐⭐]): ");
                    scanf("%d", &nota_temp);
                } while (nota_temp < 0 || nota_temp > 5);
                while (getchar() != '\n')
                    ;

                do
                {
                    printf("Você quer adicionar um comentario? (S) -> sim || (N) -> nao\n");
                    scanf("%c", &coment);
                    while (getchar() != '\n')
                        ;
                    coment = toupper(coment);
                } while (coment != 'S' && coment != 'N');

                strcpy(nova_avaliacao.comentario, "");
                if (coment == 'S')
                {
                    printf("Comentário curto: ");
                    fgets(nova_avaliacao.comentario, sizeof(nova_avaliacao.comentario), stdin);
                    remover_quebra_linha(nova_avaliacao.comentario);
                }
                else
                {
                    strcpy(nova_avaliacao.comentario, "Sem comentário");
                }

                // 3. RECALCULAR A MEDIA DOS FILMES AUTOMATICAMENTE

                filme_edit.soma_notas += nota_temp; // somatorio de notas totais
                filme_edit.qtdAvalia++;             // quantidade de avaliação

                // Proteção contra divisão por zero e cálculo da média
                if (filme_edit.qtdAvalia > 0)
                {
                    filme_edit.avaliacao_media = (float)filme_edit.soma_notas / filme_edit.qtdAvalia;
                }

                // 4. SALVAR ALTERAÇÃO NO ARQUIVO DE FILMES (Sobrescrever)

                fseek(arqfilme, offset_filme, SEEK_SET); // Volta para o início do registro
                fwrite(&filme_edit, sizeof(Filmes), 1, arqfilme);

                // Força a gravação no disco agora
                fflush(arqfilme);

                // 5. REGISTRAR O LOG DA AVALIAÇÃO (Arquivo de Avaliações)
                strcpy(nova_avaliacao.titulo, filme_edit.titulo);
                strcpy(nova_avaliacao.usuario, usuario_logado);
                nova_avaliacao.avaliacao = nota_temp;

                fseek(arqavaliacoes, 0, SEEK_END); // Vai para o fim
                fwrite(&nova_avaliacao, sizeof(Avaliar), 1, arqavaliacoes);
                fflush(arqavaliacoes); // força a gravar logo

                printf(GREEN "\nAvaliação registrada com sucesso!\n" RESET);
                printf("Pressione ENTER para continuar...");
                getchar();
            }
            else
            {
                printf(ORANGE "ID Inválido!\n" RESET);
                getchar();
            }
        }

    } while (opcao_nav != 'S');

    printf("\nRetornando ao menu principal...\n");
}

long contarTotalFilmes(FILE *arqfilme)
{
    if (arqfilme == NULL)
    {
        return 0;
    }

    // 1. Vai para o fim do arquivo
    fseek(arqfilme, 0, SEEK_END);

    // 2. Obtém a posição atual (tamanho total do arquivo em bytes)
    long tamanho_bytes = ftell(arqfilme);

    // 3. Volta o ponteiro para o início
    fseek(arqfilme, 0, SEEK_SET);

    // 4. Calcula o número de filmes (registros)
    // Se o tamanho for 0, retorna 0. Senão, divide pelo tamanho da struct Filme.
    if (tamanho_bytes == 0)
    {
        return 0;
    }

    // Garante a divisão correta pelo tamanho do registro
    return tamanho_bytes / sizeof(Filmes);
}

void pioresfilmes(FILE *arqfilme)
{
    Filmes filme_lido;
    Filmes piores[5];
    int i, j;

    // 1. Inicializa o vetor com notas altas impossíveis

    for (i = 0; i < 5; i++)
    {
        piores[i].avaliacao_media = 100.0;
        strcpy(piores[i].titulo, "---"); // Limpa o nome visualmente
    }

    fseek(arqfilme, 0, SEEK_SET); // Volta ao início do arquivo

    // 2. Lê filme por filme
    while (fread(&filme_lido, sizeof(Filmes), 1, arqfilme) == 1)
    {
        // Se a nota do filme lido for MENOR que a do 5º lugar (o menos pior dos piores)
        if (filme_lido.avaliacao_media < piores[4].avaliacao_media)
        {
            // Substitui o último da lista pelo novo filme
            piores[4] = filme_lido;

            // 3. Ordena o vetor (Bubble Sort) para que o pior nota fique em [0]

            for (i = 0; i < 5; i++)
            {
                for (j = i + 1; j < 5; j++)
                {
                    if (piores[i].avaliacao_media > piores[j].avaliacao_media)
                    {
                        Filmes temp = piores[i];
                        piores[i] = piores[j];
                        piores[j] = temp;
                    }
                }
            }
        }
    }
    // 4. Exibição Bonita
    printf(ORANGE "\n                     ========== TOP 5 PIORES FILMES ===========\n" RESET);

    int encontrou_algum = 0;
    for (i = 0; i < 5; i++)
    {
        // Só imprime se a nota for válida (menor que 100)
        if (piores[i].avaliacao_media < 100.0)
        {
            printf(BLUE "\n                     [%dº Lugar]\n" RESET, i + 1);
            printf("                     Título: %s\n", piores[i].titulo);
            printf("                     Média: %.1f\n", piores[i].avaliacao_media);
            encontrou_algum = 1;
        }
    }

    if (!encontrou_algum)
    {
        printf("\nNenhum filme cadastrado ou avaliado ainda.\n");
    }

    printf("\n                     =========================================\n");
    printf("Pressione ENTER para voltar...");
    getchar();
}

void melhoresfilmes(FILE *arqfilme)
{
    Filmes filme_lido;
    Filmes melhores[5];
    int i, j;

    // 1. Inicializa o vetor com notas altas impossíveis

    for (i = 0; i < 5; i++)
    {
        melhores[i].avaliacao_media = 0.0;
        strcpy(melhores[i].titulo, "---"); // Limpa o nome visualmente
    }

    fseek(arqfilme, 0, SEEK_SET); // Volta ao início do arquivo

    // 2. Lê filme por filme
    while (fread(&filme_lido, sizeof(Filmes), 1, arqfilme) == 1)
    {
        // Se a nota do filme lido for maior que a do 5º lugar 
        if (filme_lido.avaliacao_media > melhores[4].avaliacao_media)
        {
            // Substitui o último da lista pelo novo filme
            melhores[4] = filme_lido;

            // 3. Ordena o vetor (Bubble Sort) para que o pior nota fique em [0]

            for (i = 0; i < 5; i++)
            {
                for (j = i + 1; j < 5; j++)
                {
                    if (melhores[i].avaliacao_media < melhores[j].avaliacao_media)
                    {
                        Filmes temp = melhores[i];
                        melhores[i] = melhores[j];
                        melhores[j] = temp;
                    }
                }
            }
        }
    }
    // 4. Exibição Bonita
    printf(ORANGE "\n                     ========== TOP 5 PIORES FILMES ===========\n" RESET);

    int encontrou_algum = 0;
    for (i = 0; i < 5; i++)
    {
        // Só imprime se a nota for válida (menor que 100)
        if (melhores[i].avaliacao_media < 100.0)
        {
            printf(BLUE "\n                     [%dº Lugar]\n" RESET, i + 1);
            printf("                     Título: %s\n", melhores[i].titulo);
            printf("                     Média: %.1f\n", melhores[i].avaliacao_media);
            encontrou_algum = 1;
        }
    }

    if (!encontrou_algum)
    {
        printf("\nNenhum filme cadastrado ou avaliado ainda.\n");
    }

    printf("\n                     =========================================\n");
    printf("Pressione ENTER para voltar...");
    getchar();
}

/*-------------------MODULO DE FUNÇÕES DE USUARIOS-------------------*/

void cadastrarUsuario(FILE *arqusuario)
{

    Usuarios user, arquser;

    printf("\n                 ---------- CADASTRANDO NOVO USUARIO ----------           \n");

    printf("\n                            Login: ");
    fgets(user.nome, sizeof(user.nome), stdin);
    remover_quebra_linha(user.nome);

    printf("\n                            Senha: ");
    fgets(user.senha, sizeof(user.senha), stdin);
    remover_quebra_linha(user.senha);

    fseek(arqusuario, 0, SEEK_SET);

    while (fread(&arquser, sizeof(arquser), 1, arqusuario) == 1)
    {
        if (strcmp(arquser.nome, user.nome) == 0)
        {
            printf("\n                            nome indisponivel!                            \n");
        }
    }

    fseek(arqusuario, 0, SEEK_END);
    fwrite(&user, sizeof(user), 1, arqusuario);
    printf("\n                            Usuario cadastrado com sucesso!                            \n");
}

Usuarios validarLogin(FILE *arqusuario)
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
            printf("\nusuario encontrado\n");
            return arquser;
        }
    }

    Usuarios nullLogin;
    strcpy(nullLogin.nome, "nullLogin");

    printf("\nUsuario não encontrado\n");
    return nullLogin;
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

void exibirAvaliacoesPorUsuario(char user[], FILE *arqavaliacoes)
{

    fseek(arqavaliacoes, 0, SEEK_SET);

    int qtAvaliacaoPorUser = 0;

    Avaliar avUser;
    while (fread(&avUser, sizeof(Avaliar), 1, arqavaliacoes) != 1)
    {
        if (strcmp(avUser.usuario, user) == 0)
        {
            printf("--------------AVALIAÇÃO %d--------------", qtAvaliacaoPorUser + 1);
            printf("\nFILME: %s\n", avUser.titulo);
            printf("\nUSUARIOS: %s\n", avUser.usuario);
            printf("\nCOMENTARIO: %s", avUser.comentario);
            printf("\nNOTA: %d\n: ", avUser.avaliacao);

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

    fseek(arqavaliacoes, 0, SEEK_SET);

    int qtAvaliacaoPorFilme = 0;

    Avaliar avFilme;
    while (fread(&avFilme, sizeof(Avaliar), 1, arqavaliacoes) != 1)
    {
        if (strcmp(avFilme.usuario, filme) == 0)
        {
            printf("--------------AVALIAÇÃO %d--------------", qtAvaliacaoPorFilme + 1);
            printf("\nFILME: %s\n", avFilme.titulo);
            printf("\nUSUARIOS: %s\n", avFilme.usuario);
            printf("\nCOMENTARIO: %s", avFilme.comentario);
            printf("\nNOTA: %d\n: ", avFilme.avaliacao);

            qtAvaliacaoPorFilme++;
        }
    }

    if (qtAvaliacaoPorFilme == 0)
    {
        printf("\nNão foram encontradas avaliações desse filmes\n");
    }

    void exibirFilmesAvaliadosPorUsuario(char user[], FILE *arqavaliacoes)
    {
        fseek(arqavaliacoes, 0, SEEK_SET);

        int qtAvaliacaoPorUser = 0;

        Avaliar avUser;
        while (fread(&avUser, sizeof(Avaliar), 1, arqavaliacoes) != 1)
        {
            if (strcmp(avUser.usuario, user) == 0)
            {
                printf("--------------AVALIAÇÃO %d--------------", qtAvaliacaoPorUser + 1);
                printf("\nFILME: %s\n", avUser.titulo);
                qtAvaliacaoPorUser++;
            }
        }

        if (qtAvaliacaoPorUser == 0)
        {
            printf("\nNão foram encontradas avaliações desse usuario\n");
        }
    }
}

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