#include "HydroCpp.h"
#include "Protein.h"
#include <iostream>
#include <queue>
#include <random>
#include <time.h>
#include <vector>

//@param arr - array to print
//@param s - start
//@param e - end
void print_vector_array(std::vector<vector2> arr, int s, int e,
                        bool breakline = true) {
  for (int i = s; i < e; i++)
    if (arr[i] != VECTOR2_INVALID)
      std::cout << "(" + arr[i].toStr() + ") ";
  if (breakline)
    std::cout << std::endl;
}

std::vector<aminoacid> randomSequence(int length) {
  std::vector<aminoacid> sequence = std::vector<aminoacid>(length);
  std::cout << "sequence forming ";
  for (int i = 0; i < length; i++) {
    sequence[i].compound = rand() % 2 == 0 ? 'P' : 'H';
    std::cout << sequence[i].compound;
    std::cout << " ";
  }
  std::cout << std::endl;
  return sequence;
}

protein create_protein(std::vector<aminoacid> sequence, char emptyChar) {
CONSTRUCT:
  protein p;
  p.emptyChar = emptyChar;
  p.initialize(sequence.size(), false, true);
  p.position = vector2(rand() % 5, rand() % 5);
  p._position = p.position;

  p.append(sequence);

  if (p.get_invalid_vectors() > 0)
    goto CONSTRUCT;

  return p;
}

void _display_random_proteins(int size, bool debug) {
  const char emptyChar = ' ';

  printf("Protein size is %d\n", size);

  for (int c = 0; c < 10; c++) {

  CONSTRUCT:
    protein p;
    p.emptyChar = emptyChar;
    //p.initialize(size, false, true);
    p.initialize(size, false, false);
    p.position = vector2(size-2, 1);
    p._position = p.position;

    std::vector<aminoacid> sequence = randomSequence(size);

    p.append(sequence);

    if (p.get_invalid_vectors() > 0)
      goto CONSTRUCT;

    std::string directions("");
    std::string relative("");
    std::vector<vector2> r = p.get_relative_coords();

    if (debug) {
      for (int i = 0; i < sequence.size(); i++) {
        directions += "(" + p.sequence[i].toStr() + ")" + " ";
        relative += "(" + r[i].toStr() + ")" + " ";
      }
    }

    // p.print(p.PRINT_MODE_INDEXED);
    p.print();
    std::cout << std::endl;
    printf("Score %.2f\n", p.score_function());
    std::cout << "Initial position " + p._position.toStr() + "\n\n";
    std::cout << "Sequence " + p.sequence_string + "\n";
    if (debug) {
      std::cout << "Vectors " + directions + "\n";
      std::cout << "Vectors relative " + relative + "\n";
    }
    std::cout << "-------------\n";
  }
}

std::vector<protein> random_population(int prole, int protein_size,
                                       std::vector<aminoacid> amino_sequence) {

  std::vector<protein> population = std::vector<protein>();

  for (int c = 0; c < prole; c++) {

    protein p;
    p.emptyChar = ' ';
    p.initialize(protein_size, true, true);
    p.position = vector2(rand() % 5, rand() % 5);

    // std::vector<aminoacid> sequence = randomSequence(protein_size);

    p.append(amino_sequence);
    population.push_back(p);
  }

  return population;
}

class protein_comparator {
public:
  bool operator()(protein a, protein b) {
    return a.score_function() - a.get_invalid_vectors() * 10 <
           b.score_function() - b.get_invalid_vectors() * 10;
  }
};

