#pragma once 
#include "String.h"

class Direction {
private:
  String str; 
  Direction* pNext; 
public: 
  void push_back(String temp);  
};