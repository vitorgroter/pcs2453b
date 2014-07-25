#ifndef EVENT_H
#define EVENT_H

#include <map>

class Event {
public:
	virtual void execute() = 0;
	virtual ~Event();
};

#endif // EVENT_H

