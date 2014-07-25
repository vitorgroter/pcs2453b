#ifndef COMMON_H
#define COMMON_H

#include <istream>
#include <list>
#include <cassert>

#include "tree.h"

std::string readString(std::istream & stream);
char readEqualSign(std::istream & stream);
double readDouble(std::istream & stream);
int readInteger(std::istream & stream);
std::string readQuotes(std::istream & stream);
std::list<std::string> readQuotedStringsList(std::istream & stream);
Tree <std::string> * readStringTree (std::istream & stream);
bool isPath(std::string filepath);
bool isRelativePath(std::string str);
std::string getParentDir(std::string filepath);
std::string getPageBreaker(std::string message);

#endif // COMMON_H

