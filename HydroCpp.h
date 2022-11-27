#ifndef HYDRO_H
#define HYDRO_H

#define AMINOACID_NULL aminoacid('n', -2);

struct aminoacid {
  char compound;
  int index;

  aminoacid() {
    compound = 'n';
    index = -2;
  }

  aminoacid(char c, int i) {
    compound = c;
    index = i;
  }

  bool operator==(aminoacid b) {
    return b.compound == this->compound && b.index == this->index;
  }

  bool operator!=(aminoacid b) { return !(*this == b); }
};

class narayNode {
public:
  double valor;
  narayNode *up;
  narayNode *down;
  narayNode *right;
  narayNode *left;

  enum POS { UP, DOWN, RIGHT, LEFT };

  narayNode() {}

  narayNode(double _valor)
  {
    valor = _valor;
    up = new narayNode();
    down = new narayNode();
    left = new narayNode();
    right = new narayNode();
  }

  narayNode(double _valor, narayNode *_up, narayNode *_down,
            narayNode *_left, narayNode *_right) {
    valor = _valor;
    up = _up;
    down = _down;
    left = _left;
    right = _right;
  }

  // adiciona vizinho
  void neighbor(narayNode *_neighbor, POS placement) {
    switch (placement) {
    case UP:
      up = _neighbor;
      break;

    case DOWN:
      down = _neighbor;
      break;

    case LEFT:
      left = _neighbor;
      break;

    case RIGHT:
      right = _neighbor;
      break;
    }
  }
};

#endif