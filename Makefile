all: file 

file: main.o Person.o String.o FullName.o Direction.o Discipline.o DisciplineForm.o DisciplineNode.o Semestr.o Grade.o Database.o
	g++ main.o Person.o String.o FullName.o Direction.o Discipline.o DisciplineForm.o DisciplineNode.o Semestr.o Grade.o -o file
main.o: main.cpp Person.h
	g++ -c main.cpp
Person.o: Person.cpp FullName.h Direction.h Discipline.h
	g++ -c Person.cpp 
String.o: String.cpp config.h
	g++ -c String.cpp
FullName.o: FullName.cpp String.h
	g++ -c FullName.cpp
Direction.o: Direction.cpp String.h
	g++ -c Direction.cpp
Discipline.o: Discipline.cpp DisciplineForm.h
	g++ -c Discipline.cpp
DisciplineForm.o: DisciplineForm.cpp DisciplineNode.h	Semestr.h
	g++ -c DisciplineForm.cpp
DisciplineNode.o: DisciplineNode.cpp String.h 
	g++ -c DisciplineNode.cpp
Semestr.o: Semestr.cpp Grade.h
	g++ -c Semestr.cpp
Grade.o: Grade.cpp 
	g++ -c Grade.cpp
Database.o: Database.cpp Person.h
	g++ -c Database.cpp
