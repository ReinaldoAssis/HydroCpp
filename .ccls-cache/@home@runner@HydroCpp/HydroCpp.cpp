#include "HydroCpp.h"
#include "Protein.h"
#include "Tester.h"
#include "Vector2.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

vector<aminoacid> randomSequence(int length) {
  vector<aminoacid> sequence = vector<aminoacid>(length);
  for (int i = 0; i < length; i++) {
    sequence[i].compound = rand() % 2 == 0 ? 'P' : 'H';
  }
  return sequence;
}

int main() {

  const int size = 10;

  printf("Protein size is %d\n", size);

  srand(time(NULL));

  for (int c = 0; c < 10; c++) {

    protein p;
    p.emptyChar = ' ';
    p.initialize(size, false, true);
    p.position = vector2(rand() % 5, rand() % 5);

    vector<aminoacid> sequence = randomSequence(size);
    for (int i = 0; i < size; i++)
      printf("%c ", sequence[i].compound);
    printf("\n\n");

    p.append(sequence);

    // p.print(p.PRINT_MODE_INDEXED);
    p.print();
  }

  printf("\nTest result %s\n", run_all_tests() ? "[ALL PASSING]" : "[FAIL]");

  return 0;
}