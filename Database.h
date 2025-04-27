#pragma once 
#include "Group.h"

class Database {
private:
  Group* head; 
  Group* tail;
public: 
  Database();
  ~Database();
  void AddGroup(Group* group);
  Group* FindGroup(int number); 
  Group* GetHead() const { return head; }
};