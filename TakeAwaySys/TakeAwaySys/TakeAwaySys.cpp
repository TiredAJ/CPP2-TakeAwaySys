/*Consolas - 20pt*/
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

/*allows the pound symbol to be accessed throughout the program*/
const string CurrencySym = "\x9C";
/*exclusive non-constant global variable for persistent titles*/
string MenuTitle;

class Customer
{
public:
	Customer()
	{
		Clear();
	}

	void CreateCustomer(int NoCustomers)
	{/*allows for the creatrion of a customer, NoCustomers is used to assign
	 the numerical part of the Customer's ID*/
		string Command;

		do
		{
			/*first use of persistent titling,*/
			MenuTitle = "Create Customer > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			CustID = ("CID" + to_string(NoCustomers));

			cout << "Please enter the customer's: " << endl;
			cout << "(Optional* fields, enter [-1] to skip)" << endl;
			cout << "name: ";
			getline(cin >> ws, Name);
			cout << "Email*: ";
			getline(cin >> ws, Email);
			cout << "Phone No*: ";
			getline(cin >> ws, PhoneNo);

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Create Address");

			/*creates the home address for the customer*/
			Home.CreateAddress();

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirm Details");

			cout << Name << ", " << CustID << endl;
			cout << Home;

			/*checks if Email and PhoneNo should be displayed*/
			if (Email != "-1")
			{
				cout << "\t" << "Email: " << Email << endl;
			}

			if (PhoneNo != "-1")
			{
				cout << "\t" << "Phone No: " << PhoneNo << endl;
			}

			/*use of .Line() to generate a line of dashes*/
			AJT.Graphics.Line('-', 35);

			cout << "Is this correct? [yes/no]" << endl << "> ";
			cin >> Command;

			/*validity checker*/
			Command = AJT.VC.YNCheck(Command);

			if (Command == "yes")
			{
				return;
			}

		} while (Command != "yes");
	}

	void Clear()
	{/*Clears the customer object*/
		CustID = "-1";
		Name = "Unnamed";
		Home.Clear();
		Email = "Undefined";
		PhoneNo = "Undefined";
	}

	string GetName()
	{
		return Name;
	}

	string GetID()
	{
		return CustID;
	}

	friend ostream& operator<<(ostream& OS, const Customer Cust)
	{/*overloaded operator for outputting to the terminal*/
		AJT.Graphics.Line('-', 35);

		OS << Cust.Name << ", " << Cust.CustID << endl;
		OS << Cust.Home;

		/*checks again if Email and PhoneNo should be displayed*/
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
	{/*overloaded for writing to a file. The + sign is used as a delimiter
	 as commas are used by orders*/
		Filer << Cust.CustID << "+" << Cust.Name << "+" << Cust.Email;
		Filer << "+" << Cust.PhoneNo;
		Filer << "+";
		Filer << Cust.Home << endl;

		return Filer;
	}

	friend ifstream& operator>>(ifstream& Obtainer, Customer& Cust)
	{/*overloaded for reading from a file*/
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
		Cust.Home.ReadAddr(Segments[4]);

		Segments.clear();

		return Obtainer;
	}

private:
	string CustID;
	string Name;
	Address Home;
	string Email;
	string PhoneNo;
};

class FoodItem
{/*class for food objects*/
public:
	FoodItem()
	{
		Clear();
	}

