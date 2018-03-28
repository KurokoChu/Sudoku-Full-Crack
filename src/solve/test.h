// #include <python.h>
#define True 1
#define False 0
#define is ==
#define isnot !=
#define EmptySlot 0

// Global Variables
int possible_num, test = 0;

// Declare Function
int **Init_Board(int row, int col);
int Find_EmptySlot(int **board, int start_r, int start_c);
int CanFillIn(int num, int **board, int size_r, int size_c);
int *Candidate_Digit(int **board, int size_r, int size_c);
int *Eliminate_Digit(int **board, int *Digit_arr, int row, int col, int size);
int AppendIn(int num, int **board, int size_r, int size_c, char cmp);
int IsValid_Board(int **board, int size_r, int size_c);
void Show_Board(int **board, int size_r, int size_c);
int **Init_Board(int size_r, int size_c);
int ArrayCount_1D(int *arr, int size);
int ArrayCount_2D(int **arr, int size_r, int size_c);
int *MemoryManage_1D(int size);
int **MemoryManage_2D(int row, int col);

// Memorize row and column on board
typedef struct{
    int x;
    int y;
    int *arr;
    int num;
} sudo;
sudo cell[9][9];
sudo eliminate[9][9];
sudo lock[9][9];

typedef struct{
    int *arr;
    int num;
} sudo2;
sudo2 filled[27];

typedef struct{
    int x;
    int y;
    int len;
} point;
point coord;

int Find_EmptySlot(int **board, int start_r, int start_c) {
    /* Return True if found empty slot on board, False otherwise */
    int i = start_r, j = start_c;
    for (; i < 9; ) {
        for (; j < 9; ) {
            if (board[i][j] is EmptySlot) {
                coord.x = i;
                coord.y = j;
                return True;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return False;
}

int *Candidate_Digit(int **board, int size_r, int size_c) {
    /* Find all possible numbers that can fill on board */
    int *Digit_arr, num = 0;
    Digit_arr = MemoryManage_1D(size_r);
    for (int i = 0; i < 9; ++i) {
        if (CanFillIn(i + 1, board, size_r, size_c) is True) {
            Digit_arr[i] = i + 1;
            ++num;
        }
    }
    coord.len = num;
    Digit_arr = Eliminate_Digit(board, Digit_arr, coord.x, coord.y, size_r);
    return Digit_arr;
}

int *Eliminate_Digit(int **board, int *Digit_arr, int row, int col, int size) {
    int num = 0;
    for (int i = 0; i < 9; ++i) {
        if (eliminate[row][col].arr[i] isnot EmptySlot) {
            if (eliminate[row][col].arr[i] is Digit_arr[i]) {
                Digit_arr[i] = 0;
                ++num;
            }
        }
    }
    coord.len -= num;
    return Digit_arr;
}

int CanFillIn(int num, int **board, int size_r, int size_c) {
    /* Return True if number can fill on board, False otherwise */
    if (AppendIn(num, board, size_r, size_c, 'r') 
        && AppendIn(num, board, size_r, size_c , 'c') 
        && AppendIn(num, board, size_r, size_c , 's')) {
        return True;
    }
    else {
        return False;
    }
}

int AppendIn(int num, int **board, int size_r, int size_c, char cmp) {
    /* Check Sudoku's Three rule */
    int sub_x, sub_y;
    switch(cmp) {
        case 'r':
            for (int i = 0; i < size_c; ++i) {
                if (board[coord.x][i] is num && i isnot coord.y) {
                    return False;
                }
            }
        case 'c':
            for (int i = 0; i < size_r; ++i) {
                if (board[i][coord.y] is num && i isnot coord.x) {
                    return False;
                }
            }
        case 's':
            sub_x = (coord.x % 3 is 0) ? coord.x: coord.x - (coord.x % 3);
            sub_y = (coord.y % 3 is 0) ? coord.y: coord.y - (coord.y % 3);
            for (int i = sub_x; i < sub_x + 3; ++i) {
                for (int j = sub_y; j < sub_y + 3; ++j) {
                    if (board[i][j] is num && (i isnot coord.x && j isnot coord.y)) {
                        return False;
                    }
                }
            }
    }
    return True;
}

int IsValid_Board(int **board, int size_r, int size_c) {
    /* Return True if board have solution, False otherwise */
    for (int i = 0; i < size_r; ++i) {
        for (int j = 0; j < size_c; ++j){
            if (board[i][j] isnot EmptySlot) {
                coord.x = i;
                coord.y = j;
                if (CanFillIn(board[i][j], board, size_r, size_c) is False) {
                    return False;
                }
            }
        }
    }
    return True;
}

void Show_Board(int **board, int size_r, int size_c) {
    /* Show each digit on board */
    printf("------------------------\n");
    for (int i = 0; i < size_r; ++i) {
        for (int j = 0; j < size_c; ++j) {
            (j == 0) ? printf("| "): 1;
            printf("%d ", board[i][j]);
            (j % 3 == 2) ? printf("| "): 1;
        }
        printf("\n");
        (i % 3 == 2) ? printf("------------------------\n"): 1;
    }
}

int **Init_Board(int size_r, int size_c) {
    /* Create Sudoku's board */
    int **board;
    board = MemoryManage_2D(size_r, size_c);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            scanf("%d", &board[i][j]);
        }
    }
    return board;
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
