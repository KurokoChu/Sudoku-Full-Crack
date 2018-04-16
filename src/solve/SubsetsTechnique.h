int Find_NakedPair(int **board, int row, int col);
int Find_NakedTriple(int **board, int row, int col);
int Row_NakedTriple(int **board, int row, int col);
int Col_NakedTriple(int **board, int row, int col);
int Sub_NakedTriple(int **board, int row, int col);
int Find_HiddenPair(int **board, int row, int col);
int Row_HiddenPair(int **board, int row, int col);
int Col_HiddenPair(int **board, int row, int col);

int Find_NakedPair(int **board, int row, int col) {
    if (cell[row][col].num isnot 2) {
        return False;
    }

    coord_pair.arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].arr[i] isnot EmptySlot) {
            coord_pair.arr[i] = i + 1;
        }
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
                    if (count is 2) {
                        coord_pair.x1 = row;
                        coord_pair.y1 = col;
                        coord_pair.x2 = i;
                        coord_pair.y2 = j;
                        for (int num = 0; num < 9; ++num) {
                            (cell[row][col].arr[num] isnot EmptySlot) ? Block_LockedSub(board, num + 1, row, col): 1;
                        }
                        if (eliminated is True) {
                            return True;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (i is col || board[row][i] isnot EmptySlot || cell[row][i].num isnot 2) {
            continue;
        }
        count = 0;
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[row][i].arr[j]) {
                ++count;
                if (count is 2) {
                    coord_pair.x1 = row;
                    coord_pair.y1 = col;
                    coord_pair.x2 = row;
                    coord_pair.y2 = i;
                    for (int num = 0; num < 9; ++num) {
                        (cell[row][col].arr[num] isnot EmptySlot) ? Block_LockedRow(board, num + 1, row, col): 1;
                    }
                    if (eliminated is True) {
                        return True;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (i is row || board[i][col] isnot EmptySlot || cell[i][col].num isnot 2) {
            continue;
        }
        count = 0;
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[i][col].arr[j]) {
                ++count;
                if (count is 2) {
                    coord_pair.x1 = row;
                    coord_pair.y1 = col;
                    coord_pair.x2 = i;
                    coord_pair.y2 = col;
                    for (int num = 0; num < 9; ++num) {
                        (cell[row][col].arr[num] isnot EmptySlot) ? Block_LockedCol(board, num + 1, row, col): 1;
                    }
                    if (eliminated is True) {
                        return True;
                    }
                }
            }
        }
    }
    return False;
}

int Find_NakedTriple(int **board, int row, int col) {
    if (cell[row][col].num isnot 2 && cell[row][col].num isnot 3) {
        return False;
    }

    coord_pair.arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].arr[i] isnot EmptySlot) {
            coord_pair.arr[i] = i + 1;
        }
    }
    if (Sub_NakedTriple(board, row, col) is True) {
        return True;
    }
    else if (Row_NakedTriple(board, row, col) is True) {
        return True;
    }
    else if (Col_NakedTriple(board, row, col) is True) {
        return True;
    }
    return False;
}

int Row_NakedTriple(int **board, int row, int col) {
    coord_pair.x1 = -1;
    coord_pair.y1 = -1;
    coord_pair.x2 = -1;
    coord_pair.y2 = -1;
    coord_pair.x3 = -1;
    coord_pair.y3 = -1;
    int count, triple_count = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] isnot EmptySlot || (cell[row][i].num isnot 2 && cell[row][i].num isnot 3)) {
            continue;
        }
        count = 0;
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[row][i].arr[j]) {
                ++count;
            }
        }
        if (count is cell[row][i].num) {
            ++triple_count;
            if (coord_pair.x1 is -1 && coord_pair.y1 is -1) {
                coord_pair.x1 = row;
                coord_pair.y1 = i;
            }
            else if (coord_pair.x2 is -1 && coord_pair.y2 is -1) {
                coord_pair.x2 = row;
                coord_pair.y2 = i;
            }
            else if (coord_pair.x3 is -1 && coord_pair.y3 is -1) {
                coord_pair.x3 = row;
                coord_pair.y3 = i;
            }
        }
    }

    if (triple_count is 3) {
        for (int num = 0; num < 9; ++num) {
            (coord_pair.arr[num] isnot EmptySlot) ? Block_RowTriple(board, num + 1, row, col): 1;
        }
        if (eliminated is True) {
            return True;
        }
    }

    return False;
}

