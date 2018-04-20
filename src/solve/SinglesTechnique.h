#ifndef SINGLES_H_
#define SINGLES_H_

int Find_FullHouse(int **board, int row, int col);
int FullHouse_Row(int **board, int row, int col);
int FullHouse_Col(int **board, int row, int col);
int FullHouse_Sub(int **board, int row, int col);
int Find_NakedSingle(int **board, int row, int col);
int Find_HiddenSingle(int **board, int row, int col);
int Find_BlockNumber(int **board, int row, int col, int num);
int Find_RowBlock(int **board, int row, int col, int num);
int Find_ColBlock(int **board, int row, int col, int num);

#endif
