#ifndef PROTEIN_H
#define PROTEIN_H

#include "Vector2.h"
#include <vector>
#include "HydroCpp.h"

struct protein {

    std::vector<std::vector<aminoacid>> matrix;
    std::string sequence_string;
    std::vector<vector2> sequence;

    int length;
    vector2 position = vector2(0, 0);
    bool randomizeSequences = false;
    char emptyChar = '*';

    vector2 _position = vector2(0, 0);

    protein(){}

    protein(int _length, vector2 initialPosition=vector2(0,0), bool randomStart=false, bool _randomizeSequences=false, char _emptyChar='*')
    {
        length = _length;
        position = initialPosition;
        _position = initialPosition;
        randomizeSequences = _randomizeSequences;
        emptyChar = _emptyChar;
        this->initialize(length, randomStart, randomizeSequences);
    }

    enum PRINT_MODE {
        PRINT_MODE_NORMAL,
        PRINT_MODE_INDEXED
    };

    void initialize(int _length, bool randomStart = false, bool _randomizeSequences = false);
    void append(std::vector<aminoacid> sequence);
    void print(PRINT_MODE mode = PRINT_MODE_NORMAL);

    // Checks if position + move respects the boundaries of the matrix and if the position is available
    // @param move movement in respect to current position
    // @returns true if move was successful
    bool checkMove(vector2 move);

    // Checks if location is available
    // @param location location to check
    // @returns true if location is available
    bool checkAvailable(vector2 position);
    void move(vector2 move);
    bool place(vector2 location, aminoacid element);
    bool place(int x, int y, aminoacid element);

    // Trys to generate a valid delta movement
    // @returns a valid delta movement if possible, otherwise returns VECTOR2_INVALID
    //vector2 _brute_force_positions();

    vector2 random_valid_delta();

    //@returns the active energy in the protein 
    int score_function();

    //@returns an array of elements displacements in relation to the initial element
    std::vector<vector2> get_relative_coords();

    //@returns the amount of invalid vectors
    int get_invalid_vectors();


};

#endif