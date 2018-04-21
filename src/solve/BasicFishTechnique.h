#ifndef BASICFISH_H_
#define BASICFISH_H_

int Find_XWing(int **board, int row, int col);
int RowBase_XWing(int **board, int row, int col);
int ColBase_XWing(int **board, int row, int col);
void Block_RowQuart(int **board, int num, int row_block, int col_block);
void Block_ColQuart(int **board, int num, int row_block, int col_block);

#endif
