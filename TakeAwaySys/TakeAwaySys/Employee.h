#pragma once
#include <string>
#include "Address.h"

using namespace std;

class Employee
{/*base class for employee types*/
public:
	Employee()
	{}

	virtual void CreateEmployee(int Index)
	{/*allows the creation of a new employee. Index is used to 
	 determine the numerical value of their ID*/
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
	{/*for displaying details*/
		cout << EmpID << endl << "Name: " << Name << endl;
		cout << "\tPhone No.: " << PhoneNo << endl << "\tPosition: ";
		cout << Position << endl << "Home: " << endl << Addrs << endl;

		//AJT.Graphics.Line('-', 45);
	}

	virtual void Clear()
	{/*clears an employee*/
		Name.clear();
		EmpID.clear();
		PhoneNo.clear();
		Addrs.Clear();
	}

	virtual void SetPosition(string Input)
	{/*specifically sets the position of an employee*/
		Position = Input;
	}

	virtual string GetID()
	{return EmpID;}

	virtual void SetID(string Input)
	{EmpID = Input;}

	virtual string GetPosition()
	{
		return Position;
	}

	virtual void Read(ifstream& Reader)
	{/*uses a passed in Reader object to fill the details of the employee*/
		string Temp, Block;
		vector <string> Segments;

		getline(Reader >> ws, Block);

		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != ',')
			{
				Temp += Block[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
			Segments.push_back(Temp);
			Temp.clear();

			EmpID = Segments[0];
			Name = Segments[1];
			PhoneNo = Segments[2];
			Position = Segments[3];
			
			Reader >> Addrs;

			Segments.clear();
		}
	}

	virtual void Write(ofstream& Writer)
	{/*same as Read(), but with the Writer object*/
		string Data;

		Data = EmpID + "," + Name + "," + PhoneNo + "," + Position + ",";

		Writer << Data << endl << Addrs << endl;
	}

protected:
	string EmpID;
	string Name;
	string PhoneNo;
	string Position;
	Address Addrs;
};