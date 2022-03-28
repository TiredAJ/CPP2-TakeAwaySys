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
#include "CommaRemover.h"

using namespace std;

CommaRemover CRHandler;
ScrClnTM SCHandler;
Graphics GHandler;
const string CurrencySym = "\x9C";
string MenuTitle;

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

		double Price;

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
	//work out nicer way to handle  cuisine name and prefix
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
	string OrderID;
	bool Open;
	vector <FoodItem> Basket;
	Customer Cust;
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
