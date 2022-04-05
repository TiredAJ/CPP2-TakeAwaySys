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

class Customer
{
public:
	Customer()
	{
		Clear();
	}
	
	void CreateCustomer(int NoCustomers)
	{
		string Command;

		do
		{
			MenuTitle = "Create Customer > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			CustID = ("CID" + to_string(NoCustomers));

			cout << "Please enter the customer's: " << endl;
			cout << "(For optional* fields, enter [-1])" << endl;
			cout << "name: ";
			getline(cin >> ws, Name);
			cout << "Email*: ";
			getline(cin >> ws, Email);
			cout << "Phone No*: ";
			getline(cin >> ws, PhoneNo);

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Create Address");

			Home.CreateAddress();

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirm Details");
			
			cout << Name << ", " << CustID << endl;
			cout << Home;

			if (Email != "-1")
			{
				cout << "\t" << "Email: " << Email << endl;
			}

			if (PhoneNo != "-1")
			{
				cout << "\t" << "Phone No: " << PhoneNo << endl;
			}

			AJT.Graphics.Line('-', 35);

			cout << "Is this correct? [yes/no]" << endl << "> ";
			cin >> Command;

			while (Command != "yes" && Command != "no")
			{
				cout << "Please enter [yes] or [no]" << endl << "> ";
				cin >> Command;
			}

			if (Command == "yes")
			{
				return;
			}

		} while (Command != "yes");		
	}

	void Clear()
	{
		CustID = "-1";
		Name = "Unnamed";
		Home.Clear();
		Email = "Undefined";
		PhoneNo = "Undefined";
		Loyalty = 0;
	}

	string GetName()
	{return Name;}

	string GetID()
	{return CustID;}

	friend ostream& operator<<(ostream& OS, const Customer Cust)
	{
		AJT.Graphics.Line('-', 35);

		OS << Cust.Name << ", " << Cust.CustID << endl;		
		OS << Cust.Home;

		if (Cust.Email != "-1")
		{
			OS << "\t" << "Email: " << Cust.Email << endl;
		}

		if (Cust.PhoneNo != "-1")
		{
			OS << "\t" << "Phone No: " << Cust.PhoneNo << endl;
		}

		AJT.Graphics.Line('-', 35);
		
		return OS;
	}

	friend ofstream& operator<<(ofstream& Filer, const Customer Cust)
	{
		Filer << Cust.CustID << "+" << Cust.Name << "+";
		Filer << Cust.Email << "+" << Cust.PhoneNo << "+" << Cust.Loyalty;
		Filer << "+" << Cust.Home << endl;

		return Filer;
	}

