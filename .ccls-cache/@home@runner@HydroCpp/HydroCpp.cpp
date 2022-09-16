#include "HydroCpp.h"
#include "Genetics.h"
#include "Protein.h"
#include "Tester.h"
#include "Vector2.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

#define POPULATION_SIZE 1000

int main() {

  srand(time(NULL));
  
  _display_random_proteins();
  //evolution();

  printf("\nTest result %s\n", run_all_tests() ? "[ALL PASSING]" : "[FAIL]");

  return 0;
}