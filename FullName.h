#pragma once 
#include "String.h"

class FullName {
private:
  String str;

  FullName* pNext; 
public: 
  FullName();
  FullName(String temp);
  FullName(const FullName& other);
  ~FullName();
  void push_back(String temp);
  String GetStr() const { return str; }
  FullName* GetNext() const { return pNext; }
};
