#pragma once
#include "Person.h"
#include "Direction.h"
#include "Discipline.h"

class Group {
private: 
  Person* head; 
  Person* tail;  

  int YEAR; // год поступления
  Direction* DIRECT; // направление
  Discipline* DISCPLINE; // дисциплины
  int GroupNumber;

  Group* pNext; 
public: 
  Group();
  Group(Group& other);
  Person* GetHead(); // получаем начало на список студентов
  void SetYEAR(int year);
  void SetDIRECT(Direction* direct);
  void SetGroupNumber(int number);
  //void SetDISCPLINE();
  void push_back(Person& temp);
  void SetNext(Group* temp);
  Group* GetNext();
  int GetNumber();
};