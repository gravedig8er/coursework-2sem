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
  int group; 

  while (discipline.get(ch)) {
    if (is_digit(ch)) { // находимся внутри дисциплин
      discipline.unget();
      discipline >> group; // считали номер группы 
      discipline.get(ch); 
      while (ch != '\n') discipline.get(ch); // теперь ch хранит \n
      discipline.get(ch); // указываем на символ. считываем его
    }

    DisciplineNode temp; // здесь хранится вся строка-дисциплина
    char buffer[N+1] = {};
    buffer[0] = ch;
    int counter = 1; 

    discipline.get(ch);
    while (ch != '\n' && !discipline.eof()) { // Изменено условие: проверяем \n и конец файла
      buffer[counter++] = ch; 
      if (counter == N) {
        buffer[counter] = '\0';
        temp.push_back(String(buffer));
        reset(buffer, N+1);
        counter = 0;
      }
      discipline.get(ch);
    }

    if (counter > 0) {
      buffer[counter] = '\0';
      temp.push_back(String(buffer));
      reset(buffer, N+1);
      counter = 0;
    }
    
    // !!!Сейчас temp хранит целиком дисциплину как положено в памяти
    /*Здесь нужно пройти по всей базе дисцилпин и понять, есть такая или нет
      потом добавить ее в базу в случае чего и пройти по Group-Discip до конца,
      сделать указатель на эту область из базы.
    
    */
    DisciplineNode* add = DB.find(temp); // ищем дисцплину в базе
    if (!add) { // если ничего не нашли, то создаем
      DB.push_back(temp); // записали в базу дисциплину
      add = DB.find(temp); // нашли только что добавленную дисциплину и взяли ее указатель (здесь происходит глубокое копирование)
    }
    Group* find = base.FindGroup(group); // нашли группу по номеру
    find->AddDiscipl(add); // подвязали к списку дисциплин внутри группы
    // каждая дисциплина знает у каких групп она идет
    add->push_back(group); // заносим в список номер группы 
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
      output << "\"" << temp->GetStr().GetLine() << "\"";
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