#pragma once
#include "ClassRegister.h"
#include <iostream>
#include <string>

using namespace yazi::reflect;

class B : public Object
{
public:
	B() {}
	~B() {}
	
	void show()
	{
		std::cout << "B" << std::endl;
	}

public:
	std::string m_name;
};

REGISTER_CLASS(B);