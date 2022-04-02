//Consolas - 20pt
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Employee.h"
#include "Address.h"
#include "AJTools.h"

using namespace std;

AJTools AJT;

const string CurrencySym = "\x9C";
string MenuTitle;

class Date
{
public:
	Date()
	{
		Minute = -1;
		Hour = -1;
		Day = -1;
		Month = -1;
		Year = -1;
	}

	void SetTime()
	{
		string Input;
		do
		{
			Input.clear();

			do
			{
				cout << "Please enter the current: " << endl;
				cout << "Hour [0-23]: ";
				cin >> Input;
			} while (stoi(Input) > 23 || stoi(Input) < 0);

			if (Input.size() == 1)
			{Input = "0" + Input;}
			
			Hour = stoi(Input);
			Input.clear();

			do
			{
				cout << "Minute [0-59]: ";
				cin >> Input;
			} while (stoi(Input) > 59 || stoi(Input) < 0);

			if (Input.size() == 1)
			{Input = "0" + Input;}

			Minute = Input;
			Input.clear();

			cout << endl << Hour << ":" << Minute << endl;
			cout << "Confirm time? [yes/no]" << endl << "> ";
			cin >> Input;
		} while (Input == "no");
	}
	
	void SetDate()
	{
		string Input;
		do
		{
			Input.clear();

			do
			{
				cout << "Please enter the:" << endl;
				cout << "Year[202#]: ";
				cin >> Input;
			} while (Input.size() != 4);
			Year = stoi(Input);

			do
			{
				cout << "Month [1-12]: ";
				cin >> Input;
			} while (stoi(Input) > 12 || stoi(Input) < 0);			
			
			if (Input.size() == 1)
			{Input = "0" + Input;}

			Month = Input;
			Input.clear();

			do
			{
				cout << "Day [1-" << MonthDays[stoi(Month) - 1] << "]: ";
				cin >> Input;
			} while (stoi(Input) > MonthDays[stoi(Month) - 1] || stoi(Input) < 1);

			if (Input.size() == 1)
			{Input = "0" + Input;}

			Day = Input;
			Input.clear();
			
			cout << Day << "/" << Month << "/" << Year << endl;
			cout << "Confirm Date? [yes/no]" << endl << "> ";
			cin >> Input;
		} while (Input == "no");
	}

	void SetDateTime()
	{
		SetTime();
		SetDate();

		AJT.SCH.ScreenCleanerTM(0);
	}

	bool operator>(Date D2)
	{
		if (this->Year < D2.Year)
		{return false;}
		else if (this->Year > D2.Year)
		{return true;}
		else if (this->Month > D2.Month)
		{return true;}
		else if (this->Day > D2.Day)
		{return true;}
		else if (this->Hour > D2.Hour)
		{return true;}
		else if (this->Minute > D2.Minute)
		{return true;}
		else 
		{return false;}
	}

	bool operator<(Date D2)
	{
		if (this->Year > D2.Year)
		{return false;}
		else if (this->Year < D2.Year)
		{return true;}
		else if (stoi(this->Month) < stoi(D2.Month))
		{return true;}
		else if (stoi(this->Day) < stoi(D2.Day))
		{return true;}
		else if (this->Hour < D2.Hour)
		{return true;}
		else if (stoi(this->Minute) < stoi(D2.Minute))
		{return true;}
		else
		{return false;}
	}

	string GetDate()
	{
		string Temp;
		Temp = Hour + ":" + Minute;
		Temp += " " + Day + "/" + Month + "/" + to_string(Year);
		return Temp;
	}

	void SplitDate(string Input)	//string -> Date
	{
		Hour = Input.substr(0, 2);
		Minute = Input.substr(3, 2);
		Day = Input.substr(6, 2);
		Month = Input.substr(9, 2);
		Year = stoi(Input.substr(12));
	}

	friend ostream& operator<<(ostream& OS, const Date Dt)
	{
		if (stoi(Dt.Hour) != -1)
		{
			OS << Dt.Hour << ":" << Dt.Minute << "  " << Dt.Day << "/" << Dt.Month;
			OS << "/" << Dt.Year;

			return OS;
		}
	}

private:
	string Day;
	string Month;
	int Year;
	string Minute;
	string Hour;

	int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};

class Customer
{
public:
	Customer()
	{
	
	}
	
	void CreateCustomer()
	{

	}

	void CreateCustomer(string Input)
	{

	}

	void EditCustomer()
	{

	}

	void NewOrder()
	{

	}

private:

