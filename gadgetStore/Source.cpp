#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <limits>
#undef max

using namespace std;

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

/*string chooseItem() {
	string kod;

	cout << "ENTER CODE FOR THE PRODUCT YOU WANTED TO BUY";
	cout << endl << " -----> :  ";
	getline(cin, kod);
	
	return kod;
	system("pause");
}*/

int main() {

	int status;
	char homepage, code[10];

	do {

		status=homeDisplay();

		if (status == 1) { //BUYERS PAGE
			buyersMenu();
			cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY : ";
			cin.ignore();
			cin.getline(code, 10);
			cout << code << endl;
		}
		else if (status == 2) { // ADMIN PAGE
			cout << "WELCOME TO ADMIN PAGE" << endl; //will put function for admin(check stocks/check total profit)
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
	} while ((homepage == 'Y') || (homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	return 0;
}
