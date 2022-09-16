#include <iostream>
#include <time.h>
#include <random>
#include <vector>
#include "Protein.h"
#include "HydroCpp.h"

std::vector<aminoacid> randomSequence(int length) {
  std::vector<aminoacid> sequence = std::vector<aminoacid>(length);
  for (int i = 0; i < length; i++) {
    sequence[i].compound = rand() % 2 == 0 ? 'P' : 'H';
  }
  return sequence;
}

void _display_random_proteins()
{
  const int size = 10;

  printf("Protein size is %d\n", size);

  srand(time(NULL));

  for (int c = 0; c < 10; c++) {

    protein p;
    p.emptyChar = ' ';
    p.initialize(size, false, true);
    p.position = vector2(rand() % 5, rand() % 5);

    std::vector<aminoacid> sequence = randomSequence(size);
    // for (int i = 0; i < size; i++)
    //   printf("%c ", sequence[i].compound);
    // printf("\n\n");

    p.append(sequence);

    // p.print(p.PRINT_MODE_INDEXED);
    p.print();
    printf("Score %d\n\n",p.score_function());
    }
}