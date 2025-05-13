#include "MyFunctions.h"
#include <iostream> 
#include "String.h"

void reset(char* str, int size) {
  for (int i = 0; i < size; i++) {
    str[i] = '\0';
  }
}

bool is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}


struct UniqueDirection {
    Direction* dir;         
    UniqueDirection* next;    
};

bool DirectionsEqual(const Direction* a, const Direction* b) {
    return (*a == *b);
}

void PrintDirection(std::fstream& output, const Direction* dir) {
    while (dir != nullptr) {
        String str = dir->GetStr();
        if (str.GetLine()[0] != '\0') { 
          output << str.GetLine();
          if (dir->GetNext() != nullptr) output << "->";
          else output << ' ';
        }
        dir = dir->GetNext();
      }
}

void PrintDisciplineChain(std::fstream& output, const Discipline* disc) {
    if (!disc)
        return;
    // Получаем внутренний узел, содержащий информацию о дисциплине.
    // Метод GetObj() определён как: DisciplineNode* GetObj() const { return obj; }
    // Чтобы избежать потери квалификатора const, сохраняем в const DisciplineNode*
     DisciplineNode* dnode = disc->GetObj();
    while (dnode != nullptr) {
        // Получаем указатель на цепочку строк, описывающих название дисциплины.
        // В DisciplineNode поле string (тип Direction*) хранит эту цепочку.
        Direction* dir = dnode->GetDir();
        // Выводим цепочку (например, "Math->Algebra")
        PrintDirection(output, dir);
        // Получаем следующий узел. 
        // Так как GetNext() возвращает DisciplineNode* (без const),
        // применяем static_cast, чтобы получить const DisciplineNode*
        DisciplineNode* next = dnode->GetNext();
        if (next != nullptr)
            output << "->";
        else
            output << " ";
        dnode = next;
    }
}

int MyStrCmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1) - ((unsigned char)*s2);
}

int CompareFullName(const FullName* a, const FullName* b) {
    while (a != nullptr && b != nullptr) {
        int cmp = MyStrCmp(a->GetStr().GetLine(), b->GetStr().GetLine());
        if (cmp != 0)
            return cmp;
        a = a->GetNext();
        b = b->GetNext();
    }
    if (a == nullptr && b != nullptr)
        return -1;
    if (a != nullptr && b == nullptr)
        return 1;
    return 0;
}

void PrintFullName(std::fstream& output, const FullName* fio) {
    while (fio != nullptr) {
        String str = fio->GetStr();
        if (str.GetLine()[0] != '\0') { 
          output << str.GetLine();
          if (fio->GetNext() != nullptr) output << "->";
          else output << ' ';
        }
        fio = fio->GetNext();
      }
}

void PrintStudentsGroupedByDirection(std::fstream& output, const Database &base) {
    UniqueDirection* processedDirs = nullptr;
    UniqueDirection* lastUnique = nullptr;
    
    for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
        Direction* currentDir = g->GetDirection();
        bool alreadyProcessed = false;
        for (UniqueDirection* check = processedDirs; check != nullptr; check = check->next) {
            if (DirectionsEqual(check->dir, currentDir)) {
                alreadyProcessed = true;
                break;
            }
        }
        if (!alreadyProcessed) {
            Direction* newDir = new Direction(*currentDir);
            UniqueDirection* node = new UniqueDirection;
            node->dir = newDir;
            node->next = nullptr;
            if (lastUnique) {
                lastUnique->next = node;
                lastUnique = node;
            } else {
                processedDirs = lastUnique = node;
            }
        }
    }
    
    for (UniqueDirection* uniq = processedDirs; uniq != nullptr; uniq = uniq->next) {
        output << "Направление: ";
        PrintDirection(output, uniq->dir);
        output << "\n";
        
        int aggregatedCount = 0;
        for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
            if (DirectionsEqual(g->GetDirection(), uniq->dir)) {
                for (Person* p = g->GetHead(); p != nullptr; p = p->GetNext()) {
                    aggregatedCount++;
                }
            }
        }
        if (aggregatedCount == 0) {
            output << "  Нет студентов в этом направлении.\n";
            continue;
        }
        
        Person** studArr = new Person*[aggregatedCount];
        int index = 0;
        for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
            if (DirectionsEqual(g->GetDirection(), uniq->dir)) {
                for (Person* p = g->GetHead(); p != nullptr; p = p->GetNext()) {
                    studArr[index++] = p;
                }
            }
        }
        
        for (int i = 0; i < aggregatedCount - 1; i++) {
            for (int j = 0; j < aggregatedCount - i - 1; j++) {
                if (CompareFullName(studArr[j]->GetFio(), studArr[j+1]->GetFio()) > 0) {
                    Person* temp = studArr[j];
                    studArr[j] = studArr[j+1];
                    studArr[j+1] = temp;
                }
            }
        }
        
        for (int i = 0; i < aggregatedCount; i++) {
            Person* p = studArr[i];
            output << p->GetId() << "\t";
            PrintFullName(output, p->GetFio());
            output << '\n';
        }
        output << "====================================\n\n";
        
        delete [] studArr;
    }
    
    while (processedDirs) {
        UniqueDirection* tmp = processedDirs;
        processedDirs = processedDirs->next;
        delete tmp->dir;  
        delete tmp;
    }
}

