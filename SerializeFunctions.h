#pragma once
#include "MyString.h"
#include "Collection.hpp"
#include <fstream>

void writeStringToFile(std::ofstream& ofs, const MyString& str);
MyString readStringFromFile(std::ifstream& ifs);

