#include "Direction.h"


Direction::Direction() {
  this->str = String();
  this->pNext = nullptr;
}

Direction::Direction(String temp) {
  this->str = temp; 
  this->pNext = nullptr;
}

Direction::Direction(const Direction& other) {
  this->str = other.str;

  if (other.pNext) this->pNext = new Direction(*(other.pNext));
  else this->pNext = nullptr;
}

Direction::~Direction() {
  if (pNext != nullptr) {
    delete pNext;
    pNext = nullptr;
  }
}

void Direction::push_back(String temp) {
  Direction* current = this; 
  while (current->pNext) {
    current = current->pNext;
  }

  current->pNext = new Direction(temp);
}

bool Direction::operator==(const Direction& other) const {
  if (!(this->str == other.str)) return false; // предполагается, что operator== для String реализован
  if (this->pNext == nullptr && other.pNext == nullptr) return true;
  
  if ((this->pNext == nullptr) != (other.pNext == nullptr)) return false;
  
  return (*this->pNext) == (*other.pNext);
}

void Direction::SetNext(Direction* temp) {
  this->pNext = temp; 
}