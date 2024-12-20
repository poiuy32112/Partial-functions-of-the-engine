#pragma once

#include <iostream>
#include <string>
#include "ClassRegister.h"
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