	void CreateDish(string CuisineSpec)
	{/*allows for the creation of a dish. CuisineSpec holds the cuisine's
	 prefix (for FoodID), the cuisine and what value the ID should be*/
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

		/*allows for a temporary popularity*/
		cout << "Expected popularity [low/med/high]: ";
		cin >> Popularity;

		cout << "Availability*: ";
		cin >> Availability;

		/*Splits CuisineSpec into it's base components*/
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

	void ReadDish(string Block)
	{
		string Temp;
		vector <string> Segments;

		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != '+')
			{
				Temp += Block[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
		}
		Segments.push_back(Temp);
		Temp.clear();

		FoodID = Segments[0];
		Name = Segments[1];
		Price = stod(Segments[2]);
		Cuisine = Segments[3];
		Course = Segments[4];
		Popularity = Segments[5];
		Availability = stoi(Segments[6]);
	}

	void UpdatePop()
	{/*allows the user (likely the chef, or by proxy) to update the popualrity
	 of any existing dish*/
		string Input;
		MenuTitle = "Update Popularity > " + Name;
		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Current popularity: " << Popularity << endl;
		cout << "Updated [low/med/high]: ";
		cin >> Input;

		/*potential for a VC option with more than 2 controls*/
		while (Input != "high" && Input != "med" && Input != "low")
		{
			cout << "Please enter either [low][med] or [high]: ";
			cin >> Input;
		}

		Popularity = Input;

		return;
	}

	void UpdateAvail()
	{/*similar thing, but allows for the user to update the availability
	 of a dish either after restocking or resetting the next day*/
		string Input;
		MenuTitle = "Update Availability > " + Name;
		AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

		cout << "Current Availability: " << Availability << endl;
		cout << "Updated [>1]: ";
		cin >> Input;

		while (stoi(Input) <= 1)
		{
			cout << "Please enter a value greater than [1]: ";
			cin >> Input;
		}

		Availability = stoi(Input);

		return;
	}

	void Clear()
	{/*clears a food object*/
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
	{
		this->Cuisine = Cuisine;
	}

	void SetID(string ID)
	{
		this->FoodID = ID;
	}

	string GetID()
	{
		return FoodID;
	}

	string GetName()
	{
		return Name;
	}

	double GetPrice()
	{
		return Price;
	}

	int GetAvail()
	{return Availability;}

	/*added is called when an item is added to a basket*/
	void Added()
	{Availability--;}

	/*removed is called when a basket is cleared*/
	void Removed()
	{Availability++;}

	void Display()
	{
		cout << Name << endl << "\tID:" << FoodID << endl;
		cout << "\tCuisine: " << Cuisine << endl;
		cout << "\tPrice: " << CurrencySym << setprecision(2) << fixed << Price;
		cout << endl << "\tCourse: " << Course << endl;
		cout << "\tPopularity: " << Popularity << endl;
		cout << "\tAvailability: " << Availability << endl;
		AJT.Graphics.Line('-', 45);
	}

	FoodItem& operator=(const FoodItem& FI2)
	{/*overloaded assignment operator, not strictly necessary, 
	 but wanted to make sure*/
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
	{/*overloaded file writer object. + symbol used as Order 
	 mainly uses commas*/
		Filer << FI.FoodID << "+" << FI.Name << "+" << FI.Price << "+";
		Filer << FI.Cuisine << "+" << FI.Course << "+,";
		Filer << FI.Popularity << "+" << FI.Availability << endl;

		return Filer;
	}

	friend ifstream& operator>>(ifstream& Obtainer, FoodItem& FI)
	{/*overloaded file reader object*/
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

		/*assigns elements of the vector to fields of the food object*/
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
	{/*Overloaded ostream operator for outputting to the terminal
	 tabs are used to neaten output*/
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
{/*Order object ties customers to food items*/
public:
	Order()
	{/*ensures new object is empty*/
		Clear();
	};

	void AddItem(FoodItem& AddedItem)
	{/*adds a chosen FoodItem to basket*/
		Basket.push_back(&AddedItem);

		/*updates the price of the basket*/
		BasketPrice += AddedItem.GetPrice();
	}

	void SetDelivery(bool Input, double DeliveryCost)
	{/*sets whether order is a delivery or for pickup*/
		Delivery = Input;
		/*updates delivery cost*/
		this->DeliveryCost = DeliveryCost;
	}

	void SetOpen(bool Input)
	{/*determines the open/closed state of an order 
	 (ie, if it's been picked up)*/
		Open = Input;
	}

	void Clear()
	{/*clears the order*/
		Basket.clear();
		Cust.Clear();
		OrderID.clear();
		Open = true;
		Delivery = true;
		BasketPrice = 0;
		DeliveryCost = 0;
	}

	void SetID(int ID)
	{
		OrderID = "ODR-" + to_string(ID);
	}

	void SetCust(Customer Cust)
	{
		this->Cust = Cust;
	}

	int GetBasketSize()
	{
		return Basket.size();
	}

	string GetID()
	{
		return OrderID;
	}

	double GetBasketPrice()
	{
		return BasketPrice;
	}

	void GetBasketItem(int Index)
	{
		Basket[Index]->Display();
	}

	void BasketItemMin(int Index)
	{
		cout << Basket[Index]->GetName();
	}

	void ReturnItems()
	{
		/*resets the dishes in the basket*/
		for (int i = 0; i < Basket.size(); i++)
		{
			Basket[i]->Removed();
		}
	}

	string GetCustID()
	{
		return Cust.GetID();
	}

	double GetPrice()
	{
		return BasketPrice + DeliveryCost;
	}

	vector <FoodItem*> GetBasket()
	{/*returns the basket as a vector*/
		return Basket;
	}

	friend ostream& operator<<(ostream& OS, const Order OR)
	{/*overloaded output to the terminal*/
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
			cout << "\t" << OR.Basket[i]->GetName() << endl;
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

	friend ofstream& operator<<(ofstream& Filer, Order OR)
	{/*overloaded Writer object*/
		Filer << OR.OrderID << "," << OR.Basket.size() << ",";
		Filer << OR.Cust.GetID() << "," << OR.Delivery << "," << OR.Open << endl;

		for (int i = 0; i < OR.Basket.size(); i++)
		{
			Filer << OR.Basket[i] << ":";
		}		

		return Filer;
	}

	friend ifstream& operator>>(ifstream& Obtainer, Order OR)
	{/*overloaded reader object*/
		vector <string> Segments;
		string Line, Temp;
		int BasketSize;

		getline(Obtainer >> ws, Line);

		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] != ',')
			{
				Temp += Line[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}			
		}
		Segments.push_back(Temp);
		Temp.clear();

		OR.OrderID = Segments[0];
		BasketSize = stoi(Segments[1]);
		OR.CustID = Segments[2];

		if (Segments[3] == "1")
		{OR.Delivery = true;}
		else
		{OR.Delivery = false;}

		if (Segments[4] == "1")
		{OR.Open = true;}
		else
		{OR.Open = false;}

		Segments.clear();
		Temp.clear();
		getline(Obtainer >> ws, Line);

		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] != ':')
			{
				Temp += Line[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
		}
		Segments.push_back(Temp);
		Temp.clear();

		FoodItem TempFood;

		for (int i = 0; i < BasketSize; i++)
		{
			TempFood.ReadDish(Segments[i]);
			OR.AddItem(TempFood);
		}

		return Obtainer;
	}

private:
	vector <FoodItem*> Basket;
	Customer Cust;
	string OrderID;
	string CustID;
	bool Open;
	bool Delivery;
	double BasketPrice;
	double DeliveryCost;
};

class Menu
{/*not to confused with a menu of options, 
 this menu holds the different available food items*/
public:
	Menu()
	{}

	string Searcher()
	{/*looks for the queried food item, and returns it's location in both 
	 the main and sub-vectors of Dishes<>*/
		bool Found = false;
		string Query;

		MenuTitle += "Search > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

		cout << "Please enter either the FoodID or it's name:";
		cout << endl << "> ";

		getline(cin >> ws, Query);

		for (int i = 0; i < Dishes.size(); i++)
		{/*searching the outer vector*/
			for (int j = 0; j < Dishes[i].size(); j++)
			{/*Searching the sub-vectors*/
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
		/*not found clause*/
		if (Found == true)
		{/*shouldn't happen, but just in case*/
			cout << "ERROR::object found, but not returned (Searcher())" << endl;
			abort();
		}
		else
		{/*main error message*/
			cout << "Searcher could not find the item you were looking for, apologies" << endl;
			return("-1");
		}
	}

	void ReadFile()
	{/*Reads in dishes from the Dishes file*/
		ifstream Reader;
		FoodItem TempFood;
		vector <FoodItem> TempFoods;
		int NoCuisines, NoDishes, Counter;
		string Temp;

		Reader.open("Dishes.txt");

		/*obtains how many cuisines there are*/
		Reader >> NoCuisines;

		for (int i = 0; i < NoCuisines; i++)
		{
			/*obtains the number of dishes in a cuisine*/
			Reader >> NoDishes;

			/*gets the cuisine*/
			Reader >> Temp;

			/*adds it to the vector of cuisines*/
			Cuisine.push_back(Temp);
			Temp.clear();
			TempFoods.clear();

			/*nabs each item of food and adds it to a temporary vector*/
			for (int j = 0; j < NoDishes; j++)
			{
				Reader >> TempFood;
				TempFoods.push_back(TempFood);
				TempFood.Clear();
			}

			/*the vector is then pushed back to the Dishes vector
			with this, each subvector is a cuisine*/
			Dishes.push_back(TempFoods);
		}
	}

	void WriteFile()
	{/*writes dishes to the file*/
		string Temp;
		ofstream Writer;
		Writer.open("Dishes.txt");

		/*writes the number of cuisines*/
		Writer << Cuisine.size() << endl;

		for (int i = 0; i < Cuisine.size(); i++)
		{
			/*writes the number of dishes in each cuisine*/
			Writer << Dishes[i].size() << endl;

			/*writes the details of the cuisine*/
			Writer << Cuisine[i] << endl;

			/*writes every dish in a cuisine*/
			for (int j = 0; j < Dishes[i].size(); j++)
			{
				Writer << Dishes[i][j];
			}
		}

		Writer.close();
	}

	void NewDish()
	{/*allows the user to create a new dish*/
		vector <FoodItem> TempFoods;
		string Command, Input;
		int ChosenCuisine;

		MenuTitle = "New Dish >";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		/*checks if the new dish requires a new cuisine*/
		cout << "Would you like to add a new cuisine? [yes/no]" << endl << "> ";
		cin >> Command;

		Command = AJT.VC.YNCheck(Command);
		
		if (Command == "yes")
		{
			MenuTitle = "New Dish > ";

			CreateCuisine();

			/*allows the user to opt-out*/
			cout << "Would you like to add a new dish? [yes/no]" << endl;
			cin >> Command;

			Command = AJT.VC.YNCheck(Command);

			if (Command == "no")
			{
				return;
			}
		}

		Input.clear();
		Command.clear();

		do
		{
			MenuTitle = "New Dish > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Choose Cuisine" + "\n");

			/*checks if there are saved cuisines*/
			if (Cuisine.size() == 0)
			{
				cout << "There are no cuisines available, please make a new cuisine first" << endl;
				return;
			}

			FoodItem TempFood;

			/*allows the user to choose an existing cuisine*/
			AJT.Graphics.DisplayOptions(Cuisine, 0);
			cin >> Command;

			//replace with VC?
			while (stoi(Command) > Cuisine.size() + 1 || stoi(Command) < 1)
			{
				cout << "Please choose a cuisine[1-" << Cuisine.size() + 1 << "]" << endl;
				cin >> Command;
			}

			cout << "You've chosen: " << Cuisine[stod(Command) - 1];
			ChosenCuisine = stoi(Command) - 1;

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + Cuisine[ChosenCuisine]);

			/*checks if the cuisine is empty*/
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

			/*allows user to restart*/
			cout << "Is this correct? [yes/no] " << endl << "> ";
			cin >> Command;

			Command = AJT.VC.YNCheck(Command);

			if (Command != "no")
			{
				TempFoods.clear();

				if (Dishes.size() == 0)
				{
					/*adds dish to the temporary vector
					temporary vector is then added to Dishes*/
					TempFoods.push_back(TempFood);
					Dishes.push_back(TempFoods);
				}
				else
				{
					if (Dishes.size() <= ChosenCuisine)
					{
						/*adds dish to the temporary vector
						temporary vector is then added to Dishes*/
						TempFoods.push_back(TempFood);
						Dishes.push_back(TempFoods);
					}
					else
					{
						/*adds new dish to the specific cuisine in Dishes*/
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
	{/*UpdatePop allows for the user to update the popularity of a dish*/
		//index in the outer, inner vectors + location of comma
		int OuterVal, InnerVal, Mid;
		string Temp, Command;
		bool Active = true;

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			MenuTitle = "Update Popularity > ";

			/*uses Searcher to retrieve the location of the dish within
			Dishes*/
			Temp = Searcher();

			if (Temp == "-1")
			{/*not found clause*/
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
			{/*splits the returned value into it's position on the 
			 main and sub-vectors*/
				Mid = Temp.find(',');
				OuterVal = stoi(Temp.substr(0, Mid));
				InnerVal = stoi(Temp.substr(Mid + 1));

				MenuTitle = "Update Popularity > " + Dishes[OuterVal][InnerVal].GetName();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle);

				/*calls UpdatePop for the specific dish*/
				Dishes[OuterVal][InnerVal].UpdatePop();

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + " > Details");

				/*shows the new popularity*/
				cout << "Updated: ";
				cout << Dishes[OuterVal][InnerVal];

				cout << "Type [return] to return to menu" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.CustCheck(Command, "return");

				return;
			}
		} while (Active == true);
		/*just in case*/
		cout << "ERROR::Program escaped the loop" << endl;
		abort();
	}

	void UpdateAvail()
	{/*similar to UpdatePop, but for availability*/
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

				cout << "Type [return] to return to menu" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.CustCheck(Command, "return");

				return;
			}
			cout << "ERROR::program escaped the loop (UpdateAvail)" << endl;
			abort();
		} while (Active == true);
	}

	void EditDish()
	{/*allows the user to edit a dish by displaying the previous 
	 values, then allowing the user to make a new dish to replace
	 it*/
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

				/*displays the current details of the dish*/
				cout << "Current Details: " << endl;
				cout << Dishes[OuterVal][InnerVal] << endl;

				/*creates a new dish*/
				TempDish.CreateDish(Cuisine[OuterVal] + "," + to_string(Dishes[OuterVal].size()));

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Updated Details");

				cout << TempDish;

				/*new dish overwrites previous*/
				Dishes[OuterVal][InnerVal] = TempDish;

				cout << "Type [return] to return to menu" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.CustCheck(Command, "return");

				return;
			}
		} while (Active == true);
	}

	void DeleteDish()
	{/*allows the user to delete a dish*/
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

				Command = AJT.VC.YNCheck(Command);

				if (Command == "yes")
				{
					/*sets the dish's ID to -1, which gets picked
					up in the for-loop below*/
					Dishes[OuterVal][InnerVal].SetID("-1");

					/*a temporary vector hold the dishes of a cuisine*/
					for (int i = 0; i < Dishes[OuterVal].size(); i++)
					{
						/*ignores any dishes with an ID of -1*/
						if (Dishes[OuterVal][i].GetID() != "-1")
						{
							TempFoods.push_back(Dishes[OuterVal][i]);
						}
					}
					/*overwrites previous cuisine sub-vector*/
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
	{/*displays the menu to the user. The menu is split into pages, 
	 with a page for each cuisine*/
		string Command, Input;
		int CuisineChoice, CurrentPg;

		Command.clear();

		/*holds the current page*/
		CurrentPg = 0;

		MenuTitle = "Menu Browse > Page ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + to_string(CurrentPg + 1));

			cout << AJT.CMH.Remove(',', Cuisine[CurrentPg], "left") << endl;

			/*displays every dish of a cuisine*/
			if (Dishes[CurrentPg].empty() != true)
			{
				for (int i = 0; i < Dishes[CurrentPg].size(); i++)
				{
					cout << Dishes[CurrentPg][i];
				}
			}
			else
			{
				/*displays if there aren't any dishes in a specific cuisine*/
				cout << endl << "*No dishes*" << endl;
			}

			cout << endl;

			/*allows the user to change which page, or cuisine they're viewing*/
			cout << "Which page would you like to visit?" << endl << "[1-";
			cout << Cuisine.size() << "] or [exit] to leave" << endl << "> ";
			cin >> Command;

			if (Command == "exit")
			{
				return;
			}

			Command = AJT.VC.NumRangeCheck(Command, 1, Cuisine.size());

			CurrentPg = stoi(Command) - 1;

		} while (Command != "exit");
	}

	void CreateCuisine()
	{/*allows the user to create a cuisine/create a new sub vector in Dishes*/
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

				/*cuisine prefix is used for FoodID*/
				cout << "Cuisine Prefix: ";
				cin >> Temp;

				cout << endl << "Cuisine Name: " << Input << endl;
				cout << "Cuisine Prefix: " << Temp << endl;
				cout << "Is this correct? [yes/no]" << endl;
				cin >> Command;
			} while (Command != "yes" && Command == "no");

			/*Temp holds the prefix and name together, separated by a comma*/
			Temp += "," + Input;
			Cuisine.push_back(Temp);

			/*TempFoods is a blank vector, but assigns a space for dishes
			of the new cusine*/
			Dishes.push_back(TempFoods);

			Input.clear();
			Temp.clear();

			cout << endl << "Would you like to make another cuisine? [yes/no]" << endl;
			cin >> Command;

			Command = AJT.VC.YNCheck(Command);

		} while (Command == "yes" && Command != "no");

		MenuTitle.clear();
	}

	void EditDetailsMenu()
	{/*function-junction that handles the sub-menu for 
	 manipulating FoodItem objects*/
		string Command; int Choice;
		vector <string> Options{ 
			"Edit Item","Edit Popularity","Edit Availability","Delete Item" 
		};

		MenuTitle = "Edit Details Menu > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			/*displays the menu options*/
			AJT.Graphics.DisplayOptions(Options, 1);
			cin >> Command;

			if (Command == "exit")
			{
				return;
			}

			Command = AJT.VC.NumRangeCheck(Command, 1, Options.size() + 1);

			Choice = stoi(Command);

			/*junction part of the function junction*/
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
				/*just in case*/
				cout << "ERROR::Outside Switch Case boundaries" << endl;
				abort();
				break;
			}
			}

		} while (Command != "exit");
		return;
	}

