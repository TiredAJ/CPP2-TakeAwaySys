#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class AJTools
{
/// <AJTools>
/// AJTools (AJT) was set to replace the failed Graphics header from
/// C++ (coursework) 1, and extend it's functionality.
/// I've tried to use it to reduce repetition in code (with VC 
/// helping significantly with that). I'm hoping to continue the
/// development of AJTools for future projects of mine.
/// A major part I'd like to implement is using templates 
/// </AJTools>

private:
	class Table
	{
	/*Table was designed to handle generating tables for formatted
	* output. I'd like to expand Table to accept CSV vectors eventually.
	*/
	public:
		Table()
		{}

		Table(string Name, char PrimBorder, char SecBorder, char OuterBorder)
		{/*For initialising a table*/
			TableName = Name;
			PrimaryBorder = PrimaryBorder;
			SecondaryBorder = SecBorder;
			this->OuterBorder = OuterBorder;
		}

		string GetName()
		{/*retrieves the name of the table*/
			return TableName;
		}

		void AddHeader(string Header)
		{/*adds a header to the table*/
			Headers.push_back(Header);
			FieldWidths.push_back(Header.size());
		}

		void AddRecord(string Record)
		{/*adds a record to the table*/
			string TempStr;
			vector <string> TempFields;

			for (int i = 0; i < Record.length(); i++)
			{/*for-loop separates input into fields*/
				if (Record[i] != ',')
				{
					TempStr += Record[i];
				}
				else
				{
					TempFields.push_back(TempStr);

					if (TempStr.size() > FieldWidths[NoFields])
					{
						FieldWidths[NoFields] = TempStr.size();
						NoFields++;
					}

					TempStr.clear();
				}
			}
			TempFields.push_back(TempStr);

			/*works out the size of each individual field*/
			if (TempStr.size() > FieldWidths[NoFields])
			{
				FieldWidths[NoFields] = TempStr.size();
				NoFields++;
			}

			TempStr.clear();
			Records.push_back(TempFields);
		}
		
		//ok, hear me out. we have Display(), ToFile() and GenerateTable();
		//GenerateTable() creates a table like normal, but adds it to a 
		//single string. That string is then outputted through either ofstream
		//or ostream
		void Display()
		{/*might overload with ostream*/
			int FieldWidth = 3;
			int TableWidth;

			for (int i = 0; i < FieldWidths.size(); i++)
			{/*works out the total width of the table*/
				TableWidth += FieldWidths[i];
			}

			/*calculates other parameters*/
			int TableInnerWidth = TableWidth + 2;
			int TableLength = (Records.size() * 2) + 3;
			int RecordCount = 0;
			string FormatString;

			/*this segment actually displays the table*/
			for (int i = 0; i <= TableLength; i++)
			{
				if (i == 0 || i == TableLength)
				{/*for the top and bottom border*/
					cout << endl << FormatString.assign(TableWidth, OuterBorder);
				}
				else if (i == 1)
				{/*inserts the headers*/
					cout << endl << OuterBorder;
					for (int j = 0; j < Headers.size(); j++)
					{
						cout << left << " " << setw(FieldWidth - 1) << Headers[j] << OuterBorder;
					}
				}
				else if (i == 2)
				{/*prints the line beneath the headers*/
					cout << endl << OuterBorder << FormatString.assign(TableInnerWidth, PrimaryBorder);
					cout << OuterBorder;
				}
				else if (i > 3 && (i % 2 == 0))
				{/*Displays the records*/
					cout << endl << OuterBorder;
					int FieldCount = 0;

					for (int k = 0; k < Records[RecordCount].size(); k++)
					{
						cout << " " << setw(FieldWidths[FieldCount]) << Records[RecordCount][k] << OuterBorder;
					}
					RecordCount++;
					FieldCount++;
				}
				else if (i > 3 && (i % 2 == 1))
				{/*inserts lines between records*/
					cout << endl << OuterBorder;
					cout << FormatString.assign(TableInnerWidth, SecondaryBorder) << OuterBorder;
				}
			}
		}

		void ToFile(string FileLoc)
		{//used for report?

		}

		private:
			string TableName = "Default";
			char PrimaryBorder = '='; char SecondaryBorder = '-'; char OuterBorder = '*';
			vector <string> Headers;
			vector <vector <string>> Records;	//Records stored as CSVs
			vector <int> FieldWidths;
			int NoFields;
		};

	class _CommaRemover
	{/*Comma remover is an odd one, again. Right now, it splits one variable that 
	 has two pieces of data in it, I.E. "ITA,Italian", and only shows the requested
	 part*/
	public:
		_CommaRemover()
		{};

		string Remove(char Removable, string Input, string Option)
		{
			string Temp, Result;
			Temps.clear();
			
			/*for-loop separates input into a vector*/
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

			/*for-loop pieces the vector back together, omitting 
			either the first or last element*/
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

	class _ScrClnTM
	{/*what it says on the tin, but with extra functionality and colours removed*/
	public:
		_ScrClnTM()
		{}

		void ScreenCleanerTM(int Option)
		{/*standard screen cleaner*/
			system("cls");
		}

		void ScreenCleanerTM(int Option, string Keeps)
		{/*screen cleaner with a persistent title*/
			system("cls");
			cout << Keeps << endl;
		}

		/*I'd like to potentially add another one that has 
		a temporary banner underneath the title for success messages etc.*/
	};

	class _Graphics
	{/*The new graphics table. It implements the functions needed to 
	 operate the Table class with extra handy bits*/
	public:
		_Graphics()
		{}

		void TableSetup(string TableName, char PrimaryBorder, char SecondaryBorder, char OuterBorder)
		{/*table initialisation*/
			Table TempTable(TableName, PrimaryBorder, SecondaryBorder, OuterBorder);
			Tables.push_back(TempTable);
		}

		void AddHeaders(string TableName, string NewHeader)
		{/*adds headers*/
			bool Found = false;
			for (int i = 0; i < Tables.size(); i++)
			{
				if (Tables[i].GetName() == TableName)
				{
					Found = true;
					Tables[i].AddHeader(NewHeader);

					break;
				}
			}
			if (Found == false)
			{
				cout << "ERROR::Table not found" << endl;
			}
			/*because the table stuff uses the Table Name as it's ID, 
			I plan on adding a function to display saved tables*/
		}

		void AddRecord(string TableName, string Record)
		{/*adds a record*/
			bool Found = false;
			for (int i = 0; i < Tables.size(); i++)
			{
				if (Tables[i].GetName() == TableName)
				{
					Found = true;
					Tables[i].AddRecord(Record);

					break;
				}
			}
			if (Found == false)
			{
				cout << "ERROR::couldn't add record to the table" << endl;
			}
		}

		void Display(string TableName)
		{/*displays a specified table*/
			for (int i = 0; i < Tables.size(); i++)
			{
				if (Tables[i].GetName() == TableName)
				{
					Tables[i].Display();
					break;
				}
				else
				{
					cout << endl << "ERROR::Cannot find specified table" << endl;
				}
			}
		}

		void ToFile(string TableName, string FileLoc)
		{/*used for displaying tables in a file*/
			for (int i = 0; i < Tables.size(); i++)
			{
				if (Tables[i].GetName() == TableName)
				{
					Tables[i].ToFile(FileLoc);
					break;
				}
				else
				{
					cout << endl << "ERROR::Cannot find specified table" << endl;
				}
			}
		}
		
		void DisplayOptions(vector <string> Input, int Option)
		{/*this function loops through a vector of options, and formats it as
		 a menu*/
			int NoOptions;

			NoOptions = Input.size();

			switch (Option)
			{
			case 0:
			{/*just the included options*/
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << Input[i] << endl;
				}
				break;
			}
			case 1:
			{/*extra exit option*/
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << Input[i] << endl;
				}
				cout << Input.size() + 1 << ") Exit" << endl << endl;
				NoOptions++;
				break;
			}
			case 2:
			{/*for inputted strings that have two pieces of data in one*/
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << GCR.Remove(',', Input[i], "left") << endl;
				}
				break;
			}
			case 3:
			{
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << GCR.Remove(',', Input[i], "right") << endl;
				}
				break;
			}
			default:
			{
				cout << "ERROR::Option out of bounds" << endl;
				break;
			}
			}

			/*Shows the user the range of their options*/
			cout << "Please choose an option [1-" << NoOptions << "]" << endl;
		}

		void Line(char Character, int Length)
		{/*this function serves two purposes
		 - removes the need for FormatLine variables
		 - reduces mistakes in mixing up the input for .assign*/
			string TempString;
			cout << TempString.assign(Length, Character) << endl;
		}

	private:
		vector <Table> Tables;
		_CommaRemover GCR;
	};
	
	class _ValidityChecker
	{/*ValidityChecker (VC) removes all the "while input is incorrect, ask for correct"
	 loops that follow menus and confirmation messages.*/
	public:
		_ValidityChecker()
		{}

		/*I could do the functions by refecence instead of value, but I think
		it's easier to read the command manually assigned*/
		string YNCheck(string Input)
		{/*simply checks if input is a yes or a no. Loops if false*/
			while (Input != "yes" && Input != "no")
			{
				cout << "Please enter [yes] or [no]" << endl << "> ";
				cin >> Input;
			}

			return Input;
		}

		string CustCheck(string Input, string Control)
		{/*checks if input equals the control variable*/
			while (Input != Control)
			{
				cout << "Please enter [" << Control << "]" << endl << "> ";
				cin >> Input;
			}

			return Input;
		}

		string NumRangeCheck(string Input, int LowerBound, int UpperBound)
		{/*checks if input is between parameters*/
			while (stoi(Input) < LowerBound && stoi(Input) > UpperBound)
			{
				cout << "Please enter a value between [" << LowerBound;
				cout << "] and [" << UpperBound << "]" << endl;
				cin >> Input;
			}

			return Input;
		}
	};

public:
	AJTools()
	{}

	_Graphics Graphics;		/*Graphics handler*/
	_CommaRemover CMH;		/*CommaRemover handler*/
	_ScrClnTM SCH;			/*ScreenCleaner Handler*/
	_ValidityChecker VC;	/*VC Handler*/
};