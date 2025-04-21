#include "FullName.h"

FullName::FullName() {

}

FullName::FullName(const FullName& other) {
  this->str = other.str;
  this->pNext = nullptr;

  FullName* currentOther = other.pNext;
  FullName* currentThis = this;

  while (currentOther != nullptr) {
    currentThis->pNext = new FullName();             
    currentThis = currentThis->pNext;                
    currentThis->str = currentOther->str;            
    currentThis->pNext = nullptr;                    
    currentOther = currentOther->pNext;              
  }
}


FullName::~FullName() {

}

void FullName::push_back(String temp) {
  FullName* current = this;
  while (current->pNext) {
      current = current->pNext;
  }

  FullName* newNode = new FullName;
  newNode->str = temp;
  newNode->pNext = nullptr;

  current->pNext = newNode;
}

