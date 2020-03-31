#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;


struct Usr{			//Structure used to enter the details into the user file
	char id[10];
	char pass[10];
};
Usr u;


struct Train{			//Structure to extract data for Train.txt
	char name[20];		//Train number  123 and 124.
	int n, tn;
};
Train t;

struct Userres{			//Structure for makin the file Reservation Details.	
	char id[10];		//rn tells number of seats reserved.	
	char tname[20];
	char board[20], dest[20];
	int tno, rn;
};
Userres r;


// Function to implement strcmp function
int str_cmp(const char *X, const char *Y)
{
        while(*X != '\0'&& *Y !='\0' )
        {
                if (*X != *Y)
                        break;
                X++;
                Y++;
        }
        return *(const unsigned char*)X - *(const unsigned char*)Y;
}







class Admin{				// Admin Class - Add users(Id and Passwords)
	char *id, *pass;		// Delete users, display user id and passwords
	public:				// And lastly display the reservations done by the user
	Admin():id("jack316"), pass("1234") {}
	void menu();
	void input(); //Method for admin authentication...
	void add_User();
	void del_User();
	void disp_User();
	void disp_res();	
};

void Admin::input(){
	char id[10], pass[10];
	ifstream f;
	f.open("User log.txt", ios::in);
	cout << "Enter Admin ID\n";
	cin >> id;
	cout << "Enter password\n"; 
	cin >> pass;
	while(f.read((char *)&u, sizeof(u))){
		if(str_cmp(this->id, id)==0 && str_cmp(this->pass, pass)==0)
			menu();
	}
	f.close();
}
void Admin::menu(){ 			//Displays the Menu for Admin
	int ch1;
	cout<<"\t\tMenu\n";
	cout<<"1. Add User\n2. Delete User\n3. Display User\n4. Display reservation details of user\n5. Exit\n";
	cin>>ch1;
	switch(ch1){
		case 1:
			add_User();
			break;
		case 2:
			del_User();
			break;
		case 3: 
			disp_User();
			break;
		case 4:
			disp_res();
			break;
		case 5:
			exit(0);
		default : 
			cout<<"Invalid Choice\n";
			menu();
	}
	menu();
}

//Enter user Details choice 1 to call add_User() again else menu()
void Admin::add_User(){
	int ch;
	fstream f;
	f.open("User log.txt", ios::app);
	cout<<"Enter user id\n";
	cin>>u.id;
	cout<<"Enter user password\n";
	cin>>u.pass;
	f.write((char *)&u, sizeof(u));
	f.close();
	cout<<"Enter 1 for adding user\n";
	cin>>ch;
	if(ch == 1)
		add_User();
	else
		menu();
}

void Admin::del_User(){
	fstream f1, f2;
	char idd[10];
	f1.open("User log.txt", ios::in);
	f2.open("tmp.txt", ios::app);
	cout<<"Enter user Id\n";
	cin>>idd;
	while(f1.read((char *)&u, sizeof(u))){
		if(str_cmp(idd, u.id)==0)
			continue;
		f2.write((char *)&u, sizeof(u));
	}
	remove("User log.txt");
	rename("tmp.txt", "User log.txt");
	f1.close();
	f2.close();
}

void Admin::disp_User(){
	fstream f;
	f.open("User log.txt", ios::in);
	while(f.read((char *)&u, sizeof(u))){
		cout<<"Id - "<<u.id<<endl<<"Password - "<<u.pass<<endl;
	}
	f.close();
}

void Admin::disp_res(){
	char idd[20];
	ifstream f;
	f.open("Reservation Details.txt", ios::in);
	cout << "Enter user ID whose details are to be listed\n";
	cin >> idd;
	while(f.read((char *)&r, sizeof(r))){
		if(str_cmp(idd, r.id) == 0){
			cout << "User ID :- " << r.id << endl;
			cout << "Train Number :- " << r.tno << endl;
			cout << "Train Name :- " << r.tname << endl;
			cout << "Boarding Station :- " << r.board << endl;
			cout << "Destination Station :- " << r.dest << endl;
			cout << "Number of reserved seats :- " << r.rn << endl;
		}
	}
	f.close();
	menu();	
}

class User{			//This class will reserve seats, cancel ticket and Enquiry
	public: void new_user();
		void input(); 	//Function to input user id and password and authenticate..
		void menu(); 	//Display menu for user.
		void reserve();
		void cancel(); 
		void enquire();	//Display the ticket details...
};





void User::new_user(){
        int ch;
        fstream f;
        f.open("User log.txt", ios::app);
        cout<<"Enter user id\n";
        cin>>u.id;
        cout<<"Enter user password\n";
        cin>>u.pass;
        f.write((char *)&u, sizeof(u));
        f.close();
        cout<<"Enter 1 for adding user\n";
        cin>>ch;
        if(ch == 1)
                new_user();
               // menu();
}





