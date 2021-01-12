#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <cstdio> // utk pakai rename function to rename 
#include <limits> //semata nak buat error
#undef max //semata nak buat error
using namespace std;

//struct
struct gadget { //syariff
	string type;
	string gadgetName;
	string desc1;
	string desc2;
	string desc3;
	string desc4;
	int stock = 0;
	double price = 0;
	string gadgetCode;
};

//function prototype
int homeDisplay();
int gadgetTypeSelection();
string buyersMenu(int, gadget[]);
void kiraDuit(string&, gadget[], double&, int&, ofstream&);
void adminLogin(int&);
void displayAdminPage(double, gadget[]);
void receipt(double, ifstream&, int);
void writeIntoTemp(ofstream&, ifstream&, gadget[], ofstream&, ifstream&);


int main() {
	//fixed console size   //syariff
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 950, 600, TRUE); // 950 width, 600 height
	//end of fixed console size

	ofstream inOut("receiptTemp.txt", ios::trunc); //masukkan data dalam file semata2 nak display gadget in receipt
	ifstream readDisplay("receiptTemp.txt"); //read input to display gadget yg dibeli at receipt

	ifstream gadgetList("gadget.txt"); //read gadget items
	ofstream tempGadget("tempGadget.txt"); //store gadget items then the file is renamed into main file

	int status, selection, count = 0;
	char homepage;
	double sum = 0.00, sumAllBuyer = 0.00; //sum tu total harga buyer beli, sumAllBuyer tu total semua pembelian with receipt berlainan
	string code;

	gadget gajet[10]; // 10 gadgets

	string myString;
	string line;
	int i = 0;

	//loop to get data from textfile into struct
	while (getline(gadgetList, line)) {
		stringstream ss(line);
		getline(ss, gajet[i].type, ',');
		getline(ss, gajet[i].gadgetName, ',');
		getline(ss, gajet[i].desc1, ',');
		getline(ss, gajet[i].desc2, ',');
		getline(ss, gajet[i].desc3, ',');
		getline(ss, gajet[i].desc4, ',');
		getline(ss, myString, ','); //to get int stock
		gajet[i].stock = stoi(myString);
		getline(ss, myString, ',');  // to get double stock
		gajet[i].price = stod(myString);
		getline(ss, gajet[i].gadgetCode, ',');

		i++;
	}

	int customer = 1;
	do { // syariff
		home:
		status = homeDisplay();
		if (status == 1) { //BUYERS PAGE
			back:
			int hehe = 0;
			selection = gadgetTypeSelection();
			code = buyersMenu(selection, gajet);
			kiraDuit(code, gajet, sum, hehe, inOut);
			if (hehe == 5) { // bila input salah
				system("pause");
				system("cls");
				goto back;
			}
			cout << "\nDo you want to buy another gadget? Click 1 if yes || Click 2 if no : ";
			cin >> hehe;
			if (hehe == 1) { //bila input 1/yes
				system("cls");
				goto back;
			}
			else {
				system("cls");
			}
			// FUNCTION FOR DISCOUNT : MEMBERSHIP/ COUPON CODE WHATEVER LAH HAHAHA
			receipt(sum, readDisplay, customer);
			system("pause");
			system("cls");
		}
		else if (status == 2) { // ADMIN PAGE
			adminLogin(count);
			if (count == 3) {
				count = 0;
				goto home;
			}
			displayAdminPage(sumAllBuyer, gajet);  //will put function for admin(check stocks/check total profit)
		}
		else if (status == 3) { // EXIT PROGRAM UWU
			writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay); // TO WRITE / CLOSE / REMOVE & RENAME TEXT FILE
			return 0;
		}
		else { // ERROR (SALAH INPUT TAK LETAK 1 OR 2 OR 3)
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

		sumAllBuyer = sumAllBuyer + sum;
		sum = 0.00;
		cout << "\nBack to homepage ?(Y|N) " << endl;
		cout << endl << " -----> :  ";
		cin >> homepage;
		if (homepage == 'Y' || homepage == 'y') {
			// .clear() untuk buang customer lama punya receipt display
			inOut.clear();
			readDisplay.clear();
			customer++;
		}
		system("cls");
	} while ((homepage == 'Y') || (homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay); // TO WRITE / CLOSE/ REMOVE & RENAME TEXT FILE

	return 0;
}

