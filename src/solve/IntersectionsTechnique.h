typedef struct {
    int x1, y1, x2, y2, x3, y3, *arr, num;
} point2;
point2 coord_pair;

int Find_LockedPair(int **board, int row, int col);
void Block_LockedPair(int **board, int row_block, int col_block);
int Find_LockedCandidates_1(int **board, int row, int col);
void Block_LockedRow(int **board, int num, int row_block, int col_block);
void Block_LockedCol(int **board, int num, int row_block, int col_block);
void Block_LockedSub(int **board, int num, int row_block, int col_block);
int Find_LockedCandidates_2(int **board, int row, int col);
int Count_SameDigit_Row(int **board, int index, int row, int col);
int Count_SameDigit_Col(int **board, int index, int row, int col);

int Find_LockedPair(int **board, int row, int col) {
    if (cell[row][col].num isnot 2) {
        return False;
    }
    int count, sub_x = row - (row % 3), sub_y = col - (col % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if ((i is row && j is col) || cell[i][j].num isnot 2) {
                continue;
            }
            count = 0;
            for (int k = 0; k < 9; ++k) {
                if (cell[row][col].arr[k] isnot EmptySlot && cell[row][col].arr[k] is cell[i][j].arr[k]) {
                    ++count;
                    if (count is 2 && (row is i || col is j)) {
                        coord_pair.x1 = row;
                        coord_pair.y1 = col;
                        coord_pair.x2 = i;
                        coord_pair.y2 = j;
                        Block_LockedPair(board, row, col);
                        Block_LockedPair(board, i, j);
                        if (eliminated is True) {
                            return True;
                        }
                        return True;
                    }
                }
            }
        }
    }
    return False;
}

void Block_LockedPair(int **board, int row_block, int col_block) {
    if (coord_pair.x1 is coord_pair.x2) {
        for (int i = 0; i < 9; ++i) {
            if (board[row_block][i] is EmptySlot) {
                if (i isnot coord_pair.y1 && i isnot coord_pair.y2) {
                    for (int j = 0; j < 9; ++j) {
                        if (cell[row_block][col_block].arr[j] isnot EmptySlot) {
                            Eliminate_Digit(board, cell[row_block][col_block].arr[j], row_block, i);
                        }
                    }
                }
            }
        }
    }
    else if (coord_pair.y1 is coord_pair.y2) {
        for (int i = 0; i < 9; ++i) {
            if (board[i][col_block] is EmptySlot) {
                if (i isnot coord_pair.x1 && i isnot coord_pair.x2) {
                    for (int j = 0; j < 9; ++j) {
                        if (cell[row_block][col_block].arr[j] isnot EmptySlot) {
                            Eliminate_Digit(board, cell[row_block][col_block].arr[j], i, col_block);
                        }
                    }
                }
            }
        }
    }
    int sub_x = row_block - (row_block % 3), sub_y = col_block - (col_block % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] is EmptySlot) {
                if ((i isnot coord_pair.x1 && j isnot coord_pair.y1) || (i isnot coord_pair.x2 && j isnot coord_pair.y2)) {
                    for (int k = 0; k < 9; ++k) {
                        if (cell[row_block][col_block].arr[k] isnot EmptySlot) {
                            Eliminate_Digit(board, cell[row_block][col_block].arr[k], i, j);
                        }
                    }
                }
            }
        }
    }
}

