#pragma once

#include <string>

namespace yazi
{

namespace reflect
{

class ClassMethod
{
public:
	ClassMethod() : m_name(""), m_method(0) {}
	ClassMethod(const std::string& name, uintptr_t method) : m_name(name), m_method(method) {}
	~ClassMethod() {}

	const std::string& name()
	{
		return m_name;
	}

	uintptr_t method()
	{
		return m_method;
	}

private:
	std::string m_name;
	uintptr_t m_method;
};

}
}
