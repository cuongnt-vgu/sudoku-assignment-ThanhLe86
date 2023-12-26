#include "naked_triples.h"

void SaveNakedTripleCandidate(SudokuBoard* p_board, struct Naked_tripl_Pos* newpos, Cell* CurrentCell, Cell* SecondCell, Cell* ThirdCell)
{
    int index = CurrentCell->row_index;
    int index2 = CurrentCell->col_index;
    int idx = SecondCell->col_index;
    int idx3 = ThirdCell->col_index;

    for(int positionidx = 0; positionidx < 3; positionidx++)
        newpos->position[positionidx] = malloc(sizeof(struct Position));

    struct Position* FirstCellPos = newpos->position[0];
    struct Position* SecondCellPos = newpos->position[1];
    struct Position* ThirdCellPos = newpos->position[2];
    
    FirstCellPos->row = CurrentCell->row_index;
    FirstCellPos->col = CurrentCell->col_index;
    FirstCellPos->box = CurrentCell->box_index;
    FirstCellPos->posinsidebox = Locate_inbox(p_board, index, index2, CurrentCell->box_index);
    CurrentCell->found = true;

    SecondCellPos->row = SecondCell->row_index;
    SecondCellPos->col = SecondCell->col_index;
    SecondCellPos->box = SecondCell->box_index;
    SecondCellPos->posinsidebox = Locate_inbox(p_board, index, idx, SecondCell->box_index);
    SecondCell->found = true;

    ThirdCellPos->row = ThirdCell->row_index;
    ThirdCellPos->col = ThirdCell->col_index;
    ThirdCellPos->box = ThirdCell->box_index;
    ThirdCellPos->posinsidebox = Locate_inbox(p_board, index, idx3, ThirdCell->box_index);
    ThirdCell->found = true;
                                    
}

void SolvewNakedTripls(SudokuBoard* p_board, int naked_tripl_quant)
{
    struct Naked_tripl_Pos* NakedTripl_position;
    struct Position* Cell_position1;
    struct Position* Cell_position2;
    struct Position* Cell_position3;
    Cell* temp;

    for(int index = 0; index < naked_tripl_quant; index++)
    {
        //Current Naked triple position 
        NakedTripl_position = p_board->Nt_Positions[index];
        //Cells in said naked triple position
        Cell_position1 = NakedTripl_position->position[0];
        Cell_position2 = NakedTripl_position->position[1];
        Cell_position3 = NakedTripl_position->position[2];

        //Solve if same row
        if(Cell_position1->row == Cell_position2->row && Cell_position2->row == Cell_position3->row)
        {
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                //Current cell being solved
                temp = p_board->p_rows[Cell_position1->row][idx];
                if(temp->found != true && temp->num_candidates > 1)
                {
                    for(int idx2 = 0; idx2 < 3; idx2++)
                    {
                        if(temp->candidates[NakedTripl_position->candidateValues[idx2]] == 1)
                        {
                            temp->candidates[NakedTripl_position->candidateValues[idx2]] = 0;
                            temp->num_candidates--;
                        }
                    }
                }
            }
        }

        //Solve if same column
        if(Cell_position1->col == Cell_position2->col && Cell_position2->col == Cell_position3->col)
        {
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                //Current cell being solved
                temp = p_board->p_cols[Cell_position1->col][idx];
                if(temp->found != true && temp->num_candidates > 1)
                {
                    for(int idx2 = 0; idx2 < 3; idx2++)
                    {
                        if(temp->candidates[NakedTripl_position->candidateValues[idx2]] == 1)
                        {
                            temp->candidates[NakedTripl_position->candidateValues[idx2]] = 0;
                            temp->num_candidates--;
                        }
                    }
                }
            }
        }

        //Solve if same box
        if(Cell_position1->box == Cell_position2->box && Cell_position2->box == Cell_position3->box)
        {
            for(int idx = 0; idx < BOARD_SIZE; idx++)
            {
                //Current cell being solved
                temp = p_board->p_boxes[Cell_position1->box][idx];
                if(temp->found != true && temp->num_candidates > 1)
                {
                    for(int idx2 = 0; idx2 < 3; idx2++)
                    {
                        if(temp->candidates[NakedTripl_position->candidateValues[idx2]] == 1)
                        {
                            temp->candidates[NakedTripl_position->candidateValues[idx2]] = 0;
                            temp->num_candidates--;
                        }
                    }
                }
            }
        }

    }
}

