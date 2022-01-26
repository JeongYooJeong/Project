#include <iostream>
using namespace std;

void SHAPES(); // To Programming Problem 1 Function
void MATH();  // To Programming Problem 2 Function
unsigned long long Factorial(int x); // To calculate factorial value in programing problem 2 function
unsigned long long COMB(int n, int k); // To calculate combination value in programing problem 2 function

int main()
{	
	while(1)
	{	
		int i=0;
		char option;

		for(i=0; i<31; i++)
			cout << "#";
		cout << "\n"
			 << "Main Menu\n"
			 << "Enter your command!\n";
		for(i=0; i<31; i++)
			cout << "#";
		cout << "\n\n";
		cout << "1. Problem1\n2. Problem2\n0. Exit\n\n"
		     << "Command >> "; // I made the main menu!!

		cin >> option;

		switch(option) // run the process user enter
		{
			case '1':
				SHAPES(); // Nested function...show a shape according the number,using *
				break;
			case '2':
				MATH(); // Nested function...I can calculate combination or Factorial value
				break;
			case '0':
				cout << "\nProgram is terminating\n\n"; // program terminate
				return 0;
			default :
				cout << "\nWrong input. Please choose one of the above options.\n\n"; //Error
				continue;
		}	

	}	
	return 0;
}

void SHAPES() //Programing Problem 1.
{
	char option;
	int i,j;

	cout << "\n*Drawing a shape\n"
		 << "(1-Rectangle, 2-Triangle, 3-Inverted Triangle, 4-Letter 'H', 0-Back to Main Menu\n)";

	while(1)
	{	
		cout << "Choose shape >> ";
		cin >> option;
	
		cout << "\n";

		switch(option)
		{
			case '1':
				for (i=0; i<5; i++)
				{
					for(j=0; j<9; j++)
						cout << "*";
					cout << "\n";
				}
				cout << "\n";
				break;
			case '2':
				for (i=0; i<5; i++)
				{	
					for(j=i; j<4; j++)
						cout << " ";
					for(j=0; j < 2*i+1	;j++)
						cout << "*";
					cout << "\n";
				}
				cout << "\n";
				break;
			case '3':
				for (i=0; i<5; i++)
				{
					for(j=0; j<i ; j++)
						cout << " ";
					for(j=0; j< 9-2*i ;j++)
						cout << "*";
					cout << "\n";
				}
				cout << "\n";
				break;
			case '4':
				for(i=0; i<5; i++)
				{					
					for(j=0; j<9; j++)
						if(i!=2)
							if(j<2 || j>6)
								cout << "*";
							else
								cout << " ";
						else
							cout << "*";
					cout << "\n";
				}
				cout << "\n";
				break;
			case '0':
				cout << "Back to main menu\n\n";
				return; //Back to main menu
			default:
				cout << "Wrong input. Please choose one of the above options.\n\n";
				continue; //Error		
		}	
	}	
}	

void MATH() // Programing Problem 2.
{
	char option;
	int n,k;

	cout << "\n*Choose Function of calculator\n(1-Factorial, 2-Combination, 0-Back to main menu)\n";

	while(1)
	{
		cout << "Choose function >> ";
		cin >> option;
		
		switch(option)
		{
			case '1':
				cout << "\nInput of N [n!] = ";
				cin >> n;
				cout <<n<<"! is "<<Factorial(n)<<"\n\n";
				break;
			case '2':
				cout << "\nInput of N = ";
				cin >> n;
				cout << "Input of K = ";
				cin >> k;
				cout << n << "C" << k << " is "<< COMB(n,k)<<"\n\n";
				break;
			case '0':
				cout << "\nBack to main menu\n\n";
				return; //Back to main menu
			default:	
				cout << "\nWrong input. Please choose one of the above options.\n\n"; //Error
		}	
	}
}	

unsigned long long Factorial(int x)
{
	if (x>1)
		return x*Factorial(x-1); //factorial calculation

	if (x==1 || x==0)
		return 1; //1! and 0! is 1 by definetion
	else
		return 0;
}

unsigned long long COMB(int n, int k)
{
	return ( Factorial(n) / (Factorial(k) * Factorial(n-k)) ); // combination calculation
}	
