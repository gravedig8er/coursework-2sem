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

// Сравнение FullName блоков, как strcmp: -1, 0, 1

// Вывод FullName
struct UniqueDirection {
    Direction* dir;         // Глубокая копия направления (со всей цепочкой)
    UniqueDirection* next;    // Связь для списка уникальных направлений
};

// Функция для сравнения двух направлений (используем рекурсивный оператор == класса Direction)
bool DirectionsEqual(const Direction* a, const Direction* b) {
    return (*a == *b);
}

// Рекурсивная функция вывода всего направления в поток.
// Выводит, например: "Compu->ter S->cienc->e and-> Engi->neeri->ng"
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

int MyStrCmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    // При этом приводим символы к unsigned char, чтобы корректно сравнивать знаковые символы
    return ((unsigned char)*s1) - ((unsigned char)*s2);
}

// Функция для сравнения ФИО двух студентов (сравниваем первую строку ФИО, например, фамилию)
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

// Функция вывода полного ФИО студента (сцепляет все блоки через "->")
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

// Функция, агрегирующая студентов по уникальным направлениям.
// Для каждого уникального направления (определяемого сравнением полной цепочки Direction)
// функция собирает всех студентов из всех групп, у которых направление совпадает, сортирует их по ФИО
// и выводит результат в заданный поток.
void PrintStudentsGroupedByDirection(std::fstream& output, const Database &base) {
    // 1. Построение списка уникальных направлений с использованием структуры UniqueDirection.
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
            // Глубокая копия текущего направления (рекурсивно копируется вся цепочка)
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
    
    // 2. Для каждого уникального направления:
    //    – агрегировать студентов из всех групп с данным направлением,
    //    – сортировать полученный массив указателей на студентов по ФИО,
    //    – выводить отсортированный список.
    for (UniqueDirection* uniq = processedDirs; uniq != nullptr; uniq = uniq->next) {
        // Вывод заголовка направления
        output << "Направление: ";
        PrintDirection(output, uniq->dir);
        output << "\n";
        
        // Подсчёт общего количества студентов с данным направлением.
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
        
        // Выделяем динамический массив для указателей на студентов.
        Person** studArr = new Person*[aggregatedCount];
        int index = 0;
        for (Group* g = base.GetHead(); g != nullptr; g = g->GetNext()) {
            if (DirectionsEqual(g->GetDirection(), uniq->dir)) {
                for (Person* p = g->GetHead(); p != nullptr; p = p->GetNext()) {
                    studArr[index++] = p;
                }
            }
        }
        
        // Сортировка студентов по ФИО (пузырьковая сортировка).
        for (int i = 0; i < aggregatedCount - 1; i++) {
            for (int j = 0; j < aggregatedCount - i - 1; j++) {
                if (CompareFullName(studArr[j]->GetFio(), studArr[j+1]->GetFio()) > 0) {
                    Person* temp = studArr[j];
                    studArr[j] = studArr[j+1];
                    studArr[j+1] = temp;
                }
            }
        }
        
        // Вывод отсортированного списка студентов.
        for (int i = 0; i < aggregatedCount; i++) {
            Person* p = studArr[i];
            output << p->GetId() << "\t";
            PrintFullName(output, p->GetFio());
            output << '\n';
        }
        output << "====================================\n\n";
        
        delete [] studArr;
    }
    
    // 3. Освобождение памяти списка уникальных направлений.
    while (processedDirs) {
        UniqueDirection* tmp = processedDirs;
        processedDirs = processedDirs->next;
        delete tmp->dir;  // Деструктор Direction рекурсивно освобождает всю цепочку.
        delete tmp;
    }
}

void PrintStudentsGroupedByYear(std::fstream& output, const Database& base) {
    Group* outer = base.GetHead();
    int processedYears[100] = {}; // фиксированный массив годов
    int yearCount = 0;

    while (outer) {
        int currentYear = outer->GetYear();

        // Проверка: уже обрабатывали такой год?
        bool alreadyProcessed = false;
        for (int i = 0; i < yearCount; ++i) {
            if (processedYears[i] == currentYear) {
                alreadyProcessed = true;
                break;
            }
        }

        if (!alreadyProcessed) {
            // Запоминаем год как обработанный
            processedYears[yearCount++] = currentYear;

            // Собираем студентов за этот год
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

            // Сортировка пузырьком по ФИО
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

            // Очистка временного списка студентов
            while (combinedHead) {
                Person* tmp = combinedHead;
                combinedHead = combinedHead->GetNext();
                delete tmp;
            }
        }

        outer = outer->GetNext();
    }
}