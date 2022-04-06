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
		cout << "Please enter a name: " << endl;
		getline(cin >> ws, Name);
		cout << "Please enter an ID: " << endl;
		cin >> EmpID;

		Addrs.CreateAddress();
	}

	virtual void Clear()
	{
		Name.clear();
		EmpID.clear();
		Addrs.Clear();
	}

	virtual void Display()
	{
		cout << EmpID << endl << "\t" << Name << endl << "\t" << PhoneNo;
		cout << endl;// << Emp.Addrs << endl;
	}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	Address Addrs;
};