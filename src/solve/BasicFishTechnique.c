#include "Sudoku.h"
#include "BasicFishTechnique.h"

int Find_XWing(int **board, int row, int col) {
    if (RowBase_XWing(board, row, col) is True) {
        return True;
    }
    else if (ColBase_XWing(board, row, col) is True) {
        return True;
    }
    return False;
}

int RowBase_XWing(int **board, int row, int col) {
    int count;
    for (int num = 0; num < 9; ++num) {
        if (cell[row][col].arr[num] isnot EmptySlot) {
            coord_pair.x1 = -1;
            coord_pair.y1 = -1;
            coord_pair.x2 = -1;
            coord_pair.y2 = -1;
            count = 0;
            for (int i = 0; i < 9; ++i) {
                if (board[row][i] isnot EmptySlot) {
                    continue;
                }
                if (cell[row][i].arr[num] isnot EmptySlot) {
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
        }
        if (count isnot 2) {
            continue;
        }
        for (int i = 0; i < 9; ++i) {
            if (board[i][coord_pair.y1] isnot EmptySlot || board[i][coord_pair.y2] isnot EmptySlot ||
                i is coord_pair.x1 || i is coord_pair.x2) {
                continue;
            }
            coord_pair.x3 = -1;
            coord_pair.y3 = -1;
            coord_pair.x4 = -1;
            coord_pair.y4 = -1;
            count = 0;
            if (cell[i][coord_pair.y1].arr[num] isnot EmptySlot && 
                cell[i][coord_pair.y2].arr[num] isnot EmptySlot) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] isnot EmptySlot) {
                        continue;
                    }
                    if (cell[i][j].arr[num] isnot EmptySlot) {
                        ++count;
                        if (coord_pair.x3 is -1 && coord_pair.y3 is -1) {
                            coord_pair.x3 = i;
                            coord_pair.y3 = j;
                        }
                        else if (coord_pair.x4 is -1 && coord_pair.y4 is -1) {
                            coord_pair.x4 = i;
                            coord_pair.y4 = j;
                        }
                    }
                }
                if (count isnot 2) {
                    continue;
                }
                Block_ColQuart(board, num + 1, coord_pair.x1, coord_pair.y1);
                Block_ColQuart(board, num + 1, coord_pair.x2, coord_pair.y2);
                if (eliminated is True) {
                    coord_pair.arr[0] = num + 1;
                    return True;
                }
            }
        }
    }
    return False;
}

int ColBase_XWing(int **board, int row, int col) {
    int count;
    for (int num = 0; num < 9; ++num) {
        if (cell[row][col].arr[num] isnot EmptySlot) {
            coord_pair.x1 = -1;
            coord_pair.y1 = -1;
            coord_pair.x2 = -1;
            coord_pair.y2 = -1;
            count = 0;
            for (int i = 0; i < 9; ++i) {
                if (board[i][col] isnot EmptySlot) {
                    continue;
                }
                if (cell[i][col].arr[num] isnot EmptySlot) {
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
        }
        if (count isnot 2) {
            continue;
        }
        for (int i = 0; i < 9; ++i) {
            if (board[coord_pair.x1][i] isnot EmptySlot || board[coord_pair.x2][i] isnot EmptySlot ||
                i is coord_pair.y1 || i is coord_pair.y2) {
                continue;
            }
            coord_pair.x3 = -1;
            coord_pair.y3 = -1;
            coord_pair.x4 = -1;
            coord_pair.y4 = -1;
            count = 0;
            if (cell[coord_pair.x1][i].arr[num] isnot EmptySlot && 
                cell[coord_pair.x2][i].arr[num] isnot EmptySlot) {
                for (int j = 0; j < 9; ++j) {
                    if (board[j][i] isnot EmptySlot) {
                        continue;
                    }
                    if (cell[j][i].arr[num] isnot EmptySlot) {
                        ++count;
                        if (coord_pair.x3 is -1 && coord_pair.y3 is -1) {
                            coord_pair.x3 = j;
                            coord_pair.y3 = i;
                        }
                        else if (coord_pair.x4 is -1 && coord_pair.y4 is -1) {
                            coord_pair.x4 = j;
                            coord_pair.y4 = i;
                        }
                    }
                }
                if (count isnot 2) {
                    continue;
                }
                Block_RowQuart(board, num + 1, coord_pair.x1, coord_pair.y1);
                Block_RowQuart(board, num + 1, coord_pair.x2, coord_pair.y2);
                if (eliminated is True) {
                    coord_pair.arr[0] = num + 1;
                    return True;
                }
            }
        }
    }
    return False;
}

void Block_RowQuart(int **board, int num, int row_block, int col_block) {
    for (int i = 0; i < 9; ++i) {
        if (board[row_block][i] is EmptySlot) {
            if (i isnot coord_pair.y1 && 
                i isnot coord_pair.y2 &&
                i isnot coord_pair.y3 &&
                i isnot coord_pair.y4) {
                Eliminate_Digit(board, num, row_block, i);
                Update_Board(board, row_block, i);
            }
        }
    }
}

void Block_ColQuart(int **board, int num, int row_block, int col_block) {
    for (int i = 0; i < 9; ++i) {
        if (board[i][col_block] is EmptySlot) {
            if (i isnot coord_pair.x1 && 
                i isnot coord_pair.x2 &&
                i isnot coord_pair.x3 &&
                i isnot coord_pair.x4) {
                Eliminate_Digit(board, num, i, col_block);
                Update_Board(board, i, col_block);
            }
        }
    }
}
