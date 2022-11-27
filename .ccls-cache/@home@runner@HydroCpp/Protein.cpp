#include "Protein.h"
#include "Vector2.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// implementação n-aria [segundo projeto]
// nesse caso trata-se de uma árvore n-ária completa (possui sempre 4 filhos)
// os filhos são cima, baixo, esquerda e direita representando as posições
// possíveis filhos vazios indicam que o espaço é proibido


//====================

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
  if (this->length >= 70) {
    std::cout << "[ERROR] Protein is too big to be printed in the terminal."
              << std::endl;
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
        bool r = place(position, amino_sequence[i]);
        while (r == false) {
          position.x = rand() % length;
          position.y = rand() % length;
          _position = position;
          r = place(position, amino_sequence[i]);
        }
        // printf("bool %d\n",r);
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
    // REGULAR CASE (it's what the professor wants)

    std::vector<int> pairs;

    for (int i = 1; i <= sqrt(length); i++) {
      if (length % i == 0) {
        if (i == length / i) {
          pairs.push_back(i);
        } else {
          pairs.push_back(i);
          pairs.push_back(length / i);
        }
        // printf("n %d\n",pairs[i]);
      }
    }

    int ry = ceil(sqrt(length));
    int rx = floor(sqrt(length));
    if (ry != rx) {
      rx = pairs[pairs.size() - 1];
      ry = pairs[pairs.size() - 2];
    }
    // if(rx*ry < length){
    //   ry++;
    // }

    printf("size is %d x %d\n", rx, ry);
    int c = 1;
    int flag = -1;

    enum Stage { down = 0, left = 1, up = 2, right = 3 };

    Stage stage = down;

    // safe precausion to not use a while loop
    // for(int n=0; n<amino_sequence.size(); n++)
    int n = 0;
    while (n < amino_sequence.size()) {
      if (stage == down && flag == -1) {
        for (int i = 0; i < ry; i++) {
          position.y++;
          place(position, amino_sequence[n]);
          n++;
        }
        flag = 0;
        stage = left;
      }

      else if (stage == left) {
        for (int i = 1; i < rx; i++) {
          position.x--;
          place(position, amino_sequence[n]);
          n++;
        }
        stage = up;

        flag++;
        if (flag == 2) {
          flag = 0;
          ry--;
          rx--;
        }

      }

      else if (stage == up) {
        for (int i = 1; i < ry; i++) {
          position.y--;
          place(position, amino_sequence[n]);
          n++;
        }
        stage = right;

        flag++;
        if (flag == 2) {
          flag = 0;
          ry--;
          rx--;
        }
      }

      else if (stage == right) {
        for (int i = 1; i < rx; i++) {
          position.x++;
          place(position, amino_sequence[n]);
          n++;
        }
        stage = down;

        flag++;
        if (flag == 2) {
          flag = 0;
          ry--;
          rx--;
        }
      }

      else if (stage == down) {
        for (int i = 1; i < ry; i++) {
          position.y++;
          place(position, amino_sequence[n]);
          n++;
        }
        stage = left;

        flag++;
        if (flag == 2) {
          flag = 0;
          ry--;
          rx--;
        }
      }
    }
  }
}

double protein::score_function() {

  double score = 0;

  struct H {
    vector2 pos = vector2(0, 0);
    int i = -1;

    H(vector2 _pos, int _i) {
      pos = _pos;
      i = _i;
    }
  };

  std::vector<H> hs;

  // first, we indentify and store all Hs in a vector
  for (int n = 0; n < sequence.size(); n++) {
    if (sequence[n] != VECTOR2_INVALID) {
      int i, j;
      i = sequence[n].y;
      j = sequence[n].x;

      if (matrix[i][j].compound == 'H')
        hs.push_back(H(vector2(j, i), n));
    }
  }

  // for each H we search in its row and in its column to add to the score

  for (int n = 0; n < hs.size(); n++) {
    vector2 _pos = hs[n].pos;

    for (int m = 0; m < hs.size(); m++) {
      // if its the same aminoacid, break one iteration
      if (hs[m].i == hs[n].i)
        continue;

      int dist = 0;
      if (hs[m].pos.x == _pos.x)
        dist = abs(hs[m].pos.y - _pos.y);
      else if (hs[m].pos.y == _pos.y)
        dist = abs(hs[m].pos.x - _pos.x);

      // printf("x %d - %d\n",hs[m].pos.x, _pos.x);
      // printf("y %d - %d\n",hs[m].pos.y, _pos.y);
      // printf("dist %d\n",dist);
      if (dist != 0)
        score += 1 / (double)dist;
    }
  }

  return score;
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