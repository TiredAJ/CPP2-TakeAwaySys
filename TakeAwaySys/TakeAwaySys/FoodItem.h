#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "ScrClnTM.h"
#include "Graphics.h"

using namespace std;

ScrClnTM SCHandler2;
Graphics GHandler2;
const string CurrencySym2 = "\x9C";

class FoodItem
{
public:
	FoodItem()
	{		
		Clear();
	}

	//Necessary?
	void CreateDish()
	{
		
	}

	void CreateDish(string CuisineSpec)
	{
		string Temp, MenuTitle;
		string Details[3];
		int Counter = 0;

		cout << "(* Values are -1 by default)" << endl;

		cout << "Dish Name: ";
		getline(cin >> ws, Name);

		cout << "Dish Price*: " << CurrencySym2;
		cin >> Price;

		cout << "Course: ";
		getline(cin >> ws, Course);

		cout << "Availability*: ";
		cin >> Availability;

		cout << "Expected popularity [low/med/high]";
		cin >> Popularity;

		for (int i = 0; i < CuisineSpec.size(); i++)
		{
			if (CuisineSpec[i] != ',')
			{
				Temp += CuisineSpec[i];
			}
			else
			{
				Details[Counter] = Temp;
				Temp.clear();
				Counter++;
			}
		}
		Details[Counter] = Temp;

		Cuisine = Details[1];
		FoodID = Details[0] + Details[2];
	}

	void UpdatePop()
	{

	}

	void UpdateAvail()
	{

	}

	void UpdatePrice()
	{

	}

	void EditDish()
	{

	}

	void DisplayDish()
	{
		string MenuTitle = "Menu > Dish > " + Name;

		cout << Name << endl << "\tID:" << FoodID << endl;
		cout << "\tCuisine: " << Cuisine << endl;
		cout << "\tPrice: " << Price << endl << "\tCourse: " << Course << endl;
		cout << "\tPopularity: " << Popularity << endl;
		cout << "\tAvailability: " << Availability << endl;
		GHandler2.Line('=', 45);
	}

	void Clear()
	{
		Name = "Default";
		Price = -1.00;
		Cuisine = "Default";
		Course = "Default";
		Popularity = "Undefined";
		Availability = -1;
	}

	string GetCuisine()
	{return Cuisine;}

	friend ofstream& operator<<(ofstream& FS, const FoodItem FI)
	{
		FS << FI.FoodID << "," << FI.Name << "," << FI.Price << ",";
		FS << FI.Cuisine << "," << FI.Course << "," << FI.Popularity;
		FS << "," << FI.Availability << endl;

		return FS;
	}

	friend ifstream& operator>>(ifstream& IS, FoodItem& FI)
	{
		vector <string> Segments;
		string Input, Temp;
		getline(IS >> ws, Input);

		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] != ',')
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

		FI.FoodID = Segments[0];
		FI.Name = Segments[1];
		FI.Price = stod(Segments[2]);
		FI.Cuisine = Segments[3];
		FI.Course = Segments[4];
		FI.Popularity = Segments[5];
		FI.Availability = stoi(Segments[6]);	

		Segments.clear();

		return IS;
	}

private:
	string FoodID;
	string Name;
	double Price;
	string Cuisine;
	string Course;
	string Popularity;
	int Availability;
};