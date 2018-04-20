#include "Sudoku.h"
#include "Eliminated.h"

void Update_Eliminated() {
    eliminated = False;
}

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
            if (eliminate[coord.x][coord.y].arr[i] is EmptySlot) {
                Digit_arr[i] = i + 1;
                ++num;
            }
        }
    }
    coord.len = num;
    return Digit_arr;
}

void Eliminate_Digit(int **board, int num, int row, int col) {
    if (cell[row][col].arr[num - 1] isnot EmptySlot) {
        eliminated = True;
        eliminate[row][col].arr[num - 1] = num;
    }
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
            sub_x = coord.x - (coord.x % 3);
            sub_y = coord.y - (coord.y % 3);
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

int **Init_Board(int size_r, int size_c) {
    /* Create Sudoku's board */
    int **board;
    board = MemoryManage_2D(size_r, size_c);
    for(int i = 0; i < size_r; ++i) {
        for(int j = 0; j < size_c; ++j) {
            board[i][j] = sudoBoard[i][j].num;
        }
    }
    return board;
}

void Update_Board(int **board, int row, int col) {
    if (board[row][col] is EmptySlot) {
        coord.x = row;
        coord.y = col;
        cell[row][col].arr = Candidate_Digit(board, 9, 9);
        cell[row][col].num = coord.len;
    }
}
