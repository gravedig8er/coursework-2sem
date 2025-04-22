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
  //==========Оценки=========
  int** FirstSem;
  int** SecondSem; 
  
  int** ExamsRetakeF; 
  int** TestsRetakeF;
  int** ExamsRetakeS; 
  int** TestsRetakeS; 
  
public: 
  Person();
  Person(const Person& temp);
  ~Person();
  void SetID(int ID);
  void SetFIO(FullName* temp);
  void SetDATE(int DATE);
  void SetDIRECT(Direction* temp);
  void SetGROUP(int GROUP);
  void SetNext(Person*);
  Person* GetNext();
};