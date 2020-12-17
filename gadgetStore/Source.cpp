#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <limits>
#undef max


using namespace std;

//struct
struct people {
	string name;
	int age = 0;
	string phonenum;
	string bankName;
	int bankNo = 0;
};

//function prototype
int homeDisplay();
void buyersMenu();
void adminPage();
void displayAdminPage();
void daftar(people& customer);
void receipt(people customer);

int main() {

	int status;
	char homepage, code[10];
	people customer;

	do {

		status=homeDisplay();

		if (status == 1) { //BUYERS PAGE
			buyersMenu();
			cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY : ";
			cin.ignore();
			cin.getline(code, 10);
			cout << code << endl;
			if (strcmp(code,"PEN01")==0) {
				cout << " You bought 32gb pendrive " << endl;
			}
			else if (strcmp(code, "PEN02") == 0) {
				cout << " You bought 64gb pendrive, pendrive mahal woo " << endl;
			}

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

void buyersMenu() { //list barangan dijual (will put stocks later)

	cout << " ******************************************* CATEGORIES OF GADGET ******************************************* " << endl;
	cout << "                                           -PENDRIVE-                                                      " << endl << endl;
	cout << "          " << "|             Capacities : 32GB             |" << "     " << "|             Capacities : 64GB             |" << endl;
	cout << "          " << "|            Speed : 100MB/s read           |" << "     " << "|            Speed : 100MB/s read           |" << endl;
	cout << "          " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << "     " << "|     Dimensions : 60mm x 21.2mm x 10mm     |" << endl;
	cout << "          " << "|             Price : RM15.50               |" << "     " << "|             Price : RM28.00               |" << endl;
	cout << "          " << "|               CODE : PEN01                |" << "     " << "|               CODE : PEN02                |" << endl;

	cout << "Mouse" << endl; //later tambah
	cout << "Headphones" << endl << endl; //later tambah
}

void daftar(people &customer) { //customer registration

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