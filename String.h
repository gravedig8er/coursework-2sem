#pragma once
#include "config.h" 

class String {
private: 
  char line[N+1];
  int length; 

public: 
  String();
  String(const String& other);
  ~String();
  String(char* src);
  int GetLength();
  void SetLength(int length);
  void operator = (const String& other);
   
  char* GetLine() { return line; }
}; 