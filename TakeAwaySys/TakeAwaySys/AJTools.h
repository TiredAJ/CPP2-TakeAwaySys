#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class AJTools
{
private:
	class Table
		{
		public:
			Table()
			{}

			Table(string Name, char PrimBorder, char SecBorder, char OuterBorder)
			{
				TableName = Name;
				PrimaryBorder = PrimaryBorder;
				SecondaryBorder = SecBorder;
				this->OuterBorder = OuterBorder;
			}

			string GetName()
			{
				return TableName;
			}

			void AddHeader(string Header)
			{
				Headers.push_back(Header);
				FieldWidths.push_back(Header.size());
			}

			void AddRecord(string Record)
			{
				string TempStr;
				vector <string> TempFields;

				for (int i = 0; i < Record.length(); i++)
				{
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

				if (TempStr.size() > FieldWidths[NoFields])
				{
					FieldWidths[NoFields] = TempStr.size();
					NoFields++;
				}

				TempStr.clear();
				Records.push_back(TempFields);
			}

			void Display()
			{
				//vector <vector <string>> TempRecords;
				int FieldWidth = 0;

				FieldWidth += 3;
				//int TableInnerWidth = (FieldWidth * Headers.size()) + (Headers.size() - 1);

				int TableWidth;

				for (int i = 0; i < FieldWidths.size(); i++)
				{
					TableWidth += FieldWidths[i];
				}

				int TableInnerWidth = TableWidth + 2;
				int TableLength = (Records.size() * 2) + 3;
				int RecordCount = 0;
				string FormatString;

				for (int i = 0; i <= TableLength; i++)
				{
					if (i == 0 || i == TableLength)
					{
						cout << endl << FormatString.assign(TableWidth, OuterBorder);
					}
					else if (i == 1)
					{
						cout << endl << OuterBorder;
						for (int j = 0; j < Headers.size(); j++)
						{
							cout << left << " " << setw(FieldWidth - 1) << Headers[j] << OuterBorder;
						}
					}
					else if (i == 2)
					{
						cout << endl << OuterBorder << FormatString.assign(TableInnerWidth, PrimaryBorder);
						cout << OuterBorder;
					}
					else if (i > 3 && (i % 2 == 0))
					{//records					
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
					{//record separators
						cout << endl << OuterBorder;
						cout << FormatString.assign(TableInnerWidth, SecondaryBorder) << OuterBorder;
					}

				}
			}

			void ToFile(string FileLoc)
			{

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
	{
	public:
		_CommaRemover()
		{};

		string Remove(char Removable, string Input, string Option) //[left/right]
		{
			string Temp, Result;
			Temps.clear();

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
	{
	public:
		_ScrClnTM()
		{}

		void ScreenCleanerTM(int Option)
		{
			system("cls");
		}

		void ScreenCleanerTM(int Option, string Keeps)
		{
			system("cls");
			cout << Keeps << endl;

		}

	private:

	};

	class _Graphics
	{
	public:
		_Graphics()
		{}

		void TableSetup(string TableName, char PrimaryBorder, char SecondaryBorder, char OuterBorder)
		{
			Table TempTable(TableName, PrimaryBorder, SecondaryBorder, OuterBorder);
			Tables.push_back(TempTable);
		}

		void AddHeaders(string TableName, string NewHeader)
		{
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
				//error message "please make a new table" etc.
			}

		}

		void AddRecord(string TableName, string Record)
		{
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
				//error message
			}
		}

		void Display(string TableName)
		{
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
		{
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
		{
			int NoOptions;

			NoOptions = Input.size();

			switch (Option)
			{
			case 0:
			{
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << Input[i] << endl;
				}
				break;
			}
			case 1:
			{
				for (int i = 0; i < Input.size(); i++)
				{
					cout << i + 1 << ") " << Input[i] << endl;
				}
				cout << Input.size() + 1 << ") Exit" << endl << endl;
				NoOptions++;
				break;
			}
			case 2:
			{
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

				break;
			}
			}

			cout << "Please choose an option [1-" << NoOptions << "]" << endl;
		}

		void Line(char Character, int Length)
		{
			string TempString;
			cout << TempString.assign(Character, Length) << endl;
		}

	private:
		vector <Table> Tables;
		_CommaRemover GCR;
	};
	
	class _ValidityChecker
	{
	public:
		_ValidityChecker()
		{

		}

		string YNCheck(string Input)
		{
			while (Input != "yes" && Input != "no")
			{
				cout << "Please enter [yes] or [no]" << endl << "> ";
				cin >> Input;
			}

			return Input;
		}

		string CustCheck(string Input, string Control)
		{
			while (Input != Control)
			{
				cout << "Please enter [" << Control << "]" << endl << "> ";
				cin >> Input;
			}

			return Input;
		}
	};

public:
	AJTools()
	{}

	_Graphics Graphics;		//Graphics handler
	_CommaRemover CMH;		//CommaRemover handler
	_ScrClnTM SCH;	//ScreenCleaner Handler
	_ValidityChecker VC;
};