void PrintStudentsGroupedByYear(std::fstream& output, const Database& base) {
    Group* outer = base.GetHead();
    int processedYears[100] = {}; 
    int yearCount = 0;

    while (outer) {
        int currentYear = outer->GetYear();

        bool alreadyProcessed = false;
        for (int i = 0; i < yearCount; ++i) {
            if (processedYears[i] == currentYear) {
                alreadyProcessed = true;
                break;
            }
        }

        if (!alreadyProcessed) {
            processedYears[yearCount++] = currentYear;

            Person* combinedHead = nullptr;
            Person* combinedTail = nullptr;

            Group* inner = base.GetHead();
            while (inner) {
                if (inner->GetYear() == currentYear) {
                    Person* p = inner->GetHead();
                    while (p) {
                        Person* newPerson = new Person(*p);
                        newPerson->SetNext(nullptr);
                        if (!combinedHead) {
                            combinedHead = combinedTail = newPerson;
                        } else {
                            combinedTail->SetNext(newPerson);
                            combinedTail = newPerson;
                        }
                        p = p->GetNext();
                    }
                }
                inner = inner->GetNext();
            }

            // сортировка
            bool swapped;
            do {
                swapped = false;
                Person* curr = combinedHead;
                Person* prev = nullptr;
                while (curr && curr->GetNext()) {
                    Person* next = curr->GetNext();
                    if (CompareFullName(curr->GetFio(), next->GetFio()) > 0) {
                        curr->SetNext(next->GetNext());
                        next->SetNext(curr);
                        if (prev)
                            prev->SetNext(next);
                        else
                            combinedHead = next;
                        swapped = true;
                        prev = next;
                    } else {
                        prev = curr;
                        curr = curr->GetNext();
                    }
                }
            } while (swapped);

            // Вывод
            output << "Год: " << currentYear << "\n";

            Person* out = combinedHead;
            while (out) {
                PrintFullName(output, out->GetFio());
                output << "\n";
                out = out->GetNext();
            }
            output << "\n";

            while (combinedHead) {
                Person* tmp = combinedHead;
                combinedHead = combinedHead->GetNext();
                delete tmp;
            }
        }

        outer = outer->GetNext();
    }
}

struct UniqueDirYear {
    Direction* dir;         // Глубокая копия направления (со всей цепочкой)
    int year;               // Год поступления (или год группы)
    UniqueDirYear* next;    // Для формирования списка уникальных ключей
};

