#include "naked_pairs.h"
#include "auxiliary.h"
#include <stdlib.h>


int Find_Same_Candidate(SudokuBoard *board, struct Naked_pairs_Pos* n_position, 
    int x, int y, int boxnum, int boxcell, int naked_pairs_num)
{
    int naked_pairs = 0;
    Cell *Currentcell;
    for(int idx = 0; idx < 2; idx++)
        n_position->position[idx] = malloc(sizeof(struct Position));

    for(int index = 0; index < BOARD_SIZE; index++)
    {
        //Find other naked pair in the same row
        int confirmationcount = 0;
        Currentcell = board->p_rows[x][index];
        if (index == y) continue;
        if (Currentcell->num_candidates == 2)
        {
            for(int idx = 0; idx < 2; idx++){
                if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
                confirmationcount++;
            }
            if(confirmationcount == 2 && Currentcell->found != true)
            {   
                n_position->position[1]->row = Currentcell->row_index;
                n_position->position[1]->col = Currentcell->col_index;
                n_position->position[1]->box = Currentcell->box_index;
                n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
                Currentcell->col_index, Currentcell->box_index);
                Currentcell->found = true;
                naked_pairs++;
            }
        }
    }

    for(int index = 0; index < BOARD_SIZE; index++)
    {
        //Find other naked pair in the same column
        int confirmationcount = 0;
        Currentcell = board->p_cols[y][index];
        if (index == x) continue;
        if (Currentcell->num_candidates == 2)
        {
            for(int idx = 0; idx < 2; idx++){
                if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
                confirmationcount++;
            }
            if(confirmationcount == 2 && Currentcell->found != true)
            {
                n_position->position[1]->row = Currentcell->row_index;
                n_position->position[1]->col = Currentcell->col_index;
                n_position->position[1]->box = Currentcell->box_index;
                n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
            Currentcell->col_index, Currentcell->box_index);
                Currentcell->found = true;
                naked_pairs++;
            }
        }
    }

    for(int index = 0; index < BOARD_SIZE; index++)
    {
        //Find other naked pair in the same box
        int confirmationcount = 0;
        Currentcell = board->p_boxes[boxnum][index];
        if (index == boxcell) continue;
        if (Currentcell->num_candidates == 2)
        {
            for(int idx = 0; idx < 2; idx++){
                if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
                confirmationcount++;
            }
            if(confirmationcount == 2 && Currentcell->found != true)
            {
                n_position->position[1]->row = Currentcell->row_index;
                n_position->position[1]->col = Currentcell->col_index;
                n_position->position[1]->box = Currentcell->box_index;
                n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
            Currentcell->col_index, Currentcell->box_index);
                Currentcell->found = true;
                naked_pairs++;
            }
        }
    }
    if(naked_pairs != 0) board->N_Positions[naked_pairs_num] = n_position;
    return naked_pairs;
}

void SaveCandidate(struct Naked_pairs_Pos* position, Cell *currcell)
{
    int newcandidateidx = 0;
    for(int idx = 0; idx < BOARD_SIZE; idx++)
    {
        if(currcell->candidates[idx] == 1){
            position->candidateValues[newcandidateidx] = idx;
            newcandidateidx++;
        }
    }
}

void SolvewNakedPairs(SudokuBoard *board, int nakedquantity){
    struct Naked_pairs_Pos *data;
    Cell *CurrentCell;
    for (int index = 0; index < nakedquantity; index++)
    {
        data = board->N_Positions[index];
        //eliminate similar candidate from row
        int row1 = data->position[0]->row;
        int row2 = data->position[1]->row;
        if(row1 == row2)
        {   
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                if(idx == data->position[0]->col || idx == data->position[1]->col) continue;
                CurrentCell = board->p_rows[row1][idx];
                for(int idx2 = 0; idx2 < 2; idx2++)
                {
                    if(CurrentCell->candidates[data->candidateValues[idx2]] == 1 
                && CurrentCell->num_candidates > 1)
                    { 
                        CurrentCell->candidates[data->candidateValues[idx2]] = 0;
                        CurrentCell->num_candidates--;
                    }
                }
            }
        }
        //eliminate similar candidate from column
        int col1 = data->position[0]->col;
        int col2 = data->position[1]->col;
        if(col1 == col2)
        {
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                if(idx == data->position[0]->row || idx == data->position[1]->row) continue;
                CurrentCell = board->p_cols[col1][idx];
                for(int idx2 = 0; idx2 < 2; idx2++)
                {
                    if(CurrentCell->candidates[data->candidateValues[idx2]] == 1 
                && CurrentCell->num_candidates > 1)
                    { 
                        CurrentCell->candidates[data->candidateValues[idx2]] = 0;
                        CurrentCell->num_candidates--;
                    }
                }
            }
        }

        //eliminate similar candidate from box
        int box1 = data->position[0]->box;
        int box2 = data->position[1]->box;
        if(box1 == box2)
        {
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                if(idx == data->position[0]->posinsidebox || idx == data->position[1]->posinsidebox) 
                continue;
                CurrentCell = board->p_boxes[box1][idx];
                for(int idx2 = 0; idx2 < 2; idx2++)
                {
                    if(CurrentCell->candidates[data->candidateValues[idx2]] == 1 
                && CurrentCell->num_candidates > 1)
                    { 
                        CurrentCell->candidates[data->candidateValues[idx2]] = 0;
                        CurrentCell->num_candidates--;
                    }
                }
            }
        }
    }
}

int naked_pairs(SudokuBoard *p_board)
{
    Cell *CurrentCell;
    int naked_pairs_quant = 0;
    p_board->N_Positions = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct Naked_pairs_Pos*));
    for (int index = 0; index < BOARD_SIZE; index++)
    {
        for (int index2 = 0; index2 < BOARD_SIZE; index2++)
        {
            CurrentCell = &p_board->data[index][index2];
            if(CurrentCell->num_candidates == 2)
            {
                int boxnum = CurrentCell->box_index;
                int posinsidebox = Locate_inbox(p_board, index, index2, boxnum);
                struct Naked_pairs_Pos *newposi = malloc(sizeof(struct Naked_pairs_Pos));
                SaveCandidate(newposi, CurrentCell);
                int quant = Find_Same_Candidate(p_board, newposi, index, index2, 
            boxnum, posinsidebox, naked_pairs_quant);
                if(quant != 0)
                {
                    naked_pairs_quant++;
                    CurrentCell->found = true; 
                    struct Position *extraction = newposi->position[0];
                    extraction->row = CurrentCell->row_index;
                    extraction->col = CurrentCell->col_index;
                    extraction->box = CurrentCell->box_index;
                    extraction->posinsidebox = Locate_inbox(p_board, CurrentCell->row_index, 
                    CurrentCell->col_index, CurrentCell->box_index);
                } 
                else
                {
                    for(int idx = 0; idx < 2; idx++)
                    { 
                        free(newposi->position[idx]);
                        newposi->position[idx] = NULL; // Avoid dangling pointers
                    }

                    free(newposi);
                    newposi = NULL; // Avoid dangling pointers
                } 
            }

        }
    }

    //Solve board with naked pairs method
    SolvewNakedPairs(p_board, naked_pairs_quant);

    //free dynamically allocated memories
    for(int i = 0; i < naked_pairs_quant; i++)
    {
        for (int j = 0; j < 2; j++) free(p_board->N_Positions[i]->position[j]);
        free(p_board->N_Positions[i]); 
    }
    free(p_board->N_Positions); // delete []

    //return number of naked pairs
    return naked_pairs_quant;
}