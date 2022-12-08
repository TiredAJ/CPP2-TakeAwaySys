#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class Address
{/*Address is a simple object that handles the addresses of 
 employees and customers*/
public:
	Address()
	{}

	void CreateAddress()
	{/*Allows user to fill the address*/
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

	void Clear()
	{/*clears address*/
		HouseNo = "-1";
		StreetName = "Undefined";
		City = "Undefined";
		County = "Undefined";
		Postcode = "Undefined";
	}

	friend ostream& operator<<(ostream& OS, const Address Addr)
	{/*overloaded operator for outputting to the terminal*/
		OS << "\t" << Addr.HouseNo << endl << "\t" << Addr.StreetName << endl;
		OS << "\t" << Addr.City << endl << "\t" << Addr.County << endl;
		OS << "\t" << Addr.Postcode << endl;
		return OS;
	}

	/*A unique delimiter was used for address as commas were used
	elsewhere up the chain*/
	friend ofstream& operator<<(ofstream& Filer, const Address Addr)
	{/*overloaded operator for outputting to a file*/
		Filer << Addr.HouseNo << ":" << Addr.StreetName << ":";
		Filer << Addr.City << ":" << Addr.County << ":";
		Filer << Addr.Postcode << endl;

		return Filer;
	}

	void ReadAddr(string Input)
	{/*splits an inputted string into an address*/
		vector <string> Segments;
		string Temp;

		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] != ':')
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

		HouseNo = Segments[0];
		StreetName = Segments[1];
		City = Segments[2];
		County = Segments[3];
		Postcode = Segments[4];
		Segments.clear();
	}
	
	friend ifstream& operator>>(ifstream& Obtainer, Address& Addr)
	{/*overloaded operator for reading from a file*/
		vector <string> Segments;
		string Temp, Block;

		getline(Obtainer >> ws, Block);

		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != ':')
			{
				Temp += Block[i];
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

private:
	string HouseNo;
	string StreetName;
	string City;
	string County;
	string Postcode;
};