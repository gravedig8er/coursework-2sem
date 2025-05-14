#include "Person.h"

Person::Person() {
  this->id = 0;
  this->group_number = 0;
  this->year = 0;

  this->fio = nullptr;
  this->direct = nullptr;

  this->grades1 = nullptr;
  this->retake_grades1 = nullptr;
  this->examMarksCount1 = nullptr;
  this->retakeMarksCount1 = nullptr;

  this->grades2 = nullptr;
  this->retake_grades2 = nullptr;
  this->examMarksCount2 = nullptr;
  this->retakeMarksCount2 = nullptr;

  this->count_discip = 0;
  this->pNext = nullptr;
}

Person::Person(const Person &other)
    : id(other.id),
      group_number(other.group_number),
      year(other.year),
      count_discip(other.count_discip),
      pNext(nullptr)
{
    if (other.fio != nullptr)
        this->fio = new FullName(*other.fio);
    else
        this->fio = nullptr;
        
    if (other.direct != nullptr)
        this->direct = new Direction(*other.direct);
    else
        this->direct = nullptr;
        
    if (other.grades1 != nullptr && other.count_discip > 0) {
        grades1 = new int**[other.count_discip];
        examMarksCount1 = new int*[other.count_discip];
        for (int i = 0; i < other.count_discip; ++i) {
            grades1[i] = new int*[2];
            examMarksCount1[i] = new int[2];
            for (int j = 0; j < 2; ++j) {
                examMarksCount1[i][j] = other.examMarksCount1[i][j];
                if (other.grades1[i][j] != nullptr && examMarksCount1[i][j] > 0) {
                    int count = examMarksCount1[i][j];
                    grades1[i][j] = new int[count];
                    for (int k = 0; k < count; ++k) {
                        grades1[i][j][k] = other.grades1[i][j][k];
                    }
                } else {
                    grades1[i][j] = nullptr;
                }
            }
        }
    } else {
        grades1 = nullptr;
        examMarksCount1 = nullptr;
    }
    
    if (other.retake_grades1 != nullptr && other.count_discip > 0) {
        retake_grades1 = new int**[other.count_discip];
        retakeMarksCount1 = new int*[other.count_discip];
        for (int i = 0; i < other.count_discip; ++i) {
            retake_grades1[i] = new int*[2];
            retakeMarksCount1[i] = new int[2];
            for (int j = 0; j < 2; ++j) {
                retakeMarksCount1[i][j] = other.retakeMarksCount1[i][j];
                if (other.retake_grades1[i][j] != nullptr && retakeMarksCount1[i][j] > 0) {
                    int count = retakeMarksCount1[i][j];
                    retake_grades1[i][j] = new int[count];
                    for (int k = 0; k < count; ++k) {
                        retake_grades1[i][j][k] = other.retake_grades1[i][j][k];
                    }
                } else {
                    retake_grades1[i][j] = nullptr;
                }
            }
        }
    } else {
        retake_grades1 = nullptr;
        retakeMarksCount1 = nullptr;
    }
    
    if (other.grades2 != nullptr && other.count_discip > 0) {
        grades2 = new int**[other.count_discip];
        examMarksCount2 = new int*[other.count_discip];
        for (int i = 0; i < other.count_discip; ++i) {
            grades2[i] = new int*[2];
            examMarksCount2[i] = new int[2];
            for (int j = 0; j < 2; ++j) {
                examMarksCount2[i][j] = other.examMarksCount2[i][j];
                if (other.grades2[i][j] != nullptr && examMarksCount2[i][j] > 0) {
                    int count = examMarksCount2[i][j];
                    grades2[i][j] = new int[count];
                    for (int k = 0; k < count; ++k) {
                        grades2[i][j][k] = other.grades2[i][j][k];
                    }
                } else {
                    grades2[i][j] = nullptr;
                }
            }
        }
    } else {
        grades2 = nullptr;
        examMarksCount2 = nullptr;
    }
    
    if (other.retake_grades2 != nullptr && other.count_discip > 0) {
        retake_grades2 = new int**[other.count_discip];
        retakeMarksCount2 = new int*[other.count_discip];
        for (int i = 0; i < other.count_discip; ++i) {
            retake_grades2[i] = new int*[2];
            retakeMarksCount2[i] = new int[2];
            for (int j = 0; j < 2; ++j) {
                retakeMarksCount2[i][j] = other.retakeMarksCount2[i][j];
                if (other.retake_grades2[i][j] != nullptr && retakeMarksCount2[i][j] > 0) {
                    int count = retakeMarksCount2[i][j];
                    retake_grades2[i][j] = new int[count];
                    for (int k = 0; k < count; ++k) {
                        retake_grades2[i][j][k] = other.retake_grades2[i][j][k];
                    }
                } else {
                    retake_grades2[i][j] = nullptr;
                }
            }
        }
    } else {
        retake_grades2 = nullptr;
        retakeMarksCount2 = nullptr;
    }
}

