#pragma once

#include "Singleton.h"
#include<string>
#include <map>
using namespace yazi::utility;

#include "ClassField.h"
#include <vector>

namespace yazi
{
namespace reflect
{

class Object
{
public:
	Object() {};
	virtual ~Object() {};

	void set_class_name(const std::string& className);
	const std::string& get_class_name() const;

	int get_field_count();
	ClassField* get_field(int pos);
	ClassField* get_field(const std::string& fieldName);

	template <typename T>
	void get(const std::string& fieldName, T& value);

	template <typename T>
	void set(const std::string& fieldName, const T& value);

	virtual void show() = 0;

private:
	std::string m_className;
};

typedef Object* (*create_object)(void);

class ClassFactory
{
	friend class Singleton<ClassFactory>;
public:
	void register_class(const std::string& className, create_object method);
	Object* create_class(const std::string& className);

	void register_class_field(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset);
	int get_field_count(const std::string& className);
	ClassField* get_field(const std::string& className, int pos);
	ClassField* get_field(const std::string& className, const std::string& fieldName);

private:
	ClassFactory() {}
	~ClassFactory() {}

private:
	std::map<std::string, create_object> m_classMap;
	std::map<std::string, std::vector<ClassField*>> m_classFields;
};

template <typename T>
void Object::get(const std::string& fieldName, T& value)
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	ClassField* field = factory->get_field(m_className, fieldName);
	size_t offset = field->offset();
	value = *(T*)((unsigned char*)(this) + offset);
}

template <typename T>
void Object::set(const std::string& fieldName, const T& value)
{
	ClassFactory* factory = Singleton<ClassFactory>::instance();
	ClassField* field = factory->get_field(m_className, fieldName);
	size_t offset = field->offset();
	*(T*)((unsigned char*)(this) + offset) = value;
}

		
}
}