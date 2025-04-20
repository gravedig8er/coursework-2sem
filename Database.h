#pragma once 
#include "Person.h"

class Database {
private: 
  Person* head; 
  Person* tail;

public: 
  Person* GetHead();
  void push_back(Person*);
};