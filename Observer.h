#pragma once
class Subject;

class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

