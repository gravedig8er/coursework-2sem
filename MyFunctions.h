#pragma once 
#include "Database.h"
#include "Person.h"
#include "Group.h"
#include "DisciplineBase.h"
#include <fstream> 

void reset(char* str, int size);
bool is_digit(char ch);
void PrintStudentsGroupedByDirection(std::fstream& output, const Database& base);
void PrintStudentsGroupedByYear(std::fstream& output, const Database& base);
void PrintStudentsGroupedByDirectionAndYear(std::fstream& output, const Database &base);
void PrintGroup(std::fstream& output, const Database &base);
void PrintDiscipline(std::fstream &output, const Database &base);