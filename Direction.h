#pragma once 
#include "String.h"

class Direction {
private: 
  String str;

  Direction* pNext;
public: 
  Direction();
  Direction(String temp);
  Direction(const Direction& other);
  ~Direction();
  void push_back(String temp);
  String GetStr() const { return str; }
  Direction* GetNext() const { return pNext; }
};