Person::~Person() {
    if (fio != nullptr) {
        delete fio;
        fio = nullptr;
    }
    if (direct != nullptr) {
        delete direct;
        direct = nullptr;
    }
    
    if (grades1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (grades1[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (grades1[i][j] != nullptr) {
                        delete [] grades1[i][j];
                        grades1[i][j] = nullptr;
                    }
                }
                delete [] grades1[i];
                grades1[i] = nullptr;
            }
        }
        delete [] grades1;
        grades1 = nullptr;
    }
    if (examMarksCount1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] examMarksCount1[i];
        }
        delete [] examMarksCount1;
        examMarksCount1 = nullptr;
    }
    if (retake_grades1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (retake_grades1[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (retake_grades1[i][j] != nullptr) {
                        delete [] retake_grades1[i][j];
                        retake_grades1[i][j] = nullptr;
                    }
                }
                delete [] retake_grades1[i];
                retake_grades1[i] = nullptr;
            }
        }
        delete [] retake_grades1;
        retake_grades1 = nullptr;
    }
    if (retakeMarksCount1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] retakeMarksCount1[i];
        }
        delete [] retakeMarksCount1;
        retakeMarksCount1 = nullptr;
    }

    // чистим память
    if (grades2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (grades2[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (grades2[i][j] != nullptr) {
                        delete [] grades2[i][j];
                        grades2[i][j] = nullptr;
                    }
                }
                delete [] grades2[i];
                grades2[i] = nullptr;
            }
        }
        delete [] grades2;
        grades2 = nullptr;
    }
    if (examMarksCount2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] examMarksCount2[i];
        }
        delete [] examMarksCount2;
        examMarksCount2 = nullptr;
    }
    if (retake_grades2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (retake_grades2[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (retake_grades2[i][j] != nullptr) {
                        delete [] retake_grades2[i][j];
                        retake_grades2[i][j] = nullptr;
                    }
                }
                delete [] retake_grades2[i];
                retake_grades2[i] = nullptr;
            }
        }
        delete [] retake_grades2;
        retake_grades2 = nullptr;
    }
    if (retakeMarksCount2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] retakeMarksCount2[i];
        }
        delete [] retakeMarksCount2;
        retakeMarksCount2 = nullptr;
    }
    
}



void Person::SetId(int id) {
  this->id = id;
}

void Person::SetYear(int year) {
  this->year = year;
}

void Person::SetFio(FullName* fio) {
  if (this->fio != nullptr) delete this->fio;
  this->fio = new FullName(*fio); 
}

void Person::SetDirect(Direction* dir) {
  if (this->direct != nullptr) delete this->direct;
  this->direct = new Direction(*dir); 
}

void Person::SetGroup(int group) {
  this->group_number = group;
}

