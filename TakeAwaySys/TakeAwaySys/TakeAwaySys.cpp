//Consolas - 20pt
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Employee.h"
#include "Address.h"
#include "FoodItem.h"
#include "Graphics.h"
#include "ScrClnTM.h"

using namespace std;

//define the handlers on a per-class basis?
ScrClnTM SCHandler;
Graphics GHandler;
const string CurrencySym = "\x9C";
string MenuTitle;

class CommaRemover
{
public:
	CommaRemover()
	{};

	string Remove(char Removable, string Input, string Option) //[left/right]
	{
		string Temp, Result;
		Temps.clear();

		for (int i = 0; i < Input.length(); i++)
		{
			if (Input[i] != Removable)
			{
				Temp += Input[i];
			}
			else if (Input[i] == Removable)
			{
				Temps.push_back(Temp);
				Temp.clear();
			}
			
		}
		Temps.push_back(Temp);

		for (int j = 0; j < Temps.size(); j++)
		{
			if (Option == "left")		//removes first section
			{
				if (j != 0)
				{
					Result += Temps[j];
				}
			}
			else if (Option == "right")		//removes last section
			{
				if (j != Temps.size())
				{
					Result += Temps[j];
				}
			}

		}

		return Result;
	}

private:
	vector <string> Temps;
};

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

		ScrClnTM();
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

class Menu
{
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
		int NoDishes;

		Reader.open("Dishes.txt");

		Reader >> NoDishes;

		for (int i = 0; i < NoDishes; i++)
		{
			Reader >> TempFood;
			Dishes.push_back(TempFood);
			TempFood.Clear();
		}
		Reader.close();
		for (int i = 0; i < Dishes.size(); i++)
		{

		}
	}

	void WriteFile()
	{
		ofstream Writer;
		Writer.open("Dishes.txt");

		Writer << Dishes.size() << endl;

		for (int i = 0; i < Dishes.size(); i++)
		{
			Writer << Dishes[i];
		}
		Writer.close();
	}

	void NewDish()
	{
		string Command, Input, Temp;

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

		MenuTitle += "New Cuisine \n";

		//double Price;

		Input.clear();
		
		do
		{
			MenuTitle = "New Dish > ";
			SCHandler.ScreenCleanerTM(0, MenuTitle + "Choose Cuisine" + "\n");

			if (Cuisine.size() == 0)
			{
				cout << "There are no cuisines available, please make a new cuisine first" << endl;
				return;
			}

			FoodItem TempFood;

			cout << "Please choose a cuisine" << endl;
			GHandler.DisplayOptions(Cuisine, 0);
			cin >> Command;
			cout << "You've chosen:" << Cuisine[stod(Command) - 1];

			SCHandler.ScreenCleanerTM(0, MenuTitle + (Cuisine[stod(Command) - 1] + "\n"));

			TempFood.CreateDish(Cuisine[stod(Command) - 1] + "," + to_string(Dishes.size()));

			SCHandler.ScreenCleanerTM(0, MenuTitle + " Display Dish");

			TempFood.DisplayDish();

			Dishes.push_back(TempFood);

			cout << "Would you like to make another dish? [yes/no]" << endl;
			cin >> Command;
			
		} while (Command != "no" || Command == "yes");

		SCHandler.ScreenCleanerTM(0);		
	}

	void UpdatePop()
	{

	}

	void UpdateAvail()
	{

	}

	void DisplayMenu() //replace with operator overload?
	{
		string Command, Input;

		cout << "Would you like to browse a specific cuisine? [yes/no]: ";
		cin >> Command;

		while (Command != "yes" && Command != "no")
		{
			cout << "Please enter [yes] or [no]: ";
			cin >> Command;
		}

		if (Command == "yes")
		{
			for (int i = 0; i < Cuisine.size(); i++)
			{
				cout << Cuisine[i];
			}

			cout << "Please select [1-" << Cuisine.size() << "]" << endl;
			cin >> Command;

			for (int i = 0; i < Dishes.size(); i++)
			{
				if (Cuisine[stod(Command)] == Dishes[i].GetCuisine())
				{
					Dishes[i].DisplayDish();
				}

			}

		}
		else
		{
			for (int i = 0; i < Cuisine.size(); i++)
			{
				cout << endl << Cuisine[i] << endl;
				for (int j = 0; j < Dishes.size(); j++)
				{
					if (Dishes[j].GetCuisine() == CRHandler.Remove(',',Cuisine[i],"left"))
					{
						Dishes[j].DisplayDish();
					}
				}
			}

			for (int i = 0; i < Dishes.size(); i++)
			{
				Dishes[i].DisplayDish();
			}
		}
		
	}

	void CreateCuisine()
	{
		string Input, Temp, Command;

		MenuTitle += "New Cuisine > \n";
		do
		{
			SCHandler.ScreenCleanerTM(0, MenuTitle);

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
	vector <FoodItem> Dishes;
	vector <string> Cuisine;

	CommaRemover CRHandler;
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
