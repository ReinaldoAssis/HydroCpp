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
#endif