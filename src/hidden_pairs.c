#include "hidden_pairs.h"

void Save_hidden_pair_position(SudokuBoard* p_board, Cell* CurrentCell, int position_inside_box, int hidden_pairs_number, int* candidate_checker)
{
    int newcandidateidx = 0;
    //Save hidden pair candidates
    for(int index = 0; index < 9; index ++)
    {
        if(candidate_checker[index] == 2) 
        {
            struct hidden_pairs_position* hidden_pairs = p_board->hidden_pairs_positions[hidden_pairs_number];
            hidden_pairs->hidden_pairs_candidates[newcandidateidx] = candidate_checker[index];
            newcandidateidx++;
        }
    }
    //Save cell position
    struct Position* newposition = p_board->hidden_pairs_positions[hidden_pairs_number]->position;
    newposition->row = CurrentCell->row_index;
    newposition->col = CurrentCell->col_index;
    newposition->box = CurrentCell->box_index;
    newposition->posinsidebox = position_inside_box;
    CurrentCell->found = true;
}

void Solve_with_hidden_pair(SudokuBoard* p_board, int hidden_pairs_number)
{
    for(int index = 0; index < hidden_pairs_number; index++)
    {
        struct Position* current_hidden_pairs_position = p_board->hidden_pairs_positions[index]->position;
        int row = current_hidden_pairs_position->row;
        int col = current_hidden_pairs_position->col;
        //check within same row
        for(int idx = 0; idx < BOARD_SIZE; idx++)
        {
            if(idx == current_hidden_pairs_position->col) continue;
            Cell* SecondCell = p_board->p_rows[current_hidden_pairs_position->row][idx];
            if(SecondCell->found == true)
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                {
                    bool is_saved_candidate = true;
                    struct hidden_pairs_position* current_hidden_pairs_candidate = p_board->hidden_pairs_positions[index];
                    for(int j = 0; j < 2; j++){
                        if(i != current_hidden_pairs_candidate->hidden_pairs_candidates[j]) 
                            is_saved_candidate = false;
                    }   
                    int cellcandidate = SecondCell->candidates[i];

                    if(cellcandidate == 1 && is_saved_candidate == false)
                    {
                        cellcandidate = 0;
                        SecondCell->num_candidates--;
                    }
                }
            }

        }
        //check within same column
        for(int idx = 0; idx < BOARD_SIZE; idx++)
        {
            if(idx == current_hidden_pairs_position->row) continue;
            Cell* SecondCell = p_board->p_cols[current_hidden_pairs_position->col][idx];
            if(SecondCell->found == true)
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                {
                    bool is_saved_candidate = true;
                    struct hidden_pairs_position* current_hidden_pairs_candidate = p_board->hidden_pairs_positions[index];
                    for(int j = 0; j < 2; j++){
                        if(i != current_hidden_pairs_candidate->hidden_pairs_candidates[j]) 
                            is_saved_candidate = false;
                    }   
                    int cellcandidate = SecondCell->candidates[i];

                    //Delete candidate
                    if(cellcandidate == 1 && is_saved_candidate == false)
                    {
                        cellcandidate = 0;
                        SecondCell->num_candidates--;
                    }
                }
            }
        }

        //check within same box
        for(int idx = 0; idx < BOARD_SIZE; idx++)
        {
            if(idx == current_hidden_pairs_position->posinsidebox) continue;
            Cell* SecondCell = p_board->p_boxes[current_hidden_pairs_position->box][idx];
            if(SecondCell->found == true)
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                {

                    bool is_saved_candidate = true;
                    struct hidden_pairs_position* current_hidden_pairs_candidate = p_board->hidden_pairs_positions[index];
                    for(int j = 0; j < 2; j++){
                        if(i != current_hidden_pairs_candidate->hidden_pairs_candidates[j]) 
                            is_saved_candidate = false;
                    }   
                    int cellcandidate = SecondCell->candidates[i];

                    //Delete candidate
                    if(cellcandidate == 1 && is_saved_candidate == false)
                    {
                        cellcandidate = 0;
                        SecondCell->num_candidates--;
                    }
                }
            }
        }

        //solve current cell
        Cell* CurrentCell = &p_board->data[row][col];
        for (int i = 0; i < BOARD_SIZE; i++)
        {

            bool is_saved_candidate = true;
            struct hidden_pairs_position* current_hidden_pairs_candidate = p_board->hidden_pairs_positions[index];
            for(int j = 0; j < 2; j++){
                if(i != current_hidden_pairs_candidate->hidden_pairs_candidates[j]) 
                    is_saved_candidate = false;
            }   
            int cellcandidate = CurrentCell->candidates[i];

            //Delete candidate
            if(cellcandidate == 1 && is_saved_candidate == false)
            {
                cellcandidate = 0;
                CurrentCell->num_candidates--;
            }
        }

    }
}

