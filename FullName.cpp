#include "FullName.h"

FullName::FullName() {
  this->str = String();
  this->pNext = nullptr;
}

FullName::FullName(String temp) {
  this->str = temp; 
  this->pNext = nullptr;
}

FullName::FullName(const FullName& other) {
  this->str = other.str;

  if (other.pNext) this->pNext = new FullName(*(other.pNext));
  else this->pNext = nullptr;
}

FullName::~FullName() {
  if (pNext != nullptr) {
    delete pNext;
    pNext = nullptr;
  }
}

void FullName::push_back(String temp) {
  FullName* current = this; 
  while (current->pNext) {
    current = current->pNext;
  }

  current->pNext = new FullName(temp);
}

