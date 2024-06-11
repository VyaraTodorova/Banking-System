#pragma once
#include "MyString.h"

enum Type {
	Open,
	Close,
	Change
};

class Task
{
public:
	Task(Type type, const MyString& name, unsigned index);
	Type getType()const;
	const MyString& getName() const;
	unsigned getIndex() const;
	void setIndex(unsigned index);

private:
	Type type;
	MyString name;
	unsigned index = 0;
};

