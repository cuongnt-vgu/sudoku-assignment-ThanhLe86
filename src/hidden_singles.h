#pragma once

#include "sudoku.h"

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_hidden_single_values(Cell **p_cells, int *hidden_single_values);

// find hidden single cells in a board, return the number of hidden single cells
int hidden_singles(SudokuBoard *p_board);
