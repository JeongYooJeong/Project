#include <iostream>
#include <string>
#include <cstdlib>
#define MAX 100
#define air_size 3 // The number of airlines

using namespace std;

class MYSEAT // This class saves each user's seat information.
{
	private:
		int seat_size; // The number of seats a user reserved
		int air[5]; // kind of airline a user reserved
		int row[5]; // row information of reserved seat
		int col[5]; // column information of reserved seat
	public:
		MYSEAT()
		{
			seat_size  = 0; //initialization
		} 
		int seat(int num)
		{
			seat_size += num;
			return seat_size; // If a user reserves seat, seat_size changes
		}

		int out_seatsize()
		{
			return seat_size;
		} // return seat_size
		
		int out_air(int i)
		{
			return air[i];
		} // return the kind of airline reserved
		int out_row(int i)
		{
			return row[i];
		} // return row information of seat
		int out_col(int i)
		{
			return col[i];
		} // return column information of seat
		void seat_info(int i,int x, int y, int z)
		{
			air[i] =x;
			row[i] =y;
			col[i] =z;
		} // save new reserved seat information
		void print(int i)
		{
			cout <<  i+1 << ": Airline " << (char)(air[i]+'A')<< " seat " << row[i]<< "." << col[i] << endl;
		} // print user's seat information 
		void st_return(int num)
		{
			int i=0;
			seat_size--;
			for(i= num-1; i< seat_size; i++)
			{
				air[i] = air[i+1];
				row[i] = row[i+1];
				col[i] = col [i+1];
			}
			cout << "Successfully Returned\n";
		}// renew seat information when user returned his seat
};
class AIRLINE // This class save airline's seat information : remaining seat number
{
	private:
		int first_remain,economy_remain;
		char seat[5][5];
	public:
		AIRLINE();
		int remain(); // the number of remaining seats
		char show_seat(int i, int j); // Seat information: O or X
		char get_seat(int i, int j); //reservation
		char return_seat(int i, int j);//return
		void get_first()
		{
			first_remain--;
		} 
		void get_economy()
		{
			economy_remain--;
		}
		int firstclass()
		{
			return first_remain;
		}
};


class BOX // In this BOX, I will put all functions and variables !!!
{
	private:
		int menu_return;// let this variable to return to menu
		string id[MAX]; 
		string password[MAX]; 
		string temp_id; // temporarily saved id information to check 
		string temp_password; // temporarily saved password information to check
		AIRLINE airth[air_size]; 
		MYSEAT myseat[MAX];
		int index; // I will put one index number to one user
		int signth; // the order of signing
	public:
		BOX()
		{
			signth = 0;
			for(int i=0; i<MAX; i++)
			{
				id[i] = "0", password[i] = "0";
			}
		} //initialization
		void process(); // menu-select process
		void sign_up(); // sign_up
		void show_status(); // show airline_seat_status
		void reserve(); //reservation
		void check(); // check whether id and password user entered exist
		int account_number(int i)
		{
			index = i;
		} // fix index number
		void see_myseat(); // show an user's seat information
		void returning(); // return seat
};

AIRLINE :: AIRLINE()
{
	for(int i=0; i<5; i++)
		for(int j=0;j<5;j++)
			seat[i][j] = 'O';
	first_remain=5,economy_remain=20;			
} // initialization
int AIRLINE :: remain()
{
	return (first_remain + economy_remain);
} // The number of remaining seat
char AIRLINE :: show_seat(int i, int j)
{
	return seat[i][j];
}

char AIRLINE :: get_seat(int i, int j)
{
	seat[i][j] = 'X';
} //seat reserved. So seat information changes O -> X
char AIRLINE :: return_seat(int i, int j)
{
	seat[i][j] = 'O';
	if (i == 0)
		first_remain++;
	else
		economy_remain++;
} // seat returned. So seat information changes X -> O. the number of remaining seat changes,too.

void BOX :: returning()
{
	int num=0; // how many returned??
	
	int air_num,i,j; // which airline, row and colmun return?? 

	see_myseat(); //show your seat you reserved
	if(menu_return == 1)
		return; // 0-to menu
	cout << "Choose number :";
	cin >> num;

	air_num = myseat[index].out_air(num-1);
	i = myseat[index].out_row(num-1);
	j = myseat[index].out_col(num-1);
	airth[air_num].return_seat(i-1,j-1);
	myseat[index].st_return(num);
}

void BOX :: see_myseat()
{
	int i=0;
	check(); // who are you?? I will check using ID and Password. 
	int size = myseat[index].out_seatsize();
	if(menu_return == 1)
		return;
	for(i=0; i<size;i++)
		myseat[index].print(i); //print your seat
}

