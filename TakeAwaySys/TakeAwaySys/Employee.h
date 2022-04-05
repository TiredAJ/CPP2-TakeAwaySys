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

	virtual void CreateEmployee()
	{

	}

	//necesary?
	void CreateEmployee(string Input)
	{

	}

	virtual void EditEmployee()
	{

	}

	virtual friend ostream& operator<<(ostream& OS, const Employee Emp)
	{
	
	}

	virtual friend ofstream& operator<<(ofstream& Filer, const Employee Emp)
	{

	}

	virtual friend ifstream& operator>>(ifstream& Obtainer, Employee Emp)
	{

	}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	Address Addrs;
};