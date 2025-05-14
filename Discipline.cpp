#include "Discipline.h"

Discipline::Discipline() {
  this->obj = nullptr; 
  this->pNext = nullptr; 
}

Discipline::Discipline(DisciplineNode* temp) {
  this->obj = temp;
  this->pNext = nullptr;
}

Discipline::~Discipline() {
  obj = nullptr;
  
}
Discipline* Discipline::GetNext() {
  return pNext;
}

void Discipline::SetNext(Discipline* temp) {
  this->pNext = temp; 
}
bool Discipline::operator==(const Discipline &other) const {
    // Если хотя бы один из объектов не имеет внутренней цепочки, то считаем
    // их равными только в случае, если оба поля равны nullptr.
    if (this->obj == nullptr || other.obj == nullptr)
        return this->obj == other.obj;
        
    // Иначе сравниваем внутренние цепочки через перегруженный оператор== для DisciplineNode.
    return *(this->obj) == *(other.obj);
}

Discipline& Discipline::operator=(const Discipline &other) {
    if (this != &other) {
        // Освобождаем уже существующий объект, если он есть
        if (obj != nullptr) {
            delete obj;
            obj = nullptr;
        }
        
        // Глубокое копирование внутреннего объекта
        if (other.obj != nullptr) {
            obj = new DisciplineNode(*other.obj); // Используем конструктор копирования DisciplineNode
        } else {
            obj = nullptr;
        }

        // Если требуется копировать и следующего элемента (для полного копирования цепочки Discipline)
        // здесь нужно быть осторожным – возможны проблемы с двойным освобождением памяти,
        // особенно если классы списков управляются внешне.
        // Можно сделать глубокое копирование следующего элемента:
        if (other.pNext != nullptr) {
            pNext = new Discipline(*other.pNext);
        } else {
            pNext = nullptr;
        }
    }
    return *this;
}