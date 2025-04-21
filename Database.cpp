#include "Database.h"

Person* Database::GetHead() {
  return head; 
}

void Database::push_back( Person& temp) {
  Person* newNode = new Person(temp); 

  if (head == nullptr) {
    head = newNode;
    tail = head;
  } 
  else {
    tail->SetNext(newNode);
    tail = newNode;
  }
}
