#include "MyFunctions.h"

void reset(char* str, int size) {
  for (int i = 0; i < size; i++) {
    str[i] = '\0';
  }
}

bool is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}