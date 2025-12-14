#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- A SUA STRUCT EXATA ---
typedef struct
{
    char titulo[100];    // 100 bytes
    char usuario[25];    // 25 bytes
    int avaliacao;       // 4 bytes
    char comentario[80]; // 80 bytes (NOVO!)
} Avaliar;

char *lista_filmes[27] = {
    "O Poderoso Chefão (1972)", "Forrest Gump (1994)", "Matrix (1999)",
    "Interestelar (2014)", "Cidade de Deus (2002)", "De volta para o Futuro (1985)",
    "Parasita (2019)", "Psicose (1960)", "Central do Brasil (1998)",
    "Lisbela e o Prisioneiro (2003)", "Carandiru (2003)", "Ópera do Malandro (1985)",
    "Before Sunrise (1995)", "O Agente Secreto (2025)", "Legalmente Loira (2001)",
    "Orgulho e Preconceito (2005)", "Como Perder Um Homem em 10 dias (2003)",
    "10 Coisas Que Eu Odeio em Você (1999)", "Gatinhas e Gatões (1984)",
    "As Patricinhas de Beverly Hills (1995)", "As Branquelas (2004)",
    "Toy Story 3 (2010)", "Sociedade dos Poetas Mortos (1989)",
    "Whiplash (2014)", "Oppenheimer (2023)", "Django Livre (2012)", "Barbie (2023)"
};

// Função para gerar um comentário automático baseado na nota
void gerar_comentario(int nota, char *buffer) {
    if (nota == 5) strcpy(buffer, "Filme excelente! Recomendo muito.");
    else if (nota == 4) strcpy(buffer, "Gostei bastante, vale a pena.");
    else if (nota == 3) strcpy(buffer, "Filme mediano, da para assistir.");
    else if (nota == 2) strcpy(buffer, "Nao gostei muito, achei fraco.");
    else strcpy(buffer, "Horrivel, perca de tempo total.");
}

void gravar(FILE *f, char *nome, char *filme, int nota) {
    Avaliar av;
    
    // 1. Preenche Titulo
    strncpy(av.titulo, filme, 99);
    av.titulo[99] = '\0';
    
    // 2. Preenche Usuario
    strncpy(av.usuario, nome, 24);
    av.usuario[24] = '\0';
    
    // 3. Preenche Nota
    av.avaliacao = nota;
    
    // 4. Preenche Comentario (Automatico)
    gerar_comentario(nota, av.comentario);
    
    fwrite(&av, sizeof(Avaliar), 1, f);
}

int main() {
    FILE *arquivo = fopen("avaliacoes.dat", "wb");
    if (!arquivo) {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    printf("--- GERANDO DADOS COM A NOVA ESTRUTURA (COM COMENTARIO) ---\n");

    // === GRUPO 1: HUGO e HANS ===
    gravar(arquivo, "Hugo", "Matrix (1999)", 5);
    gravar(arquivo, "Hugo", "O Poderoso Chefão (1972)", 5);
    gravar(arquivo, "Hugo", "Cidade de Deus (2002)", 5);
    gravar(arquivo, "Hugo", "Legalmente Loira (2001)", 1);

    gravar(arquivo, "Hans", "Matrix (1999)", 5);           
    gravar(arquivo, "Hans", "O Poderoso Chefão (1972)", 5);
    gravar(arquivo, "Hans", "Cidade de Deus (2002)", 5);   
    gravar(arquivo, "Hans", "Legalmente Loira (2001)", 1); 
    
    // Recomendações Hans -> Hugo
    gravar(arquivo, "Hans", "Interestelar (2014)", 5);
    gravar(arquivo, "Hans", "Oppenheimer (2023)", 5);
    gravar(arquivo, "Hans", "Parasita (2019)", 5);
    gravar(arquivo, "Hans", "Whiplash (2014)", 5);
    gravar(arquivo, "Hans", "Psicose (1960)", 5);

    // === GRUPO 2: REBECA e PAMPONET ===
    gravar(arquivo, "Rebeca", "Legalmente Loira (2001)", 5);
    gravar(arquivo, "Rebeca", "10 Coisas Que Eu Odeio em Você (1999)", 5);
    gravar(arquivo, "Rebeca", "O Poderoso Chefão (1972)", 2); 

    gravar(arquivo, "Pamponet", "Legalmente Loira (2001)", 5);           
    gravar(arquivo, "Pamponet", "10 Coisas Que Eu Odeio em Você (1999)", 5); 
    gravar(arquivo, "Pamponet", "O Poderoso Chefão (1972)", 2);          

    // Recomendações Pamponet -> Rebeca
    gravar(arquivo, "Pamponet", "Barbie (2023)", 5);
    gravar(arquivo, "Pamponet", "Como Perder Um Homem em 10 dias (2003)", 5);
    gravar(arquivo, "Pamponet", "Orgulho e Preconceito (2005)", 5);
    gravar(arquivo, "Pamponet", "As Branquelas (2004)", 4);
    gravar(arquivo, "Pamponet", "As Patricinhas de Beverly Hills (1995)", 5);

    // === GRUPO 3: RUAN e WESLEY ===
    gravar(arquivo, "Ruan", "Central do Brasil (1998)", 5);
    gravar(arquivo, "Ruan", "Lisbela e o Prisioneiro (2003)", 5);
    
    gravar(arquivo, "Wesley", "Central do Brasil (1998)", 5); 
    gravar(arquivo, "Wesley", "Lisbela e o Prisioneiro (2003)", 5); 

    // Recomendações Wesley -> Ruan
    gravar(arquivo, "Wesley", "Carandiru (2003)", 5);
    gravar(arquivo, "Wesley", "Ópera do Malandro (1985)", 4);
    gravar(arquivo, "Wesley", "Cidade de Deus (2002)", 5);
    gravar(arquivo, "Wesley", "De volta para o Futuro (1985)", 5);

    // === PREENCHIMENTO GERAL (BOTS) ===
    for (int i = 0; i < 27; i++) {
        gravar(arquivo, "Bot_Critico", lista_filmes[i], (i % 3) + 2); 
        gravar(arquivo, "Bot_Fan", lista_filmes[i], (i % 2) + 4); 
    }

    fclose(arquivo);
    printf("\n[SUCESSO] Arquivo 'avaliacoes.dat' recriado com a nova estrutura!\n");
    printf("Campos: Titulo[100], Usuario[25], Nota, Comentario[80]\n");
    return 0;
}