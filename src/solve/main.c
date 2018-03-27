#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

int filled_num;

int test_solve(int **board, int row, int col);
int get_step (int **board, int row, int col);
int find_full_house(int **board, int row, int col);
int row_full_house(int **board, int row, int col);
int col_full_house(int **board, int row, int col);
int sub_full_house(int **board, int row, int col);
int find_naked_single(int **board, int row, int col);
void update_board(int **board);
int lst_count(int *lst);

int main() {
    /* Main function */
    int **sudoku;
    sudoku = board_init();
    if (is_valid_board(sudoku)) {
        printf("calculating . . .\n");
        if (solve_board(sudoku, 0, 0) is True) {
            printf("\nfinish!\n");
            show_board(sudoku);
        }
        else {
            printf("can't find solution\n");
            show_board(sudoku);
        }
    }
    else {
        printf("can't find solution\n");
    }
    return 0;
}

int solve_board(int **board, int row, int col) {
    /* Find the solution */
    if (find_empty_slot(board, row, col) is False) {
        return True;
    }
    return test_solve(board, coord.x, coord.y);
}

int test_solve(int **board, int row, int col) {
    cell[row][col].x = row;
    cell[row][col].y = col;
    cell[row][col].pos_lst = determine_num(board);
    cell[row][col].pos_num = coord.len;
    switch(get_step(board, row, col)) {
        case 1:
            printf("Full House r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            return solve_board(board, 0, 0);
        case 2:
            printf("Naked Single r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            return solve_board(board, 0, 0);
        default:
            row = (col + 1 == 9) ? row + 1: row;
            col = (col + 1) % 9;
            return solve_board(board, row, col);
    }
}

int get_step(int **board, int row, int col) {
    int result;
    if (find_full_house(board, row, col) is True) {
        return 1;
    }
    else if (find_naked_single(board, row, col) is True) {
        return 2;
    }
    return 0;
}

int find_full_house(int **board, int row, int col) {
    if (row_full_house(board, row, col) is True) {
        return True;
    }
    else if (col_full_house(board, row, col) is True) {
        return True;
    }
    else if (sub_full_house(board, row, col) is True) {
        return True;
    }
    return False;
}

int row_full_house(int **board, int row, int col) {
    int count = 0, *fill_lst;
    fill_lst = memory_manage_1d();
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] isnot empty_slot) {
            ++count;
            fill_lst[board[row][i] - 1] = 1;
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            if (fill_lst[i] is empty_slot) {
                board[row][col] = i + 1;
                return True;
            }
        }
    }
    return False;
}

int col_full_house(int **board, int row, int col) {
    int count = 0, *fill_lst;
    fill_lst = memory_manage_1d();
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] isnot empty_slot) {
            ++count;
            fill_lst[board[i][col] - 1] = 1;
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            if (fill_lst[i] is empty_slot) {
                board[row][col] = i + 1;
                return True;
            }
        }
    }
    return False;
}

int sub_full_house(int **board, int row, int col) {
    int count = 0, *fill_lst, sub_x, sub_y;
    fill_lst = memory_manage_1d();
    sub_x = (row % 3 is 0) ? row: row - (row % 3), sub_y = (col % 3 is 0) ? col: col - (col % 3);
    for (int i = sub_x; i < sub_x + 3; ++i) {
        for (int j = sub_y; j < sub_y + 3; ++j) {
            if (board[i][j] isnot empty_slot) {
                ++count;
                fill_lst[board[i][j] - 1] = 1;
            }
        }
    }
    if (count is 8) {
        for (int i = 0; i < 9; ++i) {
            if (fill_lst[i] is empty_slot) {
                board[row][col] = i + 1;
                return True;
            }
        }
    }
    return False;
}

int find_naked_single(int **board, int row, int col) {
    if (cell[row][col].pos_num is 1) {
        for (int i = 0; i < 9; ++i) {
            if (cell[row][col].pos_lst[i] isnot empty_slot) {
                board[row][col] = cell[row][col].pos_lst[i];
                return True;
            }
        }
    }
    return False;
}

void update_board(int **board) {
    int num = 0;
    for (int i = 0; i < 27; ++i) {
        filled[i].lst = memory_manage_1d();
        if (i < 9) {
            for (int j = 0; j < 9; ++j) {
                filled[i].lst[j] = board[i][j];
            }
        }
        else if (i < 18) {
            for (int j = 0; j < 9; ++j) {
                filled[i].lst[j] = board[j][i % 9];
            }
        }
        else {
            int num = 0, sub_x;
            sub_x = (i < 3) ? 0: (i < 6) ? 3: 6;
            for (int j = sub_x; j < sub_x + 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    filled[i].lst[num++] = board[sub_x][k * 3];
                }
            }
        }
        filled[i].num = lst_count(filled[i].lst);
    }
}

int lst_count(int *lst) {
    int num = 0;
    for (int i = 0; i < 9; ++i) {
        if (lst[i] isnot empty_slot) {
            ++num;
        }
    }
    return num;
}
