#include "Discipline.h"

Discipline::Discipline() {
  this->obj = nullptr; 
  this->pNext = nullptr; 
}

Discipline::Discipline(DisciplineNode* temp) {
  this->obj = temp;
  this->pNext = nullptr;
}

Discipline::~Discipline() {
  obj = nullptr;
  
}
Discipline* Discipline::GetNext() {
  return pNext;
}

void Discipline::SetNext(Discipline* temp) {
  this->pNext = temp; 
}