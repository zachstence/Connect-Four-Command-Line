#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

const int ROWS = 6;
const int COLS = 7;

const char p1Piece = 'X';
const char p2Piece = 'O';

struct Player {
  int id;
  char piece;
  bool won;
};

void displayBoard(vector<vector<char>> b) {
  cout << "| 1 2 3 4 5 6 7 |" << endl;
  for (int r = 0; r < b[0].size(); r++) {
    cout << "| ";
    for (int c = 0; c < b.size(); c++) {
      cout << b[c][r] << " ";
    }
    cout << "|" << endl;
  }
  cout << "|---------------|" << endl;
}

bool won(vector<vector<char>> board, char piece) {
  for (int r = 0; r < b[0].size(); r++) {
    for (int c = 0; c < b.size(); c++) {
      if (board[c][r] == piece) {

      }
    }
  }
}

void placePiece(vector<vector<char>> &board, Player &p) {
  int c;
  cout << "Player " << p.id << ", enter a column to place a piece: ";
  cin >> c;
  for (auto it = board[c - 1].rbegin(); it != board[c - 1].rend(); ++it) {
    if (*it == ' ') {
      *it = p.piece;
      cout << *it << endl;
      break;
    }
  }
}

void displayColumn(vector<char> c) {
  for (auto it = c.begin(); it != c.end(); ++it) {
    cout << *it << endl;
  }
}

int main() {
  vector<vector<char>> board (COLS, vector<char> (ROWS, ' '));
  displayBoard(board);

  Player p1 = {1, p1Piece, false};
  Player p2 = {2, p2Piece, false};

  for (int count = 0; count < (ROWS * COLS); count++) {
    placePiece(board, p1);
    if (p1.won) break;
    displayBoard(board);

    placePiece(board, p2);
    if (p2.won) break;
    displayBoard(board);
  }

  if (p1.won) cout << "Player 1 won!" << endl;
  else if (p2.won) cout << "Player 2 won!" << endl;
  else cout << "Draw!" << endl;

}