#pragma once 
#include "FullName.h"
#include "Direction.h"

class Person {
private:
  int id;  // личное дело 
  int group_number; // группа
  int year; // год приема 
  // направление подготовки 
  FullName* fio;
  Direction* direct; // направление
  Person* pNext; 
public:
  int*** grades1; //оценки в первом семестре
  int*** grades2; //оценки во втором семестре
  int count_discip;
  int*** retake_grades1; // пересдачи в первом семестре
  int*** retake_grades2; // пересдачи во втором семестре

  int** examMarksCount1; // количество оценок по дисциплине
  int** retakeMarksCount1; // количество оценок по пересдачам

  int** examMarksCount2; // количество оценок по дисциплине
  int** retakeMarksCount2; // количество оценок по пересдачам

public: 
  Person();
  Person(const Person& other);
  ~Person();
  void SetId(int id);
  void SetYear(int year);
  void SetFio(FullName* fio);
  void SetDirect(Direction* direct);
  void SetGroup(int group);
  void SetNext(Person* next) { this->pNext = next; }
  Person* GetNext() const { return pNext; }
  int GetId() const { return id; }
  FullName* GetFio() const { return fio; }
  Direction* GetDirect() const { return direct; }
  int GetGroup() const { return group_number; }
  int GetYear() const { return year; }
  void ReserveDiscip(int count_discip);
  void ReserveMarksSem1(int number, int count);
  void ReserveMarksSem2(int number, int count);
  void AddGradeSem1(int number, char grade, char type);
  void AddGradeSem2(int number, char grade, char type);
  void AddRetakeSem1(int number, char grade, char type);
  void AddRetakeSem2(int number, char grade, char type); 
  int GetCountDiscip() const { return count_discip; } 
  void ClearDisciplines();
};