	void SelectionMenu()
	{/*function-junction for higher-level FoodItem stuff*/
		string Command; int Choice;
		vector <string> Options{
			"Browse Menu", "Edit Item", "Add Dish", "Add Cuisine",
			"Save Menu to file"
		};

		MenuTitle = "Menu Menu > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			/*displays options*/
			AJT.Graphics.DisplayOptions(Options, 1);
			cin >> Command;

			if (Command == "Exit")
			{
				return;
			}

			Command = AJT.VC.NumRangeCheck(Command, 1, Options.size() + 2);

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
				/*calls sub-sub-menu*/
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
	{/*allows user to create a new order*/
		string Command, Temp;
		int Page, Outer, Inner;
		Order TempOrder;

		Page = 0;
		MenuTitle = "Select Dishes > ";

		do
		{
			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			cout << "Would you like to search for an item? [yes/no/next]" << endl;
			cout << "[next] will allow you to proceed" << endl << "> ";
			cin >> Command;

			while (Command != "yes" && Command != "no" && Command != "next")
			{
				cout << "Please enter [yes], [no] or [next]" << endl << "> ";
				cin >> Command;
			}

			if (Command == "yes")
			{/*allows the user to enter the FoodItem's name or ID*/
				Temp = Searcher();
				Outer = stoi(AJT.CMH.Remove(',', Temp, "left"));
				Inner = stoi(AJT.CMH.Remove(',', Temp, "right"));

				if (Dishes[Outer][Inner].GetAvail() < 1)
				{
					cout << "Availability for " << Dishes[Outer][Inner].GetName();
					cout << " is too low. Please choose another item or increase ";
					cout << "availability" << endl;
					cout << "type [return] to add another item" << endl << "> ";
					cin >> Command;

					Command = AJT.VC.CustCheck(Command, "return");
				}
				else
				{
					Dishes[Page][stoi(Command) - 1].Added();
					TempOrder.AddItem(Dishes[Outer][Inner]);
				}				
			}
			else if (Command == "next")
			{/*returns to menu*/
				break;
			}
			else
			{/*allows the user to browse the menu alike DisplayMenu()*/
				do
				{
					AJT.SCH.ScreenCleanerTM(0, MenuTitle + Dishes[Page][0].GetCuisine());

					for (int j = 0; j < Dishes[Page].size(); j++)
					{
						cout << j + 1 << ") " << Dishes[Page][j] << endl;
					}

					cout << "Page " << Page + 1 << " of " << Cuisine.size() << endl;
					cout << "Please select [1-" << Dishes[Page].size() << "]";
					cout << ", type [page #] with the page you'd like to visit";
					cout << "or type [exit] to return" << endl << "> ";
					getline(cin >> ws, Command);

					if (Command[0] == 'p')
					{/*the user can either enter "page" followed by the page
					 they'd like to visit*/
						Page = stoi(AJT.VC.NumRangeCheck(Command.substr(5), 1, Cuisine.size())) - 1;
					}
					else if (Command == "exit")
					{/*jumps out*/
						break;
					}
					else if (stoi(Command) > 0)
					{/*or they can enter the index of the FoodItem*/
						Command = AJT.VC.NumRangeCheck(Command, 0, Dishes[Page].size() + 1);
						
						if (Dishes[Page][stoi(Command) - 1].GetAvail() < 1)
						{
							cout << "Availability for ";
							cout << Dishes[Page][stoi(Command) - 1].GetName();
							cout << " is too low. Please choose another item or increase ";
							cout << "availability" << endl;
							cout << "type [return] to add another item" << endl << "> ";
							cin >> Command;

							Command = AJT.VC.CustCheck(Command, "return");
						}
						else
						{
							Dishes[Page][stoi(Command) - 1].Added();
							TempOrder.AddItem(Dishes[Page][stoi(Command) - 1]);
						}						
					}

				} while (Command != "next");
			}
		} while (Command != to_string(Dishes[Page].size() + 1));

		/*Allows the user to quick-view the basket*/
		cout << "Would you like to view the basket? [yes/no]" << endl << "> ";
		cin >> Command;

		Command = AJT.VC.YNCheck(Command);

		if (Command == "yes")
		{/*displays the basket*/
			for (int i = 0; i < TempOrder.GetBasketSize(); i++)
			{
				TempOrder.BasketItemMin(i);
			}
			/*displays the basket's total price*/
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

/*Employees are split into two inherited classes with virtual functions*/
class Chef :public Employee
{
public:
	Chef()
	{}

	virtual void CreateEmployee(int Index)
	{/*allows the user to create an chef object*/
		Clear();

		cout << "Please enter:" << endl << "name: ";
		getline(cin >> ws, Name);

		cout << "Phone No.: ";
		getline(cin >> ws, PhoneNo);

		EmpID = "Emp" + to_string(Index);

		cout << "Cuisine speciality: ";
		getline(cin >> ws, Speciality);

		cout << endl;

		Addrs.CreateAddress();
	}

	virtual void Display()
	{/*displays the object*/
		cout << EmpID << endl << "Name: " << Name << endl;
		/*tabs used again to neaten formatting*/
		cout << "\tPhone No.: " << PhoneNo << endl << "\tPosition: ";
		cout << Position << endl << "\tSpeciality: " << Speciality << endl;
		cout << "Home: " << endl << Addrs;

		AJT.Graphics.Line('-', 45);
	}

	virtual void SetPosition(string Input)
	{
		Position = Input;
	}

	virtual string GetID()
	{
		return EmpID;
	}

	virtual void Clear()
	{/*clears the object*/
		Name.clear();
		EmpID.clear();
		PhoneNo.clear();
		Speciality.clear();
		Addrs.Clear();
	}

	virtual void SetID(string Input)
	{EmpID = Input;}

	virtual string GetPosition()
	{return Position;}

	virtual void Read(ifstream& Reader)
	{/*takes in a passed Reader object to read from a file*/
		string Temp, Block;
		vector <string> Segments;

		getline(Reader >> ws, Block);

		/*line of data is split up into segments*/
		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != ',')
			{
				Temp += Block[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}
		}
		Segments.push_back(Temp);
		Temp.clear();

		/*segments correspond to fields*/
		EmpID = Segments[0];
		Name = Segments[1];
		PhoneNo = Segments[2];
		Position = Segments[3];
		Speciality = Segments[4];

		/*because the address class can have overloaded functions, it's
		given control of reading it's data*/
		Reader >> Addrs;

		Segments.clear();
	}

	virtual void Write(ofstream& Writer)
	{/*passed Writer object for writing to a file*/
		string Data;

		Data = "1 " + EmpID + "," + Name + "," + PhoneNo + "," + Position;
		Data += "," + Speciality;

		Writer << Data << endl;
		/*Addrs has it's own line because the compiler kept calling the ostream
		overload instead of ofstream*/
		Writer << Addrs;
	}

private:
	string EmpID;
	string Name;
	string PhoneNo;
	string Position;
	string Speciality;
	Address Addrs;
};

class GeneralEmployee :public Employee
{/*effectively similar to Chef, but without speciality and implied position*/
public:
	GeneralEmployee()
	{};

	virtual void CreateEmployee(int Index)
	{/*allows user to create a non-chef employee*/
		Clear();

		cout << "Please enter:" << endl << "name: ";
		getline(cin >> ws, Name);

		cout << "Phone No.:";
		getline(cin >> ws, PhoneNo);

		cout << "Position: ";
		getline(cin >> ws, Position);

		EmpID = "Emp" + to_string(Index);

		cout << endl;

		Addrs.CreateAddress();
	}

	virtual void Display()
	{/*displays the details of the employee*/
		cout << EmpID << endl << "Name: " << Name << endl;
		cout << "\tPhone No.: " << PhoneNo << endl << "\tPosition: ";
		cout << Position << endl << "Home: " << endl << Addrs;

		AJT.Graphics.Line('-', 45);
	}

	virtual void SetPosition(string Input)
	{
		Position = Input;
	}

	virtual string GetID()
	{
		return EmpID;
	}

	virtual void Clear()
	{
		Name.clear();
		EmpID.clear();
		PhoneNo.clear();
		Addrs.Clear();
	}

	virtual void SetID(string Input)
	{
		EmpID = Input;
	}

	virtual string GetPosition()
	{
		return Position;
	}

	virtual void Read(ifstream& Reader)
	{/*uses the passed reader object to read in details*/
		string Temp, Block;
		vector <string> Segments;

		getline(Reader >> ws, Block);

		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != ',')
			{
				Temp += Block[i];
			}
			else
			{
				Segments.push_back(Temp);
				Temp.clear();
			}			
		}
		Segments.push_back(Temp);
		Temp.clear();

		EmpID = Segments[0];
		Name = Segments[1];
		PhoneNo = Segments[2];
		Position = Segments[3];

		Reader >> Addrs;

		Segments.clear();
	}

	virtual void Write(ofstream& Writer)
	{
		string Data;

		Data = "0 " + EmpID + "," + Name + "," + PhoneNo + "," + Position;

		Writer << Data << endl;
		Writer << Addrs;
	}

private:
	string EmpID;
	string Name;
	string PhoneNo;
	string Position;
	Address Addrs;
};

class RestraurantSys
{/*the primary class of the program, the class junction of function jucntions*/
public:
	RestraurantSys()
	{
		DeliveryCost = 2.5;
		MaxNoTakeaways = 20;
	}

