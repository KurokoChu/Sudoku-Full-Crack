#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

struct score{
    int fullhouse, nakedsingle, hiddensingle;
} p1;

int test_solve(int **board, int row, int col);
int get_step (int **board, int row, int col);
int find_full_house(int **board, int row, int col);
int row_full_house(int **board, int row, int col);
int col_full_house(int **board, int row, int col);
int sub_full_house(int **board, int row, int col);
int find_naked_single(int **board, int row, int col);
int find_hidden_single(int **board, int row, int col);
int find_block(int **board, int row, int col, int num);
void update_board(int **board);
int lst_count(int *lst);
int lst_count_2d(int **lst, int row, int col);

int main() {
    /* Main function */
    int **sudoku;
    sudoku = board_init();
    if (is_valid_board(sudoku)) {
        printf("calculating . . .\n");
        if (solve_board(sudoku, 0, 0) is True) {
            printf("\nfinish!\n");
            show_board(sudoku);
            printf("%d Full House (%d)\n", p1.fullhouse, p1.fullhouse * 4);
            printf("%d Naked Single (%d)\n", p1.nakedsingle, p1.nakedsingle * 4);
            printf("%d Hidden Single (%d)\n", p1.hiddensingle, p1.hiddensingle * 14);
            printf("Total : %d\n", (p1.fullhouse * 4) + (p1.nakedsingle * 4) + (p1.hiddensingle * 14));
        }
        else {
            printf("can't find solution\n");
            show_board(sudoku);
        }
    }
    else {
        printf("Invalid Sudoku!\n");
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
            p1.fullhouse++;
            return solve_board(board, 0, 0);
        case 2:
            printf("Naked Single r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            p1.nakedsingle++;
            return solve_board(board, 0, 0);
        case 3:
            printf("Hidden Single r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            p1.hiddensingle++;
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
    else if (find_hidden_single(board, row, col) is True) {
        return 3;
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

int find_hidden_single(int **board, int row, int col) {
    for (int i = 0; i < 9; ++i) {
        if (cell[row][col].pos_lst[i] isnot empty_slot) {
            if (find_block(board, row, col, cell[row][col].pos_lst[i]) is True) {
                board[row][col] = cell[row][col].pos_lst[i];
                return True;
            }
        }
    }
    return False;
}

int find_block(int **board, int row, int col, int num) {
    int **count, sub_x, sub_y;
    count = memory_manage_sub2d();
    sub_x = (row % 3 is 0) ? row: row - (row % 3), sub_y = (col % 3 is 0) ? col: col - (col % 3);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] is num) {
                for (int k = sub_x; k < sub_x + 3; ++k) {
                    for (int l = sub_y; l < sub_y + 3; ++l) {
                        if (board[k][l] isnot empty_slot || k is i || l is j) {
                            count[k % 3][l % 3] = 1;
                        }
                    }
                }
            }
        }
    }
    if (lst_count_2d(count, 3, 3) is 8) {
        return True;
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

int lst_count_2d(int **lst, int row, int col) {
    int num = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (lst[i][j] isnot empty_slot) {
            ++num;
            }
        }
    }
    return num;
}
