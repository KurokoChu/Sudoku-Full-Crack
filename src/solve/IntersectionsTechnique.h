#ifndef INTERSECT_H_
#define INTERSECT_H_

int Find_LockedPair(int **board, int row, int col);
int Find_LockedCandidates_1(int **board, int row, int col);
void Block_LockedRow(int **board, int num, int row_block, int col_block);
void Block_LockedCol(int **board, int num, int row_block, int col_block);
void Block_LockedSub(int **board, int num, int row_block, int col_block);
int Find_LockedCandidates_2(int **board, int row, int col);
int Count_SameDigit_Row(int **board, int index, int row, int col);
int Count_SameDigit_Col(int **board, int index, int row, int col);
int Find_LockedTriple(int **board, int row, int col);
int Row_LockedTriple(int **board, int row, int col);
int Col_LockedTriple(int **board, int row, int col);
int *Row_LockedElement(int **board, int row, int col);
int *Col_LockedElement(int **board, int row, int col);
void Block_RowTriple(int **board, int num, int row_block, int col_block);
void Block_ColTriple(int **board, int num, int row_block, int col_block);
void Block_SubTriple(int **board, int num, int row_block, int col_block);

#endif