	Order MakeOrder()
	{/*(starts the order making process) allows user to make an order*/
		string Command; int Temp; bool Valid = false;
		Customer TempCust;
		Order CurrentOrder;

		do
		{
			MenuTitle = "Make an order > ";
			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Existing Customer?");

			cout << "Is the order for an existing customer? [yes/no]" << endl << "> ";
			cin >> Command;

			Command = AJT.VC.YNCheck(Command);

			if (Command == "yes")
			{
				/*allows user to search for a customer*/
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
			{/*allows user to make a customer*/

				if (Customers.empty() == true)
				{/*if there aren't any saved customers, the new CustID is 0*/
					TempCust.CreateCustomer(0);
				}
				else
				{/*the new CustID is taken from the current number of customers*/
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

				/*checks if the program has reached the max amount of orders*/
				if (Command == "pickup" && MaxNoTakeaways < 1)
				{
					/*allows user to change the order type*/
					cout << "Max number of takeaways reached" << endl;
					cout << "Would you like to change the order type? [yes/no]" << endl << "> ";
					cin >> Command;

					Command = AJT.VC.YNCheck(Command);

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
				else
				{
					Valid = true;
				}

			} while (Valid == false);

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + " Select Foods");

			/*handles the food-end of the order*/
			CurrentOrder = Bwydlen.CreateOrder();

			/*assigns the customer to the order*/
			CurrentOrder.SetCust(TempCust);

			/*adds delivery cost if necessary*/
			if (Command == "pickup")
			{
				CurrentOrder.SetDelivery(false, 0);
			}
			else
			{
				CurrentOrder.SetDelivery(true, DeliveryCost);
			}

			AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation");

			/*creates ID*/
			CurrentOrder.SetID(Orders.size());

			/*displays the current order*/
			cout << CurrentOrder;

			cout << endl << "Is this correct? [yes/no]" << endl << "> ";
			cin >> Command;

			Command = AJT.VC.YNCheck(Command);

			if (Command == "yes")
			{
				NoOrders++;
				return CurrentOrder;
			}
			else
			{
				CurrentOrder.ReturnItems();
			}
			/*restarts the process if the order is incorrect*/
		} while (Command == "no");
		return CurrentOrder;
	}

	void WriteAllFiles()
	{/*allows the program to save all data*/
		string Command;
		ofstream Writer;

		Bwydlen.WriteFile();

		WriteEmployees();
		WriteMisc();

		/*(Writer.open("Orders.txt");
		Writer << Orders.size();

		for (int i = 0; i < Orders.size(); i++)
		{
			Writer << Orders[i];
		}

		Writer.close();
		Writer.clear();*/

		Writer.open("Customers.txt");

		Writer << Customers.size();

		for (int i = 0; i < Customers.size(); i++)
		{
			Writer << Customers[i];
		}

		Writer.close();

		WriteMisc();

		MenuTitle = "Write Files > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Files written, type [exit] to return" << endl << "> ";
		cin >> Command;
	}

	void ReadAllFiles()
	{/*allows the program to read in all data*/
		string Command;
		ifstream Reader;
		Customer TempCust;
		Order TempOrder;
		int NoCusts, NoOrders;
		
		Bwydlen.ReadFile();

		ReadEmployees();

		/*Reader.open("Orders.txt");

		Reader >> NoOrders;

		for (int i = 0; i < NoOrders; i++)
		{
			Reader >> TempOrder;

			Orders.push_back(TempOrder);

			TempOrder.Clear();
		}

		Reader.close();
		Reader.clear();*/

		ReadMisc();

		Reader.open("Customers.txt");

		Reader >> NoCusts;

		for (int i = 0; i < NoCusts; i++)
		{
			Reader >> TempCust;
			Customers.push_back(TempCust);
			TempCust.Clear();
		}

		Reader.close();

		ReadMisc();

		MenuTitle = "Read Files > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Files read, type [exit] to return" << endl << "> ";
		cin >> Command;
	}

	void DisplayMenu()
	{/*displays the food menu*/
		Bwydlen.DisplayMenu();
	}

	void CreateCusine()
	{/*allows the user to create a new cuisine*/
		Bwydlen.CreateCuisine();
	}

	void EditDeliveryCost()
	{/*allows the user to update the delivery cost*/
		MenuTitle = "Delivery cost > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "How much for delivery?" << endl << "> " << CurrencySym;
		cin >> DeliveryCost;
	}

	void BrowseCustomers()
	{/*allows the user to view all saved customers*/
		string Command;

		MenuTitle = "Browse Customers > ";
		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		for (int i = 0; i < Customers.size(); i++)
		{
			cout << Customers[i];
		}

		cout << "Enter [return] to return to menu" << endl << "> ";
		cin >> Command;

		AJT.VC.CustCheck(Command, "return");

		return;
	}

	int CustSearcher()
	{/*allows the user to search through saved customers*/
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
			{/*not found clause*/
				cout << "The searched customer could not be found" << endl;
				cout << "Would you like to try again? [yes/no]" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.YNCheck(Command);

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
	{/*allows the user to close an order if it has been completed*/
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

			/*gives the user the option to view a specific order or to close it*/
			cout << "Please type either [view #] or [close #] where # is between [1-" << Orders.size() << "]";
			cout << " or type [exit] to leave";
			cout << endl << "> ";
			cin >> Command;

			if (Command[0] == 'e')
			{/*exit clause*/
				return;
			}
			else if (Command[0] == 'v')
			{/*view clause*/
				Index = stoi(Command.substr(5));
				cout << Orders[Index];

				cout << endl << "Is this the correct order? [yes/no]" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.YNCheck(Command);

				if (Command == "yes")
				{
					Orders[Index].SetOpen(false);
					return;
				}
				else
				{/*for re-looping*/
					Valid = false;
				}
			}
			else if (Command[0] == 'c')
			{/*close clause*/
				Index = stoi(Command.substr(6));
				Orders[Index].SetOpen(false);
			}
			else
			{/*error message*/
				cout << "Please enter either [view #], [close #] or [exit]" << endl;
				cin >> Command;
			}
		} while (Valid == false);
	}

	void MainMenu()
	{/*The mani menut of the program & functionjunction*/
		vector <string> Options{
			"View Menu sub-Menu","Make New Order","Close Order","View Employee sub-Menu",
			"View Customer sub-Menu", "Misc sub-menu","Generate Report",
		};
		string Command;
		Order TempOrder;

		do
		{
			MenuTitle = "Main Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			/*displays options*/
			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			Command = AJT.VC.NumRangeCheck(Command, 1, Options.size() + 1);

			switch (stoi(Command))
			{/*junction*/
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
				EmployeeMenu();
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
				GenerateReport();
				break;
			}
			case 8:
			{/*prompts user to save files before exiting*/
				cout << "Would you like to save your files first? [yes/no]" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.YNCheck(Command);

				if (Command == "yes")
				{
					WriteAllFiles();
				}

				Command = "exit";
				break;
			}
			default:
			{
				cout << "ERROR::Outside of switch bounds (MainMenu)" << endl;
				break;
			}
			}
		} while (Command != "exit");
	}

	void CustomerMenu()
	{/*sub-menu for handling customers*/
		vector <string> Options{"View Customers","Create Customer"};
		string Command;

		do
		{
			MenuTitle = "Customer Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);
			
			/*displays options*/
			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			Command = AJT.VC.NumRangeCheck(Command, 1, Options.size() + 1);

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

				/*checks if the new CustID should be 0 or greater*/
				if (Customers.empty() == true)
				{
					TempCust.CreateCustomer(0);
				}
				else
				{
					TempCust.CreateCustomer(Customers.size());
				}

				/*adds customer to customer list*/
				Customers.push_back(TempCust);
				TempCust.Clear();
				break;
			}
			case 3:
			{
				Command = "exit";
				break;
			}
			default:
			{
				cout << "ERROR::Outside of switch bounds (CustomerMenu)" << endl;
				break;
			}
			}
		} while (Command != "exit");
	}

