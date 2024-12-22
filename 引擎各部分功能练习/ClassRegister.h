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

	ClassRegister(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset)
	{
		std::cout << "class register field " << className << "." << fieldName << std::endl;
		ClassFactory * factory = Singleton<ClassFactory>::instance();
		factory->register_class_field(className, fieldName, fieldType, offset);
	}
};

#define REGISTER_CLASS(className)				\
	Object* createObject##className()				\
	{											\
		Object* obj = new className();			\
		obj->set_class_name(#className);		\
		return obj;								\
	}											\
	ClassRegister classRegister##className(#className, createObject##className)

#define REGISTER_CLASS_FIELD(className, fieldName, fieldType) \
	className className##fieldName; \
	ClassRegister classRegister##className##fieldName(#className, #fieldName, #fieldType, (size_t)(&(className##fieldName.fieldName)) - (size_t)(&className##fieldName))

}
}
