#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <limits> //semata nak buat error
#undef max //semata nak buat error


using namespace std;

//struct
struct people {
	string name;
	int age = 0;
	string phonenum;
	string bankName;
	int bankNo = 0;
};

struct gadget {
	string gadgetName;
	string desc1;
	string desc2;
	string desc3;
	int stock=0;
	double price=0;
	string gadgetCode;
};

//function prototype
int homeDisplay();
int gadgetTypeSelection();
string buyersMenu(int , gadget []);
void adminPage();
void displayAdminPage();
void daftar(people& customer);
void receipt(people customer);

int main() {

	//fixed console size
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top,950, 600, TRUE); // 950 width, 600 height
	//end of fixed console size


	int status, selection;
	char homepage;
	string code;
	people customer;
	gadget pendrive[] = {
		{"Kingston 32 gb","32GB","70MB/s read","60mm x 21.2mm x 10mm",200,15.50,"P01"},
		{"Kingston 64 gb","64GB","100MB/s read","60mm x 21.2mm x 10mm",150,28.00,"P02"}
	};


	//string pendrive[2][5]={}

	do {

		status=homeDisplay();

		if (status == 1) { //BUYERS PAGE
			back:
			selection = gadgetTypeSelection();
			code = buyersMenu(selection,pendrive);
			
			
			if ((code == "P01") || (code == "p01")) {
				cout << " You bought 32gb pendrive " << endl;
			}
			else if ((code == "P02") || (code == "p02")) {
				cout << " You bought 64gb pendrive, pendrive mahal woo " << endl;
			}
			else if ((code == "M01") || (code == "m01")) {
				cout << " Peh beli mouse sial " << endl;
			}
			else {
				system("cls");
				goto back;
			}
			system("pause");
			system("cls");

			daftar(customer); // register user
			receipt(customer); // receipt display
		}
		else if (status == 2) { // ADMIN PAGE
			adminPage();
			displayAdminPage();  //will put function for admin(check stocks/check total profit)
		}
		else { // ERROR
			if (cin.fail()) { //when input char on int variable
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			Beep(1000, 500);
			cout << "=========> ERROR <==========  " << endl;
			cout << "PLEASE PRESS 1 FOR USER OR PRESS 2 FOR ADMIN" << endl;
			system("pause");
			system("cls");
		}

		cout << "\nBack to homepage ?(Y|N) " << endl;
		cout << endl << " -----> :  ";
		cin >> homepage;
		system("cls");
	} while ((homepage == 'Y') || (homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	return 0;
}


int homeDisplay() { // homepage

	int s;
	cout << endl << "                                  WELCOME TO GADGET STORE !               " << endl;
	cout << endl << "          " << " -------------------------------- " << "------------------------------- ";
	cout << endl << "          " << " |       PRESS 1 FOR BUYER      |" << " |      PRESS 2 FOR ADMIN      | ";
	cout << endl << "          " << " -------------------------------- " << "------------------------------- " << endl;
	cout << endl << "=========>" << " PLEASE CHOOSE CAREFULLY SINCE THERE IS NO TURNING POINT PASS HERE <==========  ";
	cout << endl << " -----> :  ";
	cin >> s;
	system("cls");

	return s;
}

int gadgetTypeSelection() { // homepage

	int selection;
	
	cout << "             CHOOSE TYPE OF GADGET " << endl;
	cout << "1 - Pendrive" << endl;
	cout << "2 - Mouse" << endl;
	cout << "3 - Headphones" << endl;
	cout << endl << " -----> :  ";
	cin >> selection;
	system("cls");

	return selection;
}

string buyersMenu(int selection,gadget pendrive[]) { 
	 
	string c;
	
	if (selection == 1) {
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -PENDRIVE-                    " << endl << endl;
		for (int i = 0; i < 2; i++) {
			cout << "Name : "       << pendrive[i].gadgetName << endl;
			cout << "Capacities : " << pendrive[i].desc1 << endl;
			cout << "Speed : "      << pendrive[i].desc2 << endl;
			cout << "Dimensions : " << pendrive[i].desc3 << endl;
			cout << "Stock : "      << pendrive[i].stock << endl;
			cout << "Price : "      << pendrive[i].price << endl;
			cout << "Code : "       << pendrive[i].gadgetCode << endl << endl;
		}
	}if (selection == 2) {

	}
	else if (selection == 3) {

	}
	
	/*
	if (selection == 1) {
		cout << " ******************************************* CATEGORIES OF GADGET ******************************************* " << endl;
		cout << "                                           -PENDRIVE-                                                      " << endl << endl;
		cout << "          " << "|             Capacities : 32GB             |" << "     " << "|             Capacities : 64GB             |" << endl;
		cout << "          " << "|            Speed : 100MB/s read           |" << "     " << "|            Speed : 100MB/s read           |" << endl;
		cout << "          " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << "     " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << endl;
		cout << "          " << "|             Price : RM15.50               |" << "     " << "|             Price : RM28.00               |" << endl;
		cout << "          " << "|                 CODE : P01                |" << "     " << "|                 CODE : P02                |" << endl;
	}
	else if (selection == 2) {
		cout << " ******************************************* CATEGORIES OF GADGET ******************************************* " << endl;
		cout << "                                           -Mouse-                                                      " << endl << endl;
		cout << "          " << "|             Capacities : 32GB             |" << "     " << "|             Capacities : 64GB             |" << endl;
		cout << "          " << "|            Speed : 100MB/s read           |" << "     " << "|            Speed : 100MB/s read           |" << endl;
		cout << "          " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << "     " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << endl;
		cout << "          " << "|             Price : RM15.50               |" << "     " << "|             Price : RM28.00               |" << endl;
		cout << "          " << "|                 CODE : M01                |" << "     " << "|                 CODE : M02                |" << endl;
	}
	else if (selection == 3) {
		cout << " ******************************************* CATEGORIES OF GADGET ******************************************* " << endl;
		cout << "                                           -Headphones-                                                      " << endl << endl;
		cout << "          " << "|             Capacities : 32GB             |" << "     " << "|             Capacities : 64GB             |" << endl;
		cout << "          " << "|            Speed : 100MB/s read           |" << "     " << "|            Speed : 100MB/s read           |" << endl;
		cout << "          " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << "     " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << endl;
		cout << "          " << "|             Price : RM15.50               |" << "     " << "|             Price : RM28.00               |" << endl;
		cout << "          " << "|                 CODE : H01                |" << "     " << "|                 CODE : H02                |" << endl;
	}*/


	cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY " << endl;
	cout << endl << " -----> :  ";
	cin.ignore();
	getline(cin,c);

	return c;
}

void daftar(people &customer) { //customer registration /nanti kena pointer char dafter for if else receipt

	char daftar;

	cout << "Do you want to register as member ? (Y|N) : ";
	cin >> daftar;
	if ((daftar == 'Y') || (daftar == 'y')) {
		cout << "\nPlease enter your name : ";
		cin.ignore();
		getline(cin, customer.name);
		cout << "\nPlease enter your age : ";
		cin >> customer.age;
		cout << "\nPlease enter your phone number : ";
		cin.ignore();
		getline(cin, customer.phonenum);
		cout << "\nPlease enter your bank account name : ";

		getline(cin, customer.bankName);
		cout << "\nPlease enter your bank account number : ";
		cin >> customer.bankNo;
	}
	else {
		cout << "\nHaha bodo tak register" << endl;
	}
}

void adminPage() { //admin page (need to login first)

	int count = 0, ch;
	string adminPassword = "";

	wrong:
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << setw(60) << "ADMIN LOGIN PAGE " << endl;
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << endl << " --------- P.A.S.S.W.O.R.D ----------- ";
	cout << endl << "           : ";
	while (ch = _getch()) { //assign ASCII value to ch
		if (ch == 13) {  //13 is ENTER key in ASCII
			if (adminPassword == "abc123") { //correct password
				system("cls");
				cout << endl << "ACCESS GRANTED" << endl;
				system("pause");
				system("cls");
				break;
			}

			//wrong password
			system("cls");
			Beep(1000, 500);
			cout << endl<<"INCORRECT ADMIN PASSWORD" << endl;
			system("pause");
			system("cls");
			adminPassword = "";
			goto wrong;
		}
		else if (ch == 8) { //8 is BACKSPACE key in ASCII
			if (adminPassword.length() > 0) { //set condition blocking error while input
				cout << "\b \b"; //buang * everytime tekan backspace
				adminPassword.erase(adminPassword.length() - 1); //erase string length
			}
		}
		else {
			cout << "*";
			adminPassword += ch;
		}
	}
}

void displayAdminPage() { //admin page ( to display stocks, number of buyers and so on)

	cout << "_________________________________________________________________________________________________________" << endl;
	cout << setw(60) << "ADMIN PAGE " << endl;
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
}

void receipt(people customer) { //receipt

	cout << "\n===== RECEIPT =====" << endl;
	cout << "customer name : " << customer.name << endl;
	cout << "customer age : " << customer.age << endl;
	cout << "customer phone number : " << customer.phonenum << endl;
	cout << "customer bank name : " << customer.bankName << endl;
	cout << "customer bank number : " << customer.bankNo << endl;
}