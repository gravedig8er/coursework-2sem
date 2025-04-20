#include "Person.h"

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