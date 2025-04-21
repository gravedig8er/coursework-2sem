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

  Person* temp = base.GetHead();
  while (!students.eof()) {
// =========================================УСТАНОВКА АЙДИШНИКА=========================
    int ID;
    students >> ID; 
    temp->SetID(ID); // личное дело

    char ch; 
    students.get(ch);
    while (ch == '\t' || ch == ' ') students.get(ch); // пропускаем пробелы между айди и фамилией

    char buffer[N+1] = {};
    int counter = 0; // количество считанных символов 
    FullName* tempFIO = new FullName; 

// =========================================УСТАНОВКА ФИО=========================
    while (ch != '\t') { // пока мы в фамилии 
      buffer[counter++] = ch; 
      if (counter == N) { 
        buffer[N] = '\0';
        tempFIO->push_back(String(buffer));
        reset(buffer, N + 1);
        counter = 0;
      }
      students.get(ch);
    }
    if (counter > 0) {
      buffer[counter] = '\0';
      tempFIO->push_back(String(buffer));
      reset(buffer, N + 1);
      counter = 0;
    }
    temp->SetFIO(tempFIO);
// =========================================УСТАНОВКА ДАТЫ ПОСТУПЛЕНИЯ=========================
    int DATE;
    students >> DATE;
    temp->SetDATE(DATE); // дата поступления 
// =========================================УСТАНОВКА НАПРАВЛЕНИЯ=========================
    students.get(ch);
    while (ch == '\t' || ch == ' ') students.get(ch); // пропускаем пробелы
    Direction* tempDIRECT = new Direction;

    while (ch != '\t') { // пока мы внутри направления
      buffer[counter++] = ch;
      if (counter == N) {
        buffer[N] = '\0';
        tempDIRECT->push_back(String(buffer));
        reset(buffer, N + 1);
        counter = 0;
      }
      students.get(ch);
    }
    if (counter > 0) {
      buffer[counter] = '\0';
      tempDIRECT->push_back(String(buffer));
      reset(buffer, N + 1);
      counter = 0;
    }
    temp->SetDIRECT(tempDIRECT);

// =========================================УСТАНОВКА ГРУППЫ=========================
    int GROUP; 
    students >> GROUP; 
    temp->SetGROUP(GROUP); // группа обучающегося

   
    while (students.get(ch) && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')); // очистка конца строки

    base.push_back(*temp);
    temp = temp->GetNext();
  }
}
