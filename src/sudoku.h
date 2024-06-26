#pragma once

#include <stdbool.h>

#define BOARD_SIZE 9

struct Position {
    int row;
    int col;
    int box;
    int posinsidebox;
    int candidateValue;
};

struct Naked_pairs_Pos
{
    int candidateValues[2];
    struct Position *position[2];
};

struct hidden_pairs_position
{
    int hidden_pairs_candidates[2];
    struct Position *position;
};


struct Naked_tripl_Pos
{
    int candidateValues[3];
    struct Position *position[3];
};


struct Cell_impl
{
    int row_index;
    int col_index;
    int box_index;
    int num_candidates;
    int candidates[BOARD_SIZE];
    int status; // solved or 0
    bool fixed;
    bool found;
};

typedef struct Cell_impl Cell;

struct SudokuBoard_impl
{
    int solved_counter;
    Cell **data; // 9x9 cell board

    Cell **p_rows[BOARD_SIZE];  // rows pointers
    Cell **p_cols[BOARD_SIZE];  // cols pointers
    Cell **p_boxes[BOARD_SIZE]; // boxes pointers
    Cell *solved_cells[BOARD_SIZE *
                       BOARD_SIZE]; // solved cell pointers (maximum)
    struct Position **hidden_single_positions;
    struct Naked_pairs_Pos **N_Positions;
    struct Naked_tripl_Pos **Nt_Positions;
    struct hidden_pairs_position** hidden_pairs_positions;
};



typedef struct SudokuBoard_impl SudokuBoard;

void init_sudoku(SudokuBoard *p_board);
void load_sudoku(SudokuBoard *p_board, char *input_text);
bool apply_constraint(Cell **p_cells, int status);
bool is_in_list(Cell **p_array, int size, Cell *p);
void print_candidate_num(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);

void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
void free_sudoku(SudokuBoard *p_board);
