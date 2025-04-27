#include <iostream> 
#include <fstream> 
#include "Database.h"
#include "Person.h"
#include "config.h"
#include "FullName.h"
#include "String.h"
#include "MyFunctions.h"
#include "Direction.h"
#include "Group.h"

int main() {
  std::fstream students, discipline, output, protocol; 
  output.open("output.txt", std::ios::out);
  if (!output.is_open()) {std::cout  << "Check file\n"; return 0;}
  Database base; // вся база студентов
  
  students.open("students.txt", std::ios::in);
  if (!students.is_open()) {std::cout << "Check file\n"; return 0;}

  discipline.open("Discipline.txt", std::ios::in);
  if (!discipline.is_open()) {std::cout << "Check file"; return 0;}


  int id; 
  char ch; 

  // заполнение
  while (students >> id) {
    Person temp; 
    char buffer[N+1];
    int counter = 0; // количество в блоке 

    temp.SetId(id); // установили номер личного дела
    students.get(ch);

    //===========Считываем фамилию=================
    while (ch == ' ' || ch == '\t') students.get(ch); // пропускаем все пробельные
    FullName* name = new FullName; // здесь будет храниться фио 

    while (ch != '\t') { // пока в фамилии 
      buffer[counter++] = ch; 
      if (counter == N) {
        buffer[counter] = '\0';
        name->push_back(String(buffer)); // закинули блок в фамилию
        reset(buffer, N+1); // сбросили строку 
        counter = 0; // счетчик равен нулю
      }
      students.get(ch);
    }
    if (counter > 0) {
      buffer[counter] = '\0';
      name->push_back(String(buffer));
      reset(buffer, N+1);
      counter = 0;
    }
    temp.SetFio(name);
    delete name; 
    //=============================================

    int year; 
    students >> year; 
    temp.SetYear(year);

    //==========Считывание направления=============
    //students.get(ch); // пропускаем \t
    while (ch == ' ' || ch == '\t') students.get(ch); // пропускаем пробелы после года

    Direction* dir = new Direction;

    while (ch != '\t') { // пока в фамилии 
      buffer[counter++] = ch; 
      if (counter == N) {
        buffer[counter] = '\0';
        dir->push_back(String(buffer)); // закинули блок в фамилию
        reset(buffer, N+1); // сбросили строку 
        counter = 0; // счетчик равен нулю
      }
      students.get(ch);
    }
    if (counter > 0) {
      buffer[counter] = '\0';
      dir->push_back(String(buffer));
      reset(buffer, N+1);
      counter = 0;
    }
    temp.SetDirect(dir);
    // delete dir;
    //===========================================

    int group;
    students >> group;
    temp.SetGroup(group);

    // считали студента и теперь его нужно определить в группу
    Group* find = base.FindGroup(group);
    if (find == nullptr) {
      find = new Group;
      find->SetGroup(group);
      find->SetDirect(dir); // устанавливаем направление
      base.AddGroup(find); // добавляем группу в базу ! 
      delete find; 
      find = base.FindGroup(group); // ищем группу в базе
    }
    find->AddStudent(temp); // добавляем студента в группу! 
    delete dir; // удаляем направление
  }

  //================Считывание дисциплин===================
  
  //=======================================================

  //===========================Вывод=============================
  // нужно перебрать все группы и каждого студента
  Group* current = base.GetHead();
  while (current != nullptr) {
    Person* currentPerson = current->GetHead(); // получаем голову группы
    while (currentPerson != nullptr) {
      output << currentPerson->GetId() << " ";
      FullName* fio = currentPerson->GetFio();
      Direction* dir = currentPerson->GetDirect();

      while (fio != nullptr) {
        String str = fio->GetStr();
        if (str.GetLine()[0] != '\0') { 
          output << str.GetLine();
          if (fio->GetNext() != nullptr) output << "->";
          else output << ' ';
        }
        fio = fio->GetNext();
      }

      output << currentPerson->GetYear() << " ";

      while (dir != nullptr) {
        String str = dir->GetStr();
        if (str.GetLine()[0] != '\0') { 
          output << str.GetLine();
          if (dir->GetNext() != nullptr) output << "->";
          else output << ' ';
        }
        dir = dir->GetNext();
      }
      output << currentPerson->GetGroup() << "\n";

      currentPerson = currentPerson->GetNext();
    }
    current = current->GetNext();
  }
  //========================================================
  students.close();
}