void PrintStudentsGroupedByDirectionAndYear(std::fstream& output, const Database &base) {
    // 1. Формируем список уникальных пар (направление, год) через обёртку UniqueDirYear.
    UniqueDirYear* processedDirs = nullptr;
    UniqueDirYear* lastUnique = nullptr;
    
    // Проходим по всем группам базы.
    for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
        Direction* currentDir = g->GetDirection();
        int currentYear = g->GetYear();  // Метод GetYear() должен возвращать год группы (или поступления).
        bool alreadyProcessed = false;
        for (UniqueDirYear* check = processedDirs; check != nullptr; check = check->next) {
            if (DirectionsEqual(check->dir, currentDir) && (check->year == currentYear)) {
                alreadyProcessed = true;
                break;
            }
        }
        if (!alreadyProcessed) {
            // Глубокая копия направления (вся цепочка) создается через конструктор копирования.
            Direction* newDir = new Direction(*currentDir);
            UniqueDirYear* node = new UniqueDirYear;
            node->dir = newDir;
            node->year = currentYear;
            node->next = nullptr;
            if (lastUnique) {
                lastUnique->next = node;
                lastUnique = node;
            } else {
                processedDirs = lastUnique = node;
            }
        }
    }
    
    // 2. Для каждого уникального ключа (направление, год) собираем студентов, сортируем их по ФИО и выводим.
    for (UniqueDirYear* uniq = processedDirs; uniq != nullptr; uniq = uniq->next) {
        // Выводим заголовок: направление и год.
        output << "Направление: ";
        PrintDirection(output, uniq->dir);
        output << " Год: " << uniq->year << "\n";
        
        // Подсчитываем количество студентов для данной пары (направление, год).
        int aggregatedCount = 0;
        for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
            if ( DirectionsEqual(g->GetDirection(), uniq->dir) && (g->GetYear() == uniq->year) ) {
                for (Person* p = g->GetHead(); p != nullptr; p = p->GetNext()) {
                    aggregatedCount++;
                }
            }
        }
        if (aggregatedCount == 0) {
            output << "  Нет студентов в этом направлении и году.\n";
            continue;
        }
        
        // Создаем динамический массив указателей на студентов.
        Person** studArr = new Person*[aggregatedCount];
        int index = 0;
        for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
            if ( DirectionsEqual(g->GetDirection(), uniq->dir) && (g->GetYear() == uniq->year) ) {
                for (Person* p = g->GetHead(); p != nullptr; p = p->GetNext()) {
                    studArr[index++] = p;
                }
            }
        }
        
        // Сортировка пузырьковым методом по полному ФИО студентов.
        for (int i = 0; i < aggregatedCount - 1; i++) {
            for (int j = 0; j < aggregatedCount - i - 1; j++) {
                if (CompareFullName(studArr[j]->GetFio(), studArr[j+1]->GetFio()) > 0) {
                    Person* temp = studArr[j];
                    studArr[j] = studArr[j+1];
                    studArr[j+1] = temp;
                }
            }
        }
        
        // Выводим отсортированный список студентов.
        for (int i = 0; i < aggregatedCount; i++) {
            Person* p = studArr[i];
            output << p->GetId() << "\t";
            PrintFullName(output, p->GetFio());
            output << "\n";
        }
        output << "====================================\n\n";
        
        delete [] studArr;
    }
    
    // 3. Освобождаем память, выделенную под список уникальных пар.
    while (processedDirs) {
        UniqueDirYear* tmp = processedDirs;
        processedDirs = processedDirs->next;
        delete tmp->dir;  // Деструктор Direction рекурсивно удаляет всю цепочку.
        delete tmp;
    }
}


void PrintGroupFullCycleResults(const Group* group, std::fstream& output) {
    output << "Результаты группы " << group->GetNumber() 
           << " (год поступления: " << group->GetYear() << "):\n\n";
    
    // Предположим, что group->GetDiscip() возвращает указатель на объект Discipline,
    // который представляет первую дисциплину в цепочке.
    Discipline* disc = group->GetDiscip();
    int discIndex = 0; // индекс дисциплины, соответствующий порядку резервирования оценок
    
    while(disc != nullptr) {
        output << "Дисциплина: ";
        // Выводим имя дисциплины. Предполагается, что PrintDisciplineChain умеет работать с объектом Discipline.
        PrintDisciplineChain(output, disc);
        output << ":\n";
        
        // Подсчитываем количество студентов в группе
        int studentCount = 0;
        for(Person* p = group->GetHead(); p != nullptr; p = p->GetNext())
            studentCount++;
        
        if(studentCount == 0) {
            output << "  Нет студентов в группе.\n";
        } else {
            Person** studArr = new Person*[studentCount];
            int index = 0;
            for(Person* p = group->GetHead(); p != nullptr; p = p->GetNext())
                studArr[index++] = p;
            
            // Сортировка студентов по полному ФИО (пузырьковая сортировка)
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - i - 1; j++) {
                    if (CompareFullName(studArr[j]->GetFio(), studArr[j+1]->GetFio()) > 0) {
                        Person* temp = studArr[j];
                        studArr[j] = studArr[j+1];
                        studArr[j+1] = temp;
                    }
                }
            }
            
            // Для каждого студента выводим ФИО и оценку по текущей дисциплине.
            for (int i = 0; i < studentCount; i++) {
                Person* p = studArr[i];
                output << "\t";
                PrintFullName(output, p->GetFio());
                output << "\t";
                // Вызываем GetMark. Так как оценки резервируются по порядковому индексу дисциплины,
                // передаём discIndex, фиксируем семестр как 1 и тип '1' (например, экзамен).
                int mark = p->GetMark(discIndex, 1, '1');
                output << mark;
                output << "\n";
            }
            
            delete [] studArr;
        }
        output << "\n";
        discIndex++;  // увеличиваем индекс дисциплины для следующей
        // Переходим к следующей дисциплине.
        // Предполагаем, что в классе Discipline определён метод GetNext(), который возвращает следующий объект Discipline в цепочке.
        disc = disc->GetNext();
    }
    output << "====================================\n\n";
}

