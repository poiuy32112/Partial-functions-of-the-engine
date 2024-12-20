#pragma once

#include <iostream>
#include <string>
#include "ClassRegister.h"

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
};

REGISTER_CLASS(A);
//Object* createObjectA()				
//{											
//	Object* obj = new A();			
//	return obj;								
//}											
//ClassRegister classRegisterA("A", createObjectA);
