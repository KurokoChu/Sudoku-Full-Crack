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
    int x1, y1, x2, y2, x3, y3, *arr, num;
} point2;
point2 coord_pair;

void Setup();
void Show_ArrayElement_1D(int *arr, int size);
int ArrayCount_1D(int *arr, int size);
int ArrayCount_2D(int **arr, int size_r, int size_c);
int *MemoryManage_1D(int size);
int **MemoryManage_2D(int row, int col);

void Setup() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cell[i][j].arr = MemoryManage_1D(9);
            eliminate[i][j].arr = MemoryManage_1D(9);
            lock_pair[i][j].arr = MemoryManage_1D(1);
            lock_can1[i][j].arr = MemoryManage_1D(1);
        }
    }
    for (int i = 0; i < 8; ++i) {
        score[i].num = False;
        score[i].arr = MemoryManage_1D(1);
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