int naked_triples(SudokuBoard *p_board)
{
    Cell* CurrentCell;
    Cell* SecondCell;
    Cell* ThirdCell;
    struct Naked_tripl_Pos* newpos;
    int naked_tripl_quant = 0;

    p_board->Nt_Positions = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct Naked_tripl_Pos*));
    for(int memidx = 0; memidx < BOARD_SIZE * BOARD_SIZE; memidx++) 
        p_board->Nt_Positions[memidx] = malloc(sizeof(struct Naked_tripl_Pos));

    for (int index = 0; index < BOARD_SIZE; index++)
    {
        for (int index2 = 0; index2 < BOARD_SIZE; index2++)
        {
            CurrentCell = &p_board->data[index][index2];
            if((CurrentCell->num_candidates == 2 || CurrentCell->num_candidates == 3) && CurrentCell->found != true)
            {
                //Find within row
                int row = index;
                int col = index2;
                for(int idx = index2 + 1; idx < BOARD_SIZE; idx++)
                {
                    SecondCell = p_board->p_rows[row][idx];
                    if((SecondCell->num_candidates == 2 || SecondCell->num_candidates == 3) && SecondCell->found != true)
                    {
                        for(int idx3 = idx + 1; idx3 < BOARD_SIZE; idx3++)
                        {
                            ThirdCell = p_board->p_rows[row][idx3];
                            if((ThirdCell->num_candidates == 2 || ThirdCell->num_candidates == 3) && ThirdCell->found != true)
                            {
                                int candidatecheck[9];
                                int candidatecount = 0;
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    candidatecheck[candidateidx] = ThirdCell->candidates[candidateidx];
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                {
                                    candidatecheck[candidateidx] += SecondCell->candidates[candidateidx];
                                    candidatecheck[candidateidx] += CurrentCell->candidates[candidateidx];
                                }
                                for (int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    if(candidatecheck[candidateidx] != 0) candidatecount++; 
                                if(candidatecount == 3)
                                {
                                    newpos = p_board->Nt_Positions[naked_tripl_quant];
                                    int candidatevaluesidx = 0;
                                    for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++){
                                        if(candidatecheck[candidateidx] != 0) 
                                        {
                                            newpos->candidateValues[candidatevaluesidx] = candidateidx;
                                            candidatevaluesidx++;
                                        }
                                    }
                                    SaveNakedTripleCandidate(p_board, newpos, CurrentCell, SecondCell, ThirdCell);
                                    naked_tripl_quant++;
                                    break;
                                }
                            }
                        }
                    }
                }

                //Find within column
                for(int idx = index + 1; idx < BOARD_SIZE; idx++)
                {
                    SecondCell = p_board->p_cols[col][idx];
                    if((SecondCell->num_candidates == 2 || SecondCell->num_candidates == 3) && SecondCell->found != true)
                    {
                        for(int idx3 = idx + 1; idx3 < BOARD_SIZE; idx3++)
                        {
                            ThirdCell = p_board->p_cols[col][idx3];
                            if((ThirdCell->num_candidates == 2 || ThirdCell->num_candidates == 3) && ThirdCell->found != true)
                            {
                                int candidatecheck[9];
                                int candidatecount = 0;
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    candidatecheck[candidateidx] = ThirdCell->candidates[candidateidx];
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                {
                                    candidatecheck[candidateidx] += SecondCell->candidates[candidateidx];
                                    candidatecheck[candidateidx] += CurrentCell->candidates[candidateidx];
                                }
                                for (int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    if(candidatecheck[candidateidx] != 0) candidatecount++; 
                                if(candidatecount == 3)
                                {
                                    newpos = p_board->Nt_Positions[naked_tripl_quant];
                                    int candidatevaluesidx = 0;
                                    for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++){
                                        if(candidatecheck[candidateidx] != 0) 
                                        {
                                            newpos->candidateValues[candidatevaluesidx] = candidateidx;
                                            candidatevaluesidx++;
                                        }
                                    }
                                    SaveNakedTripleCandidate(p_board, newpos, CurrentCell, SecondCell, ThirdCell);
                                    naked_tripl_quant++;
                                    break;   
                                }
                            }
                        }
                    }
                }

                //Find within box
                int box = CurrentCell->box_index;
                int posinsidebox = Locate_inbox(p_board, CurrentCell->row_index, CurrentCell->col_index, box);
                for(int idx = posinsidebox + 1; idx < BOARD_SIZE; idx++)
                {
                    if(idx == posinsidebox) continue;
                    SecondCell = p_board->p_boxes[box][idx];
                    if((SecondCell->num_candidates == 2 || SecondCell->num_candidates == 3) && SecondCell->found != true)
                    {
                        for(int idx3 = idx + 1; idx3 < BOARD_SIZE; idx3++)
                        {
                            ThirdCell = p_board->p_boxes[box][idx3];
                            if((ThirdCell->num_candidates == 2 || ThirdCell->num_candidates == 3) && ThirdCell->found != true)
                            {
                                int candidatecheck[9];
                                int candidatecount = 0;
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    candidatecheck[candidateidx] = ThirdCell->candidates[candidateidx];
                                for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                {
                                    candidatecheck[candidateidx] += SecondCell->candidates[candidateidx];
                                    candidatecheck[candidateidx] += CurrentCell->candidates[candidateidx];
                                }
                                for (int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++)
                                    if(candidatecheck[candidateidx] != 0) candidatecount++; 
                                if(candidatecount == 3)
                                {
                                    newpos = p_board->Nt_Positions[naked_tripl_quant];
                                    int candidatevaluesidx = 0;
                                    for(int candidateidx = 0; candidateidx < BOARD_SIZE; candidateidx++){
                                        if(candidatecheck[candidateidx] != 0) 
                                        {
                                            newpos->candidateValues[candidatevaluesidx] = candidateidx;
                                            candidatevaluesidx++;
                                        }
                                    }
                                    SaveNakedTripleCandidate(p_board, newpos, CurrentCell, SecondCell, ThirdCell);
                                    naked_tripl_quant++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //Solve board with naked triples method
    SolvewNakedTripls(p_board, naked_tripl_quant);

    //free dynamically allocated memories
    for(int i = 0; i < naked_tripl_quant; i++)
    {
        for (int j = 0; j < 3; j++) free(p_board->Nt_Positions[i]->position[j]);
    }
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        free(p_board->Nt_Positions[i]); 
    }
    free(p_board->Nt_Positions); // delete []
    p_board->Nt_Positions = NULL;

    return naked_tripl_quant;
}