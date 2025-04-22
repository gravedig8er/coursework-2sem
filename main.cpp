#include <iostream> 
#include <fstream>
#include "Database.h"
#include "MyFunctions.h"
#include "Person.h"
#include "FullName.h"


int main() {
  std::fstream students, out, protocol;
  Database base; // хранилище

  students.open("students.txt", std::ios::in);
  if (!students.is_open()) {std::cout << "Check students file"; return 0;}

  Person* temp = base.GetHead();
  
}
