//MINI PROJECT: STUDENT REPORT MANAGEMENT by TEAM 1

#include<iostream>
#include<fstream>
#include<iomanip>
#include <stdlib.h>
using namespace std;

//Student class: It will contain the student variables I have declare student's roll number, name, percentage, grade and the 5 Subjects we have in this sem.

class student
{
	int rollno;
	char name[50];
	int DS_marks, OOPs_marks, COSM_marks, ADE_marks, COA_marks;
	double per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int retrollno() const;
}; //class ends here

// Since our student function has variables that are only limited to that function, we will use scope resolution function to access marks of DS,OOPs,COSM,ADE,COA subjects.
void student::calculate()
{
	per=(DS_marks+OOPs_marks+COSM_marks+ADE_marks+COA_marks)/5.0;
	if(per>=90)
		grade='O';
	else if(per>=70&&per<90)
		grade='A';
	else if(per>=50&&per<70)
		grade='B';
    else if(per>=40&&per<50)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
    cout<<"\nPlease enter marks out of 100 (Internals + External) "<<endl;
	cout<<"\nEnter your marks in Data Structures in C : ";
	cin>>DS_marks;
	cout<<"\nEnter The marks in Object Oriented Programming using C++ : ";
	cin>>OOPs_marks;
	cout<<"\nEnter The marks in COSM : ";
	cin>>COSM_marks;
	cout<<"\nEnter The marks in Analog and Digital Electronics : ";
	cin>>ADE_marks;
	cout<<"\nEnter The marks in Computer Organization and Architecture: ";
	cin>>COA_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Data Structures : "<<DS_marks;
	cout<<"\nMarks in OOPS : "<<OOPs_marks;
	cout<<"\nMarks in COSM : "<<COSM_marks;
	cout<<"\nMarks in ADE : "<<ADE_marks;
	cout<<"\nMarks in COA :"<<COA_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<DS_marks<<setw(4)<<OOPs_marks<<setw(4)<<COSM_marks<<setw(4)
		<<ADE_marks<<setw(4)<<COA_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}

void write_student();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen

int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tSTUDENT REPORT MANAGEMENT SYSTEM";
		cout<<"\n\n\t01. VIEW STUDENT REPORT DETAILS";
		cout<<"\n\n\t02. ADD/DELETE/MODIFY REPORT";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}


void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}



void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}



void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}




void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name       DS OOPS COSM ADE COA  %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}



void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Report Card";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    cout<<" \t______________________________________"<<endl;
	cout<<"\t|             Welcome to               |"<<endl;
	cout<<"\t|                                      |"<<endl;
    cout<<"\t|                                      |"<<endl;
	cout<<"\t| CSE B STUDENT REPORT CARD MANAGEMENT |"<<endl;
	cout<<"\t|                                      |"<<endl;
    cout<<"\t|______________________________________|"<<endl;
	cout<<"\n\n\n\tPlease Enter Any Key To Start!";

   cout<<"\n\n\n\n\n\n\n\n\n\tDeveloped by TEAM 1!"<<endl;

	cin.get();
}

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.ADD STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS DATA";
	cout<<"\n\n\t3.DISPLAY STUDENT DATA ";
	cout<<"\n\n\t4.MODIFY STUDENT DATA";
	cout<<"\n\n\t5.DELETE STUDENT DATA";
	cout<<"\n\n\t6.MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
