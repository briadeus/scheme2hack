#include "scanner.h"
#include <iostream>

int main() {
  Scanner s("C:\\dev\\source\\scheme2hack\\res\\programm.scheme");
  std::cout << "starting";

  s.hasNext();

  return 0;
}