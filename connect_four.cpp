#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>

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

struct Slot {
  char disp = ' ';
  map<pair<int, int>, int> near = {
    { { -1,  1} , 0 },
    { {  0,  1} , 0 },
    { {  1,  1} , 0 },
    { {  1,  0} , 0 }
  };
};



void displayBoard(vector<vector<Slot>> b) {
  cout << "| 1 2 3 4 5 6 7 |" << endl;
  for (int r = 0; r < b[0].size(); r++) {
    cout << "| ";
    for (int c = 0; c < b.size(); c++) {
      cout << b[c][r].disp << " ";
    }
    cout << "|" << endl;
  }
  cout << "|---------------|" << endl;
}

void displayDebug(vector<vector<Slot>> b) {
  cout << "   |  0     1     2     3     4     5     6  |" << endl;
  for (int r = 0; r < b[0].size(); r++) {
    cout << "   |     |     |     |     |     |     |     |" << endl;
    cout << r << "  ";
    for (int c = 0; c < b.size(); c++) {
      cout << "| " << " " << b[c][r].disp << b[c][r].near[ {1, 0}] << " ";
    }
    cout << "|";
    cout << endl;
    cout << "   ";
    for (int c = 0; c < b.size(); c++) {
      cout << "| " << b[c][r].near[ { -1, 1}] << b[c][r].near[ {0, 1}] << b[c][r].near[ {1, 1}] << " ";
    }
    cout << "|";
    cout << endl;
  }
  cout << "   |-----------------------------------------|" << endl;
}



bool won(vector<vector<Slot>> b, char piece) {
  return false;
}

void updateCurrent(vector<vector<Slot>> &b, int c, int r) {
  // first initialize near counts of piece just placed
  // loop through near counts
  Slot *curr = &b[c][r];
  for (auto it = curr->near.begin(); it != curr->near.end(); ++it) {
    // get direction and x, y offsets
    auto direction = it->first;
    int x = direction.first;
    int y = direction.second;

    try {
      // if same piece in a direction, increment appropriate count
      // use .at() to get exception instead of segfault
      Slot *adj = &b.at(c + x).at(r + y);
      if (adj->disp == curr->disp) {
        curr->near[direction] = adj->near[direction] + 1;
      }
      // if out of bounds, just skip
    } catch (const std::out_of_range& oor) {
      continue;
    }

  }
}

void placePiece(vector<vector<Slot>> &b, Player &p) {
  int choice;
  cout << "Player " << p.id << ", enter a column to place a piece: ";
  while (true) {
    cin >> choice; // need to validate choice
    int c = choice;
    for (int r = ROWS - 1; r >= 0; r--) {
      Slot *curr = &b[c][r];
      if (curr->disp == ' ') {
        curr->disp = p.piece;

        updateCurrent(b, c, r);

        return;
      }
    }
    cout << "That column is already full, please pick another: ";
  }
}





int main() {
  vector<vector<Slot>> board (COLS, vector<Slot> (ROWS) );
  displayDebug(board);

  Player p1 = {1, p1Piece, false};
  Player p2 = {2, p2Piece, false};

  for (int count = 0; count < (ROWS * COLS); count += 2) {
    placePiece(board, p1);
    if (p1.won) break;
    displayDebug(board);

    placePiece(board, p2);
    if (p2.won) break;
    displayDebug(board);
  }

  int winner = p1.won ? 1 : p2.won ? 2 : 0;

  if (winner == 0) cout << "Draw!" << endl;
  else cout << "Player " << winner << " won!" << endl;

}