#ifndef PROTEIN_H
#define PROTEIN_H

#include "vector2.h"
#include <vector>
#include "../hydro.h"

struct protein{

    std::vector<std::vector<aminoacid>> matrix;
    int length;
    vector2 position = vector2(0,0);
    bool randomizeSequences = false;
    char emptyChar = '*';

    vector2 _position = vector2(0,0);

    enum PRINT_MODE{
        PRINT_MODE_NORMAL,
        PRINT_MODE_INDEXED
    };

    void initialize(int _length, bool randomStart=false, bool _randomizeSequences=false);
    void append(std::vector<aminoacid> sequence);
    void print(PRINT_MODE mode=PRINT_MODE_NORMAL);
    bool checkMove(vector2 move);
    bool checkAvailable(vector2 position);
    void move(vector2 move);
    bool place(vector2 location, aminoacid element);
    vector2 _brute_force_positions();




};

#endif