#include<iostream>

#include "ClassFactory.h"
using namespace yazi::reflect;

#include "A.h"
#include "B.h"

#include <stddef.h>

int main()
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	Object* a = factory->create_class("A");
	a->show();

	int count = a->get_field_count();
	for (int i = 0; i < count; i++)
	{
		ClassField* field = a->get_field(i);
		std::cout << field->name() << ", " << field->type() << ", " << field->offset() << ", " << std::endl;
	}

	//a->set("m_age", 18);

	//int age;
	//a->get("m_age", age);

	return 0;
}