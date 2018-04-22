#include <string.h>

#include "Sudoku.h"
#include "SinglesTechnique.h"
#include "IntersectionsTechnique.h"
#include "SubsetsTechnique.h"
#include "BasicFishTechnique.h"

int stepRound;

int startGuide(int **board, int onlyGetStep, int freezeLoop) {
    /* Main function */
    Setup();
    int **sudoku, size_r = 9, size_c = 9;
    eliminated = False;
    stepRound = 0;
    sudoku = Init_Board(board);
    if (IsValid_Board(sudoku, size_r, size_c)) {
        if (Solve_Board(sudoku, onlyGetStep, freezeLoop) isnot -1) {
            if (IsValid_Board(sudoku, size_r, size_c) is True && Find_EmptySlot(sudoku, 0, 0) is False) {
                Score_Summary();
                return True;
            }
            else {
                return False;
            }
        }
    }
    else {
        return -1;
    }
    return 0;
}

int Solve_Board(int **board, int onlyGetStep, int freezeLoop) {
    /* Find the solution */
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Update_Board(board, i, j);
        }
    }
    if (onlyGetStep is True) {
        if (stepRound is freezeLoop) {
            return True;
        }
    }
    if (Find_EmptySlot(board, 0, 0) is False) {
        return True;
    }
    return GetStep(board, 1, onlyGetStep, freezeLoop);
}

int GetStep(int **board, int step, int onlyGetStep, int freezeLoop) {
    if (step > 12) {
        return False;
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] is EmptySlot) {
                coord.x = i;
                coord.y = j;
                if (DoStep(board, i, j, step) is True) {
                    return Solve_Board(board, onlyGetStep, freezeLoop);
                }
            }
        }
    }
    return GetStep(board, step + 1, onlyGetStep, freezeLoop);
}

int DoStep(int **board, int row, int col, int step) {
    Update_Eliminated();
    char *text;
    text = MemoryManage_1D_Char(128);
    switch(step) {
        case 1:
            if (Find_FullHouse(board, row, col) is True) {
                score[0].num = True;
                score[0].arr[0]++;
                sprintf(text, "Full House : r%dc%d = %d", row + 1, col + 1, board[row][col]);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                textGuide[stepRound].numCoord = 1;
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        case 2:
            if (Find_NakedSingle(board, row, col) is True) {
                score[1].num = True;
                score[1].arr[0]++;
                sprintf(text, "Naked Single : r%dc%d = %d", row + 1, col + 1, board[row][col]);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                textGuide[stepRound].numCoord = 1;
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        case 3:
            if (Find_HiddenSingle(board, row, col) is True) {
                ;score[2].num = True;
                score[2].arr[0]++;
                sprintf(text, "Hidden Single : r%dc%d = %d", row + 1, col + 1, board[row][col]);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                textGuide[stepRound].numCoord = 1;
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        case 4:
            if (Find_LockedPair(board, row, col) is True) {
                ;score[3].num = True;
                score[3].arr[0]++;
                sprintf(text, "Locked Pair : [ %s] in r%dc%d and r%dc%d", Show_ArrayElement_1D(cell[row][col].arr, 9),
                                                                          coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                          coord_pair.x2 + 1, coord_pair.y2 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 2;
                ++stepRound;
                return True;
            }
            break;
        case 5:
            if (Find_LockedTriple(board, row, col) is True) {
                score[4].num = True;
                score[4].arr[0]++;
                sprintf(text, "Locked Triple : [ %s] in r%dc%d, r%dc%d and r%dc%d", Show_ArrayElement_1D(triple.arr, 9),
                                                                                    coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                                    coord_pair.x2 + 1, coord_pair.y2 + 1,
                                                                                    coord_pair.x3 + 1, coord_pair.y3 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 3;
                ++stepRound;
                return True;
            }
            break;
        case 6:
            if (Find_LockedCandidates_1(board, row, col) is True) {
                score[5].num = True;
                score[5].arr[0]++;
                sprintf(text, "Locked Candidates Type 2 \"Claiming\" : [ %d ] in r%dc%d and r%dc%d", coord_pair.arr[0],
                                                                            coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                            coord_pair.x2 + 1, coord_pair.y2 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 2;
                ++stepRound;
                return True;
            }
            break;
        case 7:
            if (Find_LockedCandidates_2(board, row, col) is True) {
                score[6].num = True;
                score[6].arr[0]++;
                sprintf(text, "Locked Candidates Type 2 \"Claiming\" : [ %d ] in ", coord_pair.arr[0]);
                strcpy(textGuide[stepRound].text, text);
                if (coord_pair.num is 1) {
                    sprintf(text, "r%dc%d and r%dc%d", coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1);
                    strcat(textGuide[stepRound].text, text);
                    textGuide[stepRound].numCoord = 2;
                }
                else {
                    sprintf(text, "r%dc%d, r%dc%d and r%dc%d", coord_pair.x1 + 1, coord_pair.y1 + 1, coord_pair.x2 + 1, coord_pair.y2 + 1, coord_pair.x3 + 1, coord_pair.y3 + 1);
                    strcat(textGuide[stepRound].text, text);
                    textGuide[stepRound].numCoord = 3;
                }
                ++stepRound;
                return True;
            }
            break;
        case 8:
            if (Find_NakedPair(board, row, col) is True) {
                score[7].num = True;
                score[7].arr[0]++;
                sprintf(text, "Naked Pair : [ %s] in r%dc%d and r%dc%d", Show_ArrayElement_1D(coord_pair.arr, 9),
                                                                         coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                         coord_pair.x2 + 1, coord_pair.y2 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 2;
                ++stepRound;
                return True;
            }
            break;
        case 9:
            if (Find_NakedTriple(board, row, col) is True) {
                score[8].num = True;
                score[8].arr[0]++;
                sprintf(text, "Naked Triple : [ %s] in r%dc%d, r%dc%d and r%dc%d", Show_ArrayElement_1D(coord_pair.arr, 9),
                                                                                   coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                                   coord_pair.x2 + 1, coord_pair.y2 + 1,
                                                                                   coord_pair.x3 + 1, coord_pair.y3 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 3;
                ++stepRound;
                return True;
            }
            break;
        case 10:
            if (Find_HiddenPair(board, row, col) is True) {
                score[9].num = True;
                score[9].arr[0]++;
                sprintf(text, "Hidden Pair : [ %s] in r%dc%d and r%dc%d", Show_ArrayElement_1D(coord_pair.arr, 9),
                                                                          coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                          coord_pair.x2 + 1, coord_pair.y2 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 2;
                ++stepRound;
                return True;
            }
            break;
        case 11:
            if (Find_HiddenTriple(board, row, col) is True) {
                score[10].num = True;
                score[10].arr[0]++;
                sprintf(text, "Hidden Triple : [ %s] in r%dc%d, r%dc%d and r%dc%d", Show_ArrayElement_1D(coord_pair.arr, 9),
                                                                                    coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                                    coord_pair.x2 + 1, coord_pair.y2 + 1,
                                                                                    coord_pair.x3 + 1, coord_pair.y3 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 3;
                ++stepRound;
                return True;
            }
            break;
        case 12:
            if (Find_XWing(board, row, col) is True) {
                score[11].num = True;
                score[11].arr[0]++;
                sprintf(text, "X-Wing : [ %d ] in r%dc%d, r%dc%d, r%dc%d and r%dc%d\n", coord_pair.arr[0],
                                                                                        coord_pair.x1 + 1, coord_pair.y1 + 1,
                                                                                        coord_pair.x2 + 1, coord_pair.y2 + 1,
                                                                                        coord_pair.x3 + 1, coord_pair.y3 + 1,
                                                                                        coord_pair.x4 + 1, coord_pair.y4 + 1);
                strcpy(textGuide[stepRound].text, text);
                textGuide[stepRound].numCoord = 4;
                ++stepRound;
                return True;
            }
            break;
        default: return False;
    }
    return False;
}

void Score_Summary() {
    char *text;
    text = MemoryManage_1D_Char(1000);
    int is_score = False, count = 0;
    if (score[0].num is True) {
        is_score = True;
        sprintf(text, "%d Full House (%d)\n", score[0].arr[0], score[0].arr[0] * 4);
        strcat(textSummary.text, text);
        count += score[0].arr[0] * 4;
    }
    if (score[1].num is True) {
        is_score = True;
        sprintf(text, "%d Naked Single (%d)\n", score[1].arr[0], score[1].arr[0] * 4);
        strcat(textSummary.text, text);
        count += score[1].arr[0] * 4;
    }
    if (score[2].num is True) {
        is_score = True;
        sprintf(text, "%d Hidden Single (%d)\n", score[2].arr[0], score[2].arr[0] * 14);
        strcat(textSummary.text, text);
        count += score[2].arr[0] * 14;
    }
    if (score[3].num is True) {
        is_score = True;
        sprintf(text, "%d Locked Pair (%d)\n", score[3].arr[0], score[3].arr[0] * 40);
        strcat(textSummary.text, text);
        count += score[3].arr[0] * 40;
    }
    if (score[4].num is True) {
        is_score = True;
        sprintf(text, "%d Locked Triple (%d)\n", score[4].arr[0], score[4].arr[0] * 60);
        strcat(textSummary.text, text);
        count += score[4].arr[0] * 50;
    }
    if (score[5].num is True) {
        is_score = True;
        sprintf(text, "%d Locked Candidates Type 1 \"Pointing\" (%d)\n", score[5].arr[0], score[5].arr[0] * 50);
        strcat(textSummary.text, text);
        count += score[5].arr[0] * 50;
    }
    if (score[6].num is True) {
        is_score = True;
        sprintf(text, "%d Locked Candidates Type 2 \"Claiming\" (%d)\n", score[6].arr[0], score[6].arr[0] * 50);
        strcat(textSummary.text, text);
        count += score[6].arr[0] * 50;
    }
    if (score[7].num is True) {
        is_score = True;
        sprintf(text, "%d Naked Pair (%d)\n", score[7].arr[0], score[7].arr[0] * 60);
        strcat(textSummary.text, text);
        count += score[7].arr[0] * 60;
    }
    if (score[8].num is True) {
        is_score = True;
        sprintf(text, "%d Naked Triple (%d)\n", score[8].arr[0], score[8].arr[0] * 80);
        strcat(textSummary.text, text);
        count += score[8].arr[0] * 80;
    }
    if (score[9].num is True) {
        is_score = True;
        sprintf(text, "%d Hidden Pair (%d)\n", score[9].arr[0], score[9].arr[0] * 70);
        strcat(textSummary.text, text);
        count += score[9].arr[0] * 70;
    }
    if (score[10].num is True) {
        is_score = True;
        sprintf(text, "%d Hidden Triple (%d)\n", score[10].arr[0], score[10].arr[0] * 100);
        strcat(textSummary.text, text);
        count += score[10].arr[0] * 100;
    }
    if (score[11].num is True) {
        is_score = True;
        sprintf(text, "%d X-Wing (%d)\n", score[11].arr[0], score[11].arr[0] * 140);
        strcat(textSummary.text, text);
        count += score[11].arr[0] * 140;
    }

    if (is_score is True) {
        sprintf(text, "Total : %d", count);
        strcat(textSummary.text, text);
    }
    else {
        sprintf(text, "No Summary");
        strcat(textSummary.text, text);
    }
}
