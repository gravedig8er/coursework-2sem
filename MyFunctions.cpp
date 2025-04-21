#include "MyFunctions.h"

void reset(char* str, int length) {
    for (int i = 0; i < length; i++) {
      str[i] = '\0';
    }
  }