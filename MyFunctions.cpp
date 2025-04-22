#include "MyFunctions.h"

void reset(char* str, int length) {
    for (int i = 0; i < length; i++) {
      str[i] = '\0';
    }
}

Group* FindGroup(Database& base, int number, int year, Direction* direct) {
  Group* current = base.GetHead();
  while (current) {
    if (current->GetNumber() == number) {
      return current; 
    }
    current = current->GetNext();
  }

  Group* newGroup = new Group();
  newGroup->SetYEAR(year);
  newGroup->SetDIRECT(direct);
  newGroup->SetGroupNumber(number); // нужно реализовать
  base.push_back(newGroup);

  return newGroup;
}
