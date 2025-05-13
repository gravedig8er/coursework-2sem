#include "DisciplineBase.h"

DisciplineBase::DisciplineBase() {
  this->head = nullptr; 
  this->tail = nullptr; 
}

DisciplineBase::~DisciplineBase() {
  DisciplineNode* current = head;
  while (current != nullptr) {
    DisciplineNode* next = current->GetNext();
    delete current;
    current = next;
  }
  head = nullptr;
  tail = nullptr;
}

DisciplineNode* DisciplineBase::find(DisciplineNode temp) {
  DisciplineNode* current = head; 
  while (current) {
    if (*current == temp) return current;
    current = current->GetNext();
  }
  return nullptr;
}

void DisciplineBase::push_back(DisciplineNode temp) {
  DisciplineNode* newNode = new DisciplineNode(temp);

  if (head == nullptr) {
    head = newNode;
    tail = head;
  } 
  else {
    tail->SetNext(newNode); 
    tail = newNode;         
  }
}