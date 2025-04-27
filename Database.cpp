#include "Database.h"

Database::Database() {
  this->head = nullptr; 
  this->tail = nullptr; 
}

Database::~Database() {
  Group* current = head;

  while (current != nullptr) {
    Group* nextGroup = current->GetNext(); 
    delete current;
    current = nextGroup;
  }
}

void Database::AddGroup(Group* group) {
  Group* newObj = new Group(*group); //! 
  if (head == nullptr) {
    head = newObj;
    tail = newObj;
  } 
  else {
    tail->SetNext(newObj);
    tail = newObj;
  }
  tail->SetNext(nullptr);
}

Group* Database::FindGroup(int number) {
  Group* current = head; 
  while (current) {
    if (current->GetNumber() == number) 
      return current;
    current = current->GetNext();
  }
  return nullptr;
}