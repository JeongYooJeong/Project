#include <iostream>
using namespace std;

class CharPair
{
	private:
		char first; //first character
		char second;//second character
	public:
		CharPair();
		char& operator [](int index); //return a character according to the index.
};
int main()
{
	CharPair a;
	a[1] = 'A',a[2]= 'B';
	cout << "a[1] and a[2] are:\n";
	cout << a[1] <<a[2] <<endl;
	cout << "Enter two letters (no spaces):\n";
	cin >> a[1] >>a[2] ; // a[index] changes
	cout << "You entered:\n";
	cout << a[1] << a[2] <<endl;
	return 0;
}
char& CharPair :: operator [](int index)
{
	if (index == 1)
		return first;
	else if(index ==2)
		return second;
}
CharPair :: CharPair()
{}
