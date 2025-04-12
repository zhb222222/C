#include<stdio.h>
#include<stdlib.h>

#define MIN(X, Y) (((X) > (Y)) ? (Y) : (X))


// Backtracing is an algorithmic-technique for solving problems recrusively 
// by trying to build a solution incrementally, one piece at a time, removing 
// those solutions that fail to satisfy the constraint of the problem statement.

typedef struct{
    int rows;
    int cols;
    int **arr;
    int count;
} board_t;

// This function check vertically, horizontally, and diagonally, whether the queen has already existed
// If so, return 0; else return 1
int check_valid(board_t * current, int index_r, int index_c) {
    if(current->arr[index_r][index_c] == 1) {
        return 0;
    }
    for(int i = 0; i < current->rows; i++) {
        if(i == index_r) {
            continue;
        }
        if(current->arr[i][index_c] == 1) {
            return 0;
        }
        int d_col = index_c + index_r - i;
        if(0 <= d_col && d_col < current->cols) {
            if(current->arr[i][d_col] == 1) {
                return 0;
            }
        }
    }

    for(int j = 0; j < current->cols; j++) {
        if(j == index_c) {
            continue;
        }
        if(current->arr[index_r][j] == 1) {
            return 0;
        }
        int d_row = index_r - index_c + j;
        if(0 <= d_row && d_row < current->rows) {
            if(current->arr[d_row][j] == 1) {
                return 0;
            }
        }
    }

    return 1;
}


int solve_queen(board_t * board) {
    if(board->count == MIN(board->cols, board->rows)) {
        return 1;
    }

    for(int i = 0; i < board->rows; i++) {
        for(int j = 0; j < board->cols; j++) {
            if(check_valid(board, i, j)) {
                board->arr[i][j] = 1;
                board->count++;
                if(solve_queen(board)) {
                    return 1;
                }

                board->arr[i][j] = 0;
                board->count--;
            }
        }
    }
    return 0;
}

void printBoard(board_t * board) {
    for(int i = 0; i < board->rows; i++) {
        for(int j = 0; j < board->cols; j++) {
            printf("%d ", board->arr[i][j]);
        }
        printf("\n");
    }
}

board_t * make_board(int num_rows, int num_cols) {
    board_t * board = malloc(sizeof(*board));
    board->cols = num_cols;
    board->rows = num_rows;
    board->arr = malloc(sizeof(*board->arr) * board->rows);
    for(int k = 0; k < num_rows; k++) {
        board->arr[k] = malloc(sizeof(*board->arr[k]) * board->cols);
    }
    for(int i = 0; i < board->rows; i++) {
        for(int j = 0; j < board->cols; j++) {
            board->arr[i][j] = 0;
        }
    }
    return board;
}



int main(void) {
    // You can easily set the number of rows and columns you want.
    // num_cols and num_rows are not required to be the same.
    // However, they should be no more than 10.
    int num_rows = 5;
    int num_cols = 7;
    board_t * board = make_board(num_rows, num_cols);

    printf("The original board is: \n");
    printBoard(board);

    int result = solve_queen(board);
    if(result == 0) {
        printf("We cannot solve this.\n");
    }
    else {
        printf("We Successfully solve this problem! And a possible result is:\n");
        printBoard(board);
    }


    for(int k = 0; k < num_rows; k++) {
        free(board->arr[k]);
    }
    free(board->arr);
    free(board);
}
