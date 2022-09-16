#include "HydroCpp.h"
#include "Protein.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

std::vector<aminoacid> randomSequence(int length) {
  std::vector<aminoacid> sequence = std::vector<aminoacid>(length);
  for (int i = 0; i < length; i++) {
    sequence[i].compound = rand() % 2 == 0 ? 'P' : 'H';
  }
  return sequence;
}

void _display_random_proteins() {
  const int size = 10;

  printf("Protein size is %d\n", size);

  for (int c = 0; c < 10; c++) {

    protein p;
    p.emptyChar = ' ';
    p.initialize(size, false, true);
    p.position = vector2(rand() % 5, rand() % 5);

    std::vector<aminoacid> sequence = randomSequence(size);

    p.append(sequence);

    std::string directions("");
    std::string relative("");
    std::vector<vector2> r = p.get_relative_coords();
    for(int i=0; i<sequence.size(); i++){
      directions += "("+p.sequence[i].toStr()+")"+" ";
      relative += "("+r[i].toStr()+")"+" ";
    }
        
    // p.print(p.PRINT_MODE_INDEXED);
    p.print();
    printf("Score %d\n\n", p.score_function());
    std::cout << "Sequence " + p.sequence_string+"\n";
    std::cout << "Vectors "+directions+"\n";
    std::cout << "Vectors relative "+relative+"\n";
    std::cout << "-------------\n";
  }
}

std::vector<protein> random_population(int prole, int protein_size) {

  std::vector<protein> population = std::vector<protein>();

  for (int c = 0; c < prole; c++) {

    protein p;
    p.emptyChar = ' ';
    p.initialize(protein_size, false, true);
    p.position = vector2(rand() % 5, rand() % 5);

    std::vector<aminoacid> sequence = randomSequence(protein_size);

    p.append(sequence);
    population.push_back(p);
  }

  return population;
}

class protein_comparator{
public:
  bool operator()(protein a,protein b)
  {
    return a.score_function() < b.score_function();
  }
};

std::vector<protein> breed_and_mutate(std::vector<protein> initial_prole)
{
  int prole = initial_prole.size();
  std::priority_queue<protein,std::vector<protein>,protein_comparator> queue;
  
  for(int i=0; i<prole; i++)
    queue.push(initial_prole[i]);

  // std::vector<protein> selected;

  // for(int i=0; i<100; i++){
  //   selected.push_back(queue.top());
  //   queue.pop();
  // }

  protein selected[100];
  for(int i=0; i<100; i++)
  {
    selected[i] = queue.top();
    queue.pop();
  }

  //DEBUG
  // for(int i=0; i<10; i++)
  // {
  //   printf("%d ",selected[i].score_function());
  // }
  // printf("\n");
  
  //mutation, creates new prole

  enum placement {
    BEGINNING,
    END
  };
  
  for(int i=0; i<prole; i++)
  {
    //determines if subdivision of protein starts at the beginning or at the end
    placement subprotein = rand() % 2 == 0 ? BEGINNING : END;
    vector2 displacement = vector2(0,0);

    //selectes a random individual from population
    int indexA = rand() % (sizeof(selected)/sizeof(selected[0]));
    int indexB = rand() % (sizeof(selected)/sizeof(selected[0]));
    protein parentA = selected[indexA];
    protein parentB = selected[indexB];

    //determines how much we can displace a protein
    // int max_x = parentA.length - 1 - parentA._position.x;
    // int min_x = parentA._position.x;

    // int max_y = parentA.length - 1 - parentA._position.y;
    // int min_y = parentA._position.y;
    //-----
    
    protein child = protein(parentA.length);
    
    
    
    
  }
  
  return std::vector<protein>();
}

void evolution()
{
  std::vector<protein> initial_prole = random_population(100, 10);
  breed_and_mutate(initial_prole);
}
