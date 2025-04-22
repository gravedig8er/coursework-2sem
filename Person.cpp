#include "Person.h"

Person::Person() {

}

Person::~Person() {
  if (FIO) delete FIO;
  if (DIRECT) delete DIRECT;
  if (DISCIPLINE) delete DISCIPLINE;
}


Person::Person(const Person& temp) {
  this->ID = temp.ID;
  this->GROUP = temp.GROUP;
  this->DATE = temp.DATE;

  if (temp.FIO) {
    this->FIO = new FullName(*temp.FIO); 
  } 
  else {
    this->FIO = nullptr;
  }

  if (temp.DIRECT) {
    this->DIRECT = new Direction(*temp.DIRECT);  
  } 
  else {
    this->DIRECT = nullptr;
  }

  if (temp.DISCIPLINE) {
    this->DISCIPLINE = new Discipline(*temp.DISCIPLINE);  
  } 
  else {
    this->DISCIPLINE = nullptr;
  }

  this->pNext = nullptr;  
}


void Person::SetID(int ID) {
  this->ID = ID;
}

void Person::SetFIO(const FullName& temp) {
  if (this->FIO) delete this->FIO;
  this->FIO = new FullName(temp); // ← копия
}

void Person::SetDIRECT(const Direction& temp) {
  if (this->DIRECT) delete this->DIRECT;
  this->DIRECT = new Direction(temp); // ← копия
}

void Person::SetDATE(int DATE) {
  this->DATE = DATE;
}


void Person::SetGROUP(int GROUP) {
  this->GROUP = GROUP;
}

Person* Person::GetNext() {
  return pNext;
}

void Person::SetNext(Person* temp) {
  this->pNext = temp;
}