#pragma once 
#include "FullName.h"
#include "Direction.h"

class Person {
private:
  int id;  // личное дело 
  int group_number; // группа
  int year; // год приема 
  // направление подготовки 
  FullName* fio;
  Direction* direct; // направление

  Person* pNext; 
public: 
  Person();
  Person(const Person& other);
  ~Person();
  void SetId(int id);
  void SetYear(int year);
  void SetFio(FullName* fio);
  void SetDirect(Direction* direct);
  void SetGroup(int group);
  void SetNext(Person* next) { this->pNext = next; }
  Person* GetNext() const { return pNext; }
  int GetId() const { return id; }
  FullName* GetFio() const { return fio; }
  Direction* GetDirect() const { return direct; }
  int GetGroup() const { return group_number; }
  int GetYear() const { return year; }
};