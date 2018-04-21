#ifndef SUBSETS_H_
#define SUBSETS_H_

int Find_NakedPair(int **board, int row, int col);
int Find_NakedTriple(int **board, int row, int col);
int Row_NakedTriple(int **board, int row, int col);
int Col_NakedTriple(int **board, int row, int col);
int Sub_NakedTriple(int **board, int row, int col);
int Find_HiddenPair(int **board, int row, int col);
int Row_HiddenPair(int **board, int row, int col);
int Col_HiddenPair(int **board, int row, int col);
int Sub_HiddenPair(int **board, int row, int col);
int Find_HiddenTriple(int **board, int row, int col);
int Row_HiddenTriple(int **board, int row, int col);
int Col_HiddenTriple(int **board, int row, int col);
int Sub_HiddenTriple(int **board, int row, int col);

#endif