int Find_LockedCandidates_1(int **board, int row, int col) {
    int count, sub_x = row - (row % 3), sub_y = col - (col % 3), **num_arr;
    num_arr = MemoryManage_2D(9, 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (i is row && j is col || board[i][j] isnot EmptySlot) {
                continue;
            }
            for (int k = 0; k < 9; ++k) {
                if (cell[row][col].arr[k] isnot EmptySlot && cell[row][col].arr[k] is cell[i][j].arr[k]) {
                    ++num_arr[k][0];
                    if (num_arr[k][0] is 1) {
                        (num_arr[k][1] is EmptySlot) ? num_arr[k][1] = i: 1;
                        (num_arr[k][2] is EmptySlot) ? num_arr[k][2] = j: 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 9; ++i) {
        if (num_arr[i][0] is 1 && (row is num_arr[i][1] || col is num_arr[i][2])) {
            coord_pair.x1 = row;
            coord_pair.y1 = col;
            coord_pair.x2 = num_arr[i][1];
            coord_pair.y2 = num_arr[i][2];
            coord_pair.arr[0] = i + 1;
            coord_pair.num = 1;
            if (row is num_arr[i][1]) {
                Block_LockedRow(board, coord_pair.arr[0], row, col);

            }
            else if (col is num_arr[i][2]) {
                Block_LockedCol(board, coord_pair.arr[0], row, col);
            }
            Block_LockedSub(board, coord_pair.arr[0], row, col);
            if (eliminated is True) {
                return True;
            }
        }
    }
    return False;
}

void Block_LockedRow(int **board, int num, int row_block, int col_block) {
    for (int i = 0; i < 9; ++i) {
        if (board[row_block][i] is EmptySlot) {
            if (i isnot coord_pair.y1 && i isnot coord_pair.y2) {
                Eliminate_Digit(board, num, row_block, i);
                Update_Board(board, row_block, i);
            }
        }
    }
}

void Block_LockedCol(int **board, int num, int row_block, int col_block) {
    for (int i = 0; i < 9; ++i) {
        if (board[i][col_block] is EmptySlot) {
            if (i isnot coord_pair.x1 && i isnot coord_pair.x2) {
                Eliminate_Digit(board, num, i, col_block);
                Update_Board(board, i, col_block);
            }
        }
    }
}

void Block_LockedSub(int **board, int num, int row_block, int col_block) {
    int sub_x = row_block - (row_block % 3), sub_y = col_block - (col_block % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] is EmptySlot) {
                if ((i isnot coord_pair.x1 && j isnot coord_pair.y1) || (i isnot coord_pair.x2 && j isnot coord_pair.y2)) {
                    Eliminate_Digit(board, num, i, j);
                    Update_Board(board, i, j);
                }
            }
        }
    }
}

int Find_LockedCandidates_2(int **board, int row, int col) {
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].arr[i] isnot EmptySlot) {
            coord_pair.x1 = row;
            coord_pair.y1 = col;
            coord_pair.num = 1;
            coord_pair.arr[0] = i + 1;
            if (Count_SameDigit_Row(board, i, row, col) is True) {
                Block_LockedSub(board, cell[row][col].arr[i], row, col);
                if (eliminated is True) {
                    return True;
                }
            }
            if (Count_SameDigit_Col(board, i, row, col) is True) {
                Block_LockedSub(board, cell[row][col].arr[i], row, col);
                if (eliminated is True) {
                    return True;
                }
            }
        }
    }
    return False;
}

int Count_SameDigit_Row(int **board, int index, int row, int col) {
    int count = 0;
    for (int i = 0; i < 9; ++i) {
        if (i is col || board[row][i] isnot EmptySlot) {
            continue;
        }
        if (cell[row][col].arr[index] is cell[row][i].arr[index]) {
            ++count;
            if (count is 1) {
                coord_pair.x2 = row;
                coord_pair.y2 = i;
            }
            else if (count is 2) {
                coord_pair.x3 = row;
                coord_pair.y3 = i;
            }
        }
    }
    if (count is 1
        && (coord_pair.x2 - (coord_pair.x2 % 3) is row - (row % 3))
        && (coord_pair.y2 - (coord_pair.y2 % 3) is col - (col % 3))) {
        coord_pair.num = 1;
        return True;
    }
    else if (count is 2
        && (coord_pair.x2 - (coord_pair.x2 % 3) is row - (row % 3))
        && (coord_pair.y2 - (coord_pair.y2 % 3) is col - (col % 3))
        && (coord_pair.x3 - (coord_pair.x3 % 3) is row - (row % 3))
        && (coord_pair.y3 - (coord_pair.y3 % 3) is col - (col % 3))) {
        coord_pair.num = 2;
        return True;
    }
    return False;
}

int Count_SameDigit_Col(int **board, int index, int row, int col) {
    int count = 0;
    for (int i = 0; i < 9; ++i) {
        if (i is row || board[i][col] isnot EmptySlot) {
            continue;
        }
        if (cell[row][col].arr[index] is cell[i][col].arr[index]) {
            ++count;
            if (count is 1) {
                coord_pair.x2 = i;
                coord_pair.y2 = col;
            }
            else if (count is 2) {
                coord_pair.x3 = i;
                coord_pair.y3 = col;
            }
        }
    }
    if (count is 1
        && (coord_pair.x2 - (coord_pair.x2 % 3) is row - (row % 3))
        && (coord_pair.y2 - (coord_pair.y2 % 3) is col - (col % 3))) {
        coord_pair.num = 1;
        return True;
    }
    else if (count is 2
        && (coord_pair.x2 - (coord_pair.x2 % 3) is row - (row % 3))
        && (coord_pair.y2 - (coord_pair.y2 % 3) is col - (col % 3))
        && (coord_pair.x3 - (coord_pair.x3 % 3) is row - (row % 3))
        && (coord_pair.y3 - (coord_pair.y3 % 3) is col - (col % 3))) {
        coord_pair.num = 2;
        return True;
    }
    return False;
}
