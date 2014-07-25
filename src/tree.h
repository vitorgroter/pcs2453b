#ifndef TREE_H
#define TREE_H

#include <list>

template <class Type> class Tree {
public:
	std::list <Tree <Type> *> children;	
	Type data;
};

#endif //TREE_H

