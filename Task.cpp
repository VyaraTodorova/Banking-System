#include "Task.h"
Task::Task(Type type, const MyString& name, unsigned index): type(type), name(name), index(index) {}

Type Task::getType()const
{
	return type;
}

const MyString& Task::getName() const
{
	return name;
}

unsigned Task::getIndex() const
{
	return index;
}

void Task::setIndex(unsigned index)
{
	this->index = index;
}