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
    int selected; // if spot has been selected
};

// checks for bomb in board spot
int ifBomb(struct Spot A[], int b)
{
    // return 1 if spot is bomb, 0 if not
    if (A[b].bomb)
        return 1;
    return 0;
}

// counts how many bombs are in each row and col
void countBomb(struct Spot A[], int b[], int c[])
{
    for (int i=0;i<SIZE;i++)
    {
        if (ifBomb(A,i))
        {
            b[i/5]++; // counts bombs in row
            c[i%5]++; // counts bombs in col
        }
    }
}

// counts how many points are in each row and col
void countPoints(struct Spot A[], int b[], int c[])
{
    for (int i=0;i<SIZE;i++)
    {
        b[i/5] += A[i].value; // counts points in row
        c[i%5] += A[i].value; // counts points in col
    }
}

// prints 2d game board
void printBoard(struct Spot A[], int b[],int c[], int d[], int e[])
{
    for (int i=0;i<SIZE;i++)
    {
        // prints x if spot hasn't been selected
        if (!A[i].selected)
            printf("%c   ",'x');
        // prints value after being selected
        else
            printf("%d   ",A[i].value);
        if (i % 5 == 4)
        {
            printf(" %d/%d\n",d[i/5],b[i/5]); // prints row stats
        }
    }
    printf("\n");
    for (int j=0;j<5;j++)
    {
        printf("%d/%d ",e[j],c[j]); // prints col stats
    }
    printf("\n");
}

// checks if spot with bomb has been selected
int checkLoss(struct Spot A[], int b)
{
    if (A[b].bomb == 1 && A[b].selected == 1)
        return 1;
    return 0;
}

// initializes game board
void matrixInit(struct Spot A[])
{
    for (int i=0;i<SIZE;i++)
    {
        A[i].value = 1;
    }
    int bombs = 6; // # of total bombs
    int points = 5; // # of extra points to be allocated
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
    // allocates extra points to board
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
    int loss = 0;
    int loc;
    matrixInit(board);
    countBomb(board,rowBombArr,colBombArr);
    countPoints(board,rowValArr,colValArr);
    printBoard(board,rowBombArr,colBombArr,rowValArr,colValArr);
    while (!loss)
    {
        int loc;
        printf("Enter spot: ");
        scanf("%d",&loc);
        board[loc].selected = 1;
        printBoard(board,rowBombArr,colBombArr,rowValArr,colValArr);
        loss = checkLoss(board,loc);
    }
    return EXIT_SUCCESS;
}