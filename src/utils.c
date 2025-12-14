#include <stdio.h>
#include <string.h>
#include "utils.h" 

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

