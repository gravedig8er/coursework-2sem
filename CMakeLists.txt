cmake_minimum_required(VERSION 3.10)  
project(MyProject)  # Название проекта

set(CMAKE_CXX_STANDARD 17)  # Используем стандарт C++17

set(SOURCES 
    Database.cpp
    Direction.cpp
    Discipline.cpp
    DisciplineBase.cpp
    DisciplineNode.cpp
    FullName.cpp
    Group.cpp
    main.cpp
    MyFunctions.cpp
    Person.cpp
    String.cpp

)

set(HEADERS
    config.h
    Database.h
    Direction.h
    Discipline.h
    DisciplineBase.h
    DisciplineNode.h
    FullName.h
    Group.h
    MyFunctions.h
    Person.h
    String.h
)

# Создаём исполняемый файл
add_executable(file ${SOURCES} ${HEADERS})
