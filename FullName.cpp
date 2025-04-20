#include "FullName.h"

void FullName::push_back(String temp) {
  FullName* current = this;
  while (current->pNext) {
      current = current->pNext;
  }

  FullName* newNode = new FullName;
  newNode->value = temp;
  newNode->pNext = nullptr;

  current->pNext = newNode;
}