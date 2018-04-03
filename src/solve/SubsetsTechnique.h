int Find_NakedPair(int **board, int row, int col);

int Find_NakedPair(int **board, int row, int col) {
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
