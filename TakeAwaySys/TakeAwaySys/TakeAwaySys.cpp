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
		string Command, Input, Temp, MenuTitle;
		FoodItem TempFood;

		cout << "New Dish" << endl;
		
		cout << "Would you like to add a new cuisine? [yes/no]" << endl << "> ";
		cin >> Command;

		while (Command != "yes" && Command != "no")
		{
			cout << "Please enter [yes] or [no]" << endl << "> ";
			cin >> Command;
		}

		
		if (Command == "yes")
		{
			do
			{
				Input.clear();

				MenuTitle = "New Dish > New Cuisine";

				SCHandler.ScreenCleanerTM(0, (MenuTitle + "\n"));

				cout << "Cuisine Name: ";
				cin >> Input;

				cout << "Cuisine Prefix: ";
				cin >> Temp;			

				Command.clear();

				cout << endl << "New Cuisine: " << Input;
				cout << endl << "Prefix: " << Temp << endl;
				cout << "Is this correct? [yes/no]" << endl;
				cin >> Command;

				Temp = Temp + "," + Input;
			} while (Command != "yes");

			Cuisine.push_back(Temp);
			Input.clear();

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

		MenuTitle = "New Dish > ";

		double Price;

		Input.clear();
		SCHandler.ScreenCleanerTM(0, MenuTitle + "\n\n");

		if (Cuisine.size() == 0)
		{
			cout << "There are no cuisines available, please make a new cuisine first" << endl;
			return;
		}

		cout << "Please choose a cuisine" << endl;
		GHandler.DisplayOptions(Cuisine, 0);
		cin >> Command;
		cout << "You've chosen:" << Cuisine[stod(Command) - 1];

		SCHandler.ScreenCleanerTM(0, MenuTitle + (Cuisine[stod(Command) - 1] + "\n"));

		TempFood.CreateDish(Cuisine[stod(Command) - 1] + "," + to_string(Dishes.size()));

		TempFood.DisplayDish();
	}

	void UpdatePop()
	{

	}

	void UpdateAvail()
	{

	}

private:
	vector <FoodItem> Dishes;
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

}
