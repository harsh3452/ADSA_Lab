#include <stdio.h>

int board[20][20];
int n;

int isSafe(int row, int col)
{
    int i, j;

    for(i = 0; i < row; i++)
        if(board[i][col])
            return 0;

    for(i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if(board[i][j])
            return 0;

    for(i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if(board[i][j])
            return 0;

    return 1;
}

int solveNQueens(int row)
{
    int col;

    if(row == n)
        return 1;

    for(col = 0; col < n; col++)
    {
        if(isSafe(row, col))
        {
            board[row][col] = 1;

            if(solveNQueens(row + 1))
                return 1;

            board[row][col] = 0;
        }
    }

    return 0;
}

void printBoard()
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(board[i][j])
                printf("Q ");
            else
                printf(". ");
        }

        printf("\n");
    }
}

int main()
{
    printf("Enter number of queens: ");
    scanf("%d", &n);

    if(solveNQueens(0))
    {
        printf("\nSolution:\n");
        printBoard();
    }
    else
    {
        printf("No solution exists\n");
    }

    return 0;
}