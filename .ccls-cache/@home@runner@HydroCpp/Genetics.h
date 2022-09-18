#ifndef GENETICS
#define GENETICS
#include "Protein.h"
#include <vector>

void _display_random_proteins(int size = 5, bool debug = true);
std::vector<protein> random_population(int prole, int protein_size,
                                       std::vector<aminoacid> amino_sequence);
void evolution();

protein create_protein(std::vector<aminoacid> sequence, char emptyChar = ' ');

#endif