#include "String.h"
#include "MyFunctions.h"

String::String() : line{}, length{0} {}

String::String(char* src) {
  length = 0;
  if (src == nullptr) return;

  int i = 0;
  while (i < N && src[i] != '\0') { // ограничение по N
      line[i] = src[i];
      i++;
  }
  line[i] = '\0';
  length = i;
}

String::~String() {

}

int String::GetLength() {
  return this->length;
}

void String::SetLength(int length) {
  this->length = length; 
}

String::String(const String& other) {
  reset(line, N+1);
  this->length = other.length;
  line[length] = '\0';

  for (int i = 0; i < other.length; i++) {
    this->line[i] = other.line[i];
  }
}

void String::operator=(const String& other) {
  if (this != &other) {
    reset(line, N+1);
    length = other.length;
    for (int i = 0; i < length; i++) {
        line[i] = other.line[i];
    }
    line[length] = '\0';
  }
}
