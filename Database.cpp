#include "Database.h"

Person* Database::GetHead() {
  return head; 
}

void Database::push_back(Person* temp) {
  if (head == nullptr) {head = new Person(temp); tail = head;}
  else {
    Person* v = new Person(temp);
    tail->SetNext(v);
    tail = v; 
  }
}