	string CustID;
	string Name;
	Address Home;
	string Email;
	string PhoneNo;
	int Loyalty;
};

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

		cout << "Dish Price*: " << CurrencySym;
		cin >> Price;

		cout << "Course: ";
		getline(cin >> ws, Course);

		cout << "Availability*: ";
		cin >> Availability;

		cout << "Expected popularity [low/med/high]: ";
		cin >> Popularity;

		//so, prefix + cuisine + ID# comes in, below splits it
		//into a 3-part vector.
		//make it better

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

		Cuisine = Details[0] + "," + Details[1];
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
	{
		return Cuisine;
	}

	friend ofstream& operator<<(ofstream& FS, const FoodItem FI)
	{
		FS << FI.FoodID << "," << FI.Name << "," << FI.Price << ",";
		FS << AJT.CMH.Remove(',', FI.Cuisine, "left");
		FS << "," << FI.Course << "," << FI.Popularity;
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

	friend ostream& operator<<(ostream& OS, const FoodItem FI)
	{
		MenuTitle = "Menu > Dish > " + FI.Name;

		OS << FI.Name << endl << "\tID:" << FI.FoodID << endl;
		OS << "\tCuisine: " << FI.Cuisine << endl;
		OS << "\tPrice: " << CurrencySym << setprecision(2) << fixed << FI.Price;
		OS << endl << "\tCourse: " << FI.Course << endl;
		OS << "\tPopularity: " << FI.Popularity << endl;
		OS << "\tAvailability: " << FI.Availability << endl;
		AJT.Graphics.Line('=', 45);

		return OS;
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

class Menu
{
	/*
	* so, to delete a dish, I was thinking we set the ID to -1
	* then in the delete function, when copying things to the temp
	* vector, we ignore any with an ID of -1
	*/
public:
	Menu()
	{

	}

	void Searcher()
	{

	}

	void ReadFile()
	{
		ifstream Reader;
		FoodItem TempFood;
		vector <FoodItem> TempFoods;
		int NoCuisines, NoDishes, Counter;
		string Temp;

		Reader.open("Dishes.txt");

		Reader >> NoCuisines;

		for (int i = 0; i < NoCuisines; i++)
		{
			Reader >> NoDishes;
			Reader >> Temp;

			Cuisine.push_back(Temp);
			Temp.clear();
			TempFoods.clear();

			for (int j = 0; j < NoDishes; j++)
			{
				Reader >> TempFood;
				TempFoods.push_back(TempFood);
				TempFood.Clear();
			}
			Dishes.push_back(TempFoods);
		}
	}

	void WriteFile()
	{
		ofstream Writer;
		Writer.open("Dishes.txt");

		Writer << Cuisine.size() << endl;

		for (int i = 0; i < Cuisine.size(); i++)
		{
			Writer << Dishes[i].size() << endl;
			Writer << Cuisine[i] << endl;

			for (int j = 0; j < Dishes[i].size(); j++)
			{
				Writer << Dishes[i][j];
			}
		}

		Writer.close();
	}

	//here next
	void NewDish()
	{
		vector <FoodItem> TempFoods;
		string Command, Input;
		int ChosenCuisine;

		MenuTitle = "New Dish >";

		cout << MenuTitle << endl;
		
		cout << "Would you like to add a new cuisine? [yes/no]" << endl << "> ";
		cin >> Command;

		while (Command != "yes" && Command != "no")
		{
			cout << "Please enter [yes] or [no]" << endl << "> ";
			cin >> Command;
		}

		if (Command == "yes")
		{
				MenuTitle = "New Dish > ";

				CreateCuisine();
				
			do
			{
				cout << "Would you like to add a new dish? [yes/no]" << endl;
				cin >> Command;

				if (Command == "no")
				{
					return;
				}

			} while (Command != "yes" && Command != "no");
		}

		Input.clear();
		Command.clear();
		
		do
		{
			MenuTitle = "New Dish > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Choose Cuisine" + "\n");

			if (Cuisine.size() == 0)
			{
				cout << "There are no cuisines available, please make a new cuisine first" << endl;
				return;
			}

			FoodItem TempFood;

			AJT.Graphics.DisplayOptions(Cuisine, 0);
			cin >> Command;

			while (stoi(Command) > Cuisine.size() + 1 || stoi(Command) < 1)
			{
				cout << "Please choose a cuisine[1-" << Cuisine.size() + 1 << "]" << endl;
				cin >> Command;
			}

			cout << "You've chosen:" << Cuisine[stod(Command) - 1];
			ChosenCuisine = stoi(Command) - 1;

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + (Cuisine[ChosenCuisine] + "\n"));

			if (Dishes.size() == 0)
			{
				TempFood.CreateDish(Cuisine[ChosenCuisine] + ",0");				
			}
			else
			{
				if (Dishes.size() <= ChosenCuisine)
				{
					TempFood.CreateDish(Cuisine[ChosenCuisine] + ",0");
				}
				else
				{
					TempFood.CreateDish(Cuisine[ChosenCuisine] + "," + to_string(Dishes[ChosenCuisine].size()));
				}				
			}
			

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + " Display Dish");

			cout << TempFood;

			TempFoods.clear();

			if (Dishes.size() == 0)
			{
				TempFoods.push_back(TempFood);
				Dishes.push_back(TempFoods);
			}
			else
			{
				if (Dishes.size() <= ChosenCuisine)
				{
					TempFoods.push_back(TempFood);
					Dishes.push_back(TempFoods);
				}
				else
				{
					Dishes[ChosenCuisine].push_back(TempFood);
				}				
			}		

			cout << "Would you like to make another dish? [yes/no]" << endl;
			cin >> Command;
			
		} while (Command != "no" || Command == "yes");

		AJT.SCH.ScreenCleanerTM(0);
	}

	void UpdatePop()
	{

	}

	void UpdateAvail()
	{

	}

	void DisplayMenu()
	{
		string Command, Input;
		int CuisineChoice;

		cout << "Would you like to browse a specific cuisine? [yes/no]: ";
		cin >> Command;

		while (Command != "yes" && Command != "no")
		{
			cout << "Please enter [yes] or [no]: ";
			cin >> Command;
		}

		if (Command == "yes")
		{
			AJT.Graphics.DisplayOptions(Cuisine, 2);

			/*for (int i = 0; i < Cuisine.size(); i++)
			{
				cout << i+1 << ") " << AJT.CMH.Remove(',', Cuisine[i], "left") << endl;
			}*/

			cin >> Input;

			while (stoi(Input) > Cuisine.size() || stoi(Input) < 1)
			{
				cout << "Please select [1-" << Cuisine.size() << "]" << endl;
				cin >> Input;
			}

			CuisineChoice = stoi(Input) - 1;

			for (int i = 0; i < Dishes[CuisineChoice].size(); i++)
			{
				cout << Dishes[CuisineChoice][i];
			}

		}
		else
		{
			for (int i = 0; i < Cuisine.size(); i++)
			{
				cout << AJT.CMH.Remove(',', Cuisine[i], "left") << endl;

				for (int j = 0; j < Dishes[i].size(); j++)
				{
					cout << Dishes[i][j];
				}

				cout << endl;
			}
		}		
	}

	void CreateCuisine()
	{
		string Input, Temp, Command;

		MenuTitle += "New Cuisine > \n";
		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			do
			{
				cout << "Cuisine Name: ";
				cin >> Input;

				cout << "Cuisine Prefix: ";
				cin >> Temp;

				cout << endl << "Cuisine Name: " << Input << endl;
				cout << "Cuisine Prefix: " << Temp << endl;
				cout << "Is this correct? [yes/no]" << endl;
				cin >> Command;
			} while (Command != "yes" && Command == "no");
			
			Temp += "," + Input;
			Cuisine.push_back(Temp);

			Input.clear();
			Temp.clear();

			cout << endl << "Would you like to make another cuisine? [yes/no]" << endl;
			cin >> Command;

		} while (Command == "yes" && Command != "no");

		MenuTitle.clear();
	}

