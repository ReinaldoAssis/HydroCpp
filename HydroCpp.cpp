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

bool isNumber(char x)
{
  return x >= 48 && x <= 57;
}

int main() {

  srand(time(NULL));

  std::cout << "Input: ";
  std::string choice("");
  std::cin >> choice;

  if(choice.find("rnd") != std::string::npos)
  {
    std::string nm("");
    std::cin >> nm;

    int _size = nm.length() > 0 ? std::stoi(nm) : 5;
    _display_random_proteins(_size,false);
  }

  else if(choice == "ev")
    evolution();

  else if(choice == "test")
    printf("\nTest result %s\n", run_all_tests() ? "[ALL PASSING]" : "[FAIL]");

  else
  {
    if(choice.find_first_not_of("PH") != std::string::npos)
    {
      std::cout << "Input invalido.\n";
      exit(1);
    }
    else
    {
      for(int c=0; c<100; c++)
      {
        std::string line("");
        if(c == 0) std::getline(std::cin,line);
        
        std::vector<aminoacid> sequence;
        for(int i=0; i<choice.size(); i++)
          sequence.push_back(aminoacid(choice[i],i));
        
        protein p = create_protein(sequence);
        if(p.length <= 100)
          p.print();
        std::cout << std::endl;
        printf("Score %d\n",p.score_function());
        
        std::getline(std::cin,line);
        if(line.size() != 0) break;
      }
    }
  }

  return 0;
}