	friend ifstream& operator>>(ifstream& Obtainer, Customer& Cust)
	{
		vector <string> Segments;
		string Input, Temp;
		getline(Obtainer >> ws, Input);

		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] != '+')
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

		Cust.CustID = Segments[0];
		Cust.Name = Segments[1];
		Cust.Email = Segments[2];
		Cust.PhoneNo = Segments[3];
		Cust.Loyalty = stoi(Segments[4]);
		Cust.Home.ReadAddr(Segments[5]);

		Segments.clear();

		return Obtainer;
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

	void CreateDish(string CuisineSpec)
	{
		string Temp;
		string Details[3];
		int Counter = 0;

		cout << "(* Values are -1 by default)" << endl;

		cout << "Dish Name: ";
		getline(cin >> ws, Name);

		cout << "Dish Price*: " << CurrencySym;
		cin >> Price;

		cout << "Course: ";
		getline(cin >> ws, Course);

		cout << "Expected popularity [low/med/high]: ";
		cin >> Popularity;

		cout << "Availability*: ";
		cin >> Availability;
		
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
		string Input;
		MenuTitle = "Update Popularity > " + Name;
		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Current popularity: " << Popularity << endl;
		cout << "Updated [low/med/high]: ";
		cin >> Input;

		while (Input != "high" && Input !="med" && Input != "low")
		{
			cout << "Please enter either [low][med] or [high]: ";
			cin >> Input;
		}

		Popularity = Input;

		return;
	}

	void UpdateAvail()
	{
		string Input;
		MenuTitle = "Update Availability > " + Name;
		AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

		cout << "Current Availability: " << Availability << endl;
		cout << "Updated [>1]: ";
		cin >> Input;

		while (stoi(Input) <= 1 )
		{
			cout << "Please enter a value greater than [1]: ";
			cin >> Input;
		}

		Availability = stoi(Input);

		return;
	}

	void UpdatePrice()
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

	void SetCuisine(string Cuisine)
	{this->Cuisine = Cuisine;}
	
	void SetID(string ID)
	{this->FoodID = ID;}

	string GetID()
	{return FoodID;}

	string GetName()
	{return Name;}

	double GetPrice()
	{return Price;}

	FoodItem& operator=(const FoodItem& FI2)
	{
		this->FoodID = FI2.FoodID;
		this->Name = FI2.Name;
		this->Price = FI2.Price;
		this->Cuisine = FI2.Cuisine;
		this->Course = FI2.Course;
		this->Popularity = FI2.Popularity;
		this->Availability = FI2.Availability;

		return *this;
	}

	friend ofstream& operator<<(ofstream& Filer, const FoodItem FI)
	{
		Filer << FI.FoodID << "+" << FI.Name << "+" << FI.Price << "+";
		Filer << FI.Cuisine << "+" << FI.Course << "+,";
		Filer << FI.Popularity << "+" << FI.Availability << endl;

		return Filer;
	}

	friend ifstream& operator>>(ifstream& Obtainer, FoodItem& FI)
	{
		vector <string> Segments;
		string Input, Temp;
		getline(Obtainer >> ws, Input);

		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] != '+')
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

		return Obtainer;
	}

	friend ostream& operator<<(ostream& OS, const FoodItem FI)
	{
		//MenuTitle = "Menu > Dish > " + FI.Name;

		OS << FI.Name << endl << "\tID:" << FI.FoodID << endl;
		OS << "\tCuisine: " << FI.Cuisine << endl;
		OS << "\tPrice: " << CurrencySym << setprecision(2) << fixed << FI.Price;
		OS << endl << "\tCourse: " << FI.Course << endl;
		OS << "\tPopularity: " << FI.Popularity << endl;
		OS << "\tAvailability: " << FI.Availability << endl;
		AJT.Graphics.Line('-', 45);

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

class Order
{
public:
	Order()
	{
		Clear();
	};

	Order(int ID)
	{
		OrderID = ID;
	}

	void AddItem(FoodItem AddedItem)
	{
		Basket.push_back(AddedItem);
		BasketPrice += AddedItem.GetPrice();
	}

	void SetDelivery(bool Input, double DeliveryCost)
	{
		Delivery = Input;
		this->DeliveryCost = DeliveryCost;
	}

	void SetOpen(bool Input)
	{
		Open = Input;
	}

	//tf is this for?
	void ReadCustomer(string Customer)
	{

	}

	void Clear()
	{
		Basket.clear();
		Cust.Clear();
		OrderID.clear();
		Open = true;
		Delivery = true;
		BasketPrice = 0;
		DeliveryCost = 0;
	}

	void SetID(int ID)
	{OrderID = "ODR-" + to_string(ID);}

	void SetCust(Customer Cust)
	{
		this->Cust = Cust;
	}

	int GetBasketSize()
	{return Basket.size();}

	string GetID()
	{return OrderID;}

	double GetBasketPrice()
	{return BasketPrice;}

	FoodItem GetBasketItem(int Index)
	{return Basket[Index];}

	friend ostream& operator<<(ostream& OS, const Order OR)
	{
		OS << OR.OrderID << endl;		
		OS << OR.Cust << endl;
		
		if (OR.Delivery == true)
		{
			OS << "Delivery Order" << endl;
		}
		else
		{
			OS << "Pickup Order" << endl;
		}

		for (int i = 0; i < OR.Basket.size(); i++)
		{
			OS << OR.Basket[i];
		}

		OS << "Basket Price: " << CurrencySym << setprecision(2) << fixed << OR.BasketPrice << endl;

		if (OR.Delivery == true)
		{
			OS << " Total Price: " << CurrencySym << setprecision(2) << fixed << (OR.DeliveryCost + OR.BasketPrice);
			OS << endl;
		}
		else
		{
			OS << " Total Price: " << CurrencySym << setprecision(2) << fixed << OR.BasketPrice << endl;
		}

		AJT.Graphics.Line('=', 45);

		return OS;
	}

	friend ofstream& operator<<(ofstream& OS, Order OR)
	{
		OS << OR.OrderID << "," << OR.Basket.size() << ",:";

		for (int i = 0; i < OR.Basket.size(); i++)
		{
			OS << OR.Basket[i] << ":";
		}

		OS << "+" << OR.Cust.GetID() << "+" << OR.Delivery << "+" << OR.Open << endl;

		return OS;
	}

	friend ifstream& operator>>(ifstream& IS, Order OR)
	{
		vector <string> Segments;
		string Line, Temp;

		getline(IS >> ws, Line);

		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] != ',')
			{
				Temp += Line[i];
			}
			else if (Line[i] == ':')
			{
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
			Segments.push_back(Temp);
			Temp.clear();
		}



	}

