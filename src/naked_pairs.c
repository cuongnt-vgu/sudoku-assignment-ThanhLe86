#include "naked_pairs.h"
#include "auxiliary.h"
#include <stdlib.h>


// int Find_Same_Candidate(SudokuBoard *board, struct Naked_pairs_Pos* n_position, 
//     int x, int y, int boxnum, int boxcell)
// {
//     int naked_pairs = 0;
//     Cell *Currentcell;
//     for(int index = 0; index < BOARD_SIZE; index++)
//     {
//         //Find other naked pair in the same row
//         int confirmationcount = 0;
//         Currentcell = board->p_rows[x][index];
//         if (index == y) continue;
//         if (Currentcell->num_candidates == 2)
//         {
//             for(int idx = 0; idx < 2; idx++){
//                 if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
//                 confirmationcount++;
//             }
//             if(confirmationcount == 2)
//             {
//                 n_position->position[1]->row = Currentcell->row_index;
//                 n_position->position[1]->col = Currentcell->col_index;
//                 n_position->position[1]->box = Currentcell->box_index;
//                 n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
//                 Currentcell->col_index, Currentcell->box_index);
//                 naked_pairs++;
//             }
//         }
//     }

//     for(int index = 0; index < BOARD_SIZE; index++)
//     {
//         //Find other naked pair in the same column
//         int confirmationcount = 0;
//         Currentcell = &board->p_cols[y][index];
//         if (index == x) continue;
//         if (Currentcell->num_candidates == 2)
//         {
//             for(int idx = 0; idx < 2; idx++){
//                 if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
//                 confirmationcount++;
//             }
//             if(confirmationcount == 2)
//             {
//                 n_position->position[1]->row = Currentcell->row_index;
//                 n_position->position[1]->col = Currentcell->col_index;
//                 n_position->position[1]->box = Currentcell->box_index;
//                 n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
//                 Currentcell->col_index, Currentcell->box_index);
//                 naked_pairs++;
//             }
//         }
//     }

//     for(int index = 0; index < BOARD_SIZE; index++)
//     {
//         //Find other naked pair in the same box
//         int confirmationcount = 0;
//         Currentcell = &board->p_boxes[boxnum][index];
//         if (index == boxcell) continue;
//         if (Currentcell->num_candidates == 2)
//         {
//             for(int idx = 0; idx < 2; idx++){
//                 if(Currentcell->candidates[n_position->candidateValues[idx]] == 1)
//                 confirmationcount++;
//             }
//             if(confirmationcount == 2)
//             {
//                 n_position->position[1]->row = Currentcell->row_index;
//                 n_position->position[1]->col = Currentcell->col_index;
//                 n_position->position[1]->box = Currentcell->box_index;
//                 n_position->position[1]->posinsidebox = Locate_inbox(board, Currentcell->row_index,
//                 Currentcell->col_index, Currentcell->box_index);
//                 naked_pairs++;
//             }
//         }
//     }
//     return naked_pairs;
// }

// void SaveCandidate(struct Naked_pairs_Pos* position, Cell *currcell)
// {
//     int newcandidateidx = 0;
//     for(int idx = 0; idx < BOARD_SIZE; idx++)
//     {
//         if(currcell->candidates[idx] == 1){
//             newcandidateidx++;
//             position->candidateValues[newcandidateidx] = idx;
//         }
//     }
// }

int naked_pairs(SudokuBoard *p_board)
{
    // Cell *CurrentCell;
    // int naked_pairs_quant = 0;
    // for (int index = 0; index < BOARD_SIZE; index++)
    // {
    //     for (int index2 = 0; index2 < BOARD_SIZE; index2++)
    //     {
    //         CurrentCell = &p_board->data[index][index2];
    //         if(CurrentCell->num_candidates == 2)
    //         {
    //             int boxnum = CurrentCell->box_index;
    //             int posinsidebox = Locate_inbox(p_board, index, index2, boxnum);
    //             struct Naked_pairs_Pos *newposi = malloc(sizeof(struct Naked_pairs_Pos));
    //             SaveCandidate(newposi, CurrentCell);
    //             int quant = Find_Same_Candidate(p_board, newposi, index, index2, boxnum, posinsidebox);
    //             if(quant != 0) naked_pairs_quant++;
                
    //         }

    //     }
    // }
    // return naked_pairs_quant;
    return 0;
}