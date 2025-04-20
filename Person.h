#pragma once 
#include "FullName.h"
#include "Direction.h"
#include "Discipline.h"

class Person {
private: 
  int ID; // личное дело 
  int GROUP; // группа 
  int DATE; // дата зачисления

  FullName* FIO; // ФИО
  Direction* DIRECT; // направление обучения 
  Discipline* DISCIPLINE; // дисциплины 

  Person* pNext; // указатель на следующего человека 
};