#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

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

	//use different delimter for address, pls, I beg

	friend ifstream& operator>>(ifstream& Obtainer, Address& Addr)
	{
		vector <string> Segments;
		string Input, Temp;
		getline(Obtainer >> ws, Input);

		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] != '+')
			{
				Temp += Input[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
		}
		Segments.push_back(Temp);
		Temp.clear();

		Addr.HouseNo = Segments[0];
		Addr.StreetName = Segments[1];
		Addr.City = Segments[2];
		Addr.County = Segments[3];
		Addr.Postcode = Segments[4];
		Segments.clear();

		return Obtainer;
	}

	friend ofstream& operator<<(ofstream& Filer, const Address Addr)
	{
		Filer << Addr.HouseNo << "+" << Addr.StreetName << "+";
		Filer << Addr.City << "+" << Addr.County << "+";
		Filer << Addr.Postcode << endl;
	}

private:
	string HouseNo;
	string StreetName;
	string City;
	string County;
	string Postcode;
};