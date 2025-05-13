#include "Group.h"

Group::Group() {
  this->head = nullptr; 
  this->tail = nullptr; 
  this->number = 0;
  this->year = 0;
  this->count_discip = 0;

  this->pNext = nullptr;
  this->direct = nullptr; 
  this->discip = nullptr; 
}

Group::Group(const Group& other) {
  this->head = nullptr;
  this->tail = nullptr;
  this->number = other.number;
  this->year = other.year;
  this->count_discip = other.count_discip;
  this->pNext = nullptr;
  this->direct = nullptr;
  this->discip = nullptr;

  Person* current = other.head;
  while (current != nullptr) {
    Person* newPerson = new Person(*current);
    if (head == nullptr) {
      head = newPerson;
      tail = newPerson;
    } else {
      tail->SetNext(newPerson);
      tail = newPerson;
    }
    current = current->GetNext();
  }
  if (tail != nullptr) {
    tail->SetNext(nullptr);
  }

  if (other.direct != nullptr) {
    this->direct = new Direction(*(other.direct));
  }

  Discipline* otherDiscip = other.discip;
  Discipline* last = nullptr;
  while (otherDiscip != nullptr) {
    DisciplineNode* node = otherDiscip->GetObj();
    Discipline* newDisc = new Discipline(node);
    if (discip == nullptr) {
      discip = newDisc;
      last = newDisc;
    } else {
      last->SetNext(newDisc);
      last = newDisc;
    }
    otherDiscip = otherDiscip->GetNext();
  }
}

Group::~Group() {
  Person* current = head;
  while (current != nullptr) {
    Person* nextPerson = current->GetNext();  
    delete current;
    current = nextPerson;
  }
  head = nullptr;
  tail = nullptr;
  
  if (direct != nullptr) {
    delete direct;
    direct = nullptr;
  }
  
  Discipline* currentDisc = discip;
  while (currentDisc != nullptr) {
    Discipline* nextDisc = currentDisc->GetNext();
    delete currentDisc;
    currentDisc = nextDisc;
  }
  discip = nullptr;
}
void Group::AddStudent(Person temp) {
  Person* newObj = new Person(temp); //! 
  if (head == nullptr) {
    head = newObj;
    tail = newObj;
  } 
  else {
    tail->SetNext(newObj);
    tail = newObj;
  }
  tail->SetNext(nullptr); 
}

void Group::SetDirect(Direction* dir) {
  if (this->direct != nullptr) delete this->direct;
  this->direct = new Direction(*dir); 
}

void Group::AddDiscipl(DisciplineNode* temp) {
  if (discip == nullptr) {
    discip = new Discipline(temp);  
  } 
  else {
    Discipline* current = discip;
    while (current->GetNext()) {
      current = current->GetNext();
    }
    current->SetNext(new Discipline(temp));  
  }
}
