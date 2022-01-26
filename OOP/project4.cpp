#include <iostream>
#include <string>

using namespace std;

const int dataSize = 10; // Maximum number of students

class Student
{
	private:
		string studentName;
		int studentId;
	public:
		Student();
		Student(string getName, int getId);
		string callName(); //return studentName
		int callId(); // return studentId
};
class Class
{
	private:
		string instructor;
		string className;
		int total;
		Student* studentList[dataSize]; //pointer array to handle easily each student 
	public:
		Class();
		~Class(); // destructor to delete student pointer array
		Class(string getClassName, string getInstructor);
		Class(const Class& original); // copy constructor
		const Class& operator = (const Class& original); // member assignment operator
		void Register(string newName, int newId);
		void Withdraw(int deleteId);
		void SetClassName(string newClassName, string newInstructor);
		void Display();
		Class& myClass(); //return this class
		friend ostream& operator << (ostream& outputStream, const Class& printClass); // overloading to display class information
};

ostream& operator << (ostream& outputStream, const Class& printClass)
{
	int i=0;
	outputStream << "Professor :" << printClass.instructor << "       " << "Class Name :" <<printClass.className << "\n";
	for(i=0; i<48; i++)
		outputStream << "=";
	outputStream << "\n"
				 << "Total number of students :" << printClass.total << "\n\n";
	for(i=0; i< printClass.total; i++)
		outputStream << printClass.studentList[i]->callName() << "     " << printClass.studentList[i]->callId() << "\n";
	outputStream << "\n";
	return outputStream; 
}
int main()
{
   Class OOP("OOP", "Kim");
   OOP.Register("Aisha", 2015123123);
   OOP.Register("Smith", 2015123124);
   OOP.Register("Jenny", 2015123125);
   OOP.Display();
   
   Class DATA = OOP;

   DATA.SetClassName("Data Structure", "Yang");
   DATA.Withdraw(2015123123);
   DATA.Display();

   OOP.Display();

   Class Network(OOP);

   Network.SetClassName("NetWork", "Han");
   Network.Register("Esmay", 2015123126);
   Network.Display();

   OOP.Display();
   return 0;
}
Class :: Class () 
{
	total = 0;
}
Class :: ~Class()
{
	for(int i=0; i<total; i++)
		delete studentList[i];
}
Class :: Class (string getClassName, string getInstructor)
{
	total =0;
	className = getClassName;
	instructor = getInstructor;
}
Class :: Class (const Class& original)
{
	total = original.total;
	className = original.className;
	instructor = original.instructor;
	for(int i=0; i < total; i++)
		studentList[i] = new Student(original.studentList[i]->callName(), original.studentList[i]->callId());
}
const Class& Class :: operator = (const Class& original)
{
	total = original.total;
	className = original.className;
	instructor = original.instructor;
	for(int i=0; i < total; i++)
		studentList[i] = new Student(original.studentList[i]->callName(), original.studentList[i]->callId());
	return *this;
}
void Class :: Register (string newName, int newId)
{
	studentList[total] = new Student(newName, newId);
	total++;
}
void Class :: Withdraw (int deleteId)
{
	for(int i=0; i<total; i++)
		if(studentList[i]->callId() == deleteId)
		{	
			delete studentList[i];
			for(int j=i; j<total; j++)
				studentList[j] = studentList[j+1];
			studentList[total-1] = NULL;
			break;
		}
	total--;
}
void Class :: SetClassName(string newClassName, string newInstructor)
{
	className = newClassName;
	instructor = newInstructor;
}
void Class :: Display()
{
	cout << myClass() <<endl;
}
Class& Class :: myClass()
{
	return *this;
}
Student :: Student() {}
Student :: Student(string getName, int getId)
{
	studentName = getName;
	studentId = getId;
}
string Student :: callName()
{
	return studentName;
}
int Student :: callId()
{
	return studentId;
}

