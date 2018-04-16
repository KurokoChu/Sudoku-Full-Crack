#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"
#include "test.h"
#include "SinglesTechnique.h"
#include "IntersectionsTechnique.h"
#include "SubsetsTechnique.h"

void Score_Summary();
int Solve_Board(int **board, int row, int col);
int GetStep(int **board, int step);
int DoStep(int **board, int row, int col, int step);

int main() {
    /* Main function */
    Setup();
    int **sudoku, size_r = 9, size_c = 9;
    sudoku = Init_Board(size_r, size_c);
    if (IsValid_Board(sudoku, size_r, size_c)) {
        printf("\nPlaying . . .\n\n");
        if (Solve_Board(sudoku, 0, 0) isnot -1) {
            if (IsValid_Board(sudoku, size_r, size_c) is True && Find_EmptySlot(sudoku, 0, 0) is False) {
                printf("\nFinish!\n");
                Show_Board(sudoku, size_r, size_c);
                Score_Summary();
            }
            else {
                printf("Need more Technique to solve\n");
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

int Solve_Board(int **board, int row, int col) {
    /* Find the solution */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Update_Board(board, i, j);
        }
    }
    if (Find_EmptySlot(board, 0, 0) is False) {
        return True;
    }
    return GetStep(board, 1);
}

int GetStep(int **board, int step) {
    if (step > 10) {
        return False;
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] is EmptySlot) {
                coord.x = i;
                coord.y = j;
                if (DoStep(board, i, j, step) is True) {
                    return Solve_Board(board, 0, 0);
                }
            }
        }
    }
    return GetStep(board, step + 1);
}

int DoStep(int **board, int row, int col, int step) {
    eliminated = False;
    switch(step) {
        case 1:
            if (Find_FullHouse(board, row, col) is True) {
                (score[0].num is False) ? score[0].num = True: 1;
                score[0].arr[0]++;
                printf("Full House : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
                return True;
            }
            break;
        case 2:
            if (Find_NakedSingle(board, row, col) is True) {
                (score[1].num is False) ? score[1].num = True: 1;
                score[1].arr[0]++;
                printf("Naked Single : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
                return True;
            }
            break;
        case 3:
            if (Find_HiddenSingle(board, row, col) is True) {
                (score[2].num is False) ? score[2].num = True: 1;
                score[2].arr[0]++;
                printf("Hidden Single : r%dc%d = %d\n", row + 1, col + 1, board[row][col]);
                return True;
            }
            break;
        case 4:
            if (Find_LockedPair(board, row, col) is True) {
                (score[3].num is False) ? score[3].num = True: 1;
                score[3].arr[0]++;
                printf("Locked Pair : [ ");
                Show_ArrayElement_1D(cell[row][col].arr, 9);
                printf("] in r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                   coord_pair.x2 + 1, coord_pair.y2 + 1);
                return True;
            }
            break;
        case 5:
            if (Find_LockedTriple(board, row, col) is True) {
                (score[4].num is False) ? score[4].num = True: 1;
                score[4].arr[0]++;
                printf("Locked Triple : [ ");
                Show_ArrayElement_1D(triple.arr, 9);
                printf("] in r%dc%d, r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                           coord_pair.x2 + 1, coord_pair.y2 + 1, 
                                                           coord_pair.x3 + 1, coord_pair.y3 + 1);
                return True;
            }
            break;
        case 6:
            if (Find_LockedCandidates_1(board, row, col) is True) {
                (score[5].num is False) ? score[5].num = True: 1;
                score[5].arr[0]++;
                printf("Locked Candidates Type 1 \"Pointing\" : [ %d ] in r%dc%d and r%dc%d\n", coord_pair.arr[0],
                                                                                                coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                                                                coord_pair.x2 + 1, coord_pair.y2 + 1);
                return True;
            }
            break;
        case 7:
            if (Find_LockedCandidates_2(board, row, col) is True) {
                (score[6].num is False) ? score[6].num = True: 1;
                score[6].arr[0]++;
                printf("Locked Candidates Type 2 \"Claiming\" : [ %d ] in ", coord_pair.arr[0]);
                (coord_pair.num is 1) ? printf("r%dc%d and r%dc%d\n", 
                                        coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                        coord_pair.x2 + 1, coord_pair.y2 + 1):
                                    printf("r%dc%d, r%dc%d and r%dc%d\n", 
                                        coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                        coord_pair.x2 + 1, coord_pair.y2 + 1, 
                                        coord_pair.x3 + 1, coord_pair.y3 + 1);
                return True;
            }
            break;
        case 8:
            if (Find_NakedPair(board, row, col) is True) {
                (score[7].num is False) ? score[7].num = True: 1;
                score[7].arr[0]++;
                printf("Naked Pair : [ ");
                Show_ArrayElement_1D(coord_pair.arr, 9);
                printf("] in r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                   coord_pair.x2 + 1, coord_pair.y2 + 1);
                return True;
            }
            break;
        case 9:
            if (Find_NakedTriple(board, row, col) is True) {
                (score[8].num is False) ? score[8].num = True: 1;
                score[8].arr[0]++;
                printf("Naked Triple : [ ");
                Show_ArrayElement_1D(coord_pair.arr, 9);
                printf("] in r%dc%d, r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                           coord_pair.x2 + 1, coord_pair.y2 + 1,
                                                           coord_pair.x3 + 1, coord_pair.y3 + 1);
                return True;
            }
            break;
        case 10:
            if (Find_HiddenPair(board, row, col) is True) {
                (score[9].num is False) ? score[9].num = True: 1;
                score[9].arr[0]++;
                printf("Hidden Pair : [ ");
                Show_ArrayElement_1D(coord_pair.arr, 9);
                printf("] in r%dc%d and r%dc%d\n", coord_pair.x1 + 1, coord_pair.y1 + 1, 
                                                   coord_pair.x2 + 1, coord_pair.y2 + 1);
                return True;
            }
            break;
        default: return False;
    }
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
        printf("%d Locked Triple (%d)\n", score[4].arr[0], score[4].arr[0] * 60);
        count += score[4].arr[0] * 50;
    }
    if (score[5].num is True) {
        is_score = True;
        printf("%d Locked Candidates Type 1 \"Pointing\" (%d)\n", score[5].arr[0], score[5].arr[0] * 50);
        count += score[5].arr[0] * 50;
    }
    if (score[6].num is True) {
        is_score = True;
        printf("%d Locked Candidates Type 2 \"Claiming\" (%d)\n", score[6].arr[0], score[6].arr[0] * 50);
        count += score[6].arr[0] * 50;
    }
    if (score[7].num is True) {
        is_score = True;
        printf("%d Naked Pair (%d)\n", score[7].arr[0], score[7].arr[0] * 60);
        count += score[7].arr[0] * 60;
    }
    if (score[8].num is True) {
        is_score = True;
        printf("%d Naked Triple (%d)\n", score[8].arr[0], score[8].arr[0] * 80);
        count += score[8].arr[0] * 80;
    }
    if (score[9].num is True) {
        is_score = True;
        printf("%d Hidden Pair (%d)\n", score[9].arr[0], score[9].arr[0] * 70);
        count += score[9].arr[0] * 70;
    }

    if (is_score is True) {
        printf("Total : %d\n", count);
    }
    else {
        printf("No Summary\n");
    }
}
