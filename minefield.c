// minefield.c by Trevor Taka
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 25 // size of board

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
    if (A[b].bomb)
    {
        return 1;
    }
    return 0;
}

void countBomb(struct Spot A[], int b[], int c[])
{
    for (int i=0;i<SIZE;i++)
    {
        if (ifBomb(A,i))
        {
            b[i/5]++;
            c[i%5]++; 
        }
    }
}

void countPoints(struct Spot A[], int b[], int c[])
{
    for (int i=0;i<SIZE;i++)
    {
        b[i/5] += A[i].value;
        c[i%5] += A[i].value;
    }
}

// prints 2d game board
void printBoard(struct Spot A[], int b[],int c[], int d[], int e[])
{
    for (int i=0;i<SIZE;i++)
    {
        printf("%d   ",A[i].value);
        if (i % 5 == 4)
        {
            printf(" %d/%d\n",d[i/5],b[i/5]);
        }
    }
    printf("\n");
    for (int j=0;j<5;j++)
    {
        printf("%d/%d ",e[j],c[j]);
    }
}

// initializes game board
void matrixInit(struct Spot A[])
{
    for (int i=0;i<SIZE;i++)
    {
        A[i].value = 1;
    }
    int bombs = 6;
    int points = 5;
    int temp = 0;
    srand(time(NULL)); // seeds random
    // initializes bomb locations
    while (bombs > 0)
    {
        temp = rand() % SIZE; // random number between 0 and 24
        if (!ifBomb(A,temp)) // if location isn't already bomb
        {
            A[temp].bomb = 1; // sets if bomb to 1
            A[temp].value = 0; // sets point value to 0
            bombs--;
        }
    }
    // initializes spot point values
    while (points > 0)
    {
        temp = rand() % SIZE;
        if (!ifBomb(A,temp))
        {
            A[temp].value++;
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
    struct Spot board[SIZE] = {};
    int rowBombArr[5] = {};
    int rowValArr[5] = {};
    int colBombArr[5] = {};
    int colValArr[5] = {};
    matrixInit(board);
    countBomb(board,rowBombArr,colBombArr);
    countPoints(board,rowValArr,colValArr);
    printBoard(board,rowBombArr,colBombArr,rowValArr,colValArr);
    return EXIT_SUCCESS;
}