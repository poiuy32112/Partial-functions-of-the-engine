#pragma once

#include<string>
#include"ClassFactory.h"

namespace yazi
{
namespace reflect
{

class ClassRegister
{
public:
	ClassRegister(const std::string& className, create_object method)
	{
		std::cout << "class register " << className << std::endl;
		ClassFactory* factory = Singleton<ClassFactory>::instance();
		factory->register_class(className, method);
	}

};

#define REGISTER_CLASS(className)				\
	Object* createObject##className()				\
	{											\
		Object* obj = new className();			\
		return obj;								\
	}											\
	ClassRegister classRegister##className(#className, createObject##className)
}
}
