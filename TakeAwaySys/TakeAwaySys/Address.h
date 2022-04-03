#pragma once
#include <string>

using namespace std;

class Address
{
public:
	Address()
	{

	}

	void CreateAddress()
	{

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

private:
	string HouseNo;
	string StreetName;
	string City;
	string County;
	string Postcode;
};