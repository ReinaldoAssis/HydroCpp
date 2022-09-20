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
  sequence_string = "";
}

void protein::print(PRINT_MODE mode) {
  if(this->length >= 70){
    std::cout << "[ERROR] Protein is too big to be printed in the terminal." << std::endl;
    return;
  }
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

    matrix[location.y][location.x] = element;
    sequence.push_back(location);
    sequence_string += element.compound;
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

void protein::append(vector<aminoacid> amino_sequence) {
  if (randomizeSequences) {
    // iterate over sequence and branch aminoacids randomly
    for (int i = 0; i < amino_sequence.size(); i++) {
      // sets aminoacid index
      amino_sequence[i].index = i;

      if (i == 0) {
        place(position, amino_sequence[i]);
        // if (checkMove(vector2(0, 1)))
        //   matrix[position.y + 1][position.x] = aminoacid('*', -1);
        // else if (checkMove(vector2(0, -1)))
        //   matrix[position.y - 1][position.x] = aminoacid('*', -1);
        // else if (checkMove(vector2(1, 0)))
        //   matrix[position.y][position.x + 1] = aminoacid('*', -1);
        // else if (checkMove(vector2(-1, 0)))
        //   matrix[position.y][position.x - 1] = aminoacid('*', -1);

        continue;
      }

      // Determines if the inicial delta will be in the x or y axis
      vector2 delta = random_valid_delta();
      if (delta == VECTOR2_INVALID) {
        // printf("[ERROR] Brute force failed %c at %d\n",
               // amino_sequence[i].compound, i);

        sequence.push_back(VECTOR2_INVALID);
        sequence_string += amino_sequence[i].compound;

      } else {
        place(position + delta, amino_sequence[i]);
        position += delta;
      }
    }
  } else {
    for (int i = 0; i < amino_sequence.size(); i++) {
      if (position.x == length) {
        position.x = 0;
        position.y++;
      }
      if (matrix[position.y][position.x].compound == this->emptyChar) {
        place(position, amino_sequence[i]);

        position.x++;
      }
    }
  }
}

// OLD SCORE FUNCTION
// int protein::score_function() {
//   int score = 0;

//   // THIS IS INSANELY INEFFICIENT! I'm just doing it as a temporary solution!
//   // for (int i = 0; i < this->length; i++) {
//   //   for (int j = 0; j < this->length; j++) {
//   //     if (this->matrix[i][j].compound == 'H') {
//   //       if (i - 1 >= 0)
//   //         if (this->matrix[i - 1][j].compound == 'H')
//   //           score++;

//   //       if (i + 1 < this->length)
//   //         if (this->matrix[i + 1][j].compound == 'H')
//   //           score++;

//   //       if (j - 1 >= 0)
//   //         if (this->matrix[i][j - 1].compound == 'H')
//   //           score++;

//   //       if (j + 1 < this->length)
//   //         if (this->matrix[i][j + 1].compound == 'H')
//   //           score++;
//   //     }
//   //   }
//   // }

//   for (int n = 0; n < sequence.size(); n++) {

//     if (sequence[n] != VECTOR2_INVALID) {
//       int i, j;
//       i = sequence[n].y;
//       j = sequence[n].x;

//       if (this->matrix[i][j].compound == 'H') {
//         if (i - 1 >= 0)
//           if (this->matrix[i - 1][j].compound == 'H')
//             score++;

//         if (i + 1 < this->length)
//           if (this->matrix[i + 1][j].compound == 'H')
//             score++;

//         if (j - 1 >= 0)
//           if (this->matrix[i][j - 1].compound == 'H')
//             score++;

//         if (j + 1 < this->length)
//           if (this->matrix[i][j + 1].compound == 'H')
//             score++;
//       }
//     }
//   }

//   return score;
// }

double protein::score_function() {

  double score=0;

  struct H
  {
    vector2 pos = vector2(0,0);
    int i=-1;

    H(vector2 _pos, int _i){
      pos = _pos;
      i = _i;
    }
  };
  
  std::vector<H> hs;
  
  for(int n=0; n<sequence.size(); n++)
  {
    if (sequence[n] != VECTOR2_INVALID) {
      int i, j;
      i = sequence[n].y;
      j = sequence[n].x;

      if(matrix[i][j].compound == 'H')
        hs.push_back(H(vector2(j,i),n));
    }
  }

  for(int n=0; n<hs.size(); n++)
  {
    int local_score=0;
    
  }
  
}

std::vector<vector2> protein::get_relative_coords() {
  vector2 previous = sequence[0];
  std::vector<vector2> relative;

  relative.push_back(vector2(0, 0));

  for (int i = 1; i < length; i++) {
    if (sequence[i] != VECTOR2_INVALID) {
      relative.push_back((sequence[i] - previous));
      previous = sequence[i];
    } else
      relative.push_back(VECTOR2_INVALID);
  }

  return relative;
}

int protein::get_invalid_vectors() {
  int c = 0;
  for (int i = 0; i < sequence.size(); i++)
    if (sequence[i] == VECTOR2_INVALID)
      c++;
  return c;
}