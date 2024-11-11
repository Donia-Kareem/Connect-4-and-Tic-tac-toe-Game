#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>
#include "GameConnect4AndTICTAC.h"
using namespace std ;

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer (char symbol, int dimension):Player(symbol){
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move (int& x , int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
}


// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player (int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move (int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string(){
    return "Player: " + name ;
}

// Get symbol used by player
char Player:: get_symbol () const{
    return symbol;
}



my_triangle ::my_triangle (){
    n_rows = 3;  n_cols = 5;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            if (j < (n_cols / 2 - i) || j >= (n_cols / 2 + i + 1)) {
                board[i][j] = ' ';
            } else {
                board[i][j] = '0';
            }
        }
    }
}
bool my_triangle :: update_board(int x, int y, char mark)  {
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 4) && (board[x][y] == '0')) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

bool my_triangle ::is_winner(char symbol) {
    bool diag_win = (board[0][2] != '0' && board[1][1] != '0' && board[2][0] != '0' &&
                     board[0][2] == board[1][1] && board[1][1] == board[2][0]);
    if (diag_win) {
        return true;
    }
    diag_win = (board[0][2] != '0' && board[1][3] != '0' && board[2][4] != '0' &&
                board[0][2] == board[1][3] && board[1][3] == board[2][4]);
    if (diag_win) {
        return true;
    }
    // Check row win conditions
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != '0' && board[i][1] != '0' && board[i][2] != '0' &&
            board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
    }
    // Check column win conditions
    for (int i = 0; i < 5; ++i) {
        if (board[0][i] != '0' && board[1][i] != '0' && board[2][i] != '0' &&
            board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true;
        }
    }
    return false;
}
void my_triangle ::display_board() {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            if(board[i][j]=='0'){
                cout<<"("<<i<<","<<j<<")";
            }else{
                cout<<board[i][j]<<"    ";
            }
            cout<<" ";
        }
        cout << endl;
    }
}
bool my_triangle ::is_draw() {
    return (n_moves == 9 && !is_winner('a'));
}
bool my_triangle ::game_is_over() {
    return n_moves >= 9;
}
GameManager::GameManager(Board* bpt, Player* playerPtr[2] ) {
    boardPtr = bpt;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
    int x, y;
    boardPtr->display_board();
    while (!boardPtr->game_is_over()) {
        for (auto & player : players) {
            player->get_move(x, y);
            while (!boardPtr->update_board (x, y, player->get_symbol())){
                player->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner('a')){
                cout  << player->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()){
                cout << "Draw!\n";
                return;
            }
        }
    }
}
Connect4Board::Connect4Board() {
    n_rows = 6;
    n_cols = 7;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}
bool Connect4Board::update_board(int x, int y, char mark) {
    if (x < 0 || x >= n_rows || y < 0 || y >= n_cols) {
        return false; // Invalid move, out of bounds
    }

    for (int i = n_rows - 1; i >= 0; i--) {
        if (board[i][y] == 0) {
            board[i][y] = toupper(mark);
            n_moves++;
            return true;
        }
    }

    return false; // Column is full
}
void Connect4Board::display_board() {
    for (int i = 0; i < n_rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < n_cols; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(3) << board[i][j] << " |";
        }
    }
    cout << endl;
}
bool Connect4Board::is_winner(char symbol ) {
    // Check horizontally
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j <= n_cols - 4; j++) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i][j + 1] &&
                board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3] ) {
                return true;
            }
        }
    }

    // Check vertically
    for (int i = 0; i <= n_rows - 4; i++) {
        for (int j = 0; j < n_cols; j++) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i + 1][j] &&
                board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j]) {
                return true;
            }
        }
    }

    // Check diagonally (bottom-left to top-right)
    for (int i = 3; i < n_rows; i++) {
        for (int j = 0; j <= n_cols - 4; j++) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i - 1][j + 1] &&
                board[i][j] == board[i - 2][j + 2] &&
                board[i][j] == board[i - 3][j + 3]) {
                return true;
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int i = 0; i <= n_rows - 4; i++) {
        for (int j = 0; j <= n_cols - 4; j++) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i + 1][j + 1] &&
                board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    return false;
}
bool Connect4Board::is_draw() {
    return (n_moves == n_rows * n_cols && !is_winner('a'));
}
bool Connect4Board::game_is_over() {
    return is_winner('a') || is_draw();
}
GmMngr:: GmMngr(Board* bPtr, Player* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GmMngr ::run_gm2() {
    int x, y;
    boardPtr->display_board();
    while (!boardPtr->game_is_over()) {
        for (auto & player : players) {
            player->get_move_2(x, y);

            while (!boardPtr->update_board(x, y, player->get_symbol())) {
                cout << "Invalid move. Try again.\n";
                player->get_move_2(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner('a')) {
                cout << player->to_string() << " wins!\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}

void Player::get_move_2 (int& x, int& y) {
    cout << "\nPlease enter your move column (0 to 6): ";
    cin >> y;
    x = 0; // The row will be determined by the update_board function
}
void RandomPlayer::get_move_2 (int& x , int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
}
