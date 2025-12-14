#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// --- DEFINIÇÃO DE CORES GLOBAIS ---
#define ORANGE "\033[38;5;208m"
#define GREEN "\033[38;5;41m"
#define BLUE "\033[38;5;75m"
#define RESET "\033[0m"

// --- PROTÓTIPOS ---
FILE *abrirFilme();
FILE *abrirUsuarios();
FILE *abrirAvaliacoes();
void remover_quebra_linha(char *str);


#endif