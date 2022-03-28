#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class CommaRemover
{
public:
	CommaRemover();

	string Remove(char Removable, string Input, string Option) //[left/right]
	{
		vector <string> Temps; string Temp, Result;

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
		}
		return Result;
	}

private:

};

