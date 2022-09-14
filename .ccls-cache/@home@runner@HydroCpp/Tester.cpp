#include "Tester.h"
#include "HydroCpp.h"
#include "Protein.h"
#include "Vector2.h"
#include <iostream>
#include <string>

void info(std::string msg) { std::cout << "[info] " + msg + "\n"; }

template <class x> std::string str(x a) { return std::to_string(a); }

void run_single_test(bool debug, bool result, bool &success,
                     std::string label) {
  std::string spacer = "....................";
  if (debug && result)
    std::cout << label + spacer.substr(0, 20 - label.size()) + " [OK]\n";
  else if (debug && !result)
    std::cout << label + " [ERROR]\n";
  success &= result;
}

bool test_vector2_add() {
  vector2 v1 = vector2(1, 2);
  vector2 v2 = vector2(3, 4);
  vector2 v3 = v1.add(v2);
  return v3.x == 4 && v3.y == 6;
  return true;
}

bool test_vector2_equality() {
  vector2 v1 = vector2(1, 2);
  vector2 v2 = vector2(1, 2);
  return v1 == v2;
}

bool test_vector2_inequality() {
  vector2 v1 = vector2(1, 2);
  vector2 v2 = vector2(3, 4);
  return v1 != v2;
}

bool test_protein_initialize() {
  protein p = protein(10, vector2(0, 0), false, true, '*');
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      if (p.matrix[i][j].compound != '*')
        return false;

  return true;
}

bool test_protein_place() {
  protein p = protein(10);
  aminoacid a = aminoacid('H', -1);
  aminoacid b = aminoacid('P', -1);
  p.place(vector2(0, 0), a);
  p.place(vector2(4, 0), b);
  return p.matrix[0][0].compound == 'H' && p.matrix[0][4].compound == 'P';
}

bool test_protein_checkMove() {
  protein p = protein(10);

  bool r1 = p.checkMove(vector2(-1, -1)) == false;
  bool r2 = p.checkMove(vector2(1, 1));
  bool r3 = p.checkMove(vector2(1, 0));
  bool r4 = p.checkMove(vector2(0, 1));
  bool r5 = p.checkMove(vector2(0, 4));

  return r1 && r2 && r3 && r4 && r5;
}

bool test_protein_checkAvailable() {

  bool _main = true;
  protein p = protein(10);

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      if (p.checkAvailable(vector2(i, j)) == false) {
        _main = false;
        break;
      }

  p.place(vector2(2, 5), aminoacid('x', -1));
  bool r1 = p.checkAvailable(vector2(2, 5)) == false;

  return r1 && _main;
}

bool test_protein_move() {
  protein p = protein(10);
  p.position = vector2(0, 0);

  vector2 down = vector2(0, 1);
  vector2 up = vector2(0, -1);
  vector2 left = vector2(-1, 0);
  vector2 right = vector2(1, 0);

  p.position.add(down);
  // info("r1 move " + p.position.toStr());

  bool r1 = p.position == vector2(0, 1);
  // info("r1 " + str(r1));

  p.position.add(up);
  // info("r2 move " + p.position.toStr());

  bool r2 = p.position == vector2(0, 0);
  // info("r2 " + str(r2));

  p.position.add(down);
  p.position.add(right);
  // info("r3 move " + p.position.toStr());

  bool r3 = p.position == vector2(1, 1);
  // info("r3 " + str(r3));

  p.position.add(right); // 2 1
  p.position.add(left);  // 1 1
  p.position.add(up);    // 1 0
  // info("r4 move " + p.position.toStr());

  bool r4 = p.position == vector2(1, 0);

  // info("r4 " + str(r4));

  return r1 && r2 && r3 && r4;
}

bool test_protein_valid_delta() {
  protein p = protein(3);
  aminoacid x = aminoacid('x', -1);
  p.place(vector2(0, 0), x);
  p.place(vector2(2, 0), x);

  p.position = vector2(1, 0);

  // p.print();

  vector2 delta = p.random_valid_delta();
  // info("delta " + delta.toStr());

  bool r1 = delta == vector2(0, 1);

  p = protein(5);
  p.place(4, 1, x);
  p.place(3, 0, x);
  p.place(3, 2, x);
  // p.place(2, 1, x);

  // p.print();

  p.position = vector2(3, 1);
  delta = p.random_valid_delta();

  // info("delta " + delta.toStr());

  bool r2 = delta == vector2(-1, 0);

  p = protein(5);
  p.place(4, 1, x);
  p.place(3, 0, x);

  p.position = vector2(3, 1);

  // p.print();

  delta = p.random_valid_delta();
  // info("delta " + delta.toStr());

  bool r3 = delta == vector2(-1, 0) || delta == vector2(0, 1);

  return r1 && r2 && r3;
}

bool run_all_tests(bool debug) {
  bool result = true;
  bool test = false;

  test = test_vector2_add();
  run_single_test(debug, test, result, std::string("vector2_add"));

  test = test_vector2_equality();
  run_single_test(debug, test, result, std::string("vector2_equality"));

  test = test_vector2_inequality();
  run_single_test(debug, test, result, std::string("vector2_inequality"));

  test = test_protein_initialize();
  run_single_test(debug, test, result, "protein_initialize");

  test = test_protein_place();
  run_single_test(debug, test, result, "protein_place");

  test = test_protein_checkMove();
  run_single_test(debug, test, result, "protein_check_move");

  test = test_protein_checkAvailable();
  run_single_test(debug, test, result, "protein_available");

  test = test_protein_move();
  run_single_test(debug, test, result, "protein_move");

  test = test_protein_valid_delta();
  run_single_test(debug, test, result, "protein_valid_delta");

  return result;
}