void PrintGroupSemesterResults(const Group* group, int semester, std::fstream& output) {
    output << "Результаты группы " << group->GetNumber() 
           << " (год поступления: " << group->GetYear() << "), семестр " << semester << ":\n\n";
    
    const Discipline* disc = group->GetDiscip();
    int discIndex = 0;
    while(disc != nullptr) {
        output << "Дисциплина: ";
        PrintDisciplineChain(output, disc);
        output << ":\n";
        
        int studentCount = 0;
        for(Person* p = group->GetHead(); p != nullptr; p = p->GetNext())
            studentCount++;
        
        if(studentCount == 0) {
            output << "  Нет студентов в группе.\n";
        } else {
            Person** studArr = new Person*[studentCount];
            int index = 0;
            for(Person* p = group->GetHead(); p != nullptr; p = p->GetNext())
                studArr[index++] = p;
            
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - i - 1; j++) {
                    if (CompareFullName(studArr[j]->GetFio(), studArr[j+1]->GetFio()) > 0) {
                        Person* temp = studArr[j];
                        studArr[j] = studArr[j+1];
                        studArr[j+1] = temp;
                    }
                }
            }
            
            for (int i = 0; i < studentCount; i++) {
                Person* p = studArr[i];
                output << "\t";
                PrintFullName(output, p->GetFio());
                output << "\t";
                int mark = p->GetMark(discIndex, semester, '1');
                output << mark;
                output << "\n";
            }
            
            delete [] studArr;
        }
        output << "\n";
        discIndex++;
        disc = disc->GetNext();
    }
    output << "====================================\n\n";
}

// Вспомогательная функция для получения группы по индексу (начиная с 1)
Group* GetGroupByIndex(const Database &db, int index) {
    int count = 1;
    for (Group* g = db.GetHead(); g != nullptr; g = g->GetNext(), count++) {
        if(count == index)
            return g;
    }
    return nullptr;
}

void PrintGroup(std::fstream& output, const Database &base) {
    std::cout << "Список групп:\n";
    int index = 1;
    for(Group* g = base.GetHead(); g != nullptr; g = g->GetNext(), index++) {
        std::cout << index << ". Группа " << g->GetNumber() 
                  << " (год поступления: " << g->GetYear() << ")\n";
    }
    
    int chosenIndex = 0;
    std::cout << "Введите номер группы, которую хотите выбрать: ";
    std::cin >> chosenIndex;
    
    Group* chosenGroup = GetGroupByIndex(base, chosenIndex);
    if(!chosenGroup) {
        std::cout << "Неверный номер группы!\n";
        return;
    }
    
    int reportMode = 0;
    std::cout << "\nВыберите режим отчёта:\n";
    std::cout << "1) Результаты за весь учебный курс\n";
    std::cout << "2) Результаты за конкретный семестр\n";
    std::cout << "Введите номер выбранного режима: ";
    std::cin >> reportMode;
    
    switch(reportMode) {
      case 1:
          PrintGroupFullCycleResults(chosenGroup, output);
          break;
      case 2: {
          int semester = 0;
          std::cout << "Введите номер семестра: ";
          std::cin >> semester;
          PrintGroupSemesterResults(chosenGroup, semester, output);
          break;
      }
      default:
          std::cout << "Неверный режим выбора!\n";
          break;
    }
}