// ATENTION: do not use an initial prole with less than 10 individuals!
std::vector<protein> breed_and_mutate(std::vector<protein> initial_prole) {
  int prole = initial_prole.size();
  std::priority_queue<protein, std::vector<protein>, protein_comparator> queue;

  for (int i = 0; i < prole; i++)
    queue.push(initial_prole[i]);

  // std::vector<protein> selected;

  // for(int i=0; i<100; i++){
  //   selected.push_back(queue.top());
  //   queue.pop();
  // }

  protein selected[prole / 10];
  for (int i = 0; i < prole / 10; i++) {
    selected[i] = queue.top();
    queue.pop();
  }

  // DEBUG
  // for(int i=0; i<10; i++)
  // {
  //   printf("%d ",selected[i].score_function());
  // }
  // printf("\n");

  // mutation, creates new prole
  std::vector<protein> newprole;
  for (int i = 0; i < prole; i++) {
    // determines if subdivision of protein starts at the beginning or at the
    // end placement subprotein = rand() % 2 == 0 ? BEGINNING : END;

    // selectes a random individual from population
    int indexA = rand() % (sizeof(selected) / sizeof(selected[0]));
    int indexB = rand() % (sizeof(selected) / sizeof(selected[0]));
    protein parentA = selected[indexA];
    protein parentB = selected[indexB];

    std::vector<vector2> dataA = parentA.get_relative_coords();
    std::vector<vector2> dataB = parentB.get_relative_coords();
    std::vector<vector2> genesA;
    std::vector<vector2> genesB;
    std::vector<vector2> product;

    int half = parentA.sequence.size() / 2;
    int genesA_s = rand() % half;
    int genesB_s = rand() % half;
    int mutations = parentA.length - (genesA_s + genesB_s);

    // printf("genesA %d genesB %d rest %d\n", genesA_s, genesB_s, mutations);

    genesA = std::vector<vector2>(dataA.begin(), dataA.begin() + genesA_s);
    genesB = std::vector<vector2>(dataB.begin() + genesA_s,
                                  dataB.begin() + genesA_s + genesB_s);

    // DEBUG
    // std::cout << "parentA vectors ";
    // print_vector_array(dataA, 0, parentA.length);

    // std::cout << "parentB vectors ";
    // print_vector_array(dataB, 0, parentB.length);

    // std::cout << "Crossed vectors ";
    // print_vector_array(dataA, 0, genesA.size(), false);
    // print_vector_array(dataB, genesA_s, genesA_s + genesB_s, false);

    vector2 start = vector2((parentA._position.x + parentB._position.x) / 2,
                            (parentA._position.y + parentB._position.y) / 2);
    protein child;
    child.emptyChar = ' ';
    child.position = start;
    child._position = start;
    child.initialize(parentA.length, false, true);

    for (int g = 0; g < genesA.size(); g++) {
      vector2 delta = dataA[g];
      if (delta != VECTOR2_INVALID) {
        aminoacid a = aminoacid(parentA.sequence_string[g], g);
        if (child.place(child.position + delta, a))
          child.position += delta;
        else
          child.sequence.push_back(VECTOR2_INVALID);
      } else
        child.sequence.push_back(VECTOR2_INVALID);
    }

    for (int g = genesA_s; g < genesA_s + genesB_s; g++) {
      vector2 delta = dataB[g];
      if (delta != VECTOR2_INVALID) {
        aminoacid b = aminoacid(parentB.sequence_string[g], g);
        if (child.place(child.position + delta, b))
          child.position += delta;
        else
          child.sequence.push_back(VECTOR2_INVALID);
      } else
        child.sequence.push_back(VECTOR2_INVALID);
    }

    for (int g = genesA_s + genesB_s; g < genesA_s + genesB_s + mutations;
         g++) {

      vector2 delta = child.random_valid_delta();
      if (delta != VECTOR2_INVALID) {
        aminoacid m = aminoacid(parentB.sequence_string[g], g);
        if (child.place(child.position + delta, m))
          child.position += delta;
        else
          child.sequence.push_back(VECTOR2_INVALID);
      } else
        child.sequence.push_back(VECTOR2_INVALID);
    }

    // DEBUG
    // std::vector<vector2> test = child.get_relative_coords();
    // print_vector_array(test, genesA_s + genesB_s,
    //                    genesA_s + genesB_s + mutations);

    // std::cout << "\n------------" << std::endl;

    // std::cout << "------------" << std::endl;
    // child.print();
    // std::cout << "------------" << std::endl;

    newprole.push_back(child);
  }

  return newprole;
}

protein best_score(std::vector<protein> population) {
  double max = 0;
  protein best;
  for (int i = 0; i < population.size(); i++) {
    double score = population[i].score_function();
    if (max < score) {
      max = score;
      best = population[i];
    }
  }
  return best;
}

void evolution() {
  const int _size = 30;

  std::vector<aminoacid> amino_sequence = randomSequence(_size);
  std::cout << "Starting evolution with ";
  for (int i = 0; i < amino_sequence.size(); i++)
    std::cout << amino_sequence[i].compound;
  std::cout << std::endl;

  std::vector<protein> initial_prole =
      random_population(100, _size, amino_sequence);

  protein k = best_score(initial_prole);
  printf("Initial prole score %.2f\n", k.score_function());
  k.print();

  for (int i = 0; i < 800; i++)
    initial_prole = breed_and_mutate(initial_prole);

  k = best_score(initial_prole);
  printf("Evolved prole score %.2f\n", k.score_function());
  k.print();
}