void Person::ReserveDiscip(int count_discip) {
  this->count_discip = count_discip;
  
  // Для первого семестра:
  grades1 = new int**[count_discip];
  examMarksCount1 = new int*[count_discip];
  for (int i = 0; i < count_discip; ++i) {
    grades1[i] = new int*[2]; // 0 - экзамен, 1 - зачет
    grades1[i][0] = nullptr;
    grades1[i][1] = nullptr;
    
    examMarksCount1[i] = new int[2];
    examMarksCount1[i][0] = 0;
    examMarksCount1[i][1] = 0;
  }
  
  retake_grades1 = new int**[count_discip];
  retakeMarksCount1 = new int*[count_discip];
  for (int i = 0; i < count_discip; ++i) {
    retake_grades1[i] = new int*[2]; // 0 - пересдача экзамена, 1 - пересдача зачета
    retake_grades1[i][0] = nullptr;
    retake_grades1[i][1] = nullptr;
    
    retakeMarksCount1[i] = new int[2];
    retakeMarksCount1[i][0] = 0;
    retakeMarksCount1[i][1] = 0;
  }
  
  // Для второго семестра:
  grades2 = new int**[count_discip];
  examMarksCount2 = new int*[count_discip];
  for (int i = 0; i < count_discip; ++i) {
    grades2[i] = new int*[2];
    grades2[i][0] = nullptr;
    grades2[i][1] = nullptr;
    
    examMarksCount2[i] = new int[2];
    examMarksCount2[i][0] = 0;
    examMarksCount2[i][1] = 0;
  }
  
  retake_grades2 = new int**[count_discip];
  retakeMarksCount2 = new int*[count_discip];
  for (int i = 0; i < count_discip; ++i) {
    retake_grades2[i] = new int*[2];
    retake_grades2[i][0] = nullptr;
    retake_grades2[i][1] = nullptr;
    
    retakeMarksCount2[i] = new int[2];
    retakeMarksCount2[i][0] = 0;
    retakeMarksCount2[i][1] = 0;
  }
}

void Person::ReserveMarksSem1(int number, int count) {
  if (count <= 0) return;
  
  // Выделение памяти для оценок (семестр 1)
  grades1[number][0] = new int[count]; // экзамен
  grades1[number][1] = new int[count]; // зачет
  retake_grades1[number][0] = new int[count]; // пересдачи экзамена
  retake_grades1[number][1] = new int[count]; // пересдачи зачёта

  // Инициализация значениями 0:
  for (int i = 0; i < count; i++) {
    grades1[number][0][i] = 0;
    grades1[number][1][i] = 0;
    retake_grades1[number][0][i] = 0;
    retake_grades1[number][1][i] = 0;
  }
  
  // Сохраняем размеры массивов:
  examMarksCount1[number][0] = count;
  examMarksCount1[number][1] = count;
  retakeMarksCount1[number][0] = count;
  retakeMarksCount1[number][1] = count;
}

void Person::ReserveMarksSem2(int number, int count) {
  if (count <= 0) return;
  
  grades2[number][0] = new int[count];
  grades2[number][1] = new int[count];
  retake_grades2[number][0] = new int[count];
  retake_grades2[number][1] = new int[count];

  for (int i = 0; i < count; i++) {
    grades2[number][0][i] = 0;
    grades2[number][1][i] = 0;
    retake_grades2[number][0][i] = 0;
    retake_grades2[number][1][i] = 0;
  }
  
  examMarksCount2[number][0] = count;
  examMarksCount2[number][1] = count;
  retakeMarksCount2[number][0] = count;
  retakeMarksCount2[number][1] = count;
}

void Person::AddGradeSem1(int number, char grade, char type) {
  int mark = grade - '0';
  if (type == '1') { 
    // Для экзамена (тип 1)
    for (int i = 0; i < examMarksCount1[number][0]; i++) {
      if (grades1[number][0][i] == 0) {
        grades1[number][0][i] = mark;
        break;
      }
    }
  }
  if (type == '2') { 
    // Для зачёта (тип 2)
    for (int i = 0; i < examMarksCount1[number][1]; i++) {
      if (grades1[number][1][i] == 0) {
        grades1[number][1][i] = mark;
        break;
      }
    }
  }
}

void Person::AddGradeSem2(int number, char grade, char type) {
  int mark = grade - '0';
  if (type == '1') { 
    for (int i = 0; i < examMarksCount2[number][0]; i++) {
      if (grades2[number][0][i] == 0) {
        grades2[number][0][i] = mark;
        break;
      }
    }
  }
  if (type == '2') { 
    for (int i = 0; i < examMarksCount2[number][1]; i++) {
      if (grades2[number][1][i] == 0) {
        grades2[number][1][i] = mark;
        break;
      }
    }
  }
}

