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

// allocates memory for each value and bomb counting array (+1 size for each level)
void countArrayInit(int **rowBomb, int **rowVal, int **colBomb, int **colVal, int level)
{
    *rowBomb = (int*)calloc(sqrt(SIZE)+level,sizeof(int));
    *rowVal = (int*)calloc(sqrt(SIZE)+level,sizeof(int));
    *colBomb = (int*)calloc(sqrt(SIZE)+level,sizeof(int));
    *colVal = (int*)calloc(sqrt(SIZE)+level,sizeof(int));
}

// frees memory allocated for each value and bomb counting array
void countArrayFree(int *rowBomb, int *rowVal, int *colBomb, int *colVal)
{
    free(rowBomb);
    free(rowVal);
    free(colBomb);
    free(colVal);
}

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
void printBoard(struct Spot A[], int b[],int c[], int d[], int e[], int level)
{
    system("cls"); // clear terminal screen
    printf("Level: %d\n",level+1);
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

int checkWin(struct Spot A[])
{
    for (int i=0;i<SIZE;i++)
    {
        if (A[i].value > 1 && A[i].selected == 0) 
            return 0;
    }
    return 1; 
}

// initializes game board
void matrixInit(struct Spot A[],int b)
{
    for (int i=0;i<SIZE;i++)
    {
        A[i].value = 1;
    }
    int bombs = 6+b; // # of total bombs
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
    int *rowBombArr;
    int *rowValArr;
    int *colBombArr;
    int *colValArr;
    int loss = 0;
    int win;
    int level = 0;
    int loc;
    while (level <= 2 && !loss)
    {
        win = 0;
        countArrayInit(&rowBombArr,&rowValArr,&colBombArr,&colValArr,level);
        matrixInit(board,level);
        countBomb(board,rowBombArr,colBombArr);
        countPoints(board,rowValArr,colValArr);
        printBoard(board,rowBombArr,colBombArr,rowValArr,colValArr,level);
        while (!loss && !win)
        {
            printf("Enter spot: ");
            scanf("%d",&loc);
            board[loc].selected = 1;
            printBoard(board,rowBombArr,colBombArr,rowValArr,colValArr,level);
            loss = checkLoss(board,loc);
            win = checkWin(board);
        }
        if (win)
        {
            level++; // increment the level
            memset(board,0,SIZE*sizeof(struct Spot)); // clear the board
            if (level == 3)
                printf("You win!\n");
        }
        countArrayFree(rowBombArr,rowValArr,colBombArr,colValArr);
    }
    return EXIT_SUCCESS;
}