int Col_NakedTriple(int **board, int row, int col) {
    coord_pair.x1 = -1;
    coord_pair.y1 = -1;
    coord_pair.x2 = -1;
    coord_pair.y2 = -1;
    coord_pair.x3 = -1;
    coord_pair.y3 = -1;
    int count, triple_count = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] isnot EmptySlot || (cell[i][col].num isnot 2 && cell[i][col].num isnot 3)) {
            continue;
        }
        count = 0;
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[i][col].arr[j]) {
                ++count;
            }
        }
        if (count is cell[i][col].num) {
            ++triple_count;
            if (coord_pair.x1 is -1 && coord_pair.y1 is -1) {
                coord_pair.x1 = i;
                coord_pair.y1 = col;
            }
            else if (coord_pair.x2 is -1 && coord_pair.y2 is -1) {
                coord_pair.x2 = i;
                coord_pair.y2 = col;
            }
            else if (coord_pair.x3 is -1 && coord_pair.y3 is -1) {
                coord_pair.x3 = i;
                coord_pair.y3 = col;
            }
        }
    }

    if (triple_count is 3) {
        for (int num = 0; num < 9; ++num) {
            (coord_pair.arr[num] isnot EmptySlot) ? Block_ColTriple(board, num + 1, row, col): 1;
        }
        if (eliminated is True) {
            return True;
        }
    }

    return False;
}

int Sub_NakedTriple(int **board, int row, int col) {
    coord_pair.x1 = -1;
    coord_pair.y1 = -1;
    coord_pair.x2 = -1;
    coord_pair.y2 = -1;
    coord_pair.x3 = -1;
    coord_pair.y3 = -1;
    int count, triple_count = 0, sub_x = row - (row % 3), sub_y = col - (col % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] isnot EmptySlot || (cell[i][j].num isnot 2 && cell[i][j].num isnot 3)) {
                continue;
            }
            count = 0;
            for (int k = 0; k < 9; ++k) {
                if (cell[row][col].arr[k] isnot EmptySlot && cell[row][col].arr[k] is cell[i][j].arr[k]) {
                    ++count;
                }
            }
            if (count is cell[i][j].num) {

                ++triple_count;
                if (coord_pair.x1 is -1 && coord_pair.y1 is -1) {
                    coord_pair.x1 = i;
                    coord_pair.y1 = j;
                }
                else if (coord_pair.x2 is -1 && coord_pair.y2 is -1) {
                    coord_pair.x2 = i;
                    coord_pair.y2 = j;
                }
                else if (coord_pair.x3 is -1 && coord_pair.y3 is -1) {
                    coord_pair.x3 = i;
                    coord_pair.y3 = j;
                }
            }
        }
    }

    if (triple_count is 3) {
        for (int num = 0; num < 9; ++num) {
            (coord_pair.arr[num] isnot EmptySlot) ? Block_SubTriple(board, num + 1, row, col): 1;
        }
        if (eliminated is True) {
            return True;
        }
    }

    return False;
}

int Find_HiddenPair(int **board, int row, int col) {
    if (Row_HiddenPair(board, row, col) is True) {
        return True;
    }
    else if (Col_HiddenPair(board, row, col) is True) {
        return True;
    }
    return False;
}

