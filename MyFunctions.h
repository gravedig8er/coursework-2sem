#pragma once 
#include "Group.h"
#include "Database.h"
#include "Direction.h"

void reset(char* str, int length);
Group* FindGroup(Database& base, int number, int year, Direction* direct);
