#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

int has_won(board_t board, player_t player) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1; 
            }
        }
    }

    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1; 
            }
        }
    }

    for (int row = 3; row >= 0; row--) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1; 
            }
        }
    }

    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return 1; 
            }
        }
    }

    return 0;
}

int is_full(board_t board) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == EMPTY) {
                return 0; 
            }
        }
    }
    return 1;
}

void print_board(board_t board) {
    printf("  A B C D E\n");
    for (int row = 0; row < 4; row++) {
        printf("%d ", row + 1);
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == EMPTY) {
                printf(". ");
            } else if (board[row][col] == RED) {
                printf("R ");
            } else if (board[row][col] == BLUE) {
                printf("B ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool can_place_checker(board_t board, int col, int row) {
    if (row < 0 || row >= 4 || col < 0 || col >= 5) {
        return false;
    }

    if (row == 3 || board[row + 1][col] != EMPTY) {
        return true;
    }

    return false;
}

int minimax(board_t board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 6) {
        return 0;
    }

    if (has_won(board, BLUE)) {
        return 100;
    } else if (has_won(board, RED)) {
        return -100;
    } else if (is_full(board)) {
        return 0;
    }

    if (maximizingPlayer) {
        int maxEval = -1000;
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row < 4; row++) {
                if (can_place_checker(board, col, row) && board[row][col] == EMPTY) {
                    board[row][col] = BLUE;
                    int eval = minimax(board, depth + 1, false, alpha, beta);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    board[row][col] = EMPTY;

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1000;
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row < 4; row++) {
                if (can_place_checker(board, col, row) && board[row][col] == EMPTY) {
                    board[row][col] = RED;
                    int eval = minimax(board, depth + 1, true, alpha, beta);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    board[row][col] = EMPTY;

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return minEval;
    }
}

void place_checker(board_t board, int col, int row, player_t currentPlayer) {
    board[row][col] = currentPlayer;
}

void computer_move(board_t board, player_t currentPlayer) {
    int bestMove = -1000;
    int bestCol = -1;

    for (int col = 0; col < 5; col++) {
        for (int row = 0; row < 4; row++) {
            if (can_place_checker(board, col, row) && board[row][col] == EMPTY) {
                board[row][col] = BLUE;
                int moveVal = minimax(board, 0, false, -1000, 1000);
                board[row][col] = EMPTY;

                if (moveVal > bestMove) {
                    bestMove = moveVal;
                    bestCol = col;
                }
            }
        }
    }

   
    for (int row = 3; row >= 0; row--) {
        if (can_place_checker(board, bestCol, row) && board[row][bestCol] == EMPTY) {
            place_checker(board, bestCol, row, currentPlayer);
            break;
        }
    }
}

int main() {
    srand(time(NULL));

    board_t board;
    player_t currentPlayer = RED;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            board[row][col] = EMPTY;
        }
    }

    while (1) {
        print_board(board);

        if (has_won(board, currentPlayer)) {
            printf("%s wins!\n", (currentPlayer == RED) ? "Red" : "Computer");
            break;
        }

        if (is_full(board)) {
            printf("It's a draw!\n");
            break;
        }

        int col, row;
        if (currentPlayer == RED) {
            printf("Red's turn. Enter a column (A, B, C, D, E) and row (1-4) to make your move (e.g., A3): ");
            char col_input;
            scanf(" %c%d", &col_input, &row);
            col = col_input - 'A';

            if (!can_place_checker(board, col, row - 1) || board[row - 1][col] != EMPTY) {
                printf("Invalid move. Try again.\n");
                continue;
            }

            place_checker(board, col, row - 1, currentPlayer);
        } else {
            computer_move(board, currentPlayer);
        }

        if (has_won(board, currentPlayer)) {
            print_board(board);
            printf("%s wins!\n", (currentPlayer == RED) ? "Red" : "Computer");
            break;
        }

        currentPlayer = (currentPlayer == RED) ? BLUE : RED;
    }

    return 0;
}