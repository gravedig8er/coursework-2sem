#include "Group.h"

Group::Group() {
    head = nullptr;
    tail = nullptr;
    YEAR = 0;
    DIRECT = nullptr;
    DISCPLINE = nullptr;
    GroupNumber = 0;
    pNext = nullptr;
}

Group::Group(Group& other) {
    this->YEAR = other.YEAR;
    this->GroupNumber = other.GroupNumber;

    if (other.DIRECT) {
        this->DIRECT = new Direction(*other.DIRECT);
    } else {
        this->DIRECT = nullptr;
    }

    // Глубокое копирование Discipline, если оно существует
    if (other.DISCPLINE) {
        this->DISCPLINE = new Discipline(*other.DISCPLINE);
    } else {
        this->DISCPLINE = nullptr;
    }

    this->head = nullptr;
    this->tail = nullptr;
    this->pNext = nullptr;

    // Глубокое копирование студентов
    Person* current = other.head;
    while (current) {
        this->push_back(*current);  // Добавляем копию студента
        current = current->GetNext();
    }
}

Person* Group::GetHead() {
    return head;
}

void Group::SetYEAR(int year) {
    this->YEAR = year;
}

void Group::SetDIRECT(Direction* direct) {
    if (this->DIRECT) {
        delete this->DIRECT;
    }
    this->DIRECT = new Direction(*direct); // Глубокое копирование Direction
}

void Group::SetGroupNumber(int number) {
    this->GroupNumber = number;
}

void Group::push_back(Person& temp) {
    Person* newPerson = new Person(temp);  // Глубокое копирование студента

    if (head == nullptr) {
        head = newPerson;
        tail = head;
    } else {
        tail->SetNext(newPerson);
        tail = newPerson;
    }
}

void Group::SetNext(Group* temp) {
    this->pNext = temp;
}

Group* Group::GetNext() {
    return pNext;
}

int Group::GetNumber() {
    return GroupNumber;
}