void BOX :: reserve()
{
	int i=0,j=0;
	int select=0; // which airline reserveed??
	int num=0; // how many reserved??
	int row,col;
	int all_remain=0; // The numver of all airline's seats

	for(i=0; i<air_size; i++)
	{
		all_remain += airth[i].remain();	
	}
	if(all_remain == 0)
		cout << "Sorry. All seats are already reserved. Please use this service next time.\n"; // cannot reserve anymore
	check(); // Who are you?
	if(menu_return == 1)
		return;
	if( myseat[index].out_seatsize() == 5)
	{
		cout << "You cannot reserve anymore\n";
		return;
	}
	cout << "Select Airline A, B, C (1-A, 2-B, 3-C 0-to menu)-> ";
	cin >> select;

	if(select == 0)
		return;
	
	cout << "How many seats do you need (up to 5) : ";
	cin >> num;

	
	if ( myseat[index].seat(num) > 5)
	{	
		cout << "Error: You cannot reserve " << num << " seat(s)\n";
		myseat[index].seat(-num);
		return;
	}
	for(i=0; i < num; i++)
	{
		if(airth[select-1].firstclass() ==0)
		{
			cout << "The first class seats are full\n"
				 << "Do you want to reserve economy class (Yes->1, No->2) ? ";
			cin  >> j;		
			if(j ==2 )
			{
				myseat[index].seat( -(num-i) );
				return;
			}
		}
	
	retype:
		cout << "Input "<<i+1<<"th X Y -> ";
		cin >> row;
		cin	>> col;
		if( row < 1 || row > 5 || col < 1 || col > 5)
		{
			cout << "ERROR: Please type proper seat number.\n";
			goto retype;		
		}
		if(airth[select-1].show_seat(row-1,col-1) == 'X')
		{
			cout << "ERROR: This seat is already reserved. Please type proper seat number\n";
			goto retype;
		}

		if( row == 1)
			airth[select-1].get_first();
		else
			airth[select-1].get_economy();
		myseat[index].seat_info(i,select-1,row,col);
		airth[select-1].get_seat(row-1,col-1);
	
		cout << "Successfully reserved\n";
	}
}

void BOX :: check()
{
	menu_return =0;
	int i=0;
	cout << "Input your ID (0-to menu):";
	cin >> temp_id;
	if(temp_id == "0")
	{
		menu_return = 1;
		return;
	}
	for( i=0; i<MAX; i++) //id check
	{
		if (temp_id != id[i])
		{
			if(i == MAX-1)
			{
				cout << "No ID\n";
				menu_return = 1;
				 return; 
			}
			continue;//check next index's id and password
		}
		 break;
	}
	while(1)//password check
	{
		cout << "Input your password : ";
		cin >> temp_password;
		if(temp_password == password[i])
			break;
		else
			cout << "Wrong!\n";
	}
	account_number(i); // fix index
}

void BOX :: show_status()
{
	int i=0;
	int all_remain=0;
	for(i=0; i<air_size; i++)
		all_remain += airth[i].remain();
	cout << "# Remaining Seat: "<< all_remain <<"\n\n\n";

	for(i=0; i<air_size; i++)
		cout << "  Airline "<< (char)(i+'A') << "     ";
		cout << "\n";
	for(i=0; i<air_size; i++)
		cout << "  1 2 3 4 5"<< "     ";
		cout << "\n";
	for(int row=0; row<5; row++)
	{
		for(i=0; i < air_size; i++)
		{
			cout << row+1;
			for(int col=0; col<5; col++)
			{
				cout << " "<<airth[i].show_seat(row,col);
			}
			cout << "     ";
		}
		cout << "\n";
		if(row ==0)
		{
			for(int k=0; k< air_size; k++)	
				cout << "  ---------     ";
			cout << "\n";
		}
	}
}

void BOX :: sign_up()
{
	cout << "Input your ID(0-to menu) :";
	cin >> id[signth];
	if(id[signth] == "0")
		return;
	else
		cout << "Input your password : ";
		cin >> password[signth];
		cout << "Hello "<< id[signth] <<endl;
		signth++;
}

void BOX ::  
process()
{

	int select=0;
	cout << "\n---------------------------------------------\n"
		 << "-------- Airline Reservation System  --------\n"
		 << "-------------    Menu List    ---------------\n\n";
	cout << " 1. Sign up\n 2. Show status\n 3. Reservation\n 4. Reservation condition\n 5. Returning\n 0. Exit\n"
		 <<"Select-> ";
	cin  >> select;
	cout << "\n";
	switch(select)
	{
		case 0:
			exit(0);
		case 1: sign_up(); break;
		case 2: show_status(); break;
		case 3: reserve(); break;
		case 4: see_myseat(); break;
		case 5:	returning(); break;
		default:
				cout << "Error (Please check Menu List Again)\n";
	}
} // Menu and Select ~~~

int main()
{
	BOX box;
	cout << "##################################\n"
		 << "This is Project#3-3 Solution\n"
		 << "##################################\n";
	while(1)
	{
		
		box.process();
	}
	return 0;
}
