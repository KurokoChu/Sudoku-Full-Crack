#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <python.h>
#define True 1
#define False 0
#define is ==
#define isnot !=
#define empty_slot 0

// Global Variables
int possible_num, test = 0;

// Declare Function
int **board_init();
int solve_board(int **board, int row, int col);
int find_empty_slot(int **board, int row, int col);
int append_in(int num, int **board, char *cmp);
int can_fill(int num, int **board);
int *determine_num(int **board);
int is_valid_board(int **board);
void show_board(int **board);
int *memory_manage_1d();
int **memory_manage_2d();

// Memorize row and column on board
typedef struct{
    int x;
    int y;
    int *pos_lst;
    int pos_num;
} sudo;
sudo cell[9][9];

typedef struct{
    int *lst;
    int num;
} sudo2;
sudo2 filled[27];

typedef struct{
    int x;
    int y;
    int len;
} point;
point coord;

int find_empty_slot(int **board, int row, int col) {
    /* Return True if found empty slot on board, False otherwise */
    int i = row, j = col;
    for (; i < 9; ) {
        for (; j < 9; ) {
            if (board[i][j] is empty_slot) {
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

int *determine_num(int **board) {
    /* Find all possible numbers that can fill on board */
    int *num_lst, num = 0;
    num_lst = memory_manage_1d(num_lst);
    for (int i = 0; i < 9; ++i) {
        if (can_fill(i + 1, board) is True) {
            num_lst[i] = i + 1;
            ++num;
        }
    }
    coord.len = num;
    return num_lst;
}

int can_fill(int num, int **board) {
    /* Return True if number can fill on board, False otherwise */
    if (append_in(num, board, "row") && append_in(num, board, "col") && append_in(num, board, "sub")) {
        return True;
    }
    else {
        return False;
    }
}

int append_in(int num, int **board, char *cmp) {
    /* Check Sudoku's Three rule */
    if (strcasecmp(cmp, "row") is False) {
        for (int i = 0; i < 9; ++i) {
            if (board[coord.x][i] is num && i isnot coord.y) {
                return False;
            }
        }
    }
    else if (strcasecmp(cmp, "col") is False) {
        for (int i = 0; i < 9; ++i) {
            if (board[i][coord.y] is num && i isnot coord.x) {
                return False;
            }
        }
    }
    else if (strcasecmp(cmp, "sub") is False) {
        int sub_x = (coord.x % 3 is 0) ? coord.x: coord.x - (coord.x % 3), sub_y = (coord.y % 3 is 0) ? coord.y: coord.y - (coord.y % 3);
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

int is_valid_board(int **board) {
    /* Return True if board have solution, False otherwise */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j){
            if (board[i][j] isnot empty_slot) {
                if (can_fill(board[i][j], board)) {
                    return True;
                }
            }
        }
    }
    return False;
}

void show_board(int **board) {
    /* Show each number on board */
    printf("------------------------\n");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            (j == 0) ? printf("| "): 1;
            printf("%d ", board[i][j]);
            (j % 3 == 2) ? printf("| "): 1;
        }
        printf("\n");
        (i % 3 == 2) ? printf("------------------------\n"): 1;
    }
}

int **board_init() {
    /* Create Sudoku's board */
    int **board;
    board = memory_manage_2d();
    int sol[9][9] = {{0, 0, 0,   0, 0, 0,   0, 0, 0},
                     {0, 8, 0,   6, 0, 0,   0, 7, 5},
                     {0, 1, 4,   5, 0, 0,   0, 0, 0},

                     {0, 0, 3,   2, 9, 0,   6, 0, 0},
                     {7, 0, 0,   0, 8, 0,   0, 0, 9},
                     {0, 0, 8,   0, 4, 6,   3, 0, 0},

                     {0, 0, 0,   0, 0, 3,   1, 2, 0},
                     {6, 2, 0,   0, 0, 9,   0, 4, 0},
                     {0, 0, 0,   0, 0, 0,   0, 0, 0}};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            scanf("%d", &board[i][j]);
        }
    }
    return board;
}

int *memory_manage_1d() {
    /* Memory manage 1-Dimension Array */
    int *arr;
    arr = malloc(9 * sizeof(int));
    for (int i = 0; i < 9; ++i) {
        arr[i] = 0;
    }
    return arr;
}

int **memory_manage_2d() {
    /* Memory manage 2-Dimension Array */
    int **arr;
    arr = malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; ++i) {
        arr[i] = malloc(9 * sizeof(int ));
        for (int j = 0; j < 9; ++j) {
            arr[i][j] = 0;
        }
    }
    return arr;
}