void Person::ClearDisciplines() {
    // Освобождаем память для первого семестра
    if (grades1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (grades1[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (grades1[i][j] != nullptr) {
                        delete [] grades1[i][j];
                        grades1[i][j] = nullptr;
                    }
                }
                delete [] grades1[i];
                grades1[i] = nullptr;
            }
        }
        delete [] grades1;
        grades1 = nullptr;
    }
    if (examMarksCount1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] examMarksCount1[i];
        }
        delete [] examMarksCount1;
        examMarksCount1 = nullptr;
    }
    if (retake_grades1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (retake_grades1[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (retake_grades1[i][j] != nullptr) {
                        delete [] retake_grades1[i][j];
                        retake_grades1[i][j] = nullptr;
                    }
                }
                delete [] retake_grades1[i];
                retake_grades1[i] = nullptr;
            }
        }
        delete [] retake_grades1;
        retake_grades1 = nullptr;
    }
    if (retakeMarksCount1 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] retakeMarksCount1[i];
        }
        delete [] retakeMarksCount1;
        retakeMarksCount1 = nullptr;
    }

    // Освобождаем память для второго семестра
    if (grades2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (grades2[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (grades2[i][j] != nullptr) {
                        delete [] grades2[i][j];
                        grades2[i][j] = nullptr;
                    }
                }
                delete [] grades2[i];
                grades2[i] = nullptr;
            }
        }
        delete [] grades2;
        grades2 = nullptr;
    }
    if (examMarksCount2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] examMarksCount2[i];
        }
        delete [] examMarksCount2;
        examMarksCount2 = nullptr;
    }
    if (retake_grades2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            if (retake_grades2[i] != nullptr) {
                for (int j = 0; j < 2; ++j) {
                    if (retake_grades2[i][j] != nullptr) {
                        delete [] retake_grades2[i][j];
                        retake_grades2[i][j] = nullptr;
                    }
                }
                delete [] retake_grades2[i];
                retake_grades2[i] = nullptr;
            }
        }
        delete [] retake_grades2;
        retake_grades2 = nullptr;
    }
    if (retakeMarksCount2 != nullptr) {
        for (int i = 0; i < count_discip; ++i) {
            delete [] retakeMarksCount2[i];
        }
        delete [] retakeMarksCount2;
        retakeMarksCount2 = nullptr;
    }
}

void Person::AddRetakeSem1(int number, char grade, char type) {
    int mark = grade - '0';
    if (type == '1') { // тип '1' означает пересдачу экзамена
        for (int i = 0; i < retakeMarksCount1[number][0]; i++) {
            if (retake_grades1[number][0][i] == 0) { // ищем первую свободную ячейку
                retake_grades1[number][0][i] = mark;
                break;
            }
        }
    }
    else if (type == '2') { // тип '2' означает пересдачу зачёта
        for (int i = 0; i < retakeMarksCount1[number][1]; i++) {
            if (retake_grades1[number][1][i] == 0) {
                retake_grades1[number][1][i] = mark;
                break;
            }
        }
    }
}

void Person::AddRetakeSem2(int number, char grade, char type) {
    int mark = grade - '0';
    if (type == '1') {
        for (int i = 0; i < retakeMarksCount2[number][0]; i++) {
            if (retake_grades2[number][0][i] == 0) {
                retake_grades2[number][0][i] = mark;
                break;
            }
        }
    }
    else if (type == '2') {
        for (int i = 0; i < retakeMarksCount2[number][1]; i++) {
            if (retake_grades2[number][1][i] == 0) {
                retake_grades2[number][1][i] = mark;
                break;
            }
        }
    }
}


int Person::GetMark(int disc_index, int semester, char type, bool isRetake) const {
    if (disc_index < 0 || disc_index >= count_discip)
        return 0;

    int*** gradesArr = nullptr;
    int** marksCount = nullptr;
    if (semester == 1) {
        if (isRetake) {
            gradesArr = retake_grades1;
            marksCount = retakeMarksCount1;
        } else {
            gradesArr = grades1;
            marksCount = examMarksCount1;
        }
    } else if (semester == 2) {
        if (isRetake) {
            gradesArr = retake_grades2;
            marksCount = retakeMarksCount2;
        } else {
            gradesArr = grades2;
            marksCount = examMarksCount2;
        }
    } else {
        return 0;
    }
    int typeIndex = (type == '1') ? 0 : 1;
    int cnt = marksCount[disc_index][typeIndex];
    for (int i = 0; i < cnt; i++) {
        if (gradesArr[disc_index][typeIndex][i] != 0)
            return gradesArr[disc_index][typeIndex][i];
    }
    return 0;
}