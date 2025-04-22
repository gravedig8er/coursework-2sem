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
  
public: 
  Person* GetHead(); // получаем начало на список студентов
  void push_back(Person& temp);

};