#pragma once

#include "sudoku.h"

int Locate_inbox(SudokuBoard *board, int rowPos, int colPos, int boxPos)
{
    Cell *CurrentCell;
    int result; 
    for(int idx = 0; idx < BOARD_SIZE; idx++){
        CurrentCell = board->p_boxes[boxPos][idx];
        if(CurrentCell->row_index == rowPos && CurrentCell->col_index == colPos)
        {
            result = idx;
            break;
        }
    }
    return result;
}
