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

	void Clear()
	{
		CustID = "-1";
		Name = "Unnamed";
		Home.Clear();
		Email = "Undefined";
		PhoneNo = "Undefined";
		Loyalty = -1;
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

	friend ofstream& operator<<(ofstream& FS, const FoodItem FI)
	{
		FS << FI.FoodID << "," << FI.Name << "," << FI.Price << ",";
		FS << FI.Cuisine << "," << FI.Course << ",";
		FS << FI.Popularity << "," << FI.Availability << endl;

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
		//MenuTitle = "Menu > Dish > " + FI.Name;

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

	void MakeOrder(double DeliveryCost)
	{
		string Command; int Page;
		Order TempOrder;

		MenuTitle = "Make order > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle + " Select customer > ");
		//customer select goes here

		AJT.SCH.ScreenCleanerTM(0, MenuTitle + " collection options >");

		cout << "[pickup] or [delivery]?" << endl << "> ";
		cin >> Command;

		while (Command != "pickup" && Command != "delivery")
		{
			cout << "Please choose either [pickup] or [delivery]" << endl << "> ";
			cin >> Command;
		}

		if (Command == "pickup")
		{
			TempOrder.SetDelivery(false);
		}
		else
		{
			TempOrder.SetDelivery(true);
			TempOrder.AddToTotal(DeliveryCost);
		}

		Page = 0;
		MenuTitle = "Select Dishes > ";

		do
		{
			for (int i = 0; i < Dishes[Page].size(); i++)
			{
				AJT.SCH.ScreenCleanerTM(0, MenuTitle + Dishes[Page][0].GetCuisine());

				for (int j = 0; j < Dishes[Page].size(); j++)
				{
					cout << i + 1 << ") " << Dishes[Page][i] << endl;
				}				
			}
			cout << "Please select";

		} while (Command != "6");

			//food selection loop (calls AddItem())
	}

private:
	vector<vector<FoodItem>> Dishes;
	vector <string> Cuisine;
};

class Order
{
public:
	Order()
	{
		Clear();
	};
	
	void AddItem(FoodItem AddedItem)
	{

	}

	void SetDelivery(bool Input)
	{Delivery = Input;}

	void SetOpen(bool Input)
	{Open = Input;}

	void AddToTotal(double Input)
	{Total += Input;}

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
		BasketPrice = -1;
		Total = -1;
	}

private:
	vector <FoodItem> Basket;
	Customer Cust;
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

	void EditDeliveryCost()
	{
		MenuTitle = "Delivery cost > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "How much for delivery?" << endl << "> " << CurrencySym;
		cin >> DeliveryCost;
	}

	void MainMenu()
	{
		vector <string> Options{
			"View Menu sub-menu","Make new order","View Employee Menu",
			"View Customer menu", "Change delivery cost", "Save all files",
			"Read all files"
		};
		string Command;
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
				//return as Order object?
				Order TempOrder;
				TempOrder.MakeOrder(DeliveryCost);
				Orders.push_back(TempOrder);
				TempOrder.Clear();
				break;
			}
			case 3:
			{
				//employee menu
				break;
			}
			case 4:
			{
				
				break;
			}
			case 5:
			{
				WriteAllFiles();
				break;
			}
			case 6:
			{
				ReadAllFiles();
				break;
			}
			case 7:
			{
				Command = "exit";
				break;
			}
			default:
				break;
			}
		} while (Command != "exit");
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
	/*
	* idea time
	* what if we had a sperate selection menu /within/ Menu
	* instead of having "linker" funtions connecting 
	* Rsys to Bwydlen
	* say hello to SelectionMenu()
	*/

	RestraurantSys RSys;

	//RSys.TEMPCreateDish();
	//RSys.DisplayMenu();

	//RSys.WriteAllFiles();

	RSys.ReadAllFiles();
	RSys.MainMenu();

	//RSys.TEMPUpdatePop();
	//RSys.TEMPUpdateAvail();


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
