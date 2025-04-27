#include "Group.h"

Group::Group() {
  this->head = nullptr; 
  this->tail = nullptr; 
  this->number = 0;
  this->year = 0;

  this->pNext = nullptr;
}

Group::Group(const Group& other) {
  this->head = nullptr; 
  this->tail = nullptr; 
  this->number = other.number;
  this->year = other.year;

  this->pNext = nullptr;

  Person* current = other.head;
  while (current != nullptr) {
    Person* newPerson = new Person(*current);
    if (head == nullptr) {
      head = newPerson;
      tail = newPerson;
    } 
    else {
      tail->SetNext(newPerson);
      tail = newPerson;
    }
    tail->SetNext(nullptr);
    current = current->GetNext();
  }
  if (tail != nullptr) {
    tail->SetNext(nullptr);  
  }
}

Group::~Group() {
  Person* current = head;
  while (current != nullptr) {
    Person* nextPerson = current->GetNext();  
    delete current;
    current = nextPerson;
  }
}

void Group::AddStudent(Person temp) {
  Person* newObj = new Person(temp); //! 
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

void Group::SetDirect(Direction* dir) {
  if (this->direct != nullptr) delete this->direct;
  this->direct = new Direction(*dir); 
}