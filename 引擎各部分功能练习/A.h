#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "ClassRegister.h"
using namespace yazi::reflect;

class A : public Object
{
public:
	A() {}
	~A() {}

	void show()
	{
		std::cout << "A" << std::endl;
	}

public:
	std::string m_name;
	int m_age;
	std::vector<int> m_vector;
};

REGISTER_CLASS(A);
REGISTER_CLASS_FIELD(A, m_name, string);
REGISTER_CLASS_FIELD(A, m_age, int);
REGISTER_CLASS_FIELD(A, m_vector, vector<int>);

//Object* createObjectA()				
//{											
//	Object* obj = new A();			
//	return obj;								
//}											
//ClassRegister classRegisterA("A", createObjectA);
