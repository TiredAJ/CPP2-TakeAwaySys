//Consolas - 20pt
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "Address.h"
#include "FoodItem.h"
#include "Graphics.h"
#include "ScrClnTM.h"

using namespace std;

ScrClnTM SCHandler;
Graphics GHandler;
const string CurrencySym = "\x9C";
string MenuTitle;

class CommaRemover
{
public:
	CommaRemover()
	{
		Temp = "";
		Result = "";
	};

	string Remove(char Removable, string Input, string Option) //[left/right]
	{


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
		}
		return Result;
	}

private:
	vector <string> Temps; string Temp, Result;
};

class Date
{
public:
	Date();

	void SetTime()
	{
		do
		{
			cout << "Please enter the current: " << endl;
			cout << "Hour (24hr): ";
			cin >> Input;

			while (stoi(Input) > 24 || stoi(Input) < 0)
			{
				cout << "Please enter a value between [0] and [24]: ";
				cin >> Input;
			}
			Hour = stoi(Input);
			Input.clear();

			cout << "Minute: ";
			cin >> Input;

			while (stoi(Input) > 60 || stoi(Input) < 0)
			{
				cout << "Please enter a value between [0] and [60]: ";
				cin >> Input;
			}
			Minute = stoi(Input);
			Input.clear();

			cout << "Confirm time? [yes/no]" << endl << "> ";
			cin >> Input;
		} while (Input == "no");
	}
	
	void SetDate()
	{
		do
		{
			cout << "Please only enter numerical values" << endl;
			cout << "Please enter the:" << endl;
			cout << "Year: ";
			cin >> Year;

			cout << "Month: ";
			cin >> Input;

			while (stoi(Input) > 12 || stoi(Input) < 1)
			{
				cout << "Please enter a value between [1] and [12]: ";
				cin >> Input;
			}
			Month = stoi(Input);
			Input.clear();

			cout << "Day: ";
			cin >> Input;

			do		//working here pal
			{
				if (stoi(Input) != MonthDays[Month-1])
				{
					cout << "Month " << Month << " only has " << MonthDays[Month-1];
					cout << "Please enter a value between [1] and [" << MonthDays[Month-1] << "]";
				}

			} while (true);

			cout << "Confirm Date? [yes/no]" << endl << "> ";
			cin >> Input;
		} while (Input == "no");
	}

	void SetDateTime()
	{
		SetTime();
		SetDate();
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
		else if (this->Month < D2.Month)
		{return true;}
		else if (this->Day < D2.Day)
		{return true;}
		else if (this->Hour < D2.Day)
		{return true;}
		else if (this->Minute < D2.Minute)
		{return true;}
		else
		{return false;}
	}

	string GetDate()
	{
		Temp = Hour + ":" + Minute;
		Temp += " " + Day + '/' + Month + '/' + Year;
		return Temp;
	}

	void SplitDate(string Input)
	{

	}

private:
	int Day;
	int Month;
	int Year;
	int Minute;
	int Hour;

	int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	string Input, Temp;
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

	}

	void WriteFile()
	{

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
				cout << Cuisine[i] << endl;
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

	}

	void ReadAllFiles()
	{

	}

	void ReadOrders()
	{

	}

	void ReadEmployees()
	{

	}

	void DisplayMenu()
	{
		LeMenu.DisplayMenu();
	}

	void CreateCusine()
	{
		LeMenu.CreateCuisine();
	}

	//Temp
	void TEMPCreateDish()
	{
		LeMenu.NewDish();
	}

private:
	vector <Order> Orders;
	Menu LeMenu;
	int MaxNoTakeaways;
	int NoTakeaways;
	double DeliveryCost;
};

int main()
{
	RestraurantSys RSys;

	RSys.TEMPCreateDish();
	RSys.DisplayMenu();

}
