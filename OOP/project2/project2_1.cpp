#include <iostream>

using namespace std;

class DayOfYear
{
public:
	void output();// 'output' will print the date
	int month;
	int day;	
	int get_month()
	{
		if(month < 1 || month > 12)
		{
			cout << "Error: Please enter proper month\n";
			return -1;
		}
		return 0;
	}
	int get_day()
	{
		if(month ==2 && (day < 1 || day > 28) )
		{
			cout << "Error: Please enter proper day\n";
			return -1;
		}	
		if( (month ==1 || month ==3 || month ==5 || month ==7 || month ==8 || month ==10 || month ==12) && (day <1 || day > 31) )
		{
			cout << "Error: Please enter proper day\n";
			return -1;
		}
		if( (month ==4 || month ==6 || month ==9 || month ==11) && (day < 1 || day > 30) )
		{
			cout << "Error: Please enter proper day\n";
			return -1;
		}
		return 0;
	}
};  //save date information user entered and error check

int main()
{
	DayOfYear today,birthday;// declare variables to save today's date and bithday's date	
		
	cout << "Enter today's date:\n";
	while(1)
	{		
		cout << "Enter month as a number: ";
		cin >> today.month;
		if(today.get_month() == 0)
			break;			
	}
	while(1)
	{
		cout << "Enter the day of the month: ";
		cin >> today.day;
		if(today.get_day() == 0)
			break;
	}	
	cout << "Enter your birthday:\n";
	while(1)
	{
		cout << "Enter month as a number: ";
		cin >> birthday.month;
		if(birthday.get_month() == 0)
			break;
	}
	while(1)
	{
		cout << "Enter the day of the month: ";
		cin >> birthday.day;
		if(birthday.get_day() == 0 )
			break;
	}	

	cout << "Today's date is ";
	today.output();
	cout << "Your birthday is ";
	birthday.output();

	if(today.month == birthday.month && today.day == birthday.day)
		cout << "Happy Birthday!\n"; 
	else
		cout << "Happy Unbirthday!\n";
	
	return 0;
}

void DayOfYear :: output()
{
	switch(month)
	{
		case 1:
			cout << "January "; break;
		case 2:
			cout << "February "; break;
		case 3:
			cout << "March "; break;
		case 4:
			cout << "Aprill "; break;
		case 5:
			cout << "May "; break;
		case 6:
			cout << "June "; break;
		case 7:
			cout << "July "; break;
		case 8:
			cout << "August "; break;
		case 9:
			cout << "September "; break;
		case 10:
			cout << "October "; break;
		case 11:
			cout << "November "; break;
		case 12:
			cout << "December "; break;
	}
	cout << day << endl;
}
