#include <iostream>
#include <cstdlib>
using namespace std;

class Money 
{
	private:
		int dollars;
		int cents;
	public:
		Money();
		Money(int theDollars, int theCents);
		void getMoney(double amount); // decide dollars value and cents value.
		const Money operator +(const Money& amount2)const;
		const Money operator -(const Money& amount2)const;
		bool operator ==(const Money& amount2)const;
		friend const Money operator -(const Money& amount);
		friend ostream& operator <<(ostream& outputStream, Money& amount);
		friend istream& operator >>(istream& inputStream, Money& amount);
};
const Money operator -(const Money& amount)
{
	return Money(-amount.dollars, -amount.cents);
}
ostream& operator <<(ostream& outputStream, Money& amount) // new name of cout is outputStream. It will print class information. 
{
	int absDollars = abs(amount.dollars);
	int absCents = abs(amount.cents);
	if(amount.dollars<0 || amount.cents<0)
		outputStream<<"$-"; //When dollars value is negative.
	else
		outputStream<<"$";
	outputStream<< absDollars <<'.';
	if(absCents>=10)
		outputStream<< absCents;
	else
		outputStream<<'0'<<absCents;
	return outputStream;
}
istream& operator >>(istream& inputStream, Money& amount) //new name of cin is inputStream. It will write class information.
{
	char dollarsign; //should enter dollarsign
	inputStream >> dollarsign;
	if(dollarsign != '$')
	{
		cout << "No dollar sign in Money input.\n";
		exit(1); //End
	}
	double amountAsDouble;//input is double type. It makes calculation more accurate.
	inputStream >> amountAsDouble;
	amount.getMoney(amountAsDouble);
	return inputStream;
}
int main()
{
	Money yourAmount,myAmount(10,9); //fix my money $10.09.
	cout << "Enter an amount of money: " ;
	cin >> yourAmount;
	cout << "Your amount is "<< yourAmount;
	cout<<endl;
	cout << "My amount is "<< myAmount;
	cout <<endl;

	if(yourAmount == myAmount)
		cout << "We have the same amounts.\n";
	else
		cout << "One of us is richer.\n";

	Money tryPlus = yourAmount + myAmount;
	cout<< yourAmount << " + " << myAmount << " equals " << tryPlus;
	cout << endl;

	Money tryMinus = yourAmount - myAmount;
	cout << yourAmount << " - " << myAmount << " equals " << tryMinus;
	cout << endl;
	return 0;
}
const Money Money :: operator +(const Money& amount2)const
{
	int allCents1 = cents + dollars*100;
	int allCents2 = amount2.cents + amount2.dollars*100;
	int sumCents = allCents1 + allCents2;
	int finalDollars = sumCents / 100;
	int finalCents = sumCents % 100;
	return Money(finalDollars, finalCents);
}
const Money Money :: operator -(const Money& amount2)const
{
	int allCents1 = cents + dollars*100;
	int allCents2 = amount2.cents + amount2.dollars*100;
	int gapCents = allCents1 - allCents2;
	int absGapCents = abs(gapCents);
	int finalDollars = absGapCents/100;
	int finalCents = absGapCents%100;
	if(gapCents == 0)
		return Money(0,0);
	else if(gapCents > 0)
		return Money(finalDollars, finalCents);
	else 
		return Money(-finalDollars, -finalCents);
}
bool Money :: operator ==(const Money& amount2)const
{
	return ( dollars == amount2.dollars && cents == amount2.cents );
}
Money :: Money() {}
Money :: Money(int theDollars, int theCents)
{
	dollars = theDollars;
	cents = theCents;
}
void Money :: getMoney(double amount)
{
	dollars = amount; 
	cents = (amount-dollars)*100 +0.5 ; // Because amount is double type and cents is int type, +0.5
}