private:
	vector<vector<FoodItem>> Dishes;
	vector <string> Cuisine;
};

class Order
{
public:
	Order();
	
	void AddItem(FoodItem AddedItem)
	{

	}

	void ReadCustomer(string Customer)
	{

	}

private:
	vector <FoodItem> Basket;
	Customer Cust;
	Date OrderDate;
	string OrderID;
	bool Open;
	bool Delivery;
	double BasketPrice;
	double Total;
};

class RestraurantSys
{
public:
	RestraurantSys()
	{

	}
	
	void MakeOrder()
	{

	}

	void EditOrder()
	{

	}

	void WriteOrders()
	{

	}

	void WriteEmployees()
	{

	}

	void WriteAllFiles()
	{
		Bwydlen.WriteFile();
	}

	void ReadAllFiles()
	{
		Bwydlen.ReadFile();
	}

	void ReadOrders()
	{

	}

	void ReadEmployees()
	{

	}

	void DisplayMenu()
	{
		Bwydlen.DisplayMenu();
	}

	void CreateCusine()
	{
		Bwydlen.CreateCuisine();
	}

	//Temp
	void TEMPCreateDish()
	{
		Bwydlen.NewDish();
	}

private:
	vector <Order> Orders;
	//couldn't think of a better name for the menu object
	Menu Bwydlen;
	int MaxNoTakeaways;
	int NoTakeaways;
	double DeliveryCost;
};

int main()
{
	RestraurantSys RSys;

	//RSys.TEMPCreateDish();
	//RSys.DisplayMenu();

	//RSys.WriteAllFiles();
	RSys.ReadAllFiles();
	RSys.DisplayMenu();

	/*Date TestDater1, TestDater2;

	TestDater1.SetDateTime();

	TestDater2.SetDateTime();

	if (TestDater1 > TestDater2)
	{
		cout << TestDater1;
	}
	else
	{
		cout << TestDater2;
	}*/
}
