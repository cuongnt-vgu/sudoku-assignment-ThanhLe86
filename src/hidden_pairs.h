#pragma once

#include "sudoku.h"
#include <stdlib.h>

int Locate_inbox(SudokuBoard *p_board, int rowPos, int colPos, int boxPos);
int hidden_pairs(SudokuBoard *p_board);
