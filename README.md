# 🎬 Sistema de Avaliação de Filmes

Projeto final da disciplina **Linguagem de Programação I** – UNEB  
Professora: **Maria Inés Restovic**  
Período: **2025.2**

---

## 📘 Descrição do Projeto

O **Sistema de Avaliação de Filmes** é um programa desenvolvido em **C**, voltado para apreciadores de cinema que desejam **registrar e compartilhar opiniões sobre filmes assistidos**.  
O sistema permite que o usuário cadastre uma conta, faça login, avalie filmes e visualize as médias e comentários de outros usuários.

Além disso, o projeto utiliza **arquivos binários** para armazenar os dados de forma persistente, garantindo que as informações não sejam perdidas entre as execuções do programa.

---

## 🎯 Objetivos

- Permitir **cadastro e login** de usuários com autenticação por nome e senha.  
- Disponibilizar um **catálogo de filmes** para consulta e avaliação.  
- Registrar **notas (1 a 5)** e **comentários (até 80 caracteres)** para cada filme.  
- Calcular e atualizar automaticamente as **médias de avaliação**.  
- Exibir:
  - As **avaliações e comentários** de um filme específico.  
  - Os **filmes avaliados por um usuário**.  
  - Os **Top 5 melhores e piores filmes** com base nas médias.  

---

## 🧱 Estrutura de Dados

O sistema utiliza **três arquivos binários** principais:

| Arquivo | Conteúdo | Campos Principais |
|----------|-----------|-------------------|
| `usuarios.dat` | Dados de usuários | nome, senha |
| `filmes.dat` | Catálogo de filmes | título, resumo, soma de notas, média, nº de avaliações |
| `avaliacoes.dat` | Avaliações realizadas | usuário, filme, nota, comentário |

Cada entidade é representada por uma `struct` em C.

---

## ⚙️ Funcionalidades Principais

- [x] Menu principal interativo  
- [x] Cadastro e login de usuários  
- [x] Exibição de catálogo paginado (10 filmes por tela)  
- [x] Avaliação e comentários  
- [x] Atualização automática das médias  
- [x] Relatórios: Top 5 melhores e piores filmes  
- [x] Armazenamento binário persistente  

---

## 🧩 Tecnologias Utilizadas

- **Linguagem:** C  
- **IDE Recomendada:** Visual Studio Code  
- **Compilador:** GCC (MinGW ou Linux nativo)  
- **Sistema de armazenamento:** Arquivos binários (`.dat`)  

---

## 💻 Como Executar no VS Code

### 🔹 Pré-requisitos
1. Ter o **VS Code** instalado.  
2. Ter o **GCC** (compilador C) instalado e configurado no PATH.  
   - Verifique no terminal com:  
     ```bash
     gcc --version
     ```
3. Extensão recomendada: **C/C++ (Microsoft)**.

---

### 🔹 Passos para execução

1. **Clone o repositório** (ou baixe o projeto):
   ```bash
   git clone https://github.com/seu-usuario/sistema-avaliacao-filmes.git
