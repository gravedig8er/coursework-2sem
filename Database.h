#pragma once 
#include "Group.h"

class Database {
private: 
  Group* head; 
  Group* tail;

public: 
  Group* GetHead(); 
  void push_back(Group& temp);
};