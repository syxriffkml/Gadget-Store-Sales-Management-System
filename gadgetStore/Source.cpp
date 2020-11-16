#include <iostream>
#include <cmath>
#include <cstring>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <windows.h>

using namespace std;

int homeDisplay() {
	
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

void buyersMenu() {
	
	cout << " ********************************* CATEGORIES OF GADGET ********************************* " << endl;
	cout << "Laptop" << endl;
	cout << "Mouse" << endl;
	cout << "Headphones" << endl;
	system("pause");
}

int main() {

	int status;
	char homepage;

	do {

		do {
			status = homeDisplay();
			if ((status != 1) && (status != 2)) {
				Beep(1000, 500);
				cout << "=========> ERROR <==========  " << endl;
				cout << "PLEASE PRESS 1 FOR USER OR PRESS 2 FOR ADMIN" << endl;
				system("pause");
				system("cls");
			}// Error if user input selain 1 or 2

			
			if (status == 1) {     // status 1 for buyer
				buyersMenu(); // Menu (User boleh pilih category gadget apa)
				cout << "HEHE" << endl;
				system("pause");
				system("cls");
			}
			else if (status == 2) {   // status 2 for admin
				cout << "HI ADMIN" << endl;
				//Display admin page function
				system("pause");
				system("cls");
			}
		} while ((status != 1) && (status != 2)); //do ni akan berterusan kalau user input salah


		cout << " Back to homepage ?(Y|N) " << endl;
		cout << endl << " -----> :  ";
		cin >> homepage;
		system("cls");
	} while ((homepage == 'Y' || homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	return 0;
}