int hidden_pairs(SudokuBoard *p_board)
{
    int hidden_pairs_number = 0;
    Cell* CurrentCell;

    //Memory allocation section
    p_board->hidden_pairs_positions = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct hidden_pairs_position*));
    for(int index = 0; index < BOARD_SIZE * BOARD_SIZE; index++){
        p_board->hidden_pairs_positions[index] = malloc(sizeof(struct hidden_pairs_position));
        p_board->hidden_pairs_positions[index]->position = malloc(sizeof(struct Position));
    }
    //Start operation
    for(int index = 0; index < BOARD_SIZE; index++){
        for(int index2 = 0; index2 < BOARD_SIZE; index2++){
            CurrentCell = &p_board->data[index][index2]; //see through all cells
            if(CurrentCell->found == true) continue;
            bool has_hidden_pairs = false; //if this cell is part of a hiddden pair, turn to true
            if(CurrentCell->num_candidates > 3) //if a cell has more than two candidates, proceed to find second cell
            {
                int candidate_checker[9];
                //Check within same row
                for(int idx = index2 + 1; idx < BOARD_SIZE; idx++)
                {
                    Cell* SecondCell = p_board->p_rows[index][idx];
                    if(has_hidden_pairs == true) break;
                    if(SecondCell->found == true) continue;
                    if(SecondCell->num_candidates > 3)//if more than two candidates, check if it satisfies requirements
                    { 
                        int confirmation = 0; //if confirmation = 2, these two cells are hidden pairs
                        for(int candidateidx = 0; candidateidx < 9; candidateidx++)
                        {
                            candidate_checker[candidateidx] = CurrentCell->candidates[candidateidx];
                            candidate_checker[candidateidx] += SecondCell->candidates[candidateidx];
                            if(candidate_checker[candidateidx] == 2) confirmation++;
                            if (confirmation == 2) break;
                        }
                        if(confirmation == 2){ 
                            has_hidden_pairs = true;
                            SecondCell->found = true;
                            break;
                        }
                    }
                }
                //Check within same column
                for(int idx = index + 1; idx < BOARD_SIZE; idx++)
                {
                    Cell* SecondCell = p_board->p_cols[index2][idx];
                    if(has_hidden_pairs == true) break;
                    if(SecondCell->found == true) continue;
                    if(SecondCell->num_candidates > 3)
                    {
                        int confirmation = 0; //if confirmation = 2, these two cells are hidden pairs
                        for(int candidateidx = 0; candidateidx < 9; candidateidx++)
                        {
                            candidate_checker[candidateidx] = CurrentCell->candidates[candidateidx];
                            candidate_checker[candidateidx] += SecondCell->candidates[candidateidx];
                            if(candidate_checker[candidateidx] == 2) confirmation++;
                            if (confirmation == 2) break;
                        }
                        if(confirmation == 2){ 
                            has_hidden_pairs = true;
                            SecondCell->found = true;
                            break;
                        }
                    }
                }

                //Check within same box
                int position_inside_box = Locate_inbox(p_board, CurrentCell->row_index, CurrentCell->col_index, CurrentCell->box_index);
                for(int idx = 0; idx < BOARD_SIZE; idx++)
                {
                    Cell* SecondCell = p_board->p_boxes[CurrentCell->box_index][idx];
                    if(has_hidden_pairs == true) break;
                    if(idx == position_inside_box) continue;
                    if(SecondCell->found == true) continue;
                    if(SecondCell->num_candidates > 3)
                    { 
                        int confirmation = 0; //if confirmation = 2, these two cells are hidden pairs
                        for(int candidateidx = 0; candidateidx < 9; candidateidx++)
                        {
                            candidate_checker[candidateidx] = CurrentCell->candidates[candidateidx];
                            candidate_checker[candidateidx] += SecondCell->candidates[candidateidx];
                            if(candidate_checker[candidateidx] == 2) confirmation++;
                            if (confirmation == 2) break;
                        }
                        if(confirmation == 2){ 
                            has_hidden_pairs = true;
                            SecondCell->found = true;
                            break;
                        }
                    }
                }
                if(has_hidden_pairs == true)
                {
                    Save_hidden_pair_position(p_board, CurrentCell, position_inside_box, hidden_pairs_number, candidate_checker);
                    hidden_pairs_number++;
                }
            }
        }
    }

    //solve
    Solve_with_hidden_pair(p_board, hidden_pairs_number);

    //free memory
    for(int index = 0; index < BOARD_SIZE * BOARD_SIZE; index++){
        free(p_board->hidden_pairs_positions[index]->position);
        free(p_board->hidden_pairs_positions[index]);
    }
    free(p_board->hidden_pairs_positions);

    return hidden_pairs_number;
}
