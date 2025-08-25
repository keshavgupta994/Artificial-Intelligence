#include <bits/stdc++.h>
using namespace std;

const int PLAYER = 1;  // Human (X)
const int AI = 2;      // AI (O)

char board[3][3];

// Initialize board
void initBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Check winner
int checkWin() {
    // Rows & Cols
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return (board[i][0] == 'X' ? PLAYER : AI);
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return (board[0][i] == 'X' ? PLAYER : AI);
    }
    // Diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == 'X' ? PLAYER : AI);
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == 'X' ? PLAYER : AI);

    return 0; // No winner yet
}

// Check if moves left
bool movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Minimax function
int minimax(bool isAI) {
    int score = checkWin();

    if (score == AI) return +10;
    if (score == PLAYER) return -10;
    if (!movesLeft()) return 0;

    if (isAI) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// AI move
pair<int, int> bestMove() {
    int bestVal = -1000;
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    move = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return move;
}

int main() {
    initBoard();
    cout << "Tic Tac Toe Game\n";
    cout << "You are X, AI is O\n";
    printBoard();

    while (true) {
        // Player move
        int row, col;
        cout << "Enter your move (row and col 1-3): ";
        cin >> row >> col;
        row--; col--;

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        board[row][col] = 'X';
        printBoard();

        if (checkWin() == PLAYER) {
            cout << "You win!\n";
            break;
        }
        if (!movesLeft()) {
            cout << "It's a draw.\n";
            break;
        }

        // AI move
        cout << "AI is making a move...\n";
        auto [aiRow, aiCol] = bestMove();
        board[aiRow][aiCol] = 'O';
        printBoard();

        if (checkWin() == AI) {
            cout << "AI wins!\n";
            break;
        }
        if (!movesLeft()) {
            cout << "It's a draw.\n";
            break;
        }
    }
    return 0;
}