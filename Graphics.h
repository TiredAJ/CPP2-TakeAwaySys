#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Graphics
{
public:
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

private:
	class Table
	{
	public:
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
			{TableWidth += FieldWidths[i];}

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

	private:
		string TableName = "Default";
		char PrimaryBorder = '='; char SecondaryBorder = '-'; char OuterBorder = '*';
		vector <string> Headers;
		vector <vector <string>> Records;	//Records stored as CSVs
		vector <int> FieldWidths;
		int NoFields;
	};

	vector <Table> Tables;
};