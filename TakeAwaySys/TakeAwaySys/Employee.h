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
		Clear();

		cout << "Please enter:" << endl << "name: " << endl;
		getline(cin >> ws, Name);

		cout << "Phone No.: " << endl;
		getline(cin >> ws, PhoneNo);
		
		cout << "Position: " << endl;
		getline(cin >> ws, Position);

		EmpID = "Emp" + to_string(Index);

		cout << endl;

		Addrs.CreateAddress();
	}

	virtual void Display()
	{
		cout << EmpID << endl << "Name: " << Name << endl;
		cout << "\tPhone No.: " << PhoneNo << endl << "\tPosition: ";
		cout << Position << endl << "Home: " << endl << Addrs << endl;

		//AJT.Graphics.Line('-', 45);
	}

	virtual void Clear()
	{
		Name.clear();
		EmpID.clear();
		PhoneNo.clear();
		Addrs.Clear();
	}

	virtual void SetPosition(string Input)
	{Position = Input;}

	virtual string GetID()
	{return EmpID;}

	virtual void SetID(string Input)
	{EmpID = Input;}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	string Position;
	Address Addrs;
};