int Row_HiddenPair(int **board, int row, int col) {
    coord_pair.x1 = -1;
    coord_pair.y1 = -1;
    coord_pair.x2 = -1;
    coord_pair.y2 = -1;
    coord_pair.arr = MemoryManage_1D(9);
    int count = 0, *count_arr, *num_arr, num_count = 0;
    count_arr = MemoryManage_1D(9);
    num_arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] isnot EmptySlot) {
            continue;
        }
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[row][i].arr[j]) {
                ++count_arr[j];
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (count_arr[i] is 2) {
            ++count;
            coord_pair.arr[i] = i + 1;
        }
    }
    if (count is 2) {
        for (int i = 0; i < 9; ++i) {
            if (coord_pair.arr[i] isnot EmptySlot) {
                num_arr[num_count++] = i + 1;
            }
        }
        count = 0;
        for (int i = 0; i < 9; ++i) {
            if (num_arr[0] is cell[row][i].arr[num_arr[0] - 1] && num_arr[1] is cell[row][i].arr[num_arr[1] - 1]) {
                ++count;
                if (coord_pair.x1 is -1 && coord_pair.y1 is -1) {
                    coord_pair.x1 = row;
                    coord_pair.y1 = i;
                }
                else if (coord_pair.x2 is -1 && coord_pair.y2 is -1) {
                    coord_pair.x2 = row;
                    coord_pair.y2 = i;
                }
            }
        }
        if (count isnot 2) {
            return False;
        }
        for (int num = 0; num < 9; ++num) {
            (coord_pair.arr[num] is EmptySlot) ? Eliminate_Digit(board, num + 1, coord_pair.x1, coord_pair.y1): 1;
            (coord_pair.arr[num] is EmptySlot) ? Eliminate_Digit(board, num + 1, coord_pair.x2, coord_pair.y2): 1;
        }
        if (eliminated is True) {
            return True;
        }
    }

    return False;
}


int Col_HiddenPair(int **board, int row, int col) {
    coord_pair.x1 = -1;
    coord_pair.y1 = -1;
    coord_pair.x2 = -1;
    coord_pair.y2 = -1;
    coord_pair.arr = MemoryManage_1D(9);
    int count = 0, *count_arr, *num_arr, num_count = 0;
    count_arr = MemoryManage_1D(9);
    num_arr = MemoryManage_1D(9);
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] isnot EmptySlot) {
            continue;
        }
        for (int j = 0; j < 9; ++j) {
            if (cell[row][col].arr[j] isnot EmptySlot && cell[row][col].arr[j] is cell[i][col].arr[j]) {
                ++count_arr[j];
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (count_arr[i] is 2) {
            ++count;
            coord_pair.arr[i] = i + 1;
        }
    }
    if (count is 2) {
        for (int i = 0; i < 9; ++i) {
            if (coord_pair.arr[i] isnot EmptySlot) {
                num_arr[num_count++] = i + 1;
            }
        }
        count = 0;
        for (int i = 0; i < 9; ++i) {
            if (num_arr[0] is cell[i][col].arr[num_arr[0] - 1] && num_arr[1] is cell[i][col].arr[num_arr[1] - 1]) {
                ++count;
                if (coord_pair.x1 is -1 && coord_pair.y1 is -1) {
                    coord_pair.x1 = i;
                    coord_pair.y1 = col;
                }
                else if (coord_pair.x2 is -1 && coord_pair.y2 is -1) {
                    coord_pair.x2 = i;
                    coord_pair.y2 = col;
                }
            }
        }
        if (count isnot 2) {
            return False;
        }
        for (int num = 0; num < 9; ++num) {
            (coord_pair.arr[num] is EmptySlot) ? Eliminate_Digit(board, num + 1, coord_pair.x1, coord_pair.y1): 1;
            (coord_pair.arr[num] is EmptySlot) ? Eliminate_Digit(board, num + 1, coord_pair.x2, coord_pair.y2): 1;
        }
        if (eliminated is True) {
            return True;
        }
    }

    return False;
}
