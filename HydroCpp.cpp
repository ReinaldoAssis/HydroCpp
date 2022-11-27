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

bool isNumber(char x) { return x >= 48 && x <= 57; }

protein _create_protein(std::vector<aminoacid> sequence, char emptyChar) {
CONSTRUCT:
  protein p;
  p.emptyChar = emptyChar;
  p.initialize(sequence.size(), false, false);
  // p.position = vector2(rand() % 5, rand() % 5);
  p.position = vector2(sequence.size() / 2 + 1, sequence.size() / 2);
  p._position = p.position;

  p.append(sequence);

  if (p.get_invalid_vectors() > 0)
    goto CONSTRUCT;

  return p;
}

// segundo projeto

void naraySolution(vector<aminoacid> sequencia) {
  narayNode root; // arvore n-aria
  protein p;
  p.initialize(20,false,false);
  p._position = vector2(10,10);
  p.position = vector2(10,10);
  
  root.valor = 0;
  p.place(p.position,sequencia[0]);
  // p.position = vector2(5,5);
  //i ++

  narayNode *leaf = &root; //points to the last leaf
  for(int i=1; i<sequencia.size(); i++)
  {
    char c = sequencia[i].compound;
    if(c == 'P') //no caso do meu projeto, p não altera score
    {
      vector2 delta = p.random_valid_delta();
      p.place(p.position+delta,sequencia[i]);
      p.position += delta;
      
    }
    else if(c == 'H')
    {
      //cima=0,baixo=1,esquerda=2,direita=3
      //vector<double> scores;
      double max=-1;
      int index=-1;
      protein aux = p;

      vector2 d = vector2(0,0);
      
      //cima
      d = vector2(0,-1);
      if(aux.checkMove(d))
      {
        aux.place(aux.position+d,sequencia[i]);
        double sc = aux.score_function();
        leaf->up = new narayNode(sc);
        
        if(sc > max){
          max = sc;
          index = 0;
        }
      }else{leaf->up = new narayNode(-1);}
      aux = p;

      //baixo
      d = vector2(0,1);
      if(aux.checkMove(d))
      {
        aux.place(aux.position+d,sequencia[i]);
        double sc = aux.score_function();
        leaf->down = new narayNode(sc);
        
        if(sc > max){
          max = sc;
          index = 0;
        }
      }
      else{leaf->down = new narayNode(-1);}
      aux = p;

      //esquerda
      d = vector2(-1,0);
      if(aux.checkMove(d))
      {
        aux.place(aux.position+d,sequencia[i]);
        double sc = aux.score_function();
        leaf->left = new narayNode(sc);
        
        if(sc > max){
          max = sc;
          index = 0;
        }
      }
      else{leaf->left = new narayNode(-1);}
      aux = p;

      //direita
      d = vector2(1,0);
      if(aux.checkMove(d))
      {
        aux.place(aux.position+d,sequencia[i]);
        double sc = aux.score_function();
        leaf->right = new narayNode(sc);
        
        if(sc > max){
          max = sc;
          index = 0;
        }
      }else{leaf->right = new narayNode(-1);}

      printf("\n");

      printf("root %.2f\n",leaf->valor);
      printf("c %.2f\n",leaf->up->valor);
      printf("b %.2f\n",leaf->down->valor);
      printf("e %.2f\n",leaf->left->valor);
      printf("d %.2f\n",leaf->right->valor);
      printf("\n");
      
      
      switch(index)
      {
        case 0:
          p.place(p.position+vector2(0,-1),sequencia[i]);
          p.position += vector2(0,-1);
          leaf = leaf->up;
          break;

        case 1:
          p.place(p.position+vector2(0,1),sequencia[i]);
          p.position += vector2(0,1);
          leaf = leaf->down;
          break;

        case 2:
          p.place(p.position+vector2(-1,0),sequencia[i]);
          p.position += vector2(-1,0);
          leaf = leaf->left;
          break;

        case 3:
          p.place(p.position+vector2(1,0),sequencia[i]);
          p.position += vector2(1,0);
          leaf = leaf->right;
          break;
      }
      
      
      
    }
  }

  p.print(protein::PRINT_MODE_NORMAL);
  printf("score %.2f\n\n",p.score_function());

  // printf("==== N-arya tree ====\n\n");

  // leaf = &root;
  // for(int n=0; n<sequencia.size(); n++)
  // {
  //   //if(sequencia[n].compound == 'P') continue;
  //   double u = leaf->up->valor;
  //   double d = leaf->down->valor;
  //   double l = leaf->left->valor;
  //   double r = leaf->right->valor;
    
  //   printf("[%c]\n", sequencia[n].compound);
  //   printf(" ↳ %.2f  %.2f  %.2f  %.2f\n", u, d, l, r);
  //   int index = -1;

  //   if(u >= d && u >= l && u >= r) index = 0;
  //   if(d >= u && d >= l && d >= r) index = 1;
  //   if(l >= u && l >= d && l >= r) index = 2;
  //   if(r >= u && r >= d && r >= l) index = 3;
  //   printf("max %d\n",index);

  //   if(index == 0) leaf = leaf->up;
  //   else if(index == 1) leaf = leaf->down;
  //   else if(index == 2) leaf = leaf->left;
  //   else if(index == 3) leaf = leaf->right;
  //   else printf("ERROR!!\n");
    
  // }
  
}

int main() {

  srand(time(NULL));

  std::cout << "Input: ";
  std::string choice("");
  std::cin >> choice;

  if (choice.find("rnd") != std::string::npos) {
    std::string nm("");
    std::cin >> nm;

    int _size = nm.length() > 0 ? std::stoi(nm) : 5;
    //_display_random_proteins(_size, false);

    for (int c = 0; c < 100; c++) {
      std::string line("");
      if (c == 0)
        std::getline(std::cin, line);

      _display_random_proteins(_size, false);

      std::getline(std::cin, line);
      if (line.size() != 0)
        break;
    }
  }

  else if (choice == "ev")
    evolution();

  else if (choice == "test")
    printf("\nTest result %s\n", run_all_tests() ? "[ALL PASSING]" : "[FAIL]");

  else if (choice == "nary") {
    std::cout << "Sequence: ";
    std::string s("");
    std::cin >> s;

    std::vector<aminoacid> v;

    for (int k = 0; k < s.size(); k++)
      v.push_back(aminoacid(s[k], -1));

    naraySolution(v);

  }

  else {
    if (choice.find_first_not_of("PH") != std::string::npos) {
      std::cout << "Input invalido.\n";
      exit(1);
    } else {
      std::cout << std::endl;
      for (int c = 0; c < 100; c++) {
        std::string line("");
        if (c == 0)
          std::getline(std::cin, line);

        std::vector<aminoacid> sequence;
        for (int i = 0; i < choice.size(); i++)
          sequence.push_back(aminoacid(choice[i], i));

        protein p = _create_protein(sequence, '\0');
        if (p.length <= 100) {
          p.print();
          // std::cout << '\n';
          // p.print(protein::PRINT_MODE_INDEXED);
        }
        std::cout << std::endl;
        printf("Score %.2f\n", p.score_function());
        // std::cout << p.sequence_string << std::endl;
        // std::cout << "Initial pos "+p._position.toStr() << std::endl;

        std::getline(std::cin, line);
        if (line.size() != 0)
          break;
      }
    }
  }

  return 0;
}