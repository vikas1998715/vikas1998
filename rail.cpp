#include <stdio.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;



// Function to implement strcmp function
int str_cmp(const char *X, const char *Y)
{
	while(*X != '\0')
	{
		if (*X != *Y)
			break;
		X++;
		Y++;
	}
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}


//login class.....................
class login
{
public:
    char id[100];
    char pass[100];
    char *password;
    void getid()
    {
        cout<<"Enter your id:";
        gets(id);
        password=getpass("Enter the password:");
        strcpy(pass,password);
    }
    void displayid()
    {
        cout<<"Id:";
        puts(id);
        cout<<"Password:";
        puts(pass);
    }
};
//......................................









void database()
{
    char *password;
    char *pass="vikas123";
    password=getpass("Enter the admininistrator password:");
    detail a;
    fstream f;
    int ch;
    char c;
    if(str_cmp(pass,password)!=0)
    {
        cout<<"Enter the password correctly \n";
       main menu();
    }
    if(str_cmp(pass,password)==0)
    {
        char c;
        do
        {
            cout<<"...........ADMINISTRATOR MENU...........\n";












///.......................................





	    void user_main()
{
    login a;
    int ch;
    cout<<"...................WELCOME TO THE USER MENU..........\n";
    char *password;

    fstream f;
    f.open("id.txt",ios::in|ios::out|ios::binary);
    char id[100];
    puts("Enter your id:");
    gets(id);
    password=getpass("Enter your password:");
    while(f.read((char *) & a,sizeof(a)))
    {
        if((strcmp(a.id,id)==0)&&(strcmp(a.pass,password)==0))
        {
            do
            {
       



            }
            while(ch<=3);

        }
        else
       
    {
        cout<<"Enter your user id and password correctly\n";
	main menu();
    }

    getch();
}




	//..................................................//...........................
	








	    void user_mang()
{
    int ch;
    fstream f;
    char c;
    login a;
    cout<<".......welcome to user part............\n";
    do
    {
        cout<<"1.Create id data base\n2.Add details\n";
        cout<<"3.Display details\n4.Return to the main menu\n";
        cout<<"Enter your choice:";
        cin>>ch;
        cout<<endl;
        switch(ch)
        {
        case 1:
             f.open("id.txt",ios::in|ios::out|ios::binary);

            do
            {
                a.getid();
                f.write((char *) & a,sizeof(a));
                cout<<"Do you want to add one more record\n";
                cout<<"y-Yes\nn-No\n";
                cin>>c;
            }
            while(c=='y');
            f.close();
            break;
        case 2:
        
        case 3:
            f.open("id.txt",ios::in|ios::out|ios::binary);

            f.seekg(0);
            while(f.read((char *) & a,sizeof(a)))
            {
                a.displayid();
            }
            f.close();
            break;
        }
    }
    while(ch<=3);
    getch();
}



///....................................................



int main()
{

return 0;
}
