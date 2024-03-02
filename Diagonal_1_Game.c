
    /****************************
     * Diagonal 1 Game CLI *
     * Auther : Devesh Patil
     * In this Game Players need to create the diagoral base on index of matrix. 
     * To Select the Index, its Row and Colum number need to select. 
     * After selecting if it is `0` then it become `1` otherwise vise varsa
     * It is Base on C Language and basics of Matrix & Array.
    *****************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BOX_SIZE 3

// Define the game board
int board[BOX_SIZE][BOX_SIZE];

// Define a function to initialize the board
void init_board()
{
    int i, j;
    for (i = 0; i < BOX_SIZE; i++)
    {
        for (j = 0; j < BOX_SIZE; j++)
        {
            board[i][j] = rand() % 2;
        }
    }
}

// Define a function to draw the board
void draw_board()
{
    int i, j;
    for (i = 0; i < BOX_SIZE; i++)
    {
        for (j = 0; j < BOX_SIZE; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Define a function to check if the player has won
int check_win()
{
    int i, j;
    for (i = 0; i < BOX_SIZE; i++)
    {
        int row_sum = 0, col_sum = 0;
        for (j = 0; j < BOX_SIZE; j++)
        {
            row_sum += board[i][j];
            col_sum += board[j][i];
        }
        if (row_sum != 1 || col_sum != 1)
        {
            return 0;
        }
    }
    return 1;
}

// Define the main function
int main()
{
    srand(time(NULL));
    init_board();
    int moves = 0;
    while (!check_win())
    {
        draw_board();
        printf("Enter row and column of the box to switch (e.g. '1 2'): ");
        int row, col;
        scanf("%d %d", &row, &col);
        row--;
        col--;
        if (row >= 0 && row < BOX_SIZE && col >= 0 && col < BOX_SIZE)
        {
            board[row][col] = 1 - board[row][col];
            moves++;
        }
        else
        {
            printf("Invalid move. Try again.\n");
        }
    }
    draw_board();
    printf("Congratulations! You won in %d moves.\n", moves);
    getch();
    return 0;
}
