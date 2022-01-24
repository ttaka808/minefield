// minefield.c by Trevor Taka
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// spot on board
struct Spot
{
    int value; // point value of spot
    int bomb; // if spot contains bomb
};

// checks for bomb in board spot
int ifBomb(struct Spot A[], int b)
{
    // return 1 if spot is bomb, 0 if not
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
    for (int i=0;i<25;i++)
    {
        board[i].value = 1;
    }
    int bombs = 6;
    int points = 5;
    int temp = 0;
    srand(time(NULL)); // seeds random
    // initializes bomb locations
    while (bombs > 0)
    {
        temp = rand() % 25; // random number between 0 and 24
        if (!ifBomb(board,temp)) // if location isn't already bomb
        {
            board[temp].bomb = 1; // sets if bomb to 1
            board[temp].value = 0; // sets point value to 0
            bombs--;
        }
    }
    // initializes spot point values
    while (points > 0)
    {
        temp = rand() % 25;
        if (!ifBomb(board,temp))
        {
            board[temp].value++;
            points--;
        }
    }
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