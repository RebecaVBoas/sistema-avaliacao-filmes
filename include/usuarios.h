#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdio.h>

// --- DEFINIÇÃO DA STRUCT ---
typedef struct
{
    char nome[50];
    char senha[8];
} Usuarios;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrarUsuario(FILE *arqusuario);
Usuarios validarLogin(FILE *arqusuario);
void atualizarSenha(FILE *arqusuario, Usuarios user);
void imprimirUsuarios(FILE *arqusuario);

#endif