	void MiscMenu()
	{/*miscellaneous menu */
		vector <string> Options{
			"Change Delivery Cost", "Change Maximum Takeaway Orders","Save All Files",
			"Read All Files"
		};
		string Command;

		do
		{
			MenuTitle = "Misc Sub-Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			/*displays options*/
			AJT.Graphics.DisplayOptions(Options, 1);

			cin >> Command;

			Command = AJT.VC.NumRangeCheck(Command, 1, Options.size() + 1);

			switch (stoi(Command))
			{
			case 1:
			{/*allows the user to change the delivery cost*/
				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Change delivery cost");

				cout << "Current Delivery price: " << CurrencySym;
				cout << setprecision(2) << fixed << DeliveryCost << endl;
				cout << "Please enter a new price: " << CurrencySym;
				getline(cin >> ws, Command);

				DeliveryCost = stod(Command);
				break;
			}
			case 2:
			{/*allows the user to change the MaxAmount of orders*/
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
				break;
			}
			default:
			{
				cout << "ERROR::Outside of switch bounds (MiscMenu)" << endl;
				break;
			}
			}
		} while (Command != "exit");
	}

	void EmployeeMenu()
	{/*sub-menu for employees*/
		vector <string> Options{
			"View Emplyees", "Create Employee", "Edit Employee", "Delete Employee"
		};
		string Command;
		Chef TempChef;
		GeneralEmployee GenEmp;
		int CurrentIndex;
		
		do
		{
			MenuTitle = "Employee Menu > ";

			AJT.SCH.ScreenCleanerTM(0, MenuTitle);

			/*displays options*/
			AJT.Graphics.DisplayOptions(Options, 1);
			cin >> Command;

			Command = AJT.VC.NumRangeCheck(Command, 1, (Options.size()+1));
		
			switch (stoi(Command))
			{
			case 1:
			{
				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "View Employees");

				for (auto X : Employees)
				{
					X->Display();
				}

				cout << "Type [return] to return to menu" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.CustCheck(Command, "return");

				break;
			}
			case 2:
			{/*allows the user to make a new employee*/
				do
				{
					MenuTitle = "Employee Menu > Create Employee > ";

					AJT.SCH.ScreenCleanerTM(0, MenuTitle);

					/*determines which derived class to use*/
					cout << "Is the new employee a chef? [yes/no]" << endl;
					cin >> Command;

					Command = AJT.VC.YNCheck(Command);

					/*current index keeps track of which Employees 
					element we're on*/
					if (Employees.empty() == true)
					{
						CurrentIndex = 0;
					}
					else
					{
						CurrentIndex = Employees.size();
					}

					if (Command == "yes")
					{
						/*new chef object is added, Current Index 
						should be synced with it's position*/
						Employees.push_back(new Chef);
						
						do
						{
							AJT.SCH.ScreenCleanerTM(0, MenuTitle + "New Chef > ");

							Employees[CurrentIndex]->CreateEmployee(CurrentIndex);
							/*position is set automatically*/
							Employees[CurrentIndex]->SetPosition("Chef");

							AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation > ");
							Employees[CurrentIndex]->Display();

							cout << "Is this correct? [yes/no]" << endl << "> ";
							cin >> Command;

							Command = AJT.VC.YNCheck(Command);
						} while (Command == "no");

						if (Command == "yes")
						{
							break;
						}
					}
					else
					{/*same goes for Employee*/
						/*new GeneralEmployee added to the vector 
						with CurrentIndex synced*/
						Employees.push_back(new GeneralEmployee);

						do
						{
							AJT.SCH.ScreenCleanerTM(0, MenuTitle + "New Employee > ");
							
							Employees[CurrentIndex]->CreateEmployee(CurrentIndex);

							AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation > ");
							Employees[CurrentIndex]->Display();

							cout << "Is this correct? [yes/no]" << endl << "> ";
							cin >> Command;

							Command = AJT.VC.YNCheck(Command);
						} while (Command == "no");

						if (Command == "yes")
						{
							break;
						}
					}

					if (Command == "yes")
					{/*allows the user to make a new employee*/
						cout << "Would you like to make another employee [yes/no]";
						cout << endl << "> ";
						cin >> Command;

						Command = AJT.VC.YNCheck(Command);

						if (Command == "no")
						{
							Command = "leave";
							break;
						}
					}
				} while (Command != "leave");
				break;
			}
			case 3:
			{/*edit employee*/
				/*allows the user to edit an employee by displaying the 
				current details, making a new one then overwiting the old one*/
				int ChosenIndex;
				string Temp;

				do
				{
					MenuTitle = "Employee Menu > Edit Employee > ";

					AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

					/*displays employees*/
					for (int i = 0; i < Employees.size(); i++)
					{
						cout << i + 1 << ") ";
						Employees[i]->Display();
					}

					cout << "Please enter the Employee you'd like to Edit [1-";
					cout << Employees.size() << "]" << endl << "> ";
					cin >> Command;

					ChosenIndex = stoi(AJT.VC.NumRangeCheck(Command, 1, Employees.size())) - 1;

					AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation > ");

					Employees[ChosenIndex]->Display();

					cout << "Is this correct? [yes/no]" << endl << "> ";
					cin >> Command;

					Command = AJT.VC.YNCheck(Command);

					if (Command == "yes")
					{
						cout << endl;

						/*obtains the current ID*/
						Temp = Employees[ChosenIndex]->GetID();

						/*removes the letters*/
						Temp = Temp.substr(3);

						/*creates a new employee with the old ID*/
						Employees[ChosenIndex]->CreateEmployee(stoi(Temp));
					}

					AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation > ");

					/*shows new details*/
					Employees[ChosenIndex]->Display();

					cout << "Is this correct? [yes/no]" << endl << "> ";
					cin >> Command;

					Command = AJT.VC.YNCheck(Command);

					if (Command == "yes")
					{
						break;
					}
				} while (Command != "leave");				
				break;
			}
			case 4:
			{/*delete employee*/
				/*allows the user to select an employee, then sets their ID to -1
				this is then ignored when the vector is rebuilt*/
				int ChosenIndex;
				vector <Employee*> TempEmployees;

				MenuTitle = "Employee Menu > Delete Employee > ";

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "\n");

				/*displays employees*/
				for (int i = 0; i < Employees.size(); i++)
				{
					cout << i + 1 << ") ";
					Employees[i]->Display();
				}

				cout << "Please enter the Employee you'd like to delete [1-";
				cout << Employees.size() << "]" << endl << "> ";
				cin >> Command;

				ChosenIndex = stoi(AJT.VC.NumRangeCheck(Command, 1, Employees.size())) -1;

				AJT.SCH.ScreenCleanerTM(0, MenuTitle + "Confirmation > ");

				Employees[ChosenIndex]->Display();

				cout << "Is this correct? [yes/no]" << endl << "> ";
				cin >> Command;

				Command = AJT.VC.YNCheck(Command);

				if (Command == "yes")
				{
					/*marks employee for deletion*/
					Employees[ChosenIndex]->SetID("-1");
				}

				/*rebuilds vector*/
				for (int i = 0; i < Employees.size(); i++)
				{
					if (Employees[i]->GetID() != "-1")
					{/*ignores marked employees*/
						TempEmployees.push_back(Employees[i]);
					}
				}

				/*overwrites old vector with new one*/
				Employees = TempEmployees;
				break;
			}
			case 5:
			{
				WriteEmployees();
				return;
				break;
			}
			default:
			{
				cout << "ERROR::Switch outta bounds" << endl;
				break;
			}
			}
		} while (Command != "exit");
	}

	void ReadEmployees()
	{/*reads the employee file and populates Employees<> vector*/
		ifstream Reader;
		int NoEmps, EmpType;
		string Input;
		Chef TempChef;
		GeneralEmployee TempGen;

		Employees.clear();

		Reader.open("Employees.txt");

		/*obtains the number of employees*/
		Reader >> NoEmps;

		for (int i = 0; i < NoEmps; i++)
		{
			/*reads the type of employee*/
			Reader >> EmpType;

			/*determines which derived class to use*/
			if (EmpType == 1)
			{
				Employees.push_back(new Chef);

				Employees[i]->Read(Reader);
			}
			else if (EmpType == 0)
			{
				Employees.push_back(new GeneralEmployee);

				Employees[i]->Read(Reader);
			}
			else
			{
				cout << "ERROR::Issue with the Employees file" << endl;
			}
		}
		Reader.close();
	}

	void WriteEmployees()
	{/*writes employees to file*/
		ofstream Writer;
		Writer.open("Employees.txt");

		Writer << Employees.size() << endl;

		/*auto used for simplicity*/
		for (auto X : Employees)
		{
			X->Write(Writer);
		}

		Writer.close();
	}

	void WriteMisc()
	{/*Writes the misc file*/
		ofstream Writer;
		Writer.open("Misc.txt");

		Writer << MaxNoTakeaways << endl << NoTakeaways << endl << DeliveryCost;

		Writer.close();
	}

	void ReadMisc()
	{/*reads the misc File*/
		ifstream Reader;
		Reader.open("Misc.txt");

		Reader >> MaxNoTakeaways >> NoTakeaways >> DeliveryCost;

		Reader.close();
	}

	void GenerateReport()
	{/*generates the daily report*/
		string Loyals[3], Block, Temp;
		string Cuisine, Dish, FileName, Command;
		int Counter = 0;
		double Revenue;

		/*Calculates the top 3 customers in terms of orders*/
		Block = CalculateLoyalty();

		/*splits block into 3 customers*/
		for (int i = 0; i < Block.size(); i++)
		{
			if (Block[i] != ',')
			{
				Temp += Block[i];
			}
			else
			{
				Loyals[Counter] = Temp;
				Temp.clear();
				Counter++;
			}
		}
		Loyals[Counter] = Temp;
		Temp.clear();
		Counter++;

		/*calculates the revenue from all orders*/
		Revenue = CalculateRevenue();

		/*calulates and returns the most popular cuisine*/
		Cuisine = PopularCusine();

		/*calulates and returns the most popular cuisine*/
		Dish = PopularDish();
		
		MenuTitle = "Generate Report > ";

		AJT.SCH.ScreenCleanerTM(0, MenuTitle);

		cout << "Please enter a nane for the report: " << endl << "> ";
		getline(cin >> ws, FileName);

		FileName += ".txt";

		/*writes the report*/
		ofstream Writer;
		Writer.open(FileName);

		Writer << "Daily Report" << endl;
		Writer << endl << "No. of orders booked: " << NoOrders;
		Writer << endl << "Most popular cuisine: " << Cuisine;
		Writer << endl << "Most Popular Dish: " << Dish;
		Writer << endl << "Top customers: " << endl;

		if (Loyals[0] != "-1")
		{Writer << "\t1) " << Loyals[0] << endl;}

		if (Loyals[1] != "-1")
		{Writer << "\t2)" << Loyals[1] << endl;}

		if (Loyals[2] != "-1")
		{Writer << "\t3)" << Loyals[2] << endl;}
		
		Writer << endl << endl;
		Writer << "Total Income: £" << Revenue;

		Writer.close();

		cout << FileName << " successfully created" << endl;
		cout << "Enter [return] to return to menu" << endl << "> ";
		cin >> Command;

		Command = AJT.VC.CustCheck(Command, "return");
	}

	double CalculateRevenue()
	{
		double Temp = 0 ;

		/*loops through every Order and obtains their total bill*/
		for (int i = 0; i < Orders.size(); i++)
		{
			Temp += Orders[i].GetPrice();
		}

		return Temp;
	}

	string CalculateLoyalty()
	{
		int Count;
		int LoyalCount[3] = { 0,0,0 };
		string Temp, Data, Loyals[3] = {"-1","-1","-1"};

		/*counts the occurences of each customer*/
		for (int i = 0; i < Customers.size(); i++)
		{
			Count = 0;
			for (int j = 0; j < Orders.size(); j++)
			{
				if (Orders[j].GetCustID() == Customers[i].GetID())
				{
					Count++;
				}
			}

			/*pushes back entries in Loyals[] and LoyalCount[] if Count is larger
			than a specific index*/
			if (Count > LoyalCount[0])
			{
				LoyalCount[2] = LoyalCount[1];
				Loyals[2] = Loyals[1];

				LoyalCount[1] = LoyalCount[0];
				Loyals[1] = Loyals[0];

				LoyalCount[0] = Count;
				Temp = (Customers[i].GetName() + " [" + Customers[i].GetID() + "] ");
				Loyals[0] = Temp;
			}
			else if (Count > LoyalCount[1])
			{
				LoyalCount[2] = LoyalCount[1];
				Loyals[2] = Loyals[1];

				LoyalCount[1] = Count;
				Temp = (Customers[i].GetName() + " [" + Customers[i].GetID() + "] ");
				Loyals[1] = Temp;
			}
			else if (Count > LoyalCount[2])
			{
				LoyalCount[2] = Count;
				Temp = (Customers[i].GetName() + " [" + Customers[i].GetID() + "] ");
				Loyals[2] = Temp;
			}
		}

		/*takes each index and turns it into a signle variable*/
		Data = Loyals[0] + ",";	//most
		Data += Loyals[1] + ",";
		Data += Loyals[2];		//least

		return Data;
	}

	string PopularCusine()
	{
		vector <FoodItem*> AllDishes;
		vector <FoodItem*> TempVect;
		string CurrentPop;
		vector <int> Count;
		int Temp = 0;

		/*adds the basket of every order into one vector*/
		for (int i = 0; i < Orders.size(); i++)
		{
			TempVect = Orders[i].GetBasket();
			AllDishes.insert(AllDishes.end(), TempVect.begin(), TempVect.end());
		}

		/*counts the occurence of each cuisine within all orders*/		
		for (int i = 0; i < AllDishes.size(); i++)
		{
			Temp = 0;
			for (int j = 0; j < AllDishes.size(); j++)
			{
				if (AllDishes[i]->GetCuisine() == AllDishes[j]->GetCuisine())
				{
					Temp++;
				}
			}
			Count.push_back(Temp);
		}

		int Max = -1, MaxIndex;

		/*sorts out which occurence is the greatest*/
		for (int i = 0; i < Count.size(); i++)
		{
			if (Count[i] > Max)
			{
				Max = Count[i];
				MaxIndex = i;
			}
		}
		
		return AllDishes[MaxIndex]->GetCuisine();
	}

	string PopularDish()
	{
		vector <FoodItem*> AllDishes;
		vector <FoodItem*> TempVect;
		string CurrentPop;
		vector <int> Count;
		int Temp = 0 ;

		/*adds the basket of every order into one vector*/
		for (int i = 0; i < Orders.size(); i++)
		{
			TempVect = Orders[i].GetBasket();
			AllDishes.insert(AllDishes.end(), TempVect.begin(), TempVect.end());
		}

		/*counts the occurence of each dish in all orders*/
		for (int i = 0; i < AllDishes.size(); i++)
		{
			Temp = 0;
			for (int j = 0; j < AllDishes.size(); j++)
			{
				if (AllDishes[i]->GetID() == AllDishes[j]->GetID())
				{
					Temp++;
				}
			}
			Count.push_back(Temp);
		}

		int Max = -1, MaxIndex;

		/*sorts out which occurence is the greatest*/
		for (int i = 0; i < Count.size(); i++)
		{
			if (Count[i] > Max)
			{
				Max = Count[i];
				MaxIndex = i;
			}
		}

		return AllDishes[MaxIndex]->GetName();
	}

private:
	vector <Order> Orders;
	vector <Employee*> Employees;
	vector <Customer> Customers;
	/*couldn't think of a better name for the menu object*/
	Menu Bwydlen;
	int MaxNoTakeaways;
	int NoTakeaways;
	int NoOrders = 0;
	double DeliveryCost;
};

int main()
{/* main*/
	RestraurantSys RSys;

	/*calls the main menu*/
	RSys.MainMenu();
}