private:
	vector <FoodItem> Basket;
	Customer Cust;
	string OrderID;
	bool Open;
	bool Delivery;
	double BasketPrice;
	double DeliveryCost;
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

	string Searcher()
	{
		bool Found = false;
		string Query;

		MenuTitle += "Search > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

		cout << "Please enter either the FoodID or it's name:";
		cout << endl << "> ";

		getline(cin >> ws, Query);

		for (int i = 0; i < Dishes.size(); i++)
		{
			for (int j = 0; j < Dishes[i].size(); j++)
			{
				if (Dishes[i][j].GetName() == Query)
				{
					Found = true;
					return(to_string(i) + "," + to_string(j));
				}
				else if (Dishes[i][j].GetID() == Query)
				{
					Found = true;
					return(to_string(i) + "," + to_string(j));
				}
			}
		}

		if (Found == true)
		{
			cout << "ERROR::object found, but not returned (Searcher())" << endl;
			abort();
		}
		else
		{
			cout << "We could not find the item you were looking for, apologies" << endl;
			return("-1");
		}

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
		string Temp;
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

		cout << "Dishes saved to file, type [exit] to return to menu" << endl;
		cin >> Temp;
	}

	void NewDish()
	{
		vector <FoodItem> TempFoods;
		string Command, Input;
		int ChosenCuisine;

		MenuTitle = "New Dish >";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);
		
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

			cout << "You've chosen: " << Cuisine[stod(Command) - 1];
			ChosenCuisine = stoi(Command) - 1;

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + Cuisine[ChosenCuisine]);

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

			cout << "Is this correct? [yes/no] " << endl << "> ";
			cin >> Command;

			if (Command != "no")
			{
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
		}			
			
		} while (Command != "no" || Command == "yes");

		AJT.SCH.ScreenCleanerTM(0);
	}

	void UpdatePop()
	{
		//index in the outer, inner vectors + location of comma
		int OuterVal, InnerVal, Mid;
		string Temp, Command;
		bool Active = true;

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			MenuTitle = "Update Popularity > ";

			Temp = Searcher();

			if (Temp == "-1")
			{
				cout << "Item could not be found, Return to menu? [yes/no]" << endl;
				cin >> Command;

				if (Command == "yes")
				{
					Active = false;
					return;
				}
				else
				{
					Active = true;
				}
			}
			else
			{
				Mid = Temp.find(',');
				OuterVal = stoi(Temp.substr(0, Mid));
				InnerVal = stoi(Temp.substr(Mid+1));

				MenuTitle = "Update Popularity > " + Dishes[OuterVal][InnerVal].GetName();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle);

				Dishes[OuterVal][InnerVal].UpdatePop();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + " > Details");

				cout << "Updated: ";
				cout << Dishes[OuterVal][InnerVal];

				return;
			}			
		} while (Active == true);

		cout << "ERROR::Program escaped the loop" << endl;
		abort();
		
	}

	void UpdateAvail()
	{
		int OuterVal, InnerVal, Mid;
		string Temp, Command;
		bool Active = true;

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			MenuTitle = "Update Availability > ";

			Temp = Searcher();

			if (Temp == "-1")
			{
				cout << "Item could not be found, Return to menu? [yes/no]" << endl;
				cin >> Command;

				if (Command == "yes")
				{
					Active = false;
					return;
				}
				else
				{
					Active = true;
				}
			}
			else
			{
				Mid = Temp.find(',');
				OuterVal = stoi(Temp.substr(0, Mid));
				InnerVal = stoi(Temp.substr(Mid + 1));

				MenuTitle = "Update Availability > " + Dishes[OuterVal][InnerVal].GetName();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle);

				Dishes[OuterVal][InnerVal].UpdateAvail();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + " > Details");

				cout << "Updated: ";
				cout << Dishes[OuterVal][InnerVal];

				return;
			}


		} while (Active == true);
	}

	void EditDish()
	{
		int OuterVal, InnerVal, Mid;
		string Temp, Command;
		bool Active = true;
		FoodItem TempDish;

		MenuTitle = "Edit Dish > ";

		do
		{
			TempDish.Clear();

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			Temp = Searcher();

			if (Temp == "-1")
			{
				cout << "Item could not be found, Return to menu? [yes/no]" << endl;
				cin >> Command;

				if (Command == "yes")
				{
					Active = false;
					return;
				}
				else
				{
					Active = true;
				}
			}
			else
			{
				Mid = Temp.find(',');
				OuterVal = stoi(Temp.substr(0, Mid));
				InnerVal = stoi(Temp.substr(Mid + 1));

				MenuTitle = "Edit Dish > ";

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + Dishes[OuterVal][InnerVal].GetName());

				cout << "Current Details: " << endl;
				cout << Dishes[OuterVal][InnerVal] << endl;

				TempDish.CreateDish(Cuisine[OuterVal] + "," + to_string(Dishes[OuterVal].size()));

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Updated Details");

				cout << TempDish;

				Dishes[OuterVal][InnerVal] = TempDish;

				do
				{
					cout << "Return to menu? [yes/no]" << endl << "> ";
					cin >> Command;

					if (Command == "yes")
					{return;}

				} while (true);


				return;
			}


		} while (Active == true);
	}

	void DeleteDish()
	{
		int OuterVal, InnerVal, Mid;
		string Temp, Command;
		bool Active = true;

		MenuTitle = "Delete Dish > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			Temp = Searcher();

			vector <FoodItem> TempFoods;

			if (Temp == "-1")
			{
				cout << "Item could not be found, Return to menu? [yes/no]" << endl;
				cin >> Command;

				if (Command == "yes")
				{
					Active = false;
					return;
				}
				else
				{
					Active = true;
				}
			}
			else
			{
				Mid = Temp.find(',');
				OuterVal = stoi(Temp.substr(0, Mid));
				InnerVal = stoi(Temp.substr(Mid + 1));

				MenuTitle = "Delete Dish > ";

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + Dishes[OuterVal][InnerVal].GetName());

				cout << Dishes[OuterVal][InnerVal];

				cout << "Is this the correct dish? [yes/no]" << endl << "> ";
				cin >> Command;

				while (Command != "yes" && Command != "no")
				{
					cout << "Please enter [yes] or [no]" << endl << "> ";
					cin >> Command;
				}

				if (Command == "yes")
				{
					Dishes[OuterVal][InnerVal].SetID("-1");

					for (int i = 0; i < Dishes[OuterVal].size(); i++)
					{
						if (Dishes[OuterVal][i].GetID() != "-1")
						{
							TempFoods.push_back(Dishes[OuterVal][i]);
						}						
					}
					Dishes[OuterVal] = TempFoods;
				}
				else
				{
					return;
				}

				return;
			}


		} while (Active == true);
	}

	void DisplayMenu()
	{
		string Command, Input;
		int CuisineChoice, CurrentPg;
			
		Command.clear();
		CurrentPg = 0;

		MenuTitle = "Menu Browse > Page ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + to_string(CurrentPg + 1));

			cout << AJT.CMH.Remove(',', Cuisine[CurrentPg], "left") << endl;

			if (Dishes[CurrentPg].empty() != true)
			{
				for (int i = 0; i < Dishes[CurrentPg].size(); i++)
				{
					cout << Dishes[CurrentPg][i];
				}
			}
			else
			{
				cout << endl << "*No dishes*" << endl;
			}

			cout << endl;
			cout << "Which page would you like to visit?" << endl << "[1-";
			cout << Cuisine.size() << "] or [exit] to leave" << endl << "> ";
			cin >> Command;

			if (Command == "exit")
			{return;}

			while (stoi(Command) > Cuisine.size() || stoi(Command) < 1)
			{
				cout << "Please enter a value between [1-" << Cuisine.size();
				cout << "] or type [exit] to leave" << endl << "> ";
				cin >> Command;
			}

			CurrentPg = stoi(Command) -1;

		} while (Command != "exit");
	}		

	void CreateCuisine()
	{
		string Input, Temp, Command;
		vector <FoodItem> TempFoods;

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

			Dishes.push_back(TempFoods);

			Input.clear();
			Temp.clear();

			cout << endl << "Would you like to make another cuisine? [yes/no]" << endl;
			cin >> Command;

		} while (Command == "yes" && Command != "no");

		MenuTitle.clear();
	}

	void EditDetailsMenu()
	{
		string Command; int Choice;
		vector <string> Options{ "Edit Item","Edit Popularity","Edit Availability","Delete Item"};

		MenuTitle = "Edit Details Menu > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			AJT.Graphics.DisplayOptions(Options, 1);
			cin >> Command;

			if (Command == "exit")
			{
				return;
			}

			while (stoi(Command) < 1 || stoi(Command) > Options.size() + 1)
			{
				cout << "Please enter a value between [1-" << Options.size() + 1 << "]";
				cout << endl << "> ";
				cin >> Command;
			}

			Choice = stoi(Command);

			switch (Choice)
			{
			case 1:
			{
				EditDish();
				break;
			}
			case 2:
			{
				UpdatePop();
				break;
			}
			case 3:
			{
				UpdateAvail();
				break;
			}
			case 4:
			{
				DeleteDish();
				break;
			}
			case 5:
			{
				return;
				break;
			}
			default:
			{
				cout << "ERROR::Outside Switch Case boundaries" << endl;
				abort();
				break;
			}
			}

		} while (Command != "exit");

		return;
	}

	void SelectionMenu()
	{
		string Command; int Choice;
		vector <string> Options{
			"Browse Menu", "Edit Item", "Add Dish", "Add Cuisine",
			"Save Menu to file"
		};

		MenuTitle = "Menu Menu > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			AJT.Graphics.DisplayOptions(Options, 1);
			cin >> Command;

			if (Command == "Exit")
			{return;}

			while (stoi(Command) < 1 || stoi(Command) > Options.size() +2)
			{
				cout << "Please enter a value between [1-" << Options.size() + 2 << "]";
				cout << endl << "> ";
				cin >> Command;
			}

			Choice = stoi(Command);

			switch (Choice)
			{
			case 1:
			{
				DisplayMenu();
				break;
			}
			case 2:
			{
				EditDetailsMenu();
				break;
			}
			case 3:
			{
				NewDish();
				break;
			}
			case 4:
			{
				CreateCuisine();
				break;
			}
			case 5:
			{
				WriteFile();
				break;
			}
			case 6:
			{
				Command = "exit";
				break;
			}
			default:
			{
				cout << "ERROR::Outside Switch Case boundaries" << endl;
				abort();
				break;
			}
			}

		} while (Command != "exit");

		return;
	}

	Order CreateOrder()
	{
		string Command, Temp;
		int Page, Outer, Inner;
		Order TempOrder;

		Page = 0;
		MenuTitle = "Select Dishes > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			cout << "Would you like to search for an item? [yes/no/exit]" << endl << "> ";
			cin >> Command;

			while (Command != "yes" && Command != "no" && Command != "exit")
			{
				cout << "Please enter either [yes] or [no]" << endl << "> ";
				cin >> Command;
			}

			if (Command == "yes")
			{
				Temp = Searcher();
				Outer = stoi(AJT.CMH.Remove(',', Temp, "left"));
				Inner = stoi(AJT.CMH.Remove(',', Temp, "right"));

				TempOrder.AddItem(Dishes[Outer][Inner]);
			}
			else if (Command == "exit")
			{
				break;
			}
			else
			{
				do
				{
					AJT.SCH.ScreenCleanerTM(0, MenuTitle + Dishes[Page][0].GetCuisine());

					for (int j = 0; j < Dishes[Page].size(); j++)
					{
						cout << j + 1 << ") " << Dishes[Page][j] << endl;
					}

					cout << "Page " << Page +1 << " of " << Cuisine.size() << endl;
					cout << "Please select [1-" << Dishes[Page].size() << "]";
					cout << ", type [page #] with the page you'd like to visit";
					cout << "or type [exit] to return" << endl << "> ";
					getline(cin >> ws, Command);

					if (Command[0] == 'p')
					{
						Page = stoi(Command.substr(5)) -1;
					}
					else if (Command == "exit")
					{
						break;
					}
					else if (stoi(Command) > 0)
					{
						while (stoi(Command) < 0 && stoi(Command) > Dishes[Page].size() + 1)
						{
							cout << "Please enter either [page #] or an item number" << endl << "> ";
							cin >> Command;
						}
						TempOrder.AddItem(Dishes[Page][stoi(Command) - 1]);
					}

				} while (Command != "exit");				
			}
		} while (Command != to_string(Dishes[Page].size() + 1));

		cout << "Would you like to view the basket? [yes/no]" << endl << "> ";
		cin >> Command;

		while (Command != "yes" && Command != "no")
		{
			cout << "Please enter either [yes] or [no]" << endl << "> ";
			cin >> Command;
		}

		if (Command == "yes")
		{
			for (int i = 0; i < TempOrder.GetBasketSize(); i++)
			{
				cout << TempOrder.GetBasketItem(i);
			}
			
			cout << "Basket Total: " << CurrencySym;
			cout << setprecision(2) << fixed << TempOrder.GetBasketPrice() << endl;
		}

		cout << "Type [exit] to return to view order" << endl << "> ";
		cin >> Command;

		return TempOrder;
	}
	//helo
