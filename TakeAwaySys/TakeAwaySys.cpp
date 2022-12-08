#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "Address.h"
using namespace std;

class Customer
{
public:
	Customer()
	{
	
	}

	~Customer();

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

	}

	~FoodItem();

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
public:
	Menu()
	{

	}
	~Menu();

	void Searcher()
	{

	}

private:
	vector <FoodItem> Dishes;
};

class Order
{
public:
	Order();
	~Order();

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
	~RestraurantSys();

private:
	vector <Order> Orders;
	int MaxNoTakeaways;
	int NoTakeaways;
	double DeliveryCost;
};


int main()
{
	//RestraurantSys RSys;

}
