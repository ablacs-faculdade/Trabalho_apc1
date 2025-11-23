Campo Minado em C
Jogo Campo Minado (Minesweeper) desenvolvido em linguagem C como projeto acadêmico.
Sobre o Projeto
Este projeto implementa o clássico jogo Campo Minado com interface de terminal, desenvolvido seguindo os requisitos acadêmicos de programação em C. O jogo oferece três níveis de dificuldade, sistema de pontuação e ranking dos melhores jogadores.
Funcionalidades

3 Níveis de Dificuldade

Fácil: Tabuleiro 3x3 com 2 minas
Médio: Tabuleiro 5x5 com 5 minas
Difícil: Tabuleiro 8x8 com 10 minas

Sistema de Ranking

Armazena os top 5 melhores jogadores
Ordenação automática por pontuação
Persistente durante a execução

Mecânicas do Jogo

Revelar células para descobrir números
Marcar células suspeitas com bandeira (B)
Sistema de pontuação: +10 pontos por célula revelada
Detecção automática de vitória
Tutorial integrado "Como Jogar"

Validação Completa

Proteção contra entradas inválidas
Verificação de limites do tabuleiro
Prevenção de jogadas impossíveis

Requisitos Acadêmicos Atendidos

a) Código implementado apenas com a função main()
b) Menu principal com comandos de seleção (switch-case) e repetição (while, for)
c) Validação completa da entrada de dados com tratamento de erros
d) Uso eficiente de matrizes e estruturas para armazenamento de dados

Como Compilar e Executar
Requisitos

Compilador GCC instalado
Sistema operacional: Windows, Linux ou macOS

Compilação
bashgcc campo_minado.c -o campo_minado
Execução
Windows:
bashcampo_minado.exe
Linux/macOS:
bash./campo_minado
Como Jogar
Menu Principal

Novo Jogo - Iniciar uma partida
Ver Ranking - Visualizar top 5 jogadores
Como Jogar - Tutorial do jogo
Sair - Encerrar o programa

Durante o Jogo

Digite coordenadas de 1 a N (não de 0 a N-1)
Opção 1: Revelar célula
Opção 2: Marcar/desmarcar célula suspeita
Opção 3: Desistir da partida

Símbolos do Tabuleiro

# - Célula não revelada

B - Célula marcada (possível bomba)
0-8 - Número de minas adjacentes

- - Mina (mostrada ao perder)

Objetivo
Revelar todas as células que não contêm minas sem acertar nenhuma bomba!
Estrutura do Código
Estruturas de Dados
c// Estrutura principal do jogo
struct {
char board[8][8]; // Tabuleiro real (minas e números)
char visible[8][8]; // Tabuleiro visível ao jogador
int revealed[8][8]; // Controle de células reveladas
int rows, cols; // Dimensões do tabuleiro
int mines; // Quantidade de minas
int score; // Pontuação atual
int active; // Status do jogo (ativo/inativo)
char playerName[50]; // Nome do jogador
} game;

// Estrutura de ranking
struct {
char names[5][50]; // Nomes dos top 5
int scores[5]; // Pontuações dos top 5
int total; // Quantidade de jogadores registrados
} ranking;
Algoritmos Principais

Posicionamento Aleatório de Minas

Usa rand() para gerar posições aleatórias
Verifica se posição já tem mina antes de colocar

Cálculo de Minas Adjacentes

Percorre as 8 direções ao redor de cada célula
Conta quantas minas existem nas células vizinhas
Usa arrays dx[] e dy[] para direções

Validação de Entrada

scanf() com verificação de retorno
Limpeza de buffer com while(getchar() != '\n')
Verificação de limites do tabuleiro

Sistema de Ranking

Bubble Sort para ordenação decrescente
Substitui menor pontuação se ranking estiver cheio
Mantém apenas top 5

Fluxo do Programa
Início
↓
Menu Principal (loop infinito)
↓
Opção 1: Novo Jogo
↓
Escolher Dificuldade (3x3, 5x5 ou 8x8)
↓
Inicializar Tabuleiro
↓
Posicionar Minas Aleatoriamente
↓
Calcular Números (minas adjacentes)
↓
Loop do Jogo
├─ Mostrar Tabuleiro
├─ Escolher Ação (Revelar/Marcar/Desistir)
├─ Validar Entrada
├─ Atualizar Tabuleiro
├─ Verificar Vitória/Derrota
└─ Repetir até fim do jogo
↓
Atualizar Ranking
↓
Voltar ao Menu Principal
Técnicas de Programação Utilizadas

Estruturas (struct): Organização de dados relacionados
Matrizes bidimensionais: Representação do tabuleiro
Loops aninhados: Percorrer matrizes
Switch-case: Implementação de menus
Validação robusta: Prevenção de erros de entrada
Algoritmo de ordenação: Bubble Sort para ranking
Números aleatórios: Posicionamento de minas

Arquivos do Projeto
campo-minado/
├── campo_minado.c # Código fonte principal
└── README.md # Este arquivo
Autores

[Seu Nome] - [Seu GitHub]
[Nome do Parceiro] - [GitHub do Parceiro] (se em dupla)

Informações Acadêmicas

Disciplina: Programação em C
Instituição: [Nome da Instituição]
Data: Novembro/2024

Notas Técnicas

Numeração humanizada (1-N) para melhor experiência do usuário
Conversão automática para índices de array (0 a N-1)
Três matrizes separadas para diferentes propósitos (eficiência)
Verificação de bordas ao calcular adjacências
Sistema de bandeiras para marcar células suspeitas

Tratamento de Erros
O programa trata os seguintes casos:

Entrada não numérica (letras, símbolos)
Coordenadas fora dos limites
Células já reveladas
Tentativa de marcar células reveladas
Buffer overflow em strings

# Exemplo de Partida

    CAMPO MINADO - MENU PRINCIPAL

================================

1. Novo Jogo
2. Ver Ranking
3. Como Jogar
4. Sair
   Escolha uma opcao: 1

--- NOVO JOGO ---
Digite seu nome: João

Escolha o tamanho do tabuleiro:

1. Facil (3x3 com 2 minas)
2. Medio (5x5 com 5 minas)
3. Dificil (8x8 com 10 minas)
   Escolha: 2

================================
Jogador: João
Pontos: 0 Minas: 5
================================

    1 2 3 4 5

---

1 | # # # # #
2 | # # # # #
3 | # # # # #
4 | # # # # #
5 | # # # # #

1. Revelar celula
2. Marcar/Desmarcar mina
3. Desistir
   Escolha: 1
   Digite a linha (1-5): 3
   Digite a coluna (1-5): 3
   Conceitos de C Demonstrados

Manipulação de strings
Arrays multidimensionais
Estruturas de dados compostas
Ponteiros implícitos em arrays
Funções da biblioteca padrão (stdio.h, stdlib.h, time.h)
Controle de fluxo (if, while, for, switch)
Operadores lógicos e relacionais

Licença
Este projeto é de código aberto para fins educacionais.

Desenvolvido em linguagem C
