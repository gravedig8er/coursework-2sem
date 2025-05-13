all: file

file: main.o Database.o Direction.o Discipline.o DisciplineBase.o DisciplineNode.o FullName.o Group.o MyFunctions.o Person.o String.o
	g++ main.o Database.o Direction.o Discipline.o DisciplineBase.o DisciplineNode.o FullName.o Group.o MyFunctions.o Person.o String.o -o file
main.o: main.cpp Database.h Person.h config.h FullName.h String.h MyFunctions.h Direction.h Group.h Discipline.h DisciplineNode.h DisciplineBase.h
	g++ -c main.cpp
Database.o: Database.cpp Database.h Group.h config.h Person.h
	g++ -c Database.cpp
Direction.o: Direction.cpp Direction.h String.h config.h
	g++ -c Direction.cpp
Discipline.o: Discipline.cpp Discipline.h DisciplineNode.h config.h
	g++ -c Discipline.cpp
DisciplineBase.o: DisciplineBase.cpp DisciplineBase.h DisciplineNode.h config.h
	g++ -c DisciplineBase.cpp
DisciplineNode.o: DisciplineNode.cpp DisciplineNode.h Direction.h String.h config.h
	g++ -c DisciplineNode.cpp
FullName.o: FullName.cpp FullName.h String.h config.h
	g++ -c FullName.cpp
Group.o: Group.cpp Group.h Person.h config.h Direction.h DisciplineNode.h Discipline.h
	g++ -c Group.cpp
MyFunctions.o: MyFunctions.cpp MyFunctions.h config.h Database.h String.h Group.h
	g++ -c MyFunctions.cpp
Person.o: Person.cpp Person.h FullName.h Direction.h config.h
	g++ -c Person.cpp
String.o: String.cpp String.h config.h MyFunctions.h
	g++ -c String.cpp