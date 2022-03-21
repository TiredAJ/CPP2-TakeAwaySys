#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class ScrClnTM
{
public:
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
