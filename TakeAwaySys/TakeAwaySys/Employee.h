#pragma once
#include <string>
#include "Address.h"

using namespace std;

class Employee
{
public:
	Employee()
	{

	}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	Address Addrs;
};

