#pragma once
#include "Person.h"
#include "Direction.h"

class Group {
private:
  Person* head; 
  Person* tail;
  int number; // номер группы
  int year; // год поступления

  // Direction направление
  Direction* direct;


  Group* pNext; 
public: 
  Group();
  Group(const Group& other);
  ~Group();
  Group* GetNext() const { return pNext; }
  void SetNext(Group* next) { this->pNext = next; }
  int GetNumber() const { return number; }
  void SetGroup(int number) { this->number = number; }
  void AddStudent(Person temp);
  void SetDirect(Direction* dir);
  Person* GetHead() const { return head; }
};