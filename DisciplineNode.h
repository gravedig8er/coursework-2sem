#pragma once 
#include "Direction.h"
#include "String.h"

class DisciplineNode {
private: 
  Direction* string;
  
  DisciplineNode* pNext;
  int* LGroup;
  int size; 
public: 
  DisciplineNode();
  DisciplineNode(DisciplineNode& other);
  ~DisciplineNode();
  void push_back(String);
  void SetNext(DisciplineNode* obj);
  DisciplineNode* GetNext();
  void push_back(int group);
  int* GetData() {return LGroup;}
  int GetSize() {return size;}
  Direction* GetDir() {return string;}
  bool operator==(const DisciplineNode& other) const;
};