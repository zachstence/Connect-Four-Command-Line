#include <iostream>
#include <vector>
#include <map>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;

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

bool won(vector<vector<char>> b, char piece) {
  // for (int r = 0; r < b[0].size(); r++) {
  //   for (int c = 0; c < b.size(); c++) {
  //     if (b[c][r] == piece) {

  //     }
  //   }
  // }
  return true;
}

void placePiece(vector<vector<char>> &board, Player &p) {
  int c;
  cout << "Player " << p.id << ", enter a column to place a piece: ";
  while (true) {
    cin >> c;
    for (auto it = board[c - 1].rbegin(); it != board[c - 1].rend(); ++it) {
      if (*it == ' ') {
        *it = p.piece;

        p.won = won(board, p.piece);

        return;
      }
    }
    cout << "That column is already full, please pick another: ";
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

  for (int count = 0; count < (ROWS * COLS); count += 2) {
    placePiece(board, p1);
    if (p1.won) break;
    displayBoard(board);

    placePiece(board, p2);
    if (p2.won) break;
    displayBoard(board);
  }

  int winner = p1.won ? 1 : p2.won ? 2 : 0;

  if (winner == 0) cout << "Draw!" << endl;
  else cout << "Player " << winner << " won!" << endl;

}