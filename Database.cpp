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

Person* Database::FindStudent(int id) {
  Group* currentGroup = head; 
  while (currentGroup) {
    Person* currentStudent = currentGroup->GetHead(); 
    while (currentStudent) {
      if (currentStudent->GetId() == id) 
        return currentStudent;
      currentStudent = currentStudent->GetNext();
    }
    currentGroup = currentGroup->GetNext();
  }
  return nullptr;
}

int Database::GetCountDiscip(int id) {
  Group* currentGroup = head; 
  while (currentGroup) {
    Person* currentStudent = currentGroup->GetHead(); 
    while (currentStudent) {
      if (currentStudent->GetId() == id) 
        return currentGroup->GetCountDiscip();
      currentStudent = currentStudent->GetNext();
    }
    currentGroup = currentGroup->GetNext();
  }
  return -1; 
}