#include "Person.h"

Person::Person() {
  this->id = 0;
  this->group_number = 0;
  this->year = 0;

  this->fio = nullptr;
  this->direct = nullptr;

  
  this->pNext = nullptr;
}

Person::Person(const Person& other) {
  this->id = other.id;
  this->group_number = other.group_number;
  this->year = other.year;

  if (other.fio != nullptr) {
    this->fio = new FullName(*(other.fio));
  } else {
    this->fio = nullptr;
  }

  if (other.direct != nullptr) {
    this->direct = new Direction(*(other.direct));
  } else {
    this->direct = nullptr;
  }

  this->pNext = nullptr;
}

Person::~Person() {
  if (fio != nullptr) {
    delete fio;
    fio = nullptr;
  }
  if (direct != nullptr) {
    delete direct;
    direct = nullptr;
  }
}

void Person::SetId(int id) {
  this->id = id;
}

void Person::SetYear(int year) {
  this->year = year;
}

void Person::SetFio(FullName* fio) {
  if (this->fio != nullptr) delete this->fio;
  this->fio = new FullName(*fio); 
}

void Person::SetDirect(Direction* dir) {
  if (this->direct != nullptr) delete this->direct;
  this->direct = new Direction(*dir); 
}

void Person::SetGroup(int group) {
  this->group_number = group;
}