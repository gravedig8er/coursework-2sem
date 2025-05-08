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
#include "Discipline.h"
#include "DisciplineNode.h"
#include "DisciplineBase.h"

int main() {
  std::fstream students, discipline, output, protocol; 
  output.open("output.txt", std::ios::out);
  if (!output.is_open()) {std::cout  << "Check file1\n"; return 0;}
  Database base; // вся база студентов
  
  students.open("students.txt", std::ios::in);
  if (!students.is_open()) {std::cout << "Check file2\n"; return 0;}

  discipline.open("Discipline.txt", std::ios::in);
  if (!discipline.is_open()) {std::cout << "Check file3\n"; return 0;}


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
      find->SetDirect(dir); 
      base.AddGroup(find); 
      delete find; 
      find = base.FindGroup(group); // ищем группу в базе
    }
    find->AddStudent(temp);  
    delete dir; // удаляем направление
  }

  //================Считывание дисциплин===================
  /*нужно проверять символ на цифру, если она, то запускаемся в цикле. иначе не получается 
  идти по файлу, записывая номер группы*/
  DisciplineBase DB;
  int currentGroup = 0; // Текущая группа (0 = не задана)

  while (discipline.get(ch)) {
    // Если символ — цифра, начинаем читать номер группы
    if (isdigit(ch)) {
      discipline.unget();
      discipline >> currentGroup; // Читаем номер группы

      // Пропускаем все символы до конца строки
      while (discipline.get(ch) && (ch != '\n' && ch != '\r')) {}
    } 
    // Если текущая группа задана и символ не цифра — читаем дисциплину
    else if (currentGroup != 0) {
      DisciplineNode temp;
      char buffer[N+1] = {};
      int counter = 0;

      // Пропускаем пробелы и табы в начале строки
      while (ch == ' ' || ch == '\t') {
        if (!discipline.get(ch)) break;
      }

      // Читаем название дисциплины до конца строки
      while (ch != '\n' && ch != '\r' && !discipline.eof()) {
        buffer[counter++] = ch;
        if (counter == N) {
          buffer[N] = '\0';
          temp.push_back(String(buffer));
          counter = 0;
        }
        if (!discipline.get(ch)) break;
      }

      // Добавляем оставшиеся символы
      if (counter > 0) {
        buffer[counter] = '\0';
        temp.push_back(String(buffer));
      }

      // Добавляем дисциплину, если она не пустая
      if (temp.GetDir() != nullptr) {
        DisciplineNode* add = DB.find(temp);
        if (!add) {
            DB.push_back(temp);
            add = DB.find(temp);
        }
        Group* findGroup = base.FindGroup(currentGroup);
        if (findGroup) {
            findGroup->AddDiscipl(add);
            add->push_back(currentGroup);
        }
      }
    }
  }
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
  output << "\n\n";
  // теперь выводим группы и дисциплины
  DisciplineNode* currentDiscipl = DB.GetHead();
  while (currentDiscipl != nullptr) {
    
    Direction* temp = currentDiscipl->GetDir();
    bool firstWord = true;
    while (temp != nullptr) {
      if (!firstWord)
        output << "->";
      output << temp->GetStr().GetLine();
      firstWord = false;
      temp = temp->GetNext();
    }
    output << ": ";
    
    
    // Вывод номеров групп в одной строке, разделенных запятыми.
    int* groups = currentDiscipl->GetData();
    int count = currentDiscipl->GetSize();
    for (int i = 0; i < count; i++) {
      output << groups[i];
      if (i < count - 1)
        output << ", ";
    }
    output << "\n";
    
    currentDiscipl = currentDiscipl->GetNext();
  }

  //========================================================
  students.close();
  output.close();
  protocol.close();
}