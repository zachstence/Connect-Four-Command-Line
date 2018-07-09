#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>
#include <limits>
#include <ios>

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
  cout << endl << "| 1 2 3 4 5 6 7 |" << endl;
  for (int r = 0; r < b[0].size(); r++) {
    cout << "| ";
    for (int c = 0; c < b.size(); c++) {
      cout << b[c][r].disp << " ";
    }
    cout << "|" << endl;
  }
  cout << "|---------------|" << endl;
}



bool updateAdjacent(vector<vector<Slot>> &b, int c, int r) {
  Slot *curr = &b[c][r];

  for (auto it = curr->near.begin(); it != curr->near.end(); ++it) {
    auto direction = it->first;
    int x = direction.first;
    int y = direction.second;

    int x_opp = -1 * x;
    int y_opp = -1 * y;

    int curr_c = c;
    int curr_r = r;

    for (int i = 1; i < 4; i++) {
      try {
        int next_c = c + i * x_opp;
        int next_r = r + i * y_opp;

        Slot *curr = &b.at(curr_c).at(curr_r);
        Slot *next = &b.at(next_c).at(next_r);

        if (curr->disp != ' ' && curr->disp == next->disp) {
          next->near[direction] = curr->near[direction] + 1;
          if (next->near[direction] >= 3) return true;
        }

        curr_c = next_c;
        curr_r = next_r;

      } catch (const std::out_of_range& oor) {}
    }

  }
}


bool updateCurrent(vector<vector<Slot>> &b, int c, int r) {
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
        if (curr->near[direction] >= 3) return true;
      }
      // if out of bounds, just skip
    } catch (const std::out_of_range& oor) {
      continue;
    }

  }
}


void placePiece(vector<vector<Slot>> &b, Player &p) {
  bool win = false;
  int choice;
  cout << "Player " << p.id << ", enter a column to place a piece: ";
  cin >> choice;
  while (true) {
    while (cin.fail() || choice - 1 < 0 || choice - 1 > b.size()) {
      cout << "Enter a valid column (1-" << b.size() << "): ";
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cin >> choice;
    }
    int c = choice - 1;
    for (int r = ROWS - 1; r >= 0; r--) {
      Slot *curr = &b.at(c).at(r);
      if (curr->disp == ' ') {
        curr->disp = p.piece;

        win |= updateCurrent(b, c, r);
        win |= updateAdjacent(b, c, r);
        p.won = win;

        return;
      }
    }
    cout << "That column is already full, please pick another." << endl;
    std::cin.setstate(std::ios::failbit);
  }
}



int main() {
  vector<vector<Slot>> board (COLS, vector<Slot> (ROWS) );
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
  displayBoard(board);

  int winner = p1.won ? 1 : p2.won ? 2 : 0;

  if (winner == 0) cout << "Draw!" << endl;
  else cout << "Player " << winner << " won!" << endl;
}