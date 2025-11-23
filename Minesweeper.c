#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    struct {
        char board[8][8];
        char visible[8][8];
        int revealed[8][8];
        int rows;
        int cols;
        int mines;
        int score;
        int active;
        char playerName[50];
    } game;
    
    struct {
        char names[5][50];
        int scores[5];
        int total;
    } ranking = {.total = 0};
    
    int option, i, j, k, row, col, adjacentMines;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    srand(time(NULL));
    
    while(1) {
        printf("\n================================\n");
        printf("    CAMPO MINADO - MENU PRINCIPAL\n");
        printf("================================\n");
        printf("1. Novo Jogo\n");
        printf("2. Ver Ranking\n");
        printf("3. Como Jogar\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        
        if(scanf("%d", &option) != 1) {
            while(getchar() != '\n');
            printf("Entrada invalida! Digite um numero.\n");
            continue;
        }
        
        switch(option) {
            case 1:
                printf("\n--- NOVO JOGO ---\n");
                printf("Digite seu nome: ");
                scanf(" %[^\n]", game.playerName);
                
                printf("\nEscolha o tamanho do tabuleiro:\n");
                printf("1. Facil (3x3 com 2 minas)\n");
                printf("2. Medio (5x5 com 5 minas)\n");
                printf("3. Dificil (8x8 com 10 minas)\n");
                printf("Escolha: ");
                
                int boardSize;
                if(scanf("%d", &boardSize) != 1 || boardSize < 1 || boardSize > 3) {
                    while(getchar() != '\n');
                    printf("Opcao invalida! Iniciando jogo medio.\n");
                    boardSize = 2;
                }
                
                if(boardSize == 1) {
                    game.rows = 3;
                    game.cols = 3;
                    game.mines = 2;
                } else if(boardSize == 2) {
                    game.rows = 5;
                    game.cols = 5;
                    game.mines = 5;
                } else {
                    game.rows = 8;
                    game.cols = 8;
                    game.mines = 10;
                }
                
                game.score = 0;
                game.active = 1;
                
                for(i = 0; i < game.rows; i++) {
                    for(j = 0; j < game.cols; j++) {
                        game.board[i][j] = '0';
                        game.visible[i][j] = '#';
                        game.revealed[i][j] = 0;
                    }
                }
                
                for(i = 0; i < game.mines; i++) {
                    int r, c;
                    do {
                        r = rand() % game.rows;
                        c = rand() % game.cols;
                    } while(game.board[r][c] == '*');
                    game.board[r][c] = '*';
                }
                
                for(i = 0; i < game.rows; i++) {
                    for(j = 0; j < game.cols; j++) {
                        if(game.board[i][j] != '*') {
                            adjacentMines = 0;
                            for(k = 0; k < 8; k++) {
                                int ni = i + dx[k];
                                int nj = j + dy[k];
                                if(ni >= 0 && ni < game.rows && 
                                   nj >= 0 && nj < game.cols && 
                                   game.board[ni][nj] == '*') {
                                    adjacentMines++;
                                }
                            }
                            game.board[i][j] = '0' + adjacentMines;
                        }
                    }
                }
                
                while(game.active) {
                    printf("\n================================\n");
                    printf("Jogador: %s\n", game.playerName);
                    printf("Pontos: %d  Minas: %d\n", game.score, game.mines);
                    printf("================================\n\n");
                    printf("    ");
                    for(j = 0; j < game.cols; j++) {
                        printf("%d ", j + 1);
                    }
                    printf("\n   ");
                    for(j = 0; j < game.cols; j++) {
                        printf("--");
                    }
                    printf("\n");
                    
                    for(i = 0; i < game.rows; i++) {
                        printf("%d | ", i + 1);
                        for(j = 0; j < game.cols; j++) {
                            printf("%c ", game.visible[i][j]);
                        }
                        printf("\n");
                    }
                    
                    printf("\n1. Revelar celula\n");
                    printf("2. Marcar/Desmarcar mina\n");
                    printf("3. Desistir\n");
                    printf("Escolha: ");
                    
                    if(scanf("%d", &option) != 1) {
                        while(getchar() != '\n');
                        printf("Entrada invalida!\n");
                        continue;
                    }
                    
                    if(option == 3) {
                        printf("Voce desistiu! Fim de jogo.\n");
                        game.active = 0;
                        break;
                    }
                    
                    printf("Digite a linha (1-%d): ", game.rows);
                    if(scanf("%d", &row) != 1 || row < 1 || row > game.rows) {
                        while(getchar() != '\n');
                        printf("Linha invalida!\n");
                        continue;
                    }
                    row--;
                    
                    printf("Digite a coluna (1-%d): ", game.cols);
                    if(scanf("%d", &col) != 1 || col < 1 || col > game.cols) {
                        while(getchar() != '\n');
                        printf("Coluna invalida!\n");
                        continue;
                    }
                    col--;
                    
                    if(option == 1) {
                        if(game.revealed[row][col]) {
                            printf("Celula ja revelada!\n");
                            continue;
                        }
                        
                        if(game.board[row][col] == '*') {
                            printf("\nBOOM! Voce acertou uma mina!\n");
                            printf("GAME OVER! Pontuacao final: %d\n", game.score);
                            
                            for(i = 0; i < game.rows; i++) {
                                for(j = 0; j < game.cols; j++) {
                                    game.visible[i][j] = game.board[i][j];
                                }
                            }
                            game.active = 0;
                        } else {
                            game.visible[row][col] = game.board[row][col];
                            game.revealed[row][col] = 1;
                            game.score += 10;
                            
                            int cellsRemaining = 0;
                            for(i = 0; i < game.rows; i++) {
                                for(j = 0; j < game.cols; j++) {
                                    if(!game.revealed[i][j] && game.board[i][j] != '*') {
                                        cellsRemaining++;
                                    }
                                }
                            }
                            
                            if(cellsRemaining == 0) {
                                printf("\nPARABENS! Voce venceu!\n");
                                printf("Pontuacao final: %d\n", game.score);
                                game.active = 0;
                            }
                        }
                    } else if(option == 2) {
                        if(game.revealed[row][col]) {
                            printf("Nao pode marcar celula revelada!\n");
                        } else {
                            if(game.visible[row][col] == 'B') {
                                game.visible[row][col] = '#';
                                printf("Marca removida!\n");
                            } else {
                                game.visible[row][col] = 'B';
                                printf("Celula marcada!\n");
                            }
                        }
                    }
                }
                
                if(game.score > 0) {
                    if(ranking.total < 5) {
                        for(i = 0; game.playerName[i] != '\0'; i++) {
                            ranking.names[ranking.total][i] = game.playerName[i];
                        }
                        ranking.names[ranking.total][i] = '\0';
                        ranking.scores[ranking.total] = game.score;
                        ranking.total++;
                    } else {
                        int minIdx = 0;
                        for(i = 1; i < 5; i++) {
                            if(ranking.scores[i] < ranking.scores[minIdx]) {
                                minIdx = i;
                            }
                        }
                        if(game.score > ranking.scores[minIdx]) {
                            for(i = 0; game.playerName[i] != '\0'; i++) {
                                ranking.names[minIdx][i] = game.playerName[i];
                            }
                            ranking.names[minIdx][i] = '\0';
                            ranking.scores[minIdx] = game.score;
                        }
                    }
                    
                    for(i = 0; i < ranking.total - 1; i++) {
                        for(j = 0; j < ranking.total - i - 1; j++) {
                            if(ranking.scores[j] < ranking.scores[j + 1]) {
                                int tempScore = ranking.scores[j];
                                ranking.scores[j] = ranking.scores[j + 1];
                                ranking.scores[j + 1] = tempScore;
                                
                                char tempName[50];
                                for(k = 0; ranking.names[j][k] != '\0'; k++) {
                                    tempName[k] = ranking.names[j][k];
                                }
                                tempName[k] = '\0';
                                
                                for(k = 0; ranking.names[j + 1][k] != '\0'; k++) {
                                    ranking.names[j][k] = ranking.names[j + 1][k];
                                }
                                ranking.names[j][k] = '\0';
                                
                                for(k = 0; tempName[k] != '\0'; k++) {
                                    ranking.names[j + 1][k] = tempName[k];
                                }
                                ranking.names[j + 1][k] = '\0';
                            }
                        }
                    }
                }
                break;
                
            case 2:
                printf("\n================================\n");
                printf("       TOP 5 JOGADORES\n");
                printf("================================\n");
                if(ranking.total == 0) {
                    printf("Nenhum jogo registrado ainda.\n");
                } else {
                    for(i = 0; i < ranking.total; i++) {
                        printf("%d. %-30s %d pts\n", i + 1, 
                               ranking.names[i], ranking.scores[i]);
                    }
                }
                break;
                
            case 3:
                printf("\n================================\n");
                printf("         COMO JOGAR\n");
                printf("================================\n");
                printf("Objetivo: Revelar todas as celulas sem minas!\n\n");
                printf("Regras:\n");
                printf("# = celula nao revelada\n");
                printf("B = celula marcada (possivel mina)\n");
                printf("0-8 = numero de minas adjacentes\n");
                printf("* = mina (quando revelar)\n\n");
                printf("Dicas:\n");
                printf("Use os numeros para deduzir onde estao as minas\n");
                printf("Marque celulas suspeitas\n");
                printf("+10 pontos por celula revelada\n");
                break;
                
            case 4:
                printf("Obrigado por jogar! Ate logo!\n");
                return 0;
                
            default:
                printf("Opcao invalida! Escolha 1-4.\n");
        }
    }
    
    return 0;
}