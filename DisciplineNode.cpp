#include "DisciplineNode.h"

DisciplineNode::DisciplineNode() {
  this->string = nullptr;
  this->pNext = nullptr; 
  LGroup = nullptr; 
  size = 0;
}

DisciplineNode::~DisciplineNode() {
  if (string != nullptr) {
    delete string;
    string = nullptr;
  }
  
  if (LGroup != nullptr) {
    delete[] LGroup;
    LGroup = nullptr;
  }
  
}

DisciplineNode::DisciplineNode(DisciplineNode& other) {
  if (other.string != nullptr) {
    string = new Direction(*other.string);
  } else {
    string = nullptr;
  }

  pNext = nullptr; 

  size = other.size;
  if (size > 0) {
    LGroup = new int[size];
    for (int i = 0; i < size; i++) {
      LGroup[i] = other.LGroup[i];
    }
  } else {
    LGroup = nullptr;
  }

  if (other.pNext != nullptr) {
    pNext = new DisciplineNode(*other.pNext);
  } else {
    pNext = nullptr;
  }
}

void DisciplineNode::push_back(String str) {
  Direction* newObj = new Direction(str);
  if (string == nullptr) {string = newObj;}
  else {
    Direction* current = string;
    while (current->GetNext()) {
      current = current->GetNext();
    }
    current->SetNext(newObj);

  }
}

void DisciplineNode::SetNext(DisciplineNode* obj) {
  this->pNext = obj;
}

DisciplineNode* DisciplineNode::GetNext() {
  return pNext;
}

bool DisciplineNode::operator==(const DisciplineNode& other) const {

  if (this->string == nullptr && other.string == nullptr)
      return true;
  if ((this->string == nullptr) != (other.string == nullptr))
      return false;

  const Direction* current1 = this->string;
  const Direction* current2 = other.string;
  while (current1 != nullptr && current2 != nullptr) {
      if (!(*current1 == *current2))
          return false;
      current1 = current1->GetNext();
      current2 = current2->GetNext();
  }
  return current1 == current2;
}

void DisciplineNode::push_back(int group) {
  int* newLGroup = new int[size + 1]; 

  if (LGroup != nullptr) {
    for (int i = 0; i < size; i++) {
        newLGroup[i] = LGroup[i];
    }
  }

  newLGroup[size] = group;

  delete[] LGroup;
  LGroup = newLGroup;
  
  size++;
}