//Function for user authentication...
static char id[10];
int seats; //Store the seats of the entered train number
int num; //Store train number for updating the seats inside the file
void User::input(){
	ifstream f;
	char pass[10];
	f.open("User log.txt", ios::in);
	cout << "Enter the user ID\n";
	cin >> id;
	cout << "Enter the password \n";
        cin >> pass;
	while(f.read((char *)&u, sizeof(u))){
		if(str_cmp(u.id, id)==0 && str_cmp(u.pass, pass)==0){
				menu();
		}

	}
	f.close();
	cout << "Invalid User ID or password\n";
	input();
}

//Method to display the menu of User
void User::menu(){
	int ch;
	cout << "\t\tUser Menu\n";
	cout << "1. Reserve\n2. Cancel\n3. Enquire\n4. Exit\n";
	cin >> ch;
	switch(ch){
		case 1: 
			reserve();
			break;
		case 2: 
			cancel();
			break;
		case 3: 
			enquire();
			break;
		case 4: 
			exit(0);
		default: 
			cout << "Wrong choice\n";
			menu();
	}
}

//Function to check the details entered by user is valid or not
int check(int x){
	ifstream f;
	f.open("Train.txt", ios::in);
	while(f.read((char *)&t, sizeof(t))){
		if(x == t.tn){
			seats = t.n;
			num = t.tn;
			f.close();
			return 1;
		}
	}
	f.close();
	return 0;
}

int check(char name[]){
	ifstream f;
	f.open("Train.txt", ios::in);
	while(f.read((char *)&t, sizeof(t))){
		if(str_cmp(name, t.name) == 0){
			f.close();
			return 1;
		}
	}
	f.close();
	return 0;
}

//Function to uptade the no. of seats preset in the file
void update(int X){
	ifstream f1;
	ofstream f2;
	f1.open("Train.txt", ios::in);
	f2.open("temp.txt", ios::app);
	while(f1.read((char *)&t, sizeof(t))){
		if(num == t.tn)
			t.n -= X;
		f2.write((char *)&t, sizeof(t));
	}
	remove("Train.txt");
	rename("temp.txt", "Train.txt");
	f1.close();
	f2.close();
}
//Function to check seat availability...
int checks(int x){		//x seats entered by user, y seats available in train
	ifstream f;
	f.open("Train.txt", ios::in);
	while((char *)&t,sizeof(t)){
			if(x <= seats){
				update(x);
				f.close();
				return 1;
			}
			else {
				f.close();
				return 0;
			}
		}
}
//Function to copy string..
char* copy(char *x, char *y){
	int i;
	for(i = 0; y[i] != '\0'; i++){
		x[i] = y[i];
	}
	x[i] = '\0';
	return x;
}

void User::reserve(){
	ifstream f;
	f.open("Train.txt", ios::in);

	//Display the details of the trains stored in Train.txt
	cout << "Trains available\n";
	while(f.read((char *)&t, sizeof(t))){
		cout << "Train name " << t.name << endl;
		cout << "Train number " << t.tn << endl;
		cout << "No. of seats " << t.n << endl;
	}
	f.close();
	
	//Reservartion Process
	ofstream f1;
	f1.open("Reservation Details.txt", ios::app);
	copy(r.id, id);
	while(1){					//Entering valid train number
		cout << "Enter Train number\n";
		cin >> r.tno;
		if(check(r.tno) == 1)
			break;
		else{
			cout << "Invalid number\n";
			continue;
		}

	}
	while(1){					//Entering valid train name
		cout << "Enter Train name\n";
		cin >> r.tname;
		if(check(r.tname) == 1)
			break;
		else {
			cout << "Invalid name\n";
	 		continue;
		}
	}
	cout << "Enter boarding station\n";			// Entering rest of the details
	cin >> r.board;
	cout << "Enter destination station\n";
	cin >> r.dest;
	cout << "Enter number of seats to be reserved\n";
	cin >> r.rn;
	cout << "No. of seats booked " << seats << endl;
	if(checks(r.rn)){
		cout << "Reservation successful\n";
		f1.write((char *)&r, sizeof(r));
		f1.close();
	}
	else{
		cout << "Reservation failure\n";
		r.rn = 0;
		f1.write((char *)&r, sizeof(r));
		f1.close();
	}
	int ch;
	cout << "Enter 1 to reserve more seats \n";
	cin >> ch;
	if(ch == 1)	reserve();
	else	menu();

}

voi

int main(){
	Admin a;
	User uu;
	int ch;
	cout << "1. Admin\n2.signin  User\n3 . login user ";
	cin >> ch;
	if(ch == 1){
		a.input();
	}
	else if(ch==2){
		uu.new_user();
		main();
	}
	else
		uu.input();
	return 0;
}
