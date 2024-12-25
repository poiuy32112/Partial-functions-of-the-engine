#include "A.h"
#include "B.h"
#include "ClassFactory.h"
#include <functional>
#include <iostream>
#include <stddef.h>

using namespace yazi::reflect;

int main()
{

	ClassFactory* factory = Singleton<ClassFactory>::instance();
	Object* a = factory->create_class("A");

	int n1 = a->call("f1", 1);
	int n2 = a->call("f2", 2);

	//int count = a->get_field_count();
	//for (int i = 0; i < count; i++)
	//{
	//	ClassField* field = a->get_field(i);
	//	std::cout << field->name() << ", " << field->type() << ", " << field->offset() << ", " << std::endl;
	//}

	//a->set("m_age", 18);

	//int age;
	//a->get("m_age", age);

	return 0;
}