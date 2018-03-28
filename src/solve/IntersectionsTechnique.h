typedef struct {
    int x1, y1, x2, y2;
} point2;
point2 coord_pair;

int Find_LockedPair(int **board, int row, int col);
void Block_LockedPair(int **board, int row_block, int col_block);

int Find_LockedPair(int **board, int row, int col) {
    if (cell[row][col].num isnot 2 || lock[row][col].arr[0] is True) {
        return False;
    }
    int count, sub_x = (row % 3 is 0) ? row: row - (row % 3), sub_y = (col % 3 is 0) ? col: col - (col % 3);
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
                        lock[row][col].arr[0] = True;
                        lock[i][j].arr[0] = True;
                        Block_LockedPair(board, row, col);
                        Block_LockedPair(board, i, j);
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
                            eliminate[row_block][i].arr[j] = cell[row_block][col_block].arr[j];
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
                            eliminate[i][col_block].arr[j] = cell[row_block][col_block].arr[j];
                        }
                    }
                }
            }
        }
    }
    int sub_x = (row_block % 3 is 0) ? row_block: row_block - (row_block % 3), sub_y = (col_block % 3 is 0) ? col_block: col_block - (col_block % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] is EmptySlot 
                && (i isnot coord_pair.x1 && j isnot coord_pair.y1)
                && (i isnot coord_pair.x2 && j isnot coord_pair.y2)) {
                for (int k = 0; k < 9; ++k) {
                    if (cell[row_block][col_block].arr[k] isnot EmptySlot) {
                        eliminate[i][j].arr[k] = cell[row_block][col_block].arr[k];
                    }
                }
            }
        }
    }
}
