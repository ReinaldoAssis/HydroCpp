#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct aminoacid{
    char compound;
};

struct vector2{
    int x;
    int y;
    vector2(int x, int y){
        this->x = x;
        this->y = y;
    }

    vector2 add(vector2 v){
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
};

struct protein{

    vector<vector<aminoacid>> matrix;
    int length;
    vector2 position = vector2(0,0);
    bool randomizeSequences = false;
    char emptyChar = '*';

    vector2 _position = vector2(0,0);


    void initialize(int _length, bool randomStart=false){
        length = _length;
        matrix = vector<vector<aminoacid>>(length, vector<aminoacid>(length));
        
        for(int i=0; i<_length; i++){
            for (int j=0; j<_length; j++){
                matrix[i][j].compound = this->emptyChar;
            }
        }
        
        if(randomStart){
            position.x = rand() % length;
            position.y = rand() % length;
            _position = position;
        }
    }

    void print(){
        for(int i=0; i<length; i++){
            for (int j=0; j<length; j++){
                std::cout << matrix[i][j].compound;
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    bool checkMove(vector2 move){
        if(position.x + move.x < 0 || position.x + move.x >= length) return false;
        if(position.y + move.y < 0 || position.y + move.y >= length) return false;
        return true;
    }

    bool checkAvailable(vector2 location){
        if(matrix[location.x][location.y].compound == emptyChar) return true;
        return false;
    }

    bool place(vector2 location, aminoacid element){
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

    void move(vector2 move){
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

    void append(vector<aminoacid> sequence){
        int placed = 0;
        if(randomizeSequences){
            for(int i=0; i<sequence.size(); i++){
                bool deltaxaxis = rand() % 2 == 0;
                vector2 delta = vector2(deltaxaxis ? (rand()%2 ? 1 : -1) : 0, !deltaxaxis ? (rand()%2 ? 1 : -1) : 0);
                if(checkMove(delta)){
                    place(position, sequence[i]);
                    move(delta);
                    placed++;
                } 
                else
                {
                    for(int d=0; d<4; d++)
                    {
                        switch(d){
                            case 0:
                                delta = vector2(1,0);
                                break;
                            case 1:
                                delta = vector2(-1,0);
                                break;
                            case 2:
                                delta = vector2(0,1);
                                break;
                            case 3:
                                delta = vector2(0,-1);
                                break;
                        }
                        if(checkMove(delta) && checkAvailable(position)){
                            place(position.add(delta), sequence[i]);
                            move(delta);
                            placed++;
                            break;
                        }
                    }
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
                    placed++;

                    position.x++;
                }
            }

        }

        if(placed != sequence.size()){
            printf("[ERROR] Failed to place all aminoacids\n");
        }
        
    }

};

vector<aminoacid> randomSequence(int length){
    vector<aminoacid> sequence = vector<aminoacid>(length);
    for(int i=0; i<length; i++){
        sequence[i].compound = rand()%2 == 0 ? 'P' : 'H';
    }
    return sequence;
}

int main() {
    srand(time(NULL));
    protein p;
    p.emptyChar = ' ';
    p.initialize(10);
    p.randomizeSequences = true;
    p.position = vector2(rand()%5,rand()%5);

    vector<aminoacid> sequence = randomSequence(5);
    printf("[");
    for(int i=0; i<5; i++) printf("%c ", sequence[i].compound);
    printf("]\n\n");

    p.append(sequence);

    p.print();

    return 0;
}