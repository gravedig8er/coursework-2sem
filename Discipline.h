#pragma once 
#include "DisciplineNode.h"

class Discipline {
private: 
  DisciplineNode* obj; 
  Discipline* pNext; 
public: 
  Discipline();
  Discipline(DisciplineNode* temp);
  ~Discipline();
  Discipline* GetNext();
  DisciplineNode* GetObj() const { return obj; }

  void SetNext(Discipline* temp);
  
};