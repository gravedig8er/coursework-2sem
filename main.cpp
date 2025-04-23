#include <iostream> 
#include <fstream>
#include "Database.h"
#include "MyFunctions.h"
#include "Person.h"
#include "FullName.h"


int main() {
  std::fstream students, out, protocol;
  Database base; // хранилище

  students.open("students.txt", std::ios::in);
  if (!students.is_open()) {std::cout << "Check students file"; return 0;}

  int ID; 
  char ch; 
  while (students >> ID) {
    Person temp; 
    char buffer[N + 1];
    int counter = 0;

    temp.SetID(ID); 
    students.get(ch);
  //==================Считывание фамилии==============
    while (ch == ' ' || ch == '\t') students.get(ch);
    FullName name;
    while (ch != '\t') { // пока находимся в фамилии
      buffer[counter++] = ch; 
      if (counter == N) {
        buffer[counter] = '\0';
        //... закидываем в ФИО
        name.push_back(String(buffer));
        reset(buffer, N + 1);
        counter = 0;
      }
      students.get(ch);
    }
    if (counter > 0) { // если последний кусочек не записался
      buffer[counter] = '\0';
      //...
      name.push_back(String(buffer)); 
      reset(buffer, N + 1);
      counter = 0;
    }
    temp.SetFIO(name);
  //===================================================

    int DATE; 
    students >> DATE;
    temp.SetDATE(DATE);

  //==================Считывание направления==============  
    Direction direct; 
    while (ch == ' ' || ch == '\t') students.get(ch); 

    while (ch != '\t') { // пока мы внутри направления
      buffer[counter++] = ch;
      if (counter == N) {
        buffer[counter] = '\0';
        //... закидываем в DIRECT
        direct.push_back(String(buffer));
        reset(buffer, N + 1);
        counter = 0;
      }
      students.get(ch);
    }
    if (counter > 0) {
      buffer[counter] = '\0';
      //...
      direct.push_back(String(buffer));
      reset(buffer, N + 1);
      counter = 0;
    }
    // записать DIRECTION в студента
    temp.SetDIRECT(direct);
  //=====================================================  
  int GROUP; 
  students >> GROUP;
  temp.SetGROUP(GROUP);

  while (students.get(ch) && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')); // очистка конца строки
  
  Group* add = FindGroup(base, GROUP, DATE, &direct); // нашли нужную группу или создали ее и добавили в base
  add->push_back(temp); // добавили туда студента

  }
}
