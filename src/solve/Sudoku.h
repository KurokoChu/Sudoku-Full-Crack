#ifndef SODUKU_H_
#define SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *text;
    int row, col, num, numCoord;
} text;
text textGuide[200];
text textSummary;

// #include <python.h>
#define True 1
#define False 0
#define is ==
#define isnot !=
#define EmptySlot 0

// Memorize row and column on board
typedef struct{
    int x;
    int y;
    int *arr;
    int num;
} sudo;
sudo cell[9][9];
sudo eliminate[9][9];
sudo lock_pair[9][9];
sudo lock_can1[9][9];

typedef struct{
    int *arr;
    int num;
} sudo2;
sudo2 sudoBoard[9][9];
sudo2 score[8];
sudo2 triple;

typedef struct{
    int x;
    int y;
    int len;
} point;
point coord;

typedef struct {
    int x1, y1, x2, y2, x3, y3, x4, y4, *arr, num;
} point2;
point2 coord_pair;
point2 coord_pair_text[9][9];

// Global Variables
int eliminated;

int startGuide(int **board, int onlyGetStep, int freezeLoop);
int Solve_Board(int **board, int onlyGetStep, int freezeLoop);
int GetStep(int **board, int step, int onlyGetStep, int freezeLoop);
int DoStep(int **board, int row, int col, int step);
void Score_Summary();

void Update_Eliminated();
int **Init_Board(int **board);
int Find_EmptySlot(int **board, int start_r, int start_c);
int CanFillIn(int num, int **board, int size_r, int size_c);
int *Candidate_Digit(int **board, int size_r, int size_c);
void Eliminate_Digit(int num, int row, int col);
int AppendIn(int num, int **board, int size_r, int size_c, char cmp);
int IsValid_Board(int **board, int size_r, int size_c);
void Update_Board(int **board, int row, int col);

#include "Utility.h"

#endif