private:
	vector<vector<FoodItem>> Dishes;
	vector <string> Cuisine;
};

class RestraurantSys
{
public:
	RestraurantSys()
	{
		DeliveryCost = 2.5;
	}
	
	Order MakeOrder()
	{
		string Command; int Temp; bool Valid;
		Customer TempCust;
		Order CurrentOrder;
		
		do
		{
			MenuTitle = "Make an order > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Existing Customer?");

			cout << "Is the order for an existing customer? [yes/no]" << endl << "> ";
			cin >> Command;

			while (Command != "yes" && Command != "no")
			{
				cout << "Please enter either [yes] or [no]" << endl << "> ";
				cin >> Command;
			}

			if (Command == "yes")
			{
				Temp = CustSearcher();

				if (Temp == -1)
				{
					cout << "User could not be found" << endl;
					return CurrentOrder;
				}
				else
				{
					TempCust = Customers[Temp];
				}
			}
			else if (Command == "no")
			{
				if (Customers.empty() == true)
				{
					TempCust.CreateCustomer(0);
				}
				else
				{
					TempCust.CreateCustomer(Customers.size());
				}
			}
			
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + " collection options >");

			do
			{
				cout << "[pickup] or [delivery]?" << endl << "> ";
				cin >> Command;

				while (Command != "pickup" && Command != "delivery")
				{
					cout << "Please choose either [pickup] or [delivery]" << endl << "> ";
					cin >> Command;
				}

				if (Command == "pickup" && MaxNoTakeaways < 1)
				{
					cout << "Max number of takeaways reached" << endl;
					cout << "Would you like to change the order type? [yes/no]" << endl << "> ";
					cin >> Command;

					while (Command != "yes" && Command != "no")
					{
						cout << "Please enter either [yes] or [no]" << endl << "> ";
						cin >> Command;
					}

					if (Command == "yes")
					{
						Valid = false;
					}
					else
					{
						CurrentOrder.Clear();
						CurrentOrder.SetID(-1);

						return CurrentOrder;
					}
				}
			} while (Valid == false);
			

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + " Select Foods");

			CurrentOrder = Bwydlen.CreateOrder();

			CurrentOrder.SetCust(TempCust);


			if (Command == "pickup")
			{
				CurrentOrder.SetDelivery(false, DeliveryCost);
			}
			else
			{
				CurrentOrder.SetDelivery(true, DeliveryCost);
			}

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation");

			CurrentOrder.SetID(Orders.size());

			cout << CurrentOrder;

			cout << endl << "Is this correct? [yes/no]" << endl << "> ";
			cin >> Command;

			while (Command != "yes" && Command != "no")
			{
				cout << "Please enter either [yes] or [no]" << endl << "> ";
				cin >> Command;
			}

			if (Command == "yes")
			{
				Orders.push_back(CurrentOrder);
			}
		} while (Command == "no");
		
		return CurrentOrder;
	}
	
	void WriteAllFiles()
	{
		string Command;
		Bwydlen.WriteFile();

		//write employees
		//write orders
		WriteCustomers();

		MenuTitle = "Write Files > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Files written, type [exit] to return" << endl << "> ";
		cin >> Command;
	}

	void ReadAllFiles()
	{
		string Command;
		Bwydlen.ReadFile();
		//read employees
		//read orders?
		ReadCustomers();

		MenuTitle = "Read Files > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Files read, type [exit] to return" << endl << "> ";
		cin >> Command;
	}

	void ReadCustomers()
	{
		ifstream Reader;
		Customer TempCust;
		int NoCusts;
		string Command;

		Reader.open("Customers.txt");

		if (Reader.is_open() != true)
		{
			CreateTempFiles(2);
		}
		else
		{
			Reader >> NoCusts;

			for (int i = 0; i < NoCusts; i++)
			{
				Reader >> TempCust;
				Customers.push_back(TempCust);
				TempCust.Clear();
			}
		}
		Reader.close();
		return;
	}

	void WriteCustomers()
	{
		ofstream Writer("Customers.txt");

		Writer << Customers.size();

		for (int i = 0; i < Customers.size(); i++)
		{
			Writer << Customers[i];
		}

		Writer.close();
	}

	void WriteOrders()
	{
		ofstream Writer("Orders.txt");
		Writer << Orders.size();

		for (int i = 0; i < Orders.size(); i++)
		{
			Writer << Orders[i];
		}

		Writer.close();
	}

	void DisplayMenu()
	{
		Bwydlen.DisplayMenu();
	}

	void CreateCusine()
	{
		Bwydlen.CreateCuisine();
	}

	void EditDeliveryCost()
	{
		MenuTitle = "Delivery cost > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "How much for delivery?" << endl << "> " << CurrencySym;
		cin >> DeliveryCost;
	}

	void BrowseCustomers()
	{
		string Command;

		MenuTitle = "Browse Customers > ";
		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		for (int i = 0; i < Customers.size(); i++)
		{
			cout << Customers[i];
		}

		cout << "Enter [exit] to return to menu" << endl << "> ";
		cin >> Command;

		return;
	}

	void CreateTempFiles(int Option)
	{
		ofstream Writer;
		
		switch (Option)
		{
		case 1:
		{
			Writer.open("Employees.txt");
			Writer.close();
			break;
		}
		case 2:
		{
			Writer.open("Customers.txt");
			Writer.close();
			break;
		}
		case 3:
		{
			Writer.open("Orders.txt");
			Writer.close();
			break;
		}
		case 4:
		{
			Writer.open("Dishes.txt");
			Writer.close();
			break;
		}
		default:
			break;
		}
	}

	int CustSearcher()
	{
		bool Found = false;
		string Query, Command;

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Search Customers > ");

			cout << "Please enter either the CustID or their name:";
			cout << endl << "> ";

			getline(cin >> ws, Query);

			for (int i = 0; i < Customers.size(); i++)
			{
				if (Customers[i].GetID() == Query)
				{
					Found = true;
					return i;
				}
				else if (Customers[i].GetName() == Query)
				{
					Found = true;
					return i;
				}
			}

			if (Found == false)
			{
				cout << "The searched customer could not be found" << endl;
				cout << "Would you like to try again? [yes/no]" << endl << "> ";
				cin >> Command;

				while (Command != "yes" && Command != "no")
				{
					cout << "Please enter [yes] or [no]" << endl << "> ";
					cin >> Command;
				}

				if (Command == "yes")
				{
					Found = false;
				}
				else
				{
					return -1;
				}
			}
		} while (Found == false);
		
	}

	void CloseOrder()
	{
		string Command;
		bool Valid = false;
		int Index;
		do
		{
			MenuTitle = "Close an order > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			for (int i = 0; i < Orders.size(); i++)
			{
				cout << i + 1 << ") " << Orders[i].GetID() << endl;
			}

			cout << "Please type either [view #] or [close #] where # is between [1-" << Orders.size() << "]";
			cout << " or type [exit] to leave";
			cout << endl << "> ";
			cin >> Command;

			if (Command[0] == 'e')
			{
				return;
			}
			else if (Command[0] == 'v')
			{
				Index = stoi(Command.substr(5));
				cout << Orders[Index];

				cout << endl << "Is this the correct order? [yes/no]" << endl << "> ";
				cin >> Command;

				while (Command != "yes" && Command != "no")
				{
					cout << "Please enter either [yes] or [no]" << endl << "> ";
					cin >> Command;
				}

				if (Command == "yes")
				{
					Orders[Index].SetOpen(false);
					return;
				}
				else
				{
					Valid = false;
				}

			}
			else if (Command[0] == 'c')
			{
				Index = stoi(Command.substr(6));
				Orders[Index].SetOpen(false);
			}
			else
			{
				cout << "Please enter either [view #], [close #] or [exit]" << endl;
				cin >> Command;
			}
		} while (Valid == false);		
	}

	void MainMenu()
	{
		vector <string> Options{
			"View Menu sub-Menu","Make New Order","Close Order","View Employee sub-Menu",
			"View Customer sub-Menu", "Misc sub-menu",
		};
		string Command;
		Order TempOrder;

		do
		{
			MenuTitle = "Main Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			while (stoi(Command) < 1 || stoi(Command) > Options.size() + 1)
			{
				cout << "Please enter a value between [1-" << Options.size() + 1 << "] ";
				cout << endl << "> ";
				cin >> Command;
			}

			switch (stoi(Command))
			{
			case 1:
			{
				Bwydlen.SelectionMenu();
				break;
			}
			case 2:
			{
				TempOrder = MakeOrder();

				if (TempOrder.GetID() != "-1")
				{
					Orders.push_back(TempOrder);
				}				
				break;
			}
			case 3:
			{
				CloseOrder();
				break;
			}
			case 4:
			{
				//employee menu
				break;
			}
			case 5:
			{
				CustomerMenu();
				break;
			}
			case 6:
			{
				MiscMenu();
				break;
			}
			case 7:
			{
				cout << "Would you like to save your files first? [yes/no]" << endl << "> ";
				cin >> Command;

				while (Command != "yes" && Command != "no")
				{
					cout << "Please enter either [yes] or [no]" << endl << "> ";
					cin >> Command;
				}

				if (Command == "yes")
				{
					WriteAllFiles();
				}

				Command = "exit";
				break;
			}
			default:
				break;
			}
		} while (Command != "exit");
	}

	void CustomerMenu()
	{
		vector <string> Options{"View Customers","Create Customer","Edit Customer"};
		string Command;

		do
		{
			MenuTitle = "Customer Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			while (stoi(Command) < 1 || stoi(Command) > Options.size() + 1)
			{
				cout << "Please enter a value between [1-" << Options.size() + 1 << "] ";
				cout << endl << "> ";
				cin >> Command;
			}

			switch (stoi(Command))
			{
			case 1:
			{
				BrowseCustomers();
				break;
			}
			case 2:
			{
				Customer TempCust;

				if (Customers.empty() == true)
				{
					TempCust.CreateCustomer(0);
				}
				else
				{
					TempCust.CreateCustomer(Customers.size());
				}
				Customers.push_back(TempCust);
				TempCust.Clear();
				break;
			}
			case 3:
			{
				//CustSearcher();
				break;
			}
			case 4:
			{
				Command = "exit";
				break;
			}
			default:
				break;
			}
		} while (Command != "exit");
	}

	void MiscMenu()
	{
		vector <string> Options{
			"Change Delivery Cost", "Change Maximum Takeaway Orders","Save All Files",
			"Read All Files"
		};
		string Command;

		do
		{
			MenuTitle = "Misc Sub-Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			while (stoi(Command) < 1 && stoi(Command) > Options.size()+1)
			{
				cout << "Please enter between [1-" << Options.size() + 1 << "]";
				cout << endl << "> ";
				cin >> Command;
			}

			switch (stoi(Command))
			{
			case 1:
			{
				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Change delivery cost");

				cout << "Current Delivery price: " << CurrencySym;
				cout << setprecision(2) << fixed << DeliveryCost << endl;
				cout << "Please enter a new price: " << CurrencySym;
				getline(cin >> ws, Command);

				DeliveryCost = stod(Command);
				break;
			}
			case 2:
			{
				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Change No. orders");

				cout << "Current number of max orders: " << MaxNoTakeaways << endl;
				cout << "Please enter new max: ";
				cin >> Command;

				while (stoi(Command) <= 1)
				{
					cout << "Please enter a value greater than 1: ";
					cin >> Command;

					MaxNoTakeaways = stoi(Command);
				}

				break;
			}
			case 3:
			{
				WriteAllFiles();
				break;
			}
			case 4:
			{
				ReadAllFiles();
				break;
			}
			case 5:
			{
				return;
			}
			default:
				break;
			}

		} while (Command != "exit");
	}

private:
	vector <Order> Orders;
	vector <Employee> Employees;
	vector <Customer> Customers;
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

	//RSys.ReadAllFiles();
	RSys.MainMenu();
}
