#pragma once 
#include "DisciplineNode.h"
#include "Semestr.h"

class DisciplineForm {
private: 
  DisciplineNode* head; 
  DisciplineNode* tail;

  Semestr* FirstSem; 
  Semestr* SecondSem; 

  DisciplineForm* pNext; 
};