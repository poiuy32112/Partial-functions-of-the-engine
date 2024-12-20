#include<iostream>

#include "ClassFactory.h"
using namespace yazi::reflect;

#include "A.h"
#include "B.h"

int main()
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();

	Object* a = factory->create_class("A");
	a->show();
	Object* b = factory->create_class("B");
	b->show();

	return 0;
}