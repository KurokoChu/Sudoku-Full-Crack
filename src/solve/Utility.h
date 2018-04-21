#ifndef UTILITY_H_
#define UTILITY_H_

void Setup();
char *Show_ArrayElement_1D(int *arr, int size);
int ArrayCount_1D(int *arr, int size);
int ArrayCount_2D(int **arr, int size_r, int size_c);
int *MemoryManage_1D(int size);
int **MemoryManage_2D(int row, int col);

#endif
