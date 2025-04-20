#include "Direction.h"

void Direction::push_back(String temp) {
  Direction* current = this; 
  while (current->pNext) current = current->pNext;

  Direction* newNode = new Direction;
  newNode->str = temp; 

  newNode->pNext = nullptr; 
  current->pNext = newNode;
}