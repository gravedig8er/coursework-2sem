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
public: 
  Person* GetHead(); // получаем начало на список студентов
  void SetYEAR();
  void SetDIRECT();
  void SetDISCPLINE();
  void SetGroupNumber();
  void push_back(Person& temp);

};