#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printBoard(char board[3][3]);
void userMove(char board[3][3]);
int isGameFinished(char board[3][3]);
int hasContestantWon(char board[3][3], char symbol);
void aiMove(char board[3][3]);
int* minimax(char board[3][3], char currentPlayer);
int isBoardFull(char board[3][3]);
int isValidMove(char board[3][3], int position);
void placeMove(char board[3][3], int position, char symbol);

int main() {
    printf("Welcome to game\n");
    printf("X for user O for computer\n");
    
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    printBoard(board);

    while (1) {
        userMove(board);
        printBoard(board);
        if (isGameFinished(board)){
            printBoard(board);
            break;
        }

        aiMove(board);
        printBoard(board);
        if (isGameFinished(board)) {
            printBoard(board);
            break;
        }
    }

    return 0;
}

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----\n");
    }
    printf("\n");
}

void userMove(char board[3][3]) {
    int userInput;
    while (1) {
        printf("Enter your move (1-9): ");
        scanf("%d", &userInput);
        if (isValidMove(board, userInput)) {
            break;
        } else {
            printf("%d is not a valid move.\n", userInput);
        }
    }
    placeMove(board, userInput, 'X');
}

int isGameFinished(char board[3][3]) {
    if (hasContestantWon(board, 'X')) {
        printf("Player wins!\n");
        return 1;
    }
    if (hasContestantWon(board, 'O')) {
        printf("AI wins!\n");
        return 1;
    }
    if (isBoardFull(board)) {
        printf("The game ended in a tie!\n");
        return 1;
    }
    return 0;
}

int hasContestantWon(char board[3][3], char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return 1;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return 1;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return 1;
    if (board[2][0] == symbol && board[1][1] == symbol && board[0][2] == symbol) return 1;
    return 0;
}

void aiMove(char board[3][3]) {
    int* bestMove = minimax(board, 'O');
    if (bestMove[1] != -1 && bestMove[2] != -1) {
        board[bestMove[1]][bestMove[2]] = 'O';
    }
    free(bestMove);
}

int* minimax(char board[3][3], char currentPlayer) {
    char opponent = (currentPlayer == 'O') ? 'X' : 'O';
    int bestScore = (currentPlayer == 'O') ? INT_MIN : INT_MAX;
    int currentScore;
    int* bestMove = (int*)malloc(3 * sizeof(int));
    bestMove[0] = -1; // Best score
    bestMove[1] = -1; // Row
    bestMove[2] = -1; // Col

    if (hasContestantWon(board, 'O')) {
        bestMove[0] = 1; // AI wins
        return bestMove;
    }
    if (hasContestantWon(board, 'X')) {
        bestMove[0] = -1; // Player wins
        return bestMove;
    }
    if (isBoardFull(board)) {
        bestMove[0] = 0; // Tie
        return bestMove;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = currentPlayer;
                currentScore = minimax(board, opponent)[0];
                board[i][j] = backup;
                if ((currentPlayer == 'O' && currentScore > bestScore) || (currentPlayer == 'X' && currentScore < bestScore)) {
                    bestScore = currentScore;
                    bestMove[0] = bestScore;
                    bestMove[1] = i;
                    bestMove[2] = j;
                }
            }
        }
    }
    return bestMove;
}

int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0; // Not full
            }
        }
    }
    return 1; // Full
}

int isValidMove(char board[3][3], int position) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O') return 0; // Invalid move
    else if (position > 9 || position < 1) return 0; // Invalid position
    return 1; // Valid move
}

void placeMove(char board[3][3], int position, char symbol) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    board[row][col] = symbol;
}
