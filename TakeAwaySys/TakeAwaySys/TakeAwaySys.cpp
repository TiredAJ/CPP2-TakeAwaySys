#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "Address.h"
#include "FoodItem.h"
#include "Graphics.h"

using namespace std;

void ScreenCleanerTM(int);
void ScreenCleanerTM(int, string);

Graphics GHandler;

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

				ScreenCleanerTM(0, (MenuTitle + "\n"));

				cout << "Cuisine Name: ";
				cin >> Input;

				cout << "Cuisine Prefix";
				cin >> Temp;

				Temp = Temp + "," + Input;

				Command.clear();

				cout << endl << "New Cuisine: " << Input << endl;
				cout << "Is this correct? [yes/no]" << endl;
				cin >> Command;
			} while (Command != "yes");

			Cuisine.push_back(Input);
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

		MenuTitle = "New Dish >";

		Input.clear();
		ScreenCleanerTM(0, MenuTitle + "\n\n");

		if (Cuisine.size() == 0)
		{
			cout << "There are no cuisines available, please make a new cuisine first" << endl;
			return;
		}

		cout << "Please choose a cuisine" << endl;
		GHandler.DisplayOptions(Cuisine,0);
		cin >> Command;
		cout << "You've chosen:" << Cuisine[stod(Command) - 1];

		ScreenCleanerTM(0, MenuTitle + ("\nCuisine: " + Cuisine[stod(Command) - 1] + "\n"));

		cout << "Dish Name: ";
		cin >> Input;

		cout << ""

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

void ScreenCleanerTM(int Option)
{
	system("cls");
}

void ScreenCleanerTM(int Option, string Keeps)
{
	system("cls");
	cout << Keeps << endl;

}