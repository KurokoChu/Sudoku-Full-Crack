#include "Sudoku.h"
#include "SinglesTechnique.h"

int Find_FullHouse(int **board, int row, int col) {
    if (FullHouse_Row(board, row, col) is True) {
        return True;
    }
    else if (FullHouse_Col(board, row, col) is True) {
        return True;
    }
    else if (FullHouse_Sub(board, row, col) is True) {
        return True;
    }
    return False;
}

int FullHouse_Row(int **board, int row, int col) {
    int count = 0, *fill_arr;
    fill_arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] isnot EmptySlot) {
            ++count;
            fill_arr[board[row][i] - 1] = 1;
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            if (fill_arr[i] is EmptySlot) {
                coord.x = row;
                coord.y = col;
                if (CanFillIn(i + 1, board, 9, 9) is True) {
                    board[row][col] = i + 1;
                    return True;
                }
            }
        }
    }
    return False;
}

int FullHouse_Col(int **board, int row, int col) {
    int count = 0, *fill_arr;
    fill_arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] isnot EmptySlot) {
            ++count;
            fill_arr[board[i][col] - 1] = 1;
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            coord.x = row;
            coord.y = col;
            if (fill_arr[i] is EmptySlot) {
                if (CanFillIn(i + 1, board, 9, 9) is True) {
                    board[row][col] = i + 1;
                    return True;
                }
            }
        }
    }
    return False;
}

int FullHouse_Sub(int **board, int row, int col) {
    int count = 0, *fill_arr, sub_x, sub_y;
    fill_arr = MemoryManage_1D(9);
    sub_x = row - (row % 3), sub_y = col - (col % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] isnot EmptySlot) {
                ++count;
                fill_arr[board[i][j] - 1] = 1;
            }
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            if (fill_arr[i] is EmptySlot) {
                coord.x = row;
                coord.y = col;
                if (CanFillIn(i + 1, board, 9, 9) is True) {
                    board[row][col] = i + 1;
                    return True;
                }
            }
        }
    }
    return False;
}

int Find_NakedSingle(int **board, int row, int col) {
    if (cell[row][col].num is 1) {
        for (int i = 0; i < 9; ++i) {
            if (cell[row][col].arr[i] isnot EmptySlot) {
                coord.x = row;
                coord.y = col;
                if (CanFillIn(cell[row][col].arr[i], board, 9, 9) is True) {
                    board[row][col] = cell[row][col].arr[i];
                        return True;
                }
            }
        }
    }
    return False;
}

int Find_HiddenSingle(int **board, int row, int col) {
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].arr[i] isnot EmptySlot) {
            if (Find_BlockNumber(board, row, col, cell[row][col].arr[i]) is True) {
                coord.x = row;
                coord.y = col;
                if (CanFillIn(cell[row][col].arr[i], board, 9, 9) is True) {
                    board[row][col] = cell[row][col].arr[i];
                }
                return True;
            }
        }
    }
    return False;
}

int Find_BlockNumber(int **board, int row, int col, int num) {
    int **count, sub_x, sub_y;
    count = MemoryManage_2D(9, 9);
    sub_x = row - (row % 3), sub_y = col - (col % 3);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] is num) {
                for (int k = sub_x; k < sub_x + 3; ++k) {
                    for (int l = sub_y; l < sub_y + 3; ++l) {
                        if (board[k][l] isnot EmptySlot || k is i || l is j) {
                            count[k % 3][l % 3] = 1;
                        }
                    }
                }
            }
        }
    }
    if (ArrayCount_2D(count, 3, 3) is 8) {
        return True;
    }
    if (Find_RowBlock(board, row, col, num) is True || Find_ColBlock(board, row, col, num) is True) {
        return True;
    }
    return False;
}

int Find_RowBlock(int **board, int row, int col, int num) {
    int same = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] is EmptySlot) {
            if (i isnot col) {
                if (cell[row][i].arr[num - 1] isnot EmptySlot) {
                    return False;
                }
            }
        }
    }
    return same is 0;
}

int Find_ColBlock(int **board, int row, int col, int num) {
    int same = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] is EmptySlot) {
            if (i isnot row) {
                if (cell[i][col].arr[num - 1] isnot EmptySlot) {
                    return False;
                }
            }
        }
    }
    return same is 0;
}
