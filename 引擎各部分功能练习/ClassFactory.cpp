#include "ClassFactory.h"
using namespace yazi::reflect;

void Object::set_class_name(const std::string& className)
{
	m_className = className;
}
const std::string& Object::get_class_name() const
{
	return m_className;
}

int Object::get_field_count()
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	return factory->get_field_count(m_className);
}
ClassField* Object::get_field(int pos)
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	return factory->get_field(m_className, pos);
}
ClassField* Object::get_field(const std::string& fieldName)
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	return factory->get_field(m_className, fieldName);
}

void ClassFactory::register_class(const std::string& className, create_object method)
{
	m_classMap[className] = method;
}

Object* ClassFactory::create_class(const std::string& className)
{
	auto it = m_classMap.find(className);
	if (it == m_classMap.end())
	{
		return nullptr;
	}
	return it->second();
}

void ClassFactory::register_class_field(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset)
{
	m_classFields[className].push_back(new ClassField(fieldName, fieldType, offset));
}
int ClassFactory::get_field_count(const std::string& className)
{
	return m_classFields[className].size();
}
ClassField* ClassFactory::get_field(const std::string& className, int pos)
{
	int size = m_classFields[className].size();
	if (pos < 0 || pos >= size)
	{
		return nullptr;
	}
	return m_classFields[className][pos];
}
ClassField* ClassFactory::get_field(const std::string& className, const std::string& fieldName)
{
	auto fields = m_classFields[className];
	for (auto it = fields.begin(); it != fields.end(); it++)
	{
		if ((*it)->name() == fieldName)
		{
			return (*it);
		}
	}
	return nullptr;
}