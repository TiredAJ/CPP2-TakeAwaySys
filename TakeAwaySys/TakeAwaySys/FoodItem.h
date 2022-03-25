#pragma once
#include <iostream>
#include <string>
#include <iomanip>
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
		Name = "Default";
		Price = -1.00;
		Cuisine = "Default";
		Course = "Default";
		Popularity = "Undefined";
		Availability = -1;
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

		SCHandler2.ScreenCleanerTM(0, MenuTitle);

		cout << Name << ", ID:" << FoodID << endl << endl;
		GHandler2.Line('=', 45);
		cout << "Cuisine: " << Cuisine << endl;
		cout << "Price: " << Price << endl << "Course: " << Course << endl;
		cout << "Popularity: " << Popularity << endl;
		cout << "Availability: " << Availability << endl;
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