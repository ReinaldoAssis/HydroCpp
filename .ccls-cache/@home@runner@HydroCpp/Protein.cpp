#include "Protein.h"
#include "Vector2.h"
#include <iostream>
#include <vector>

using namespace std;

void protein::initialize(int _length, bool randomStart,
                         bool _randomizeSequences) {
  length = _length;
  matrix = vector<vector<aminoacid>>(length, vector<aminoacid>(length));

  for (int i = 0; i < _length; i++) {
    for (int j = 0; j < _length; j++) {
      matrix[i][j].compound = this->emptyChar;
      matrix[i][j].index = -1;
    }
  }

  if (randomStart) {
    position.x = rand() % length;
    position.y = rand() % length;
    _position = position;
  }

  randomizeSequences = _randomizeSequences;
}

void protein::print(PRINT_MODE mode) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {

      switch (mode) {
      case PRINT_MODE_NORMAL:
        cout << matrix[i][j].compound;
        break;
      case PRINT_MODE_INDEXED:
        if (matrix[i][j].index != -1)
          std::cout << matrix[i][j].index;
        else
          std::cout << emptyChar;
        break;
      }

      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

bool protein::checkMove(vector2 move) {
  if (position.x + move.x < 0 || position.x + move.x >= length)
    return false;
  if (position.y + move.y < 0 || position.y + move.y >= length)
    return false;
  if (checkAvailable(position + move) == false)
    return false;
  return true;
}

bool protein::checkAvailable(vector2 location) {
  if (matrix[location.y][location.x].compound == emptyChar)
    return true;
  return false;
}

bool protein::place(vector2 location, aminoacid element) {
  if (location.x < 0 || location.x >= length)
    return false;
  if (location.y < 0 || location.y >= length)
    return false;

  try {
    if (matrix[location.y][location.x].compound != this->emptyChar)
      return false;
    else
      matrix[location.y][location.x] = element;
    return true;
  } catch (exception e) {
    printf("[ERROR] Failed to place aminoacid at %d, %d\n", location.x,
           location.y);
    return false;
  }
}

bool protein::place(int x, int y, aminoacid element) {
  return this->place(vector2(x, y), element);
}

vector2 protein::random_valid_delta() {
  // stores all possible deltas
  vector<vector2> deltas = vector<vector2>();
  // gets all possible movements in a given position
  if (checkMove(vector2(0, 1)))
    deltas.push_back(vector2(0, 1));
  if (checkMove(vector2(0, -1)))
    deltas.push_back(vector2(0, -1));
  if (checkMove(vector2(1, 0)))
    deltas.push_back(vector2(1, 0));
  if (checkMove(vector2(-1, 0)))
    deltas.push_back(vector2(-1, 0));

  if (deltas.size() > 0) {
    int rnd = rand() % deltas.size();

    return deltas[rnd];
  }

  return VECTOR2_INVALID;
}

void protein::append(vector<aminoacid> sequence) {
  if (randomizeSequences) {
    // iterate over sequence and branch aminoacids randomly
    for (int i = 0; i < sequence.size(); i++) {
      // sets aminoacid index
      sequence[i].index = i;

      if (i == 0) {
        place(position, sequence[i]);
        if (checkMove(vector2(0, 1)))
          place(position + vector2(0, 1), aminoacid('*', -1));
        else if (checkMove(vector2(0, -1)))
          place(position + vector2(0, -1), aminoacid('*', -1));
        else if (checkMove(vector2(1, 0)))
          place(position + vector2(1, 0), aminoacid('*', -1));
        else if (checkMove(vector2(-1, 0)))
          place(position + vector2(-1, 0), aminoacid('*', -1));

        continue;
      }

      // Determines if the inicial delta will be in the x or y axis
      vector2 delta = random_valid_delta();
      if (delta == VECTOR2_INVALID) {
        printf("[ERROR] Brute force failed %c at %d\n", sequence[i].compound,
               i);
      } else {
        // std::cout << "delta generated " + delta.toStr() + "\n";
        place(position + delta, sequence[i]);
        position += delta;
      }
    }
  } else {
    for (int i = 0; i < sequence.size(); i++) {
      if (position.x == length) {
        position.x = 0;
        position.y++;
      }
      if (matrix[position.y][position.x].compound == this->emptyChar) {
        place(position, sequence[i]);

        position.x++;
      }
    }
  }

  // if(placed != sequence.size()){
  //     printf("[ERROR] Failed to place all aminoacids\n");
  // }
}