void writeIntoTemp(ofstream& tempGadget, ifstream& gadgetList, gadget gajet[], ofstream& inOut, ifstream& readDisplay) {

	for (int i = 0; i < 10; i++) {
		tempGadget << gajet[i].type;
		tempGadget << ",";
		tempGadget << gajet[i].gadgetName;
		tempGadget << ",";
		tempGadget << gajet[i].desc1;
		tempGadget << ",";
		tempGadget << gajet[i].desc2;
		tempGadget << ",";
		tempGadget << gajet[i].desc3;
		tempGadget << ",";
		tempGadget << gajet[i].desc4;
		tempGadget << ",";
		tempGadget << gajet[i].stock;
		tempGadget << ",";
		tempGadget << gajet[i].price;
		tempGadget << ",";
		tempGadget << gajet[i].gadgetCode << endl;
	}

	inOut.close();
	readDisplay.close();
	gadgetList.close();
	tempGadget.close();

	remove("gadget.txt");  //delete test file
	int result = rename("tempGadget.txt", "gadget.txt"); //rename the temp to text 
	if (result == 0)
		puts("File successfully renamed");
	else
		perror("Error renaming file");
}

int homeDisplay() { // homepage //dida & natasha

	int s;
	cout << endl << "                                  WELCOME TO GADGET STORE !               " << endl;
	cout << endl << "          " << " -------------------------------- " << "------------------------------- ";
	cout << endl << "          " << " |       PRESS 1 FOR BUYER      |" << " |      PRESS 2 FOR ADMIN      | ";
	cout << endl << "          " << " -------------------------------- " << "------------------------------- " << endl;
	cout << endl << "          " << "                       --------------------------                       ";
	cout << endl << "          " << "                       |     PRESS 3 TO EXIT    |                       ";
	cout << endl << "          " << "                       --------------------------                       ";
	cout << endl << "=========>" << " PLEASE CHOOSE CAREFULLY SINCE THERE IS NO TURNING POINT PASS HERE <==========  ";
	cout << endl << " -----> :  ";
	cin >> s;
	system("cls");

	return s;
}

int gadgetTypeSelection() { // dida 

	int selection;
	do {
		cout << "             CHOOSE TYPE OF GADGET " << endl;
		cout << "1 - Pendrive" << endl;
		cout << "2 - Mouse" << endl;
		cout << "3 - Headphones" << endl;
		cout << "4 - Powerbank" << endl;
		cout << "ENTER NUMBER BASED ON TYPE OF GADGET" << endl;
		cout << endl << " -----> :  ";
		cin >> selection;
		system("cls");
	} while ((selection != 1) && (selection != 2) && (selection != 3) && (selection != 4));

	return selection;
}

string buyersMenu(int selection, gadget gajet[]) {

	string c;

	if (selection == 1) { //syariff
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -PENDRIVE-                    " << endl << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "P") {
				cout << "Name : " << gajet[i].gadgetName << endl;
				cout << "Capacities : " << gajet[i].desc1 << endl;
				cout << "Speed : " << gajet[i].desc2 << endl;
				cout << "Dimensions : " << gajet[i].desc3 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock : " << gajet[i].stock << endl;
				}
				cout << "Price : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Code : " << gajet[i].gadgetCode << endl << endl;
			}
		}
	}
	else if (selection == 2) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -MOUSE-                    " << endl << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "M") {
				cout << "Name : " << gajet[i].gadgetName << endl;
				cout << "Sensing Type : " << gajet[i].desc1 << endl;
				cout << "Existence of wire  : " << gajet[i].desc2 << endl;
				cout << "Dimensions : " << gajet[i].desc3 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock : " << gajet[i].stock << endl;
				}
				cout << "Price : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Code : " << gajet[i].gadgetCode << endl << endl;
			}
		}
	}
	else if (selection == 3) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -HEADPHONES-                    " << endl << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "H") {
				cout << "Name : " << gajet[i].gadgetName << endl;
				cout << "Existence of wires : " << gajet[i].desc1 << endl;
				cout << "Dimension : " << gajet[i].desc2 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock : " << gajet[i].stock << endl;
				}
				cout << "Price : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Code : " << gajet[i].gadgetCode << endl << endl;
			}
		}
	}
	else if (selection == 4) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -POWER BANK-                    " << endl << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "B") {
				cout << "Name : " << gajet[i].gadgetName << endl;
				cout << "Battery Capacities : " << gajet[i].desc1 << endl;
				cout << "Amount of Ports : " << gajet[i].desc2 << endl;
				cout << "Dimensions : " << gajet[i].desc3 << endl;
				cout << "Weight : " << gajet[i].desc4 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock : " << gajet[i].stock << endl;
				}
				cout << "Price : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Code : " << gajet[i].gadgetCode << endl << endl;
			}
		}
	}

	cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY (MAKE SURE THE CODES IN CAPITAL LETTER)" << endl; //syariff
	cout << endl << " -----> :  ";
	cin.ignore();
	getline(cin, c);

	return c;
}

void kiraDuit(string& code, gadget gajet[], double& sum, int& hehe, ofstream& inOut) { //syariff

	int quantity = 0;

startQuantity:
	for (int i = 0; i < 10; i++) {
		if (gajet[i].type == "P") { //PENDRIVE
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "THE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
				}
				else {
					cout << "PLEASE ENTER QUANTITY :" << endl;
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					sum = sum + (gajet[i].price * quantity);
					inOut << "Name : " << gajet[i].gadgetName << endl;
					inOut << "Capacities : " << gajet[i].desc1 << endl;
					inOut << "Speed : " << gajet[i].desc2 << endl;
					inOut << "Dimensions : " << gajet[i].desc3 << endl;
					inOut << "Quantity bought : " << quantity << endl << endl;
				}
			}
		}
		else if (gajet[i].type == "M") { //MOUSE
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "THE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
				}
				else {
					cout << "PLEASE ENTER QUANTITY :" << endl;
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					sum = sum + (gajet[i].price * quantity);
					inOut << "Name : " << gajet[i].gadgetName << endl;
					inOut << "Sensing Type : " << gajet[i].desc1 << endl;
					inOut << "Existence of wire  : " << gajet[i].desc2 << endl;
					inOut << "Dimensions : " << gajet[i].desc3 << endl;
					inOut << "Quantity bought : " << quantity << endl << endl;
				}
			}
		}
		else if (gajet[i].type == "H") { //HEADPHONES
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "THE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
				}
				else {
					cout << "PLEASE ENTER QUANTITY :" << endl;
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					sum = sum + (gajet[i].price * quantity);
					inOut << "Name : " << gajet[i].gadgetName << endl;
					inOut << "Existence of wires : " << gajet[i].desc1 << endl;
					inOut << "Dimension : " << gajet[i].desc2 << endl;
					inOut << "Quantity bought : " << quantity << endl << endl;
				}
			}
		}
		else if (gajet[i].type == "B") { //POWERBANK
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "THE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
				}
				else {
					cout << "PLEASE ENTER QUANTITY :" << endl;
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					sum = sum + (gajet[i].price * quantity);
					inOut << "Name : " << gajet[i].gadgetName << endl;
					inOut << "Battery Capacities : " << gajet[i].desc1 << endl;
					inOut << "Amount of Ports : " << gajet[i].desc2 << endl;
					inOut << "Dimensions : " << gajet[i].desc3 << endl;
					inOut << "Weight : " << gajet[i].desc4 << endl;
					inOut << "Quantity bought : " << quantity << endl << endl;
				}
			}
		}
		else {
			cout << "Wrong code, try again. ";
			hehe = 5;
		}
	}
}

void adminLogin(int& count) { //admin page (need to login first) //syariff

	int ch;
	string adminPassword = "", adminUser;

	wrong:
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << setw(60) << "ADMIN LOGIN PAGE " << endl;
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << "\nADMIN USERNAME ---> ";
	cin >> adminUser;
	cout << "\nADMIN PASSWORD ---> ";
	while (ch = _getch()) { //assign ASCII value to ch
		if (ch == 13) {  //13 is ENTER key in ASCII
			if ((adminPassword == "abc123" && adminUser == "Tasha") || (adminPassword == "qwerty123" && adminUser == "Syarep") || (adminPassword == "Dida123" && adminUser == "Dida")) { //correct password
				system("cls");
				cout << endl << "ACCESS GRANTED" << endl;
				system("pause");
				system("cls");
				break;
			}
			else if ((adminPassword != "abc123" && adminUser != "Tasha") || (adminPassword != "qwerty123" && adminUser != "Syarep") || (adminPassword != "Dida123" && adminUser != "Dida")) {
				//wrong password
				adminUser = "";
				adminPassword = "";
				count++;
				if (count == 3) {
					system("cls");
					Beep(1000, 500);
					cout << endl << "YOU HAVE ENTERED INCORRECT ADMIN USERNAME / PASSWORD FOR 3 TIMES" << endl;
					cout << endl << "THE PROGRAM WILL GO BACK TO HOMEPAGE" << endl;
					system("pause");
					system("cls");
					break;
				}
				else {
					system("cls");
					Beep(1000, 500);
					cout << endl << "INCORRECT ADMIN USERNAME / PASSWORD" << endl;
					system("pause");
					system("cls");
					goto wrong;
				}
			}
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

void displayAdminPage(double sumAllBuyer, gadget gajet[]) { //admin page ( to display stocks, number of buyers and so on) 

	int addStocks = 0;
	int selectStock = 0;
	int adminSelect = 0;
	int selectAddStock = 0;
	string code;

	cout << "_________________________________________________________________________________________________________" << endl;
	cout << setw(60) << "ADMIN PAGE " << endl;
	cout << "_________________________________________________________________________________________________________" << endl << endl << endl;

	cout << "1. Display / Add stocks" << endl;
	cout << "2. Display Total Profit" << endl;
	cout << "---------->";
	cin >> adminSelect;                        
	
	if (adminSelect == 1) {
		stockAdmin:
		cout << "\n1. Display all stocks data" << endl;
		cout << "2. Display pendrive stocks data" << endl;
		cout << "3. Display mouse stocks data" << endl;
		cout << "4. Display headphone stocks data" << endl;
		cout << "5. Display powerbank stocks data" << endl;
		cout << "---------->";
		cin >> selectStock;
		if (cin.fail()) {
			cout << "Please enter correct number selection!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto stockAdmin;
		}
		//display all stocks data
		cout << "=================================================================" << endl;
		cout << " Gadget Code  |         Gadget Name           |  No. of stocks  |" << endl;
		cout << "=================================================================" << endl;
		for (int i = 0; i < 10; i++) {
			if (selectStock == 1) {
				cout << setw(13) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
			}
			else if (selectStock == 2) {
				if (gajet[i].type == "P") {
					cout << setw(13) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 3) {
				if (gajet[i].type == "M") {
					cout << setw(13) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 4) {
				if (gajet[i].type == "H") {
					cout << setw(13) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 5) {
				if (gajet[i].type == "B") {
					cout << setw(13) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
		}
		cout << "=================================================================" << endl << endl;
		//end of display all stocks data

		cout << "Do you want to add gadget item stocks (PRESS 1 - YES | PRESS 2 - NO)" << endl;
		cin >> selectAddStock;

		if (selectAddStock == 1) {
			//Add stocks
			cout << "TYPE GADGET CODE FOR ITEM YOU WANT TO ADD STOCKS  : ";
			cin >> code;
			for (int i = 0; i < 10; i++) {
				if (code == gajet[i].gadgetCode) {
					cout << "Add stocks : ";
					cin >> addStocks;
					gajet[i].stock = gajet[i].stock + addStocks;
				}
			}
			//End of add stocks
		}
		else if(selectAddStock == 2) {
			return;
		}
	}
	else if (adminSelect == 2) {
		cout << "\nTOTAL PROFIT : RM" << sumAllBuyer << setprecision(2) << fixed << endl;
	}
}

void receipt(double sum, ifstream& readDisplay, int customer) { //receipt

	string line;

	cout << "\n===== RECEIPT =====" << endl;
	cout << "CUSTOMER NO :" << customer << endl << endl;
	//Loop from receiptTemp.txt
	while (getline(readDisplay, line)) {
		// Output the text from the file
		cout << line << endl;
	}
	cout << "\nTotal harga kena bayar : RM" << setprecision(2) << fixed << sum << endl;
}

