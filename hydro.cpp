#include <iostream>
#include <vector>
#include <time.h>
#include "hydro.h"
#include "Tests/tester.h"
#include "components/protein.h"
#include "components/vector2.h"

using namespace std;


vector<aminoacid> randomSequence(int length){
    vector<aminoacid> sequence = vector<aminoacid>(length);
    for(int i=0; i<length; i++){
        sequence[i].compound = rand()%2 == 0 ? 'P' : 'H';
    }
    return sequence;
}

int main() {

    // const int size=10;

    // printf("Protein size is %d\n", size);

    // srand(time(NULL));
    // protein p;
    // p.emptyChar = '*';
    // p.initialize(size, false, true);
    // p.position = vector2(rand()%5,rand()%5);

    // vector<aminoacid> sequence = randomSequence(size);
    // for(int i=0; i<size; i++) printf("%c ", sequence[i].compound);
    // printf("\n\n");

    // p.append(sequence);

    // p.print(p.PRINT_MODE_INDEXED);

    printf("Test result %d\n", run_all_tests() ? 1 : 0);

    return 0;
}