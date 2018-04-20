#ifndef UTILITY_H_
#define UTILITY_H_

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
sudo2 score[8];
sudo2 triple;
sudo2 filled[27];

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

void Setup();
void Show_ArrayElement_1D(int *arr, int size);
int ArrayCount_1D(int *arr, int size);
int ArrayCount_2D(int **arr, int size_r, int size_c);
int *MemoryManage_1D(int size);
int **MemoryManage_2D(int row, int col);

#endif
