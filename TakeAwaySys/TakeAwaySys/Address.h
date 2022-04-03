#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Address
{
public:
	Address()
	{

	}

	void CreateAddress()
	{
		cout << "Please enter: " << endl;
		cout << "House No/name: ";
		getline(cin >> ws, HouseNo);
		cout << "Street Name: ";
		getline(cin >> ws, StreetName);
		cout << "City: ";
		getline(cin >> ws, City);
		cout << "County: ";
		getline(cin >> ws, County);
		cout << "Postcode: ";
		getline(cin >> ws, Postcode);
	}

	void CreateAddress(string Input)
	{

	}

	void EditAddress()
	{

	}

	void DeleteAddress()
	{

	}

	void Clear()
	{
		HouseNo = "-1";
		StreetName = "Undefined";
		City = "Undefined";
		County = "Undefined";
		Postcode = "Undefined";
	}

	friend ostream& operator<<(ostream& OS, const Address Addr)
	{
		OS << "\t" << Addr.HouseNo << endl << "\t" << Addr.StreetName << endl;
		OS << "\t" << Addr.City << endl << "\t" << Addr.County << endl;
		OS << "\t" << Addr.Postcode << endl;
		return OS;
	}

private:
	string HouseNo;
	string StreetName;
	string City;
	string County;
	string Postcode;
};