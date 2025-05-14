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
  setlocale(LC_ALL, "Russian");
  std::fstream students, discipline, output, grades1, grades2, retakes1, retakes2, protocol; 
  output.open("output.txt", std::ios::out);
  if (!output.is_open()) {std::cout  << "Check file1\n"; return 0;}
  Database base; // вся база студентов
  
  students.open("students.txt", std::ios::in);
  if (!students.is_open()) {std::cout << "Check file2\n"; return 0;}

  discipline.open("Discipline.txt", std::ios::in);
  if (!discipline.is_open()) {std::cout << "Check file3\n"; return 0;}

  grades1.open("grades1.txt", std::ios::in);
  if (!grades1.is_open()) {std::cout << "Check file4\n"; return 0;}

  grades2.open("grades2.txt", std::ios::in);
  if (!grades2.is_open()) {std::cout << "Check file5\n"; return 0;}

  retakes1.open("retakes1.txt", std::ios::in);
  if (!retakes1.is_open()) {std::cout << "Check file6\n"; return 0;}

  retakes2.open("retakes2.txt", std::ios::in);
  if (!retakes2.is_open()) {std::cout << "Check file7\n"; return 0;}

  int id = 0; 
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
      find->SetYear(year); // устанавливаем год
    }
    find->AddStudent(temp);  
    delete dir; // удаляем направление
  }

  //================Считывание дисциплин===================
  /*нужно проверять символ на цифру, если она, то запускаемся в цикле. иначе не получается 
  идти по файлу, записывая номер группы*/
  
  DisciplineBase DB;
  int currentGroup = 0; 

  while (discipline.get(ch)) {
    if (is_digit(ch)) {
      discipline.unget();
      discipline >> currentGroup; // Читаем номер группы

      while (discipline.get(ch) && (ch != '\n' && ch != '\r')) {}
    } 
    else if (currentGroup != 0) {
      DisciplineNode temp;
      char buffer[N+1] = {};
      int counter = 0;

      while (ch == ' ' || ch == '\t') {
        if (!discipline.get(ch)) break;
      }

      while (ch != '\n' && ch != '\r' && !discipline.eof()) {
        buffer[counter++] = ch;
        if (counter == N) {
          buffer[N] = '\0';
          temp.push_back(String(buffer));
          counter = 0;
        }
        if (!discipline.get(ch)) break;
      }

      if (counter > 0) {
        buffer[counter] = '\0';
        temp.push_back(String(buffer));
      }

      if (temp.GetDir() != nullptr) {
        DisciplineNode* add = DB.find(temp);
        if (!add) {
          DB.push_back(temp);
          add = DB.find(temp);
        }
        Group* findGroup = base.FindGroup(currentGroup);
        if (findGroup) {
          findGroup->AddDiscipl(add);
          findGroup->IncCountDiscip();
          add->push_back(currentGroup);
        }
      }
    }
  }
  //=======================================================

  //=================Считывание оценок=====================
  // нужно брать количество дисцупилин в группе, по которой смотрим студента. 
  // т.к это один из индексов массива. добавил в группы count_discip
  // Считывание оценок за первый семестр
{
  int id = 0;
  int count_discip = 0;
  int number = -1; // номер дисциплины для текущего студента
  bool done = false; 
  Person* student = nullptr;
  int marks_counter = 0;
  char ch;
  
  while (grades1.get(ch)) {
    while (ch == '\n' || ch == '\r' || ch == ' ') {
      if (!grades1.get(ch)) {
        done = true;
        break;
        }
    }
    if (done) break;
    
    char next;
    if (!grades1.get(next)) { done = true; break; }
    
    if (is_digit(ch) && is_digit(next)) {
      grades1.unget();
      grades1.unget();
      grades1 >> id;  // получили id студента
      //std::cout << "Semester 1: Student id: " << id << "\n";
      count_discip = base.GetCountDiscip(id); // получили количество дисциплин для студента
      //std::cout << "Semester 1: Count disciplines: " << count_discip << "\n";
      student = base.FindStudent(id); // нашли студента в базе
      student->ReserveDiscip(count_discip); 
      if (!grades1.get(ch)) { done = true; break; }
      if (ch == '\n' || ch == '\r') {
        if (!grades1.get(ch)) { done = true; break; }
      }
      number = 0; // сброс номера дисциплины для нового студента
    } 
    else {
      grades1.unget();  
      number++;        
    }
    
    int start = (int)(grades1.tellg()) - 1;
    while (ch != '\t') {
      if (ch != ' ' && ch != '\n')
        marks_counter++; // увеличиваем счетчик оценок для дисциплины
      if (!grades1.get(ch)) { done = true; break; }
      if (grades1.eof()) { done = true; break; }
    }
    if (done) break;
    
    student->ReserveMarksSem1(number, marks_counter);
    
    char type = -1;
    if (!grades1.get(type)) { done = true; break; }
    
    grades1.seekg(start);
    if (!grades1.get(ch)) { done = true; break; }
    
    //std::cout << "Semester 1, Discipline " << number << ": ";
    while (ch != '\t') {
        if (ch != ' ' && ch != '\n' && ch != '\r') {
            //std::cout << ch << " ";
            student->AddGradeSem1(number, ch, type);
        }
        if (!grades1.get(ch)) { done = true; break; }
    }
    //std::cout << "| Type: " << type;
    //std::cout << " | Marks counter: " << marks_counter << "\n";
    marks_counter = 0; // сброс счетчика оценок
    
    if (done) break;
    if (!grades1.get(ch)) { done = true; break; }
    if (!grades1.get(ch)) { done = true; break; }
  }
} // конец блока первого семестра

{
  int id = 0;
  int count_discip = 0;
  int number = -1; // номер дисциплины для текущего студента
  bool done = false; 
  Person* student = nullptr;
  int marks_counter = 0;
  char ch;
  
  while (grades2.get(ch)) {
    while (ch == '\n' || ch == '\r' || ch == ' ') {
      if (!grades2.get(ch)) {
        done = true;
        break;
      }
    }
    if (done) break;
    
    char next;
    if (!grades2.get(next)) { done = true; break; }
    
    if (is_digit(ch) && is_digit(next)) {
      grades2.unget();
      grades2.unget();
      grades2 >> id;  // получили id студента
      //std::cout << "Semester 2: Student id: " << id << "\n";
      count_discip = base.GetCountDiscip(id); // получили количество дисциплин
      //std::cout << "Semester 2: Count disciplines: " << count_discip << "\n";
      student = base.FindStudent(id); // нашли студента в базе
      //student->ClearDisciplines();
      //student->ReserveDiscip(count_discip); 
      if (!grades2.get(ch)) { done = true; break; }
      if (ch == '\n' || ch == '\r') {
        if (!grades2.get(ch)) { done = true; break; }
      }
      number = 0; // сброс номера дисциплины для нового студента
    } 
    else {
      grades2.unget();
      number++;
    }
    
    int start = (int)(grades2.tellg()) - 1;
    while (ch != '\t') {
      if (ch != ' ' && ch != '\n')
        marks_counter++;
      if (!grades2.get(ch)) { done = true; break; }
      if (grades2.eof()) { done = true; break; }
    }
    if (done) break;
    
    student->ReserveMarksSem2(number, marks_counter);
    
    char type = -1;
    if (!grades2.get(type)) { done = true; break; }
    
    grades2.seekg(start);
    if (!grades2.get(ch)) { done = true; break; }
    
    //std::cout << "Semester 2, Discipline " << number << ": ";
    while (ch != '\t') {
      if (ch != ' ' && ch != '\n' && ch != '\r') {
        //std::cout << ch << " ";
          student->AddGradeSem2(number, ch, type);
      }
      if (!grades2.get(ch)) { done = true; break; }
    }
    //std::cout << "| Type: " << type;
    //std::cout << " | Marks counter: " << marks_counter << "\n";
    marks_counter = 0;
    
    if (done) break;
    if (!grades2.get(ch)) { done = true; break; }
    if (!grades2.get(ch)) { done = true; break; }
  }
}

//=====================================================
// Считывание пересдачных оценок за первый семестр (файл retakes1)
//=====================================================
// Считывание пересдачных оценок за первый семестр (файл retakes1)
{
  int id = 0;
  int count_discip = 0;
  int number = -1;   // Индекс дисциплины текущего студента
  Person* student = nullptr;
  char ch;
  
  while (retakes1.get(ch)) {
    while ((ch == '\n' || ch == '\r' || ch == ' ') && retakes1.get(ch)) { }
    if (retakes1.eof())
      break;
    
    char next;
    if (!retakes1.get(next))
      break;
    
    if (is_digit(ch) && is_digit(next)) {
      retakes1.unget();
      retakes1.unget();
      retakes1 >> id; // Чтение ID студента
      student = base.FindStudent(id);
      if (!student)
        continue; // Если студент не найден, переходим к следующему блоку
      count_discip = student->GetCountDiscip();
      number = 0;
      // Вывод отладочной информации о студенте
      //std::cout << "Retakes Semester 1: Student id: " << id << "\n";
      //std::cout << "Retakes Semester 1: Count disciplines: " << count_discip << "\n";
      while (retakes1.get(ch) && (ch == '\n' || ch == '\r' || ch == ' ')) { }
      retakes1.unget();
    }
    else {
      retakes1.unget();
      if (student && number < count_discip) {
        while (ch == ' ' && retakes1.get(ch)) { }

        if (ch == '0') {
          // Если встречаем '0' – по данной дисциплине пересдачи нет
          //std::cout << "Retakes Semester 1, Discipline " << number 
                    //<< ": No retake (0 encountered)\n";
          number++;
          while (retakes1.get(ch) && ch != '\n' && ch != '\r') { }
        }
        else if (is_digit(ch)) {
          char grade = ch;
          while (retakes1.get(ch) && ch != '\t') {
            if (ch == ' ')
              continue;
          }
          char type;
          retakes1.get(type);

          //std::cout << "Retakes Semester 1, Discipline " << number 
                    //<< ": Grade: " << grade << " | Type: " << type << "\n";

          student->AddRetakeSem1(number, grade, type);
          number++;
          while (retakes1.get(ch) && ch != '\n' && ch != '\r') { }
        }
        else {
            
          while (retakes1.get(ch) && ch != '\n' && ch != '\r') { }
          number++;
        }
      }
    }
  }
}


