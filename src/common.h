#ifndef COMMON_H
#define COMMON_H

#include <istream>
#include <list>
#include <cassert>

class StringNode {
public:
	~StringNode();

	std::string str;
	std::list <StringNode *> children;
};

std::string readString(std::istream & stream);
char readEqualSign(std::istream & stream);
double readDouble(std::istream & stream);
int readInteger(std::istream & stream);
std::string readQuotes(std::istream & stream);
std::list<std::string> readQuotedStringsList(std::istream & stream);
StringNode * readStringNode (std::istream & stream);
bool isPath(std::string filepath);
bool isRelativePath(std::string str);
std::string getParentDir(std::string filepath);
std::string getPageBreaker(std::string message);

#endif // COMMON_H

