#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "SinglesTechnique.h"
#include "IntersectionsTechnique.h"

void Score_Summary();
int Solve_Board(int **board, int row, int col, int size_r, int size_c);
int DoStep(int **board, int row, int col, int size_r, int size_c);
int GetStep(int **board, int row, int col);

int main() {
    /* Main function */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cell[i][j].arr = MemoryManage_1D(9);
            eliminate[i][j].arr = MemoryManage_1D(9);
            lock_pair[i][j].arr = MemoryManage_1D(1);
            lock_can1[i][j].arr = MemoryManage_1D(1);
        }
    }
    for (int i = 0; i < 6; ++i) {
        score[i].num = False;
        score[i].arr = MemoryManage_1D(1);
    }
    coord_pair.arr = MemoryManage_1D(2);
    int **sudoku, size_r = 9, size_c = 9;
    sudoku = Init_Board(size_r, size_c);
    if (IsValid_Board(sudoku, size_r, size_c)) {
        printf("\nPlaying . . .\n\n");
        if (Solve_Board(sudoku, 0, 0, size_r, size_c) is True) {
            if (Find_EmptySlot(sudoku, 0, 0) is False) {
                if (IsValid_Board(sudoku, size_r, size_c) is True) {
                    printf("\nFinish!\n");
                    Show_Board(sudoku, size_r, size_c);
                    Score_Summary();
                }
                else {
                    Show_Board(sudoku, size_r, size_c);
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
        printf("at r%dc%d\n", coord.x + 1, coord.y + 1);
    }
    return 0;
}

int Solve_Board(int **board, int row, int col, int size_r, int size_c) {
    /* Find the solution */
    for (int i = 0; i < size_r; ++i) {
        for (int j = 0; j < size_c; ++j) {
            Update_Board(board, i, j);
        }
    }
    if (Find_EmptySlot(board, row, col) is False) {
        return True;
    }
    return DoStep(board, coord.x, coord.y, size_r, size_c);
}

int DoStep(int **board, int row, int col, int size_r, int size_c) {
    int next_row, next_col;
    next_row = 0;
    next_col = 0;
    switch(GetStep(board, row, col)) {
        case 1:
            printf("Full House : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            score[0].arr[0]++;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        case 2:
            printf("Naked Single : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            score[1].arr[0]++;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        case 3:
            printf("Hidden Single : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
            score[2].arr[0]++;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        case 4:
            printf("Locked Pair : [ ");
            Show_ArrayElement_1D(cell[row][col].arr, 9);
            printf("] in r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1);
            score[3].arr[0]++;
            next_row = (col + 1 == 9) ? row + 1: row;
            next_col = (col + 1) % 9;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        case 5:
            printf("Locked Candidates Type 1 \"Pointing\" : [ %d ] in r%dc%d and r%dc%d\n", coord_pair.num, coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1);
            score[4].arr[0]++;
            next_row = (col + 1 == 9) ? row + 1: row;
            next_col = (col + 1) % 9;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        case 6:
            if (coord_pair.num is 1) {
                printf("Locked Candidates Type 2 \"Claiming\" : [ %d ] in r%dc%d and r%dc%d\n", 
                    coord_pair.arr[0], coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1);
            }
            else if (coord_pair.num is 2) {
                printf("Locked Candidates Type 2 \"Claiming\" : [ %d ] in r%dc%d, r%dc%d and r%dc%d\n", 
                    coord_pair.arr[0], coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1, coord_pair.x3 + 1, coord_pair.y3 + 1);
            }
            score[5].arr[0]++;
            next_row = (col + 1 == 9) ? row + 1: row;
            next_col = (col + 1) % 9;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
        default:
            next_row = (col + 1 == 9) ? row + 1: row;
            next_col = (col + 1) % 9;
            return Solve_Board(board, next_row, next_col, size_r, size_c);
    }
}

int GetStep(int **board, int row, int col) {
    eliminated = False;
    if (Find_FullHouse(board, row, col) is True) {
        (score[0].num is False) ? score[0].num = True: 1;
        return 1;
    }
    else if (Find_NakedSingle(board, row, col) is True) {
        (score[1].num is False) ? score[1].num = True: 1;
        return 2;
    }
    else if (Find_HiddenSingle(board, row, col) is True) {
        (score[2].num is False) ? score[2].num = True: 1;
        return 3;
    }
    else if (Find_LockedPair(board, row, col) is True && eliminated is True) {
        (score[3].num is False) ? score[3].num = True: 1;
        return 4;
    }
    else if (Find_LockedCandidates_1(board, row, col) is True && eliminated is True) {
        (score[4].num is False) ? score[4].num = True: 1;
        return 5;
    }
    else if (Find_LockedCandidates_2(board, row, col) is True && eliminated is True) {
        (score[5].num is False) ? score[5].num = True: 1;
        return 6;
    }
    return 0;
}

void Score_Summary() {
    int is_score = False, count = 0;
    if (score[0].num is True) {
        is_score = True;
        printf("%d Full House (%d)\n", score[0].arr[0], score[0].arr[0] * 4);
        count += score[0].arr[0] * 4;
    }
    if (score[1].num is True) {
        is_score = True;
        printf("%d Naked Single (%d)\n", score[1].arr[0], score[1].arr[0] * 4);
        count += score[1].arr[0] * 4;
    }
    if (score[2].num is True) {
        is_score = True;
        printf("%d Hidden Single (%d)\n", score[2].arr[0], score[2].arr[0] * 14);
        count += score[2].arr[0] * 14;
    }
    if (score[3].num is True) {
        is_score = True;
        printf("%d Locked Pair (%d)\n", score[3].arr[0], score[3].arr[0] * 40);
        count += score[3].arr[0] * 40;
    }
    if (score[4].num is True) {
        is_score = True;
        printf("%d Locked Candidates Type 1 \"Pointing\" (%d)\n", score[4].arr[0], score[4].arr[0] * 50);
        count += score[4].arr[0] * 50;
    }
    if (score[5].num is True) {
        is_score = True;
        printf("%d Locked Candidates Type 2 \"Claiming\" (%d)\n", score[5].arr[0], score[5].arr[0] * 50);
        count += score[5].arr[0] * 50;
    }

    if (is_score is True) {
        printf("Total : %d\n", count);
    }
    else {
        printf("No Summary\n");
    }
}
