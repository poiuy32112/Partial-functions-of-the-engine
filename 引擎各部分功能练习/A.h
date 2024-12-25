#pragma once

#include "ClassRegister.h"
#include <iostream>
#include <string>
#include <vector>

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

	int f1(int num)
	{
		std::cout << "f1 " << num << std::endl;
		return num;
	}

	int f2(int num)
	{
		std::cout << "f2 " << num << std::endl;
		return num;
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
REGISTER_CLASS_METHOD(A, f1);
REGISTER_CLASS_METHOD(A, f2);

//Object* createObjectA()				
//{											
//	Object* obj = new A();			
//	return obj;								
//}											
//ClassRegister classRegisterA("A", createObjectA);
