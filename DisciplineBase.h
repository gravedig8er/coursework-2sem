#pragma once 
#include "DisciplineNode.h"

class DisciplineBase {
private: 
  DisciplineNode* head; 
  DisciplineNode* tail;

public: 
  DisciplineBase();
  ~DisciplineBase();
  DisciplineNode* find(DisciplineNode temp);
  void push_back(DisciplineNode temp);
  DisciplineNode* GetHead() const { return head; }
};