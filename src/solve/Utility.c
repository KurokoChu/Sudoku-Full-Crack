#include "Sudoku.h"

void Setup() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cell[i][j].arr = MemoryManage_1D(9);
            eliminate[i][j].arr = MemoryManage_1D(9);
            lock_pair[i][j].arr = MemoryManage_1D(1);
            lock_can1[i][j].arr = MemoryManage_1D(1);
        }
    }
    for (int i = 0; i < 12; ++i) {
        score[i].num = False;
        score[i].arr = MemoryManage_1D(1);
    }
    for (int i = 0; i < 200; ++i) {
        textGuide[i].text = MemoryManage_1D(100);
    }
    coord_pair.arr = MemoryManage_1D(2);
}

void Show_ArrayElement_1D(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        (arr[i] isnot EmptySlot) ? printf("%d ", arr[i]): 1;
    }
}

int ArrayCount_1D(int *arr, int size) {
    int num = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] isnot EmptySlot) {
            ++num;
        }
    }
    return num;
}

int ArrayCount_2D(int **arr, int size_r, int size_c) {
    int num = 0;
    for (int i = 0; i < size_r; ++i) {
        for (int j = 0; j < size_c; ++j) {
            if (arr[i][j] isnot EmptySlot) {
            ++num;
            }
        }
    }
    return num;
}

int *MemoryManage_1D(int size) {
    /* Memory manage 1-Dimension Array */
    int *arr;
    arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }
    return arr;
}

int **MemoryManage_2D(int size_r, int size_c) {
    /* Memory manage 2-Dimension Array */
    int **arr;
    arr = malloc(size_r * sizeof(int *));
    for (int i = 0; i < size_r; ++i) {
        arr[i] = malloc(size_c * sizeof(int ));
        for (int j = 0; j < size_c; ++j) {
            arr[i][j] = 0;
        }
    }
    return arr;
}