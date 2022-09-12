#include "protein.h"
#include <iostream>
#include <vector>
#include "vector2.h"

using namespace std;

void protein::initialize(int _length, bool randomStart=false, bool _randomizeSequences=false){
        length = _length;
        matrix = vector<vector<aminoacid>>(length, vector<aminoacid>(length));
        
        for(int i=0; i<_length; i++){
            for (int j=0; j<_length; j++){
                matrix[i][j].compound = this->emptyChar;
                matrix[i][j].index = -1;
            }
        }
        
        if(randomStart){
            position.x = rand() % length;
            position.y = rand() % length;
            _position = position;
        }

        randomizeSequences = _randomizeSequences;
    }

void protein::print(PRINT_MODE mode=PRINT_MODE_NORMAL){
        for(int i=0; i<length; i++){
            for (int j=0; j<length; j++){

                switch(mode){
                    case PRINT_MODE_NORMAL:
                        cout << matrix[i][j].compound;
                        break;
                    case PRINT_MODE_INDEXED:
                        if(matrix[i][j].index != -1) std::cout << matrix[i][j].index;
                        else std::cout << emptyChar;
                        break;
                }

                    
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    // Checks if position + move respects the boundaries of the matrix and if the position is empty
    // @param move movement in respect to current position
    // @returns true if move was successful
    bool protein::checkMove(vector2 move){
        if(position.x + move.x < 0 || position.x + move.x >= length) return false;
        if(position.y + move.y < 0 || position.y + move.y >= length) return false;
        if(checkAvailable(position.add(move)) == false) return false;
        return true;
    }

    // Checks if location is available
    // @param location location to check
    // @returns true if location is available
    bool protein::checkAvailable(vector2 location){
        if(matrix[location.x][location.y].compound == emptyChar) return true;
        return false;
    }

    bool protein::place(vector2 location, aminoacid element){
        if(location.x < 0 || location.x >= length) return false;
        if(location.y < 0 || location.y >= length) return false;
        
        try{
            if(matrix[location.y][location.x].compound != this->emptyChar) return false;
            else matrix[location.y][location.x] = element;
            return true;
        }catch(exception e){
            printf("[ERROR] Failed to place aminoacid at %d, %d\n", location.x, location.y);
            return false;
        }
    }

    void protein::move(vector2 move){
        if(position.x + move.x > length){
            position.x = _position.x;
            position.y++;
            return;
        }
        if(position.y + move.y > length){
            printf("[ERROR] Protein is too long to fit in the matrix\n");
            return;
        }
        if(checkMove(move)){
            position.x += move.x;
            position.y += move.y;
        }
    }

    // Trys to generate a valid delta movement
    // @returns a valid delta movement if possible, otherwise returns VECTOR2_INVALID
    vector2 protein::_brute_force_positions()
    {

        bool Xaxis = rand()%2 == 0;
        vector2 delta = vector2(0,0);
        if(Xaxis)
            delta.x = rand()%2 == 0 ? 1 : -1;
        else
            delta.y = rand()%2 == 0 ? 1 : -1;

        for(int i=0; i<4; i++)
        {
            if(checkMove(position.add(delta))) return delta;
            else
            {
                switch(i)
                {
                    case 0:
                        delta = vector2(1,0);
                        break;
                    case 1:
                        delta = vector2(0,1);
                        break;
                    case 2:
                        delta = vector2(-1,0);
                        break;
                    case 3:
                        delta = vector2(0,-1);
                        break;
                }
                if(checkMove(position.add(delta))) return delta;
            }
        }

        return vector2(-1,-1);
    }

    void protein::append(vector<aminoacid> sequence){
        if(randomizeSequences){
            // iterate over sequence and branch aminoacids randomly
            for(int i=0; i<sequence.size(); i++)
            {
                sequence[i].index = i;
                //Determines if the inicial delta will be in the x or y axis
                vector2 delta = _brute_force_positions();
                if(delta == VECTOR2_INVALID){
                    printf("[ERROR] Brute force failed %c at %d\n", sequence[i].compound,i);
                }
                else
                {
                    place(position.add(delta), sequence[i]);
                    move(delta);
                }

            }
        } else
        {
            for(int i=0; i<sequence.size(); i++){
                if(position.x == length){
                    position.x = 0;
                    position.y++;
                }
                if(matrix[position.y][position.x].compound == this->emptyChar){
                    place(position, sequence[i]);

                    position.x++;
                }
            }

        }

        // if(placed != sequence.size()){
        //     printf("[ERROR] Failed to place all aminoacids\n");
        // }
        
    }