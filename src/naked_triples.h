#pragma once

#include "sudoku.h"
#include <stdlib.h>

int Locate_inbox(SudokuBoard *board, int rowPos, int colPos, int boxPos);

int naked_triples(SudokuBoard *p_board);