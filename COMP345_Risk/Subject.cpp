#include "Subject.h"

Subject::Subject()
{
	observers = new std::list<Observer*>;
}
Subject::~Subject()
{
	delete observers;
}
void Subject::Register(Observer* o) {
	observers->push_back(o);
}
void Subject::Unregister(Observer* o) {
	observers->remove(o);
}
void Subject::Notify() {
	std::list<Observer*>::iterator i = observers->begin();
	for (; i != observers->end(); i++) {
		(*i)->Update();
	}
}