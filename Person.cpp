#include "Person.h"

Person::Person() {

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

void Person::SetFIO(FullName* temp) {
  this->FIO = temp;
}

void Person::SetDATE(int DATE) {
  this->DATE = DATE;
}

void Person::SetDIRECT(Direction* temp) {
  this->DIRECT = temp;
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