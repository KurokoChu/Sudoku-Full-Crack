int Find_FullHouse(int **board, int row, int col);
int FullHouse_Row(int **board, int row, int col);
int FullHouse_Col(int **board, int row, int col);
int FullHouse_Sub(int **board, int row, int col);
int Find_NakedSingle(int **board, int row, int col);
int Find_HiddenSingle(int **board, int row, int col);
int Find_BlockNumber(int **board, int row, int col, int num);

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
                board[row][col] = i + 1;
                return True;
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
            if (fill_arr[i] is EmptySlot) {
                board[row][col] = i + 1;
                return True;
            }
        }
    }
    return False;
}

int FullHouse_Sub(int **board, int row, int col) {
    int count = 0, *fill_arr, sub_x, sub_y;
    fill_arr = MemoryManage_1D(9);
    sub_x = (row % 3 is 0) ? row: row - (row % 3), sub_y = (col % 3 is 0) ? col: col - (col % 3);
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
                board[row][col] = i + 1;
                return True;
            }
        }
    }
    return False;
}

int Find_NakedSingle(int **board, int row, int col) {
    if (cell[row][col].num is 1) {
        for (int i = 0; i < 9; ++i) {
            if (cell[row][col].arr[i] isnot EmptySlot) {
                board[row][col] = cell[row][col].arr[i];
                    return True;
            }
        }
    }
    return False;
}

int Find_HiddenSingle(int **board, int row, int col) {
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].arr[i] isnot EmptySlot) {
            if (Find_BlockNumber(board, row, col, cell[row][col].arr[i]) is True) {
                board[row][col] = cell[row][col].arr[i];
                return True;
            }
        }
    }
    return False;
}

int Find_BlockNumber(int **board, int row, int col, int num) {
    int **count, sub_x, sub_y;
    count = MemoryManage_2D(9, 9);
    sub_x = (row % 3 is 0) ? row: row - (row % 3), sub_y = (col % 3 is 0) ? col: col - (col % 3);
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
    return False;
}
