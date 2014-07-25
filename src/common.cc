#include <iostream>
#include <cctype>
#include <stdexcept>

#include "tree.h"
#include "common.h"

std::string readString(std::istream & stream) {
	std::string str;
	stream >> str;
	
	return str;
}

char readEqualSign(std::istream & stream) {
	char c;
	while ((c = stream.get()) == ' ');

	if (c != '=')
		assert(false);

	return c;
}

double readDouble(std::istream & stream) {
	double d;
	stream >> d;

	return d;
}

int readInteger(std::istream & stream) {
	int i;
	stream >> i;

	return i;
}

std::string readQuotes(std::istream & stream) {
	char c;
	std::string str;

	while ((c = stream.get()) != '\"');
	while ((c = stream.get()) != '\"') {
		str.push_back(c);
	}

	return str;
}

std::list<std::string> readQuotedStringsList(std::istream & stream) {
	char c;
	std::list<std::string> list;

	while ((c = stream.get()) != '{');
	while (true) {
		while ((c = stream.get()) == ' ');
		if (c == '\"') {
			stream.unget();
			list.push_back(readQuotes(stream));
		}
		else if(c == '}')
			return list;
	}

	assert(false);
	return list;
}

Tree <std::string> * readStringTree (std::istream & stream) {
	char c;
	Tree <std::string> * tree = new Tree <std::string> (readQuotes(stream));

	while ((c = stream.get()) == ' ');

	if (c== '\r' || c == '\n')
		return tree;
	else if (c == ',' || c == '}') {
		stream.unget();
		return tree;
	}
	else if (c == '{') {
		while (true) {
			tree->children.push_back(readStringTree(stream));
			while ((c = stream.get()) == ' ');
			if (c == ',')
				continue;
			else if (c == '}')
				break;
			else
				assert(false);
		}
	}
	else {
		assert(false);
	}

	return tree;
}

bool isPath(std::string str) {
	if (str[0] != '/') {
		return false;
	}

	for (std::string::size_type i = 0; i < str.length() - 1; i++) {
		if (str[i] == '/' && str[i + 1] == '/')
			return false;
	}

	for (std::string::size_type i = 0; i < str.length(); i++) {
		if (!(isalnum(str[i]) || str[i] == '.' || str[i] == '/' || str[i] == '_' || str[i] == ' '))
			return false;
	}

	return true;
}

bool isRelativePath(std::string str) {
	if (str.length() < 3)
		return false;

	if (str[0] != '.' || str[1] != '/')
		return false;

	for (std::string::size_type i = 0; i < str.length() - 1; i++) {
		if (str[i] == '/' && str[i + 1] == '/')
			return false;
	}

	for (std::string::size_type i = 0; i < str.length(); i++) {
		if(!(isalnum(str[i]) || str[i] == '.' || str[i] == '/' || str[i] == '_' || str[i] == ' '))
			return false;
	}

	return true;
}

std::string getParentDir(std::string filepath) {
	if (!isPath(filepath)) {
		throw std::invalid_argument("Argument is not a valid path.");
	}
	else if (filepath == "/") {
		throw std::invalid_argument("Filepath \"/\" has no parent directory");
	}
	else {
		for (int i = filepath.size() - 2; i >= 0; i--) {
			if (filepath[i] == '/')
				return filepath.substr(0, i + 1);
		}
	}

	assert(false);
}

std::string getPageBreaker(std::string message) {
	std::string left((80 - message.length()) / 2, '-');
	std::string right((80 - message.length()) / 2 + (80 - message.length()) % 2, '-');

	return left + message + right;
}

