#ifndef TREE_H
#define TREE_H

#include <list>

template <class Type> class Tree {
public:
	Tree (Type data) : data(data) {

	}

	std::list <Tree <Type> *> children;	
	Type data;
};

#endif //TREE_H