//=====================================================
// Считывание пересдачных оценок за второй семестр (файл retakes2)
{
  int id = 0;
  int count_discip = 0;
  int number = -1;   // Индекс дисциплины текущего студента
  Person* student = nullptr;
  char ch;
  
  while (retakes2.get(ch)) {
    while ((ch == '\n' || ch == '\r' || ch == ' ') && retakes2.get(ch)) { }
    if (retakes2.eof())
      break;

    char next;
    if (!retakes2.get(next))
      break;

    if (is_digit(ch) && is_digit(next)) {
      retakes2.unget();
      retakes2.unget();
      retakes2 >> id; // Считываем ID студента
      student = base.FindStudent(id);
      if (!student)
          continue;
      count_discip = student->GetCountDiscip();
      number = 0;
      // Вывод отладочной информации для нового студента
      //std::cout << "Retakes Semester 2: Student id: " << id << "\n";
      //std::cout << "Retakes Semester 2: Count disciplines: " << count_discip << "\n";
      while (retakes2.get(ch) && (ch == '\n' || ch == '\r' || ch == ' ')) { }
      retakes2.unget();
    }
    else {
      retakes2.unget();
      if (student && number < count_discip) {
        while (ch == ' ' && retakes2.get(ch)) { }

        if (ch == '0') {
          //std::cout << "Retakes Semester 2, Discipline " << number 
                        //<< ": No retake (0 encountered)\n";
          number++;
          while (retakes2.get(ch) && ch != '\n' && ch != '\r') { }
        }
        else if (is_digit(ch)) {
            char grade = ch;
            while (retakes2.get(ch) && ch != '\t') {
              if (ch == ' ')
                continue;
            }
            char type;
            retakes2.get(type);

            //std::cout << "Retakes Semester 2, Discipline " << number 
                      //<< ": Grade: " << grade << " | Type: " << type << "\n";

            student->AddRetakeSem2(number, grade, type);
            number++;
            while (retakes2.get(ch) && ch != '\n' && ch != '\r') { }
        }
        else {
          while (retakes2.get(ch) && ch != '\n' && ch != '\r') { }
          number++;
        }
      }
    }
  }
}

  //=======================================================
    // сверху было произведено считывание, теперь начинается обработка
  std::cout << "Выберите один из трех пунктов:\n";
  std::cout << "1) Студенты, сгруппированные по направлениям и/или годам приема, упорядоченные по ФИО\n";
  std::cout << "2) Результаты конкретной группы за весь цикл подготовки или конкретный семестр\n";
  std::cout << "3) Результаты по конкретной дисциплине в определенном семестре, сгруппированые по упорядоченному списку групп\n"; 
  char menu = 0; 
  std::cin >> menu; 
  switch (menu)
  {
  case '1': {
    char type = 0;
    std::cout << "\n1) Студенты, сгруппированные по направлениям\n";
    std::cout << "2) Студенты, сгруппированные по годам\n";
    std::cout << "3) Студенты, сгруппированные по направлениям и годам\n";
    std::cin >> type; 
    switch (type)
    {
    case '1':
      PrintStudentsGroupedByDirection(output, base);
      break;
    case '2':
      PrintStudentsGroupedByYear(output, base);
      break; 
    case '3':
      PrintStudentsGroupedByDirectionAndYear(output, base);
      break;
    default:
      break;
    }
    break;
  }
  case '2':
    PrintGroup(output, base);
    break;
  case '3':
    PrintDiscipline(output, base);
    break;
  default:
    break;
  }

//   //===========================Вывод=============================
//   // нужно перебрать все группы и каждого студента

//   Group* current = base.GetHead();
//   while (current != nullptr) {
//     Person* currentPerson = current->GetHead(); // получаем голову группы
//     while (currentPerson != nullptr) {
//       output << currentPerson->GetId() << "\t";
//       FullName* fio = currentPerson->GetFio();
//       Direction* dir = currentPerson->GetDirect();

//       while (fio != nullptr) {
//         String str = fio->GetStr();
//         if (str.GetLine()[0] != '\0') { 
//           output << str.GetLine();
//           if (fio->GetNext() != nullptr) output << "->";
//           else output << ' ';
//         }
//         fio = fio->GetNext();
//       }
//       output << "\t";
//       output << currentPerson->GetYear() << "\t";

//       while (dir != nullptr) {
//         String str = dir->GetStr();
//         if (str.GetLine()[0] != '\0') { 
//           output << str.GetLine();
//           if (dir->GetNext() != nullptr) output << "->";
//           else output << ' ';
//         }
//         dir = dir->GetNext();
//       }
//       output << "\t";
//       output << currentPerson->GetGroup() << "\n";

//       currentPerson = currentPerson->GetNext();
//     }
//     current = current->GetNext();
//   }
//   output << "\n\n";
//   // теперь выводим группы и дисциплины
//   DisciplineNode* currentDiscipl = DB.GetHead();
//   while (currentDiscipl != nullptr) {
    
//     Direction* temp = currentDiscipl->GetDir();
//     while (temp != nullptr) {
//         String str = temp->GetStr();
//         if (str.GetLine()[0] != '\0') {
//             output << str.GetLine();
//             if (temp->GetNext() != nullptr)
//                 output << "->";
//             else
//                 output << ' ';
//         }
//         temp = temp->GetNext();
//     }
//     output << ": ";
    
    
//     int* groups = currentDiscipl->GetData();
//     int count = currentDiscipl->GetSize();
//     for (int i = 0; i < count; i++) {
//       output << groups[i];
//       if (i < count - 1)
//         output << ", ";
//     }
//     output << "\n";
    
//     currentDiscipl = currentDiscipl->GetNext();
//   }

  


//   //вывод оценок каждого студента
// {
//   // Перебираем группы
//   Group* currentGroup = base.GetHead();
//   while (currentGroup != nullptr)
//   {
//     Person* currentStudent = currentGroup->GetHead();
//     while (currentStudent != nullptr)
//     {
        

//       output << "------------------------------\n";
//       output << "Student id: " << currentStudent->GetId() << "\n";
      
//       int discCount = currentStudent->GetCountDiscip();
//       Discipline* currentDiscip = currentGroup->GetDiscip();
      
//       for (int i = 0; i < discCount; i++)
//       {
//         output << "Discipline " << (i + 1) << " (";
//         if (currentDiscip != nullptr && currentDiscip->GetObj() != nullptr)
//         {
//           Direction* d = currentDiscip->GetObj()->GetDir();
//           bool first = true;
//           while (d != nullptr)
//           {
//             if (!first)
//               output << "->";
//             output << d->GetStr().GetLine();
//             first = false;
//             d = d->GetNext();
//           }
//         }
//         else
//         {
//           output << "Unknown";
//         }
//         output << "):\n";
        
//         // Первый семестр: обычные оценки (Exam и Credit)
//         output << "\tFirst semester: ";
//         output << "Exam: ";
//         int countExam1 = currentStudent->examMarksCount1[i][0];
//         for (int j = 0; j < countExam1; j++)
//         {
//           output << currentStudent->grades1[i][0][j] << " ";
//         }
//         output << "| Credit: ";
//         int countCredit1 = currentStudent->examMarksCount1[i][1];
//         for (int j = 0; j < countCredit1; j++)
//         {
//           output << currentStudent->grades1[i][1][j] << " ";
//         }
//         output << "\n";
        
//         // Первый семестр: пересдачи
//         output << "\tFirst semester retakes: ";
//         output << "Exam: ";
//         int countRetakeExam1 = currentStudent->retakeMarksCount1[i][0];
//         for (int j = 0; j < countRetakeExam1; j++)
//         {
//           output << currentStudent->retake_grades1[i][0][j] << " ";
//         }
//         output << "| Credit: ";
//         int countRetakeCredit1 = currentStudent->retakeMarksCount1[i][1];
//         for (int j = 0; j < countRetakeCredit1; j++)
//         {
//           output << currentStudent->retake_grades1[i][1][j] << " ";
//         }
//         output << "\n";
        
//         // Второй семестр: обычные оценки
//         output << "\tSecond semester: ";
//         output << "Exam: ";
//         int countExam2 = currentStudent->examMarksCount2[i][0];
//         for (int j = 0; j < countExam2; j++)
//         {
//           output << currentStudent->grades2[i][0][j] << " ";
//         }
//         output << "| Credit: ";
//         int countCredit2 = currentStudent->examMarksCount2[i][1];
//         for (int j = 0; j < countCredit2; j++)
//         {
//           output << currentStudent->grades2[i][1][j] << " ";
//         }
//         output << "\n";
        
//         // Второй семестр: пересдачи
//         output << "\tSecond semester retakes: ";
//         output << "Exam: ";
//         int countRetakeExam2 = currentStudent->retakeMarksCount2[i][0];
//         for (int j = 0; j < countRetakeExam2; j++)
//         {
//           output << currentStudent->retake_grades2[i][0][j] << " ";
//         }
//         output << "| Credit: ";
//         int countRetakeCredit2 = currentStudent->retakeMarksCount2[i][1];
//         for (int j = 0; j < countRetakeCredit2; j++)
//         {
//           output << currentStudent->retake_grades2[i][1][j] << " ";
//         }
//         output << "\n\n";
        
//         if (currentDiscip != nullptr)
//           currentDiscip = currentDiscip->GetNext();
//       }
//       output << "====================================\n\n";
      
//       currentStudent = currentStudent->GetNext();
//     }
//     currentGroup = currentGroup->GetNext();
//   }
// }


  //========================================================
  students.close();
  output.close();
  grades1.close();
  grades2.close();
  retakes1.close();
  retakes2.close();
  discipline.close();
  protocol.close();
}