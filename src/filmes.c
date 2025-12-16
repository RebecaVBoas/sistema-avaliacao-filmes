#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- INCLUDES LOCAIS ---
#include "filmes.h"     
#include "avaliacoes.h" 
#include "utils.h"     

#define FILMES_POR_PAGINA 10 

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


    // Validação para título não vazio
    do {
        printf("\n                            Informe o título do filme: ");
        fgets(filme.titulo, sizeof(filme.titulo), stdin);
        remover_quebra_linha(filme.titulo);
        if (strlen(filme.titulo) == 0) {
            printf("O título não pode ser vazio.\n");
        }

        int existe = buscarFilmePorTitulo(arqfilme, filme.titulo);
        if (existe) {
            printf("Um filme com esse título já está cadastrado. Tente novamente com outro título.\n");
            filme.titulo[0] = '\0'; // zera o título para continuar o loop
        }

    } while (strlen(filme.titulo) == 0);

    // Validação para resumo não vazio
    do {
        printf("\n                            Adicione o resumo: ");
        fgets(filme.resumo, sizeof(filme.resumo), stdin);
        remover_quebra_linha(filme.resumo);
        if (strlen(filme.resumo) == 0) {
            printf("O resumo não pode ser vazio.\n");
        }
    } while (strlen(filme.resumo) == 0);

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
                printf("                     Aperte ENTER para continuar...");
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
                printf("                     Aperte ENTER para continuar...");
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
                printf("                     Aperte ENTER para continuar...");
                getchar(); // espera o usuário pressionar ENTER
            }
        }
        if (opcao_nav == 'E')
        {
            Avaliar leitura_temp;
            int ja_avaliou = 0;
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

                // Verifica se já existe avaliação desse usuário para esse filme
                rewind(arqavaliacoes);
                long pos_avaliacao = -1;
                int encontrou = 0;
                while (fread(&leitura_temp, sizeof(Avaliar), 1, arqavaliacoes) == 1) {
                    if (strcmp(leitura_temp.usuario, usuario_logado) == 0 && strcmp(leitura_temp.titulo, filme_edit.titulo) == 0) {
                        encontrou = 1;
                        pos_avaliacao = ftell(arqavaliacoes) - sizeof(Avaliar);
                        break;
                    }
                }

                if (encontrou) {
                    printf(ORANGE "\nVocê já avaliou este filme. Deseja substituir a avaliação? (S/N): " RESET);
                    char resp;
                    scanf(" %c", &resp);
                    while (getchar() != '\n');
                    resp = toupper(resp);
                    if (resp != 'S') {
                        printf("Operação cancelada.\n");
                        break;
                    }
                }

                printf(BLUE "\n--- Avaliando: %s ---\n" RESET, filme_edit.titulo);

                // 2. PEDIR A NOTA E COMENTÁRIO
                int nota_temp;
                char buffer[16];

                do {
                    printf("Nota (0 a 5[⭐⭐⭐⭐⭐]): ");
                    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                        printf("Entrada inválida. Tente novamente.\n");
                        nota_temp = -1;
                    } else if (sscanf(buffer, "%d", &nota_temp) != 1) {
                        printf("Entrada inválida. Tente novamente.\n");
                        nota_temp = -1;
                    }
                } while (nota_temp < 0 || nota_temp > 5);

                do
                {
                    printf("Você quer adicionar um comentario? (S) -> sim || (N) -> nao\n");
                    scanf("%c", &coment);
                    while (getchar() != '\n')                      ;
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

                // Atualiza média do filme
                if (!encontrou) {
                    filme_edit.soma_notas += nota_temp;
                    filme_edit.qtdAvalia++;
                } else {
                    // Se for substituição, não altera qtdAvalia, apenas ajusta soma_notas
                    // Para isso, precisamos saber a nota anterior
                    filme_edit.soma_notas = filme_edit.soma_notas - leitura_temp.avaliacao + nota_temp;
                }
                if (filme_edit.qtdAvalia > 0) {
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

                if (encontrou && pos_avaliacao != -1) {
                    // Sobrescreve avaliação existente
                    fseek(arqavaliacoes, pos_avaliacao, SEEK_SET);
                    fwrite(&nova_avaliacao, sizeof(Avaliar), 1, arqavaliacoes);
                } else {
                    // Adiciona nova avaliação
                    fseek(arqavaliacoes, 0, SEEK_END);
                    fwrite(&nova_avaliacao, sizeof(Avaliar), 1, arqavaliacoes);
                }
                fflush(arqavaliacoes);

                printf(GREEN "\nAvaliação registrada com sucesso!\n" RESET);
                printf("                     Pressione ENTER para continuar...");
                getchar();
            }
            else
            {
                printf(ORANGE "ID Inválido!\n" RESET);
                getchar();
            }
        }

    } while (opcao_nav != 'S');
    system("clear");
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
    system("clear");
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
    printf("                     Pressione ENTER para voltar...");
    getchar();
}

void melhoresfilmes(FILE *arqfilme)
{
    Filmes filme_lido;
    Filmes melhores[5];
    int i, j;
    system("clear");
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
    printf(ORANGE "\n                     ========== TOP 5 MELHORES FILMES ===========\n" RESET);

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
    printf("                     Pressione ENTER para voltar...");
    getchar();
}

int buscarFilmePorTitulo(FILE *arqfilme, char *titulo_busca)
{
    Filmes filme_lido;
    int encontrado = 0;
    char filme_temp[100];

    fseek(arqfilme, 0, SEEK_SET); // Volta ao início do arquivo

    printf(ORANGE "\n                     ========== RESULTADOS DA BUSCA ===========\n" RESET);

    // Lê filme por filme
    while (fread(&filme_lido, sizeof(Filmes), 1, arqfilme) == 1)
    {
        strcpy(filme_temp, filme_lido.titulo);
        
        filme_temp[strcspn(filme_temp, " (")] = '\0'; // Remove o ano
        strupr(filme_temp);
        remover_quebra_linha(filme_temp);

        remover_quebra_linha(titulo_busca);
        strupr(titulo_busca);
        
        // Verifica se o título contém a string buscada (case insensitive)
        if (strcmp(filme_temp, titulo_busca) == 0)
        {
            // printf(BLUE "\n                     Título: %s\n" RESET, filme_lido.titulo);
            // printf("                     Resumo: %s\n", filme_lido.resumo);
            // printf("                     Avaliação Média: %.1f\n", filme_lido.avaliacao_media);
            // printf("------------------------------------------------------------\n");
            encontrado = 1;
        }
    }

    // if (!encontrado)
    // {
    //     printf("\nNenhum filme encontrado com o título contendo: %s\n", titulo_busca);
    // }

    return encontrado;

    printf("\n                     =========================================\n");
    printf("                     Pressione ENTER para voltar...");
    getchar();
}