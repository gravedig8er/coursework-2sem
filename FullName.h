#pragma once 
#include "String.h"

class FullName {
private: 
  String str;
  FullName* pNext; 
public: 
  FullName();
  FullName(const FullName& other);
  ~FullName();

  void push_back(String temp);
  
};