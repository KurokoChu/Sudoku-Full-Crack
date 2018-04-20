#include <string.h>

#include "Sudoku.h"

// Global Variables
int stepRound = 0;

void startGuide()
{
    /* Main function */
    Setup();
    int **sudoku;
    sudoku = Init_Board(9, 9);
        if (Solve_Board(sudoku, 0, 0) isnot -1) {
        }

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
    if (step > 3) {
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
    Update_Eliminated();
    strcpy(textGuide[stepRound].text, "Full House : ");
    switch(step) {
        case 1:
            if (Find_FullHouse(board, row, col) is True) {

                strcpy(textGuide[stepRound].text, "Full House : ");
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        case 2:
            if (Find_NakedSingle(board, row, col) is True) {
                strcpy(textGuide[stepRound].text, "Naked Single : ");
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        case 3:
            if (Find_HiddenSingle(board, row, col) is True) {
                strcpy(textGuide[stepRound].text, "Hidden Single : ");
                textGuide[stepRound].row = row + 1;
                textGuide[stepRound].col = col + 1;
                textGuide[stepRound].num = board[row][col];
                sudoBoard[row][col].num = board[row][col];
                ++stepRound;
                return True;
            }
            break;
        default: return False;
    }
    return False;
}
