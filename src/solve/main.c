int Solve_Board(int **board, int row, int col, int size_r, int size_c);
int DoStep(int **board, int row, int col, int size_r, int size_c);
int GetStep(int **board, int row, int col);
void update_board(int **board, int size);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "SinglesTechnique.h"
#include "IntersectionsTechnique.h"

struct score{
    int fullhouse, nakedsingle, hiddensingle, lockedpair;
} p;

int Solve_Board(int **board, int row, int col, int size_r, int size_c);
int DoStep(int **board, int row, int col, int size_r, int size_c);
int GetStep(int **board, int row, int col);
void update_board(int **board, int size);

int main() {
    /* Main function */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cell[i][j].arr = MemoryManage_1D(9);
            eliminate[i][j].arr = MemoryManage_1D(9);
            lock[i][j].arr = MemoryManage_1D(1);
        }
    }
    int **sudoku, size_r = 9, size_c = 9;
    sudoku = Init_Board(size_r, size_c);
    if (IsValid_Board(sudoku, size_r, size_c)) {
        printf("\nPlaying . . .\n\n");
        if (Solve_Board(sudoku, 0, 0, size_r, size_c) is True) {
            if (Find_EmptySlot(sudoku, 0, 0) is False) {
                if (IsValid_Board(sudoku, size_r, size_c) is True) {
                    printf("\nFinish!\n");
                    Show_Board(sudoku, size_r, size_c);
                    printf("%d Full House (%d)\n", p.fullhouse, p.fullhouse * 4);
                    printf("%d Naked Single (%d)\n", p.nakedsingle, p.nakedsingle * 4);
                    printf("%d Hidden Single (%d)\n", p.hiddensingle, p.hiddensingle * 14);
                    printf("%d Locked Pair (%d)\n", p.lockedpair, p.lockedpair * 40);
                    printf("Total : %d\n", (p.fullhouse * 4) + (p.nakedsingle * 4) + (p.hiddensingle * 14) + (p.lockedpair * 40));
                }
            }
            else {
                printf("I need to practice more\n");
                Show_Board(sudoku, size_r, size_c);
            }
        }
        else {
            printf("Can't find solution\n");
            Show_Board(sudoku, size_r, size_c);
        }
    }
    else {
        printf("Invalid Sudoku!\n");
    }
    return 0;
}

int Solve_Board(int **board, int row, int col, int size_r, int size_c) {
    /* Find the solution */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] is EmptySlot) {
                coord.x = i;
                coord.y = j;
                cell[i][j].arr = Candidate_Digit(board, 9, 9);
                cell[i][j].num = coord.len;
            }
        }
    }
    if (Find_EmptySlot(board, row, col) is False) {
        return True;
    }
    return DoStep(board, coord.x, coord.y, size_r, size_c);
}

int DoStep(int **board, int row, int col, int size_r, int size_c) {
    switch(GetStep(board, row, col)) {
        case 1:
            printf("Full House: r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            p.fullhouse++;
            return Solve_Board(board, 0, 0, size_r, size_c);
        case 2:
            printf("Naked Single: r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            p.nakedsingle++;
            return Solve_Board(board, 0, 0, size_r, size_c);
        case 3:
            printf("Hidden Single: r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            p.hiddensingle++;
            return Solve_Board(board, 0, 0, size_r, size_c);
        case 4:
            printf("Locked Pair: [ ");
            for (int i = 0; i < 9; ++i) {
                (cell[row][col].arr[i] isnot EmptySlot) ? printf("%d ", i + 1): 1;
            }
            printf("] in r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1);
            p.lockedpair++;
            row = (col + 1 == 9) ? row + 1: row;
            col = (col + 1) % 9;
            return Solve_Board(board, row, col, size_r, size_c);
        default:
            row = (col + 1 == 9) ? row + 1: row;
            col = (col + 1) % 9;
            return Solve_Board(board, row, col, size_r, size_c);
    }
}

int GetStep(int **board, int row, int col) {
    if (Find_FullHouse(board, row, col) is True) {
        return 1;
    }
    else if (Find_NakedSingle(board, row, col) is True) {
        return 2;
    }
    else if (Find_HiddenSingle(board, row, col) is True) {
        return 3;
    }
    else if (Find_LockedPair(board, row, col) is True) {
        return 4;
    }
    return 0;
}

void update_board(int **board, int size) {
    int num = 0;
    for (int i = 0; i < 27; ++i) {
        filled[i].arr = MemoryManage_1D(size);
        if (i < 9) {
            for (int j = 0; j < 9; ++j) {
                filled[i].arr[j] = board[i][j];
            }
        }
        else if (i < 18) {
            for (int j = 0; j < 9; ++j) {
                filled[i].arr[j] = board[j][i % 9];
            }
        }
        else {
            int num = 0, sub_x;
            sub_x = (i < 3) ? 0: (i < 6) ? 3: 6;
            for (int j = sub_x; j < sub_x + 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    filled[i].arr[num++] = board[sub_x][k * 3];
                }
            }
        }
        filled[i].num = ArrayCount_1D(filled[i].arr, size);
    }
}
