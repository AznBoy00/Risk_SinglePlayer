#pragma once
#include "Observer.h"
#include <list>
class Observer;

class Subject
{
public:
	Subject();
	~Subject();

	virtual void Register(Observer* o);
	virtual void Unregister(Observer* o);
	virtual void Notify();

private:
	std::list<Observer*> *observers;
};

