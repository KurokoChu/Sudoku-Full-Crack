#ifndef SUDOKUFUNCTION_H_
#define SUDOKUFUNCTION_H_

// Declare Function
int Find_EmptySlot(int **board, int start_r, int start_c);
int CanFillIn(int num, int **board, int size_r, int size_c);
int *Candidate_Digit(int **board, int size_r, int size_c);
void Eliminate_Digit(int **board, int num, int row, int col);
int AppendIn(int num, int **board, int size_r, int size_c, char cmp);
int IsValid_Board(int **board, int size_r, int size_c);
int **Init_Board(int **board);
void Update_Board(int **board, int row, int col);

#endif
