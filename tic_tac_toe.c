#include <stdio.h>
#include <stdlib.h>
// i for rows j for columns

void print_board(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
        {
            printf("-----------\n");
        }
    }
}

int check_winner(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') // space for checking empty or not board
        {
            return 1; // Rows
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return 1; // Columns
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return 1; // Diagonal
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return 1; // Diagonal
    }
    return 0;
}

int is_board_full(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

int main()
{
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char current_player = 'X';
    int row, col;

    while (1)
    {

        print_board(board);

        printf("Player %c, enter row [(0) or (1) or (2)]: ", current_player);
        scanf("%d", &row);
        printf("Player %c, enter column  [(0) or (1) or (2)]:: ", current_player);
        scanf("%d", &col);

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = current_player;
        }
        else
        {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (check_winner(board))
        {
            system("clear");
            print_board(board);
            printf("Player %c wins!\n", current_player);
            break;
        }

        if (is_board_full(board))
        {
            system("clear");
            print_board(board);
            printf("It's a tie!\n");
            break;
        }

        current_player = (current_player == 'X') ? 'Y' : 'X';
    }

    return 0;
}
