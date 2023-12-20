#include "hidden_singles.h"
#include <stdlib.h>

int Check_Board(SudokuBoard* board, int rowPos, int colPos, int boxPos, int posinbox, int candidate)
{
    Cell *Current_cell;
    int unique = 0;

    //check for candidate uniqueness in row
    for(int idx = 0; idx < BOARD_SIZE; idx++)
    {
        Current_cell = board->p_rows[rowPos][idx];
        if (idx == colPos) continue;
        if (Current_cell->candidates[candidate] == 1)
        {
            unique++;
            break;
        }
    }

    //check for candidate uniqueness in column
    for (int idx = 0; idx < BOARD_SIZE; idx++)
    {
        Current_cell = board->p_cols[colPos][idx];
        if (idx == rowPos) continue;
        if (Current_cell->candidates[candidate] == 1)
        {
            unique++;
            break;    
        }
        
    }

    //check for candidate uniqueness in box
    for (int idx = 0; idx < BOARD_SIZE; idx++)
    {
        Current_cell = board->p_boxes[boxPos][idx];
        if (idx == posinbox) continue;
        if (Current_cell->candidates[candidate] == 1)
        {
            unique++;
            break;
        }
    }
    return unique;
}

int Locate_in_box(SudokuBoard *board, int rowPos, int colPos, int boxPos)
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

void Solvewhiddensingle(SudokuBoard *board, int hidden_single_num)
{
    struct Position *position;
    Cell *CurrentCell;
    for(int index = 0; index < hidden_single_num; index++)
    {
        //extract information
        position = board->hidden_single_positions[index];
        int rowinf = position->row;
        int colinf = position->col;
        int val = position->candidateValue;

        //Set candidate in hidden single cell 
        int candidates[] = {val+1}; 
        CurrentCell = &board->data[rowinf][colinf];
        // for(int indx = 0; indx < BOARD_SIZE; indx++)
        // {
        //     if (indx == position->candidateValue) continue;
        //     CurrentCell->candidates[indx] = 0;
        // }
        set_candidates(CurrentCell, candidates, 1);
    }
}

int hidden_singles(SudokuBoard *p_board)
{
    int hidden_singles_quant = 0;
    Cell *Curr_pointer;
    p_board->hidden_single_positions = malloc(BOARD_SIZE * BOARD_SIZE* sizeof(struct Position*));
    for(int index = 0; index < BOARD_SIZE; index++)
    {
        for(int index2 = 0; index2 < BOARD_SIZE; index2++)
        { 
            Curr_pointer = &p_board->data[index][index2];
            if(Curr_pointer->num_candidates > 1)
            {
                for(int Candidate_idx = 0; Candidate_idx < BOARD_SIZE; Candidate_idx++)
                {
                    if(Curr_pointer->candidates[Candidate_idx] == 1)
                    {
                        int rowPos = Curr_pointer->row_index;
                        int colPos = Curr_pointer->col_index;
                        int boxPos = Curr_pointer->box_index;
                        int posinbox = Locate_in_box(p_board, rowPos, colPos, boxPos);
                        int res = Check_Board(p_board, rowPos, colPos, boxPos, posinbox, Candidate_idx);
                        if (res != 3)
                        {
                            struct Position *newposi = malloc(sizeof(struct Position));
                            newposi->row = index;
                            newposi->col = colPos;
                            newposi->box = boxPos;
                            newposi->posinsidebox = posinbox;
                            newposi->candidateValue = Candidate_idx;
                            p_board->hidden_single_positions[hidden_singles_quant] = newposi;
                            hidden_singles_quant++;
                        }
                    }
                }
            }
        }
    }
    Solvewhiddensingle(p_board, hidden_singles_quant);
    for(int i = 0; i < hidden_singles_quant; i++)
    {
        free(p_board->hidden_single_positions[i]); 
    }
    free(p_board->hidden_single_positions); // delete []

    return hidden_singles_quant;
}
