#include <iostream>
using namespace std;

class IntPair
{
	private:
		int first; // first number
		int second; //second number
	public:
		IntPair(int firstValue, int secondValue);
		int getFirst()const; //return first
		int getSecond()const; //return second
		IntPair operator ++(); //prefix ++a
		IntPair operator ++(int); //postfix a++ 
};

int main()
{
	IntPair a(10,29);
	cout << "Postfix a++: Start value of object a: "<<a.getFirst() << " "<< a.getSecond()<< endl;
	IntPair b = a++;
	cout << "Value returned: " << b.getFirst() << " "<< b.getSecond()<< endl;
	cout << "Changed object: " << a.getFirst() << " "<< a.getSecond()<< endl;
	a = IntPair(13,31);
	cout << "Prefix ++a: Start value of object a: "<<a.getFirst() << " " << a.getSecond() <<endl;
	b = ++a;
	cout << "Value returned: " << b.getFirst() << " "<< b.getSecond()<< endl;
	cout << "Changed object: "<< a.getFirst() << " " << a.getSecond() << endl;

	return 0;
}
IntPair IntPair :: operator ++() //++a
{
	first++;
	second++; // +1 in advance.
	return IntPair(first,second); //return the changed value

}
IntPair IntPair :: operator ++(int) //a++
{
	int tempFirst = first++; // after saving the original value,  +1
	int tempSecond = second++;
	return IntPair(tempFirst,tempSecond);//return the original value
}

IntPair :: IntPair(int firstValue, int secondValue)
{
	first = firstValue;
	second = secondValue;
}
int IntPair :: getFirst()const
{
	return first;
}
int IntPair :: getSecond()const
{
	return second;
}
