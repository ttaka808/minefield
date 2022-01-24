// minefield.c by Trevor Taka
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// spot on board
struct Spot
{
    int value; // point value
    int bomb;
};

// checks for bomb in board spot
int ifBomb(struct Spot A[], int b)
{
    if (A[b].bomb == 1)
    {
        return 1;
    }
    return 0;
}

// initializes game board
void matrixInit()
{
    struct Spot board[25] = {};
    /*for (int i=0;i<25;i++)
    {
        board[i].value = 1;
    }*/
    int bombs = 6;
    int points = 24;
    int temp = 0;
    srand(time(NULL));
    while (bombs > 0)
    {
        temp = rand() % 25;
        if (ifBomb(board,temp)==0)
        {
            board[temp].bomb = 1;
            bombs--;
        }
    }
    //while (points > 0)
    //{

    //}
}

int main(int argc, char *argv[])
{
    // shows call syntax if wrong
    /*if (argc != 2)
    {
        printf("./minefield (level)");
        return EXIT_FAILURE;
    }*/
    matrixInit();
    return EXIT_SUCCESS;
}