#include "Database.h"

Group* Database::GetHead() {
  return head; 
}

void Database::push_back(Group& temp) {
  Group* newNode = new Group(temp); 

  if (head == nullptr) {
    head = newNode;
    tail = head;
  } 
  else {
    tail->SetNext(newNode);
    tail = newNode;
  }
}
