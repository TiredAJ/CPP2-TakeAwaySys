#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "Address.h"
#include "FoodItem.h"
#include "Graphics.h"

using namespace std;

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

	}

	void UpdatePop()
	{

	}

	void UpdateAvail()
	{

	}

private:
	vector <FoodItem> Dishes;
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

private:
	vector <Order> Orders;
	int MaxNoTakeaways;
	int NoTakeaways;
	double DeliveryCost;
};

int main()
{
	RestraurantSys RSys;

}
