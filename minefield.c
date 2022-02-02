// minefield.c by Trevor Taka
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define SIZE 25 // size of board

// spot on board
struct Spot
{
    int value; // point value of spot
    int bomb; // if spot contains bomb
    int selected; // if spot has been selected
};

// Function declarations
void countArrayInit(int **rowBomb, int **rowVal, int **colBomb, int **colVal, int level);
void countArrayFree(int *rowBomb, int *rowVal, int *colBomb, int *colVal);
int ifBomb(struct Spot grid[], int location);
void matrixInit(struct Spot grid[], int level);
void countBomb(struct Spot grid[], int row[], int col[]);
void countPoints(struct Spot grid[], int row[], int col[]);
void printBoard(struct Spot grid[], int rowBomb[], int colBomb[], int rowVal[], int colVal[], int level);
int checkLoss(struct Spot grid[], int location);
int checkWin(struct Spot grid[]);

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
int ifBomb(struct Spot grid[], int location)
{
    // return 1 if spot is bomb, 0 if not
    if (grid[location].bomb)
        return 1;
    return 0;
}

// initializes game board
void matrixInit(struct Spot grid[], int level)
{
    // initializes every spot to a value of 1
    for (int i=0;i<SIZE;i++)
    {
        grid[i].value = 1;
    }
    int bombs = 6+level; // # of total bombs
    int points = 5; // # of extra points to be allocated
    int location = 0; // spot on board
    srand(time(NULL)); // seeds random
    // initializes bomb locations
    while (bombs > 0)
    {
        location = rand() % SIZE; // random number between 0 and 24
        if (!ifBomb(grid, location)) // if location isn't already bomb
        {
            grid[location].bomb = 1; // sets if bomb to 1
            grid[location].value = 0; // sets point value to 0
            bombs--;
        }
    }
    // allocates extra points to board randomly (seeded with time)
    while (points > 0)
    {
        location = rand() % SIZE;
        if (!ifBomb(grid, location))
        {
            grid[location].value++;
            points--;
        }
    }
}

// counts how many bombs are in each row and col
void countBomb(struct Spot grid[], int row[], int col[])
{
    for (int i=0;i<SIZE;i++)
    {
        if (ifBomb(grid, i))
        {
            row[i/5]++; // counts bombs in row
            col[i%5]++; // counts bombs in col
        }
    }
}

// counts how many points are in each row and col
void countPoints(struct Spot grid[], int row[], int col[])
{
    for (int i=0;i<SIZE;i++)
    {
        row[i/5] += grid[i].value; // counts points in row
        col[i%5] += grid[i].value; // counts points in col
    }
}

// prints 2d game board
void printBoard(struct Spot grid[], int rowBomb[], int colBomb[], int rowVal[], int colVal[], int level)
{
    system("cls"); // clear terminal screen
    printf("Level: %d\nTip: Points/Bombs\n",level+1);
    printf("    A   B   C   D   E\n"); // prints columns
    for (int i=0;i<SIZE;i++)
    {
        // prints x if spot hasn't been selected
        if (i % 5 == 0)
        {
            printf("%d   ",i / 5); // prints row
        }
        if (!grid[i].selected)
            printf("%c   ",'x');
        // prints value after being selected
        else
            printf("%d   ",grid[i].value);
        if (i % 5 == 4)
        {
            printf("%d/%d\n",rowVal[i/5],rowBomb[i/5]); // prints row stats
        }
    }
    printf("   ");
    for (int j=0;j<5;j++)
    {
        printf("%d/%d ",colVal[j],colBomb[j]); // prints col stats
    }
    printf("\n");
}

// checks if spot with bomb has been selected
int checkLoss(struct Spot grid[], int location)
{
    if (grid[location].bomb == 1 && grid[location].selected == 1)
        return 1;
    return 0;
}

// checks if current game board has been won
int checkWin(struct Spot grid[])
{
    for (int i=0;i<SIZE;i++)
    {
        if (grid[i].value > 1 && grid[i].selected == 0)  // won if all 2+ value spots are selected
            return 0;
    }
    return 1; 
}

int main(int argc, char *argv[])
{
    // shows call syntax if wrong
    /*if (argc != 2)
    {
        printf("./minefield (level)");
        return EXIT_FAILURE;
    }*/
    struct Spot board[SIZE] = {}; // board - array of structs Spot
    int *rowBombArr; // array of # of bombs in each row
    int *rowValArr; // array of # of points in each row
    int *colBombArr; // array of # of bombs in each column
    int *colValArr; // array of # of points in each column
    int loss = 0; // boolean loss
    int win; // boolean win
    int level = 0; // level - 1
    char coord[3]; // array of user inputted coordinates
    int loc; // location in array
    while (level <= 2 && !loss)
    {
        win = 0;
        countArrayInit(&rowBombArr, &rowValArr, &colBombArr, &colValArr, level);
        matrixInit(board, level);
        countBomb(board, rowBombArr, colBombArr);
        countPoints(board, rowValArr, colValArr);
        printBoard(board, rowBombArr, colBombArr, rowValArr, colValArr, level);
        while (!loss && !win)
        {
            // receives user input for spot selection
            printf("Enter coordinate (xy): ");
            scanf("%s",&coord);
            loc = (coord[1] - '0') * 5 + (int)coord[0] - 64; // converts coordinate into array index
            if (loc >= 1 && loc <= 25) // check for valid input
            {
                board[loc-1].selected = 1;
                printBoard(board, rowBombArr, colBombArr, rowValArr, colValArr, level); // updates board
                // checks for loss and win
                loss = checkLoss(board, loc-1);
                win = checkWin(board);
            }
            else
                printf("Enter valid coordinate on board\n");
        }
        if (win)
        {
            level++; // increment the level
            memset(board,0,SIZE*sizeof(struct Spot)); // clear the board
            if (level == 3) // win after 3 levels
                printf("You win!\n");
        }
        if (loss)
            printf("You lose!\n");
        countArrayFree(rowBombArr, rowValArr, colBombArr, colValArr);
    }
    return EXIT_SUCCESS;
}