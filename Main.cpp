#include "Lit.h"
#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> argv_s;

  for (int i = 0; i < argc; i++) {
    argv_s.push_back(argv[i]);
  }

  if (argc < 2) {
    std::cout << "Use 'lit help'.\n";

  } else {
    Lit *lit = new Lit(argv_s);
    delete lit;
  }
  return 0;
}