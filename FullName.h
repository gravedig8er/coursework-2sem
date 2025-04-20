#pragma once 
#include "String.h"

class FullName {
private: 
  String str;
  FullName* pNext; 
public: 
  void push_back(String temp);
  
};