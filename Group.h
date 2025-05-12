#pragma once
#include "Person.h"
#include "Direction.h"
#include "DisciplineNode.h"
#include "Discipline.h"

class Group {
private:
  Person* head; 
  Person* tail;
  int number; // номер группы
  int year; // год поступления

  // Direction направление
  Direction* direct;
  Discipline* discip;
  int count_discip;


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
  void AddDiscipl(DisciplineNode* temp);
  Person* GetHead() const { return head; }
  int GetCountDiscip() const { return count_discip; }
  Discipline* GetDiscip() const { return discip; }
  void IncCountDiscip() { count_discip++; }
};