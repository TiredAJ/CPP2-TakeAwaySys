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

	virtual void CreateEmployee(int Index)
	{
		cout << "Please enter:" << endl << "name: " << endl;
		getline(cin >> ws, Name);

		cout << "Phone No.:" << endl;
		getline(cin >> ws, PhoneNo);

		EmpID = "Emp" + to_string(Index);

		Addrs.CreateAddress();
	}

	virtual void Display()
	{
		cout << EmpID << endl << "Name: " << Name << endl;
		cout << "Phone No.: " << PhoneNo << endl << "Home: ";
		cout << endl << Addrs << endl;

		//AJT.Graphics.Line('-', 45);
	}

	virtual void Clear()
	{
		Name.clear();
		EmpID.clear();
		Addrs.Clear();
	}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	Address Addrs;
};