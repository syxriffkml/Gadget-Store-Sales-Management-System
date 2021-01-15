#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <cstdlib> //for random coupon
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
	int stockSold = 0; // berapa banyak barang yang dah dibeli
};

//function prototype
string homeDisplay();
string gadgetTypeSelection();
string buyersMenu(string, gadget[]);
void kiraDuit(string&, gadget[], double&, int&, ofstream&,int&);
void discountFunc(double&, string&, double&, int&);
void adminLogin(int&, string&);
void displayAdminPage(double,string, gadget[], ifstream&, int&);
void receipt(double, ifstream&, double&, int& );
void writeIntoTemp(ofstream&, ifstream&, gadget[], ofstream&, ifstream&, ofstream&, ifstream&, double&,int&);


int main() {

	//fixed console size   
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 870, 800, TRUE); // 870 width, 800 height
	//end of fixed console size

	//Receipt display text file
	ofstream inOut("receiptTemp.txt", ios::trunc); //masukkan data dalam file semata2 nak display gadget in receipt
	ifstream readDisplay("receiptTemp.txt"); //read input to display gadget yg dibeli at receipt
	//List of gadget & description  text file
	ifstream gadgetList("gadget.txt"); //read gadget items
	ofstream tempGadget("tempGadget.txt"); //store gadget items then the file is renamed into main file
	//Admin text file
	ifstream Admin("admin.txt"); //read admin
	ofstream TempAdmin("tempAdmin.txt"); //add total price into admin

	int count = 0, adminRepeat, totalSales = 0,haveDiscount=0;
	char homepage;
	double sum = 0.00, sumAllBuyer=0.00, diskaun = 0.00; //sum tu total harga buyer beli, sumAllBuyer tu total semua pembelian with receipt berlainan
	string status,selection,code,haveCoupon,coupon,adminUser;

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
		getline(ss, myString, ','); //to get int stock
		gajet[i].stockSold = stoi(myString);

		i++;
	}

	//loop to get data from textfile
	//Admin >> sumAllBuyer;
	while (getline(Admin, line)) {
		stringstream ss(line);
		getline(ss, myString, ',');  // to get double sum all buyers
		sumAllBuyer = stod(myString);
		getline(ss, myString, ','); //to get int total sales
		totalSales = stoi(myString);
	}

	do { // syariff
		home:
		status = homeDisplay();
		if (status == "1") { //BUYERS PAGE
			back:
			int hehe = 0;
			selection = gadgetTypeSelection();
			code = buyersMenu(selection, gajet);
			kiraDuit(code, gajet, sum, hehe, inOut, totalSales);
			if (hehe == 5) { // bila input code barang unavailable stock
				system("pause");
				system("cls");
				goto back;
			}  
			cout << "\nDO YOU WANT TO BUY ANOTHER GADGET? (1-YES) || (2-NO)" << endl; //syariff
			cout << endl << " ----->   ";
			cin >> hehe;
			if (hehe == 1) { //bila input 1/yes
				system("cls");
				goto back;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
			}
			// FUNCTION FOR DISCOUNT : MEMBERSHIP/ COUPON CODE WHATEVER LAH HAHAHA
			cout << endl << ifstream("interface/couponPage.txt").rdbuf();
			cout << endl <<endl<<endl<< setw(75) << "DO YOU HAVE COUPON CODE (1-YES) || (2-NO) ----->   ";
			cin >> haveCoupon;
			if (haveCoupon == "1") {
				int counter = 0;
				do {
					cout << endl << setw(72) << "ENTER COUPON CODE (CASE SENSITIVE)  ----->   ";
					cin >> coupon;
					counter++;
					if (counter == 3) {
						cout << endl <<endl<< setw(76) << "YOU HAVE ENTERED WRONG COUPON CODE FOR 3 TIMES,"<< endl;
						cout << endl << setw(81) << "THE PROGRAM WILL CONTINUE YOU PURCHASES WITHOUT DISCOUNT" << endl << endl << endl << endl;
						break;
					}
				} while (coupon != "CODE06");
				cout << endl << endl;
				system("pause");
				system("cls");
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
			}
			discountFunc(sum, coupon, diskaun, haveDiscount);
			receipt(sum, readDisplay,diskaun, haveDiscount);
			system("pause");
			system("cls");
		}
		else if (status == "2") { // ADMIN PAGE
			adminLogin(count,adminUser);
			if (count == 3) { // bila salah input sampai 3 kali
				count = 0;
				goto home;
			}
			do {
				displayAdminPage(sumAllBuyer,adminUser, gajet,Admin,totalSales);  //will put function for admin(check stocks/check total profit)
				cout << endl << setw(60) << "BACK TO SELECTION AGAIN?  (1-YES) || (2-NO)" << endl;
				cout << setw(30) <<" --------->   ";
				cin >> adminRepeat;
				if(adminRepeat == 1) { // bila salah input sampai 3 kali
					system("pause");
					system("cls");
				}
				else {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("pause");
					system("cls");
				}
			} while (adminRepeat == 1);
		}
		else if (status == "3") { // EXIT PROGRAM UWU
			writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay, TempAdmin, Admin,sumAllBuyer, totalSales); // TO WRITE / CLOSE / REMOVE & RENAME TEXT FILE
			return 0;
		}
		else { // ERROR (SALAH INPUT TAK LETAK 1 OR 2 OR 3)
			if (cin.fail() && (status != "1") && (status != "2") && (status != "3")) { //when input char on int variable 
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			Beep(1000, 500);
			cout << endl << ifstream("interface/homepageError.txt").rdbuf();
			system("pause");
			system("cls");
		}

		sumAllBuyer = sumAllBuyer + sum;
		sum = 0.00;
		cout << endl << ifstream("interface/backToHomepage.txt").rdbuf();
		cin >> homepage;
		if (homepage == 'Y' || homepage == 'y') {
			// .clear() untuk buang customer lama punya receipt display
			inOut.clear();
			readDisplay.clear();
		}
		system("cls");
	} while ((homepage == 'Y') || (homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay, TempAdmin, Admin,sumAllBuyer, totalSales); // TO WRITE / CLOSE/ REMOVE & RENAME TEXT FILE

	return 0;
}

void writeIntoTemp(ofstream& tempGadget, ifstream& gadgetList, gadget gajet[], ofstream& inOut, ifstream& readDisplay, ofstream& TempAdmin, ifstream& Admin,double& sumAllBuyer,int& totalSales) {

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
		tempGadget << gajet[i].gadgetCode;
		tempGadget << ",";
		tempGadget << gajet[i].stockSold << endl;
	}
	TempAdmin << sumAllBuyer<< "," << totalSales;

	Admin.close();
	TempAdmin.close();
	inOut.close();
	readDisplay.close();
	gadgetList.close();
	tempGadget.close();

	remove("gadget.txt");  //delete test file
	remove("admin.txt");  //delete test file
	int result1 = rename("tempGadget.txt", "gadget.txt"); //rename the temp to text 
	int result2 = rename("tempAdmin.txt", "admin.txt"); //rename the temp to text 
	if (result1 == 0 && result2 == 0)
		cout << endl << ifstream("interface/endProgram.txt").rdbuf();
	else
		perror("Error renaming file");
}

string homeDisplay() { // homepage //dida & natasha

	string s;
	cout << endl << ifstream("interface/homeDisplay.txt").rdbuf();
	cin >> s;
	system("cls");

	return s;
}

string gadgetTypeSelection() { // dida 

	string selection;

	srand(time(0));
	int v1 = (rand() % 5);
	if ((v1 == 3) || (v1 == 5)) {
		cout << "=======================================================================================================" << endl;
		cout << "                               USE COUPON CODE : CODE06 FOR 6% DISCOUNT!                               " << endl;
		cout << "=======================================================================================================" << endl;
	}

	do {
		cout << endl << ifstream("interface/gadgetTypeSelection.txt").rdbuf();
		cin >> selection;
		system("cls");
	} while ((selection != "1") && (selection != "2") && (selection != "3") && (selection != "4"));

	return selection;
}

string buyersMenu(string selection, gadget gajet[]) {

	string c;

	srand(time(0));
	int v1 = (rand() % 5);
	if ((v1 == 3) || (v1 == 5)) {
		cout << "=======================================================================================================" << endl;
		cout << "                               USE COUPON CODE : CODE06 FOR 6% DISCOUNT!                               " << endl;
		cout << "=======================================================================================================" << endl;
	}
	cout << endl << ifstream("interface/buyersMenu.txt").rdbuf() << endl << endl;
	if (selection == "1") { //syariff
		cout << "-------------------" << endl;
		cout << "TYPE --> PENDRIVE /" << endl;
		cout << "------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "P") {
				cout << "============================================================" << endl;
				cout << "Name : " << gajet[i].gadgetName << endl;
				cout <<"Capacities : " << gajet[i].desc1 << endl;
				cout <<"Speed : " << gajet[i].desc2 << endl;
				cout << "Dimensions : " << gajet[i].desc3 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock : " << gajet[i].stock << endl;
				}
				cout << "Price : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Code : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "2") { //natasha
		cout << "----------------" << endl;
		cout << "TYPE --> MOUSE /" << endl;
		cout << "---------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "M") {
				cout << "============================================================" << endl;
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
				cout << "Code : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "3") { //natasha
		cout << "---------------------" << endl;
		cout << "TYPE --> HEADPHONES /" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "H") {
				cout << "============================================================" << endl;
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
				cout << "Code : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "4") { //natasha
		cout << "---------------------" << endl;
		cout << "TYPE --> POWER BANK /" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "B") {
				cout << "============================================================" << endl;
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
				cout << "Code : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	cin.ignore();
	do {
		cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY (MAKE SURE THE CODES IN CAPITAL LETTER)" << endl; //syariff
		cout << endl << " ----->   ";
		getline(cin, c); 
		if ((c != "P01") && (c != "P02") && (c != "M01") && (c != "M02") && (c != "M03") && (c != "H01") && (c != "H02") && (c != "H03") && (c != "B01") && (c != "B02")) {
			cout << "Please enter correct product code!!" << endl << endl;
		}
	} while ((c != "P01") && (c != "P02") && (c != "M01") && (c != "M02") && (c != "M03") && (c != "H01") && (c != "H02") && (c != "H03") && (c != "B01") && (c != "B02"));
	
	return c;
	
}

void kiraDuit(string& code, gadget gajet[], double& sum, int& hehe, ofstream& inOut, int& totalSales) { //syariff

	int quantity = 0;

	startQuantity:
	for (int i = 0; i < 10; i++) {
		if (gajet[i].type == "P") { //PENDRIVE
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "\nTHE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
					cout << "THE GADGET WILL GO BACK TO TYPE OF GADGET SELECTION" << endl;
					hehe = 5;
					return;
				}
				else {
					cout << "\nPLEASE ENTER QUANTITY  ----->   ";
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "M") { //MOUSE
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "\nTHE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
					cout << "THE GADGET WILL GO BACK TO TYPE OF GADGET SELECTION" << endl;
					hehe = 5;
					return;
				}
				else {
					cout << "\nPLEASE ENTER QUANTITY  ----->   ";
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "H") { //HEADPHONES
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "\nTHE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
					cout << "THE GADGET WILL GO BACK TO TYPE OF GADGET SELECTION" << endl;
					hehe = 5;
					return;
				}
				else {
					cout << "\nPLEASE ENTER QUANTITY  ----->   ";
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "B") { //POWERBANK
			if (code == gajet[i].gadgetCode) {
				if (gajet[i].stock == 0) {
					cout << "\nTHE ITEM FOR CODE " << code << " (" << gajet[i].gadgetName << ") IS UNAVAILABLE" << endl;
					cout << "THE GADGET WILL GO BACK TO TYPE OF GADGET SELECTION" << endl;
					hehe = 5;
					return;
				}
				else {
					cout << "\nPLEASE ENTER QUANTITY  ----->   ";
					cin >> quantity;
					if ((gajet[i].stock - quantity) < 0) {
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
	}
}

void adminLogin(int& count, string& adminUser) { //admin page (need to login first) //syariff

	int ch;
	string adminPassword = "";

	wrong:
	cout << endl << ifstream("interface/adminLogin.txt").rdbuf() << endl << endl << endl << endl << endl << endl << endl;
	cout <<endl<< setw(57)<< "ADMIN USERNAME ---> ";
	cin >> adminUser;
	cout << endl << setw(57) << "ADMIN PASSWORD ---> ";
	while (ch = _getch()) { //assign ASCII value to ch
		if (ch == 13) {  //13 is ENTER key in ASCII
			if ((adminPassword == "abc123" && adminUser == "Tasha") || (adminPassword == "qwerty123" && adminUser == "Syarep") || (adminPassword == "Dida123" && adminUser == "Dida")) { //correct password
				system("cls");
				cout << endl << ifstream("interface/adminLoginCorrect.txt").rdbuf() << endl << endl << endl << endl;
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
					cout << endl << ifstream("interface/errorLogin2.txt").rdbuf() << endl << endl << endl << endl;
					system("pause");
					system("cls");
					break;
				}
				else {
					system("cls");
					Beep(1000, 500);
					cout << endl << ifstream("interface/errorLogin.txt").rdbuf() << endl <<endl << endl << endl;
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

void displayAdminPage(double sumAllBuyer, string adminUser, gadget gajet[], ifstream& Admin,int& totalSales) { //admin page ( to display stocks, number of buyers and so on) 

	int addStocks = 0; //add stock gadget
	int selectStock = 0; //select nak display mana satu for stock
	int adminSelect = 0; // select nak tengok stocks or total profit
	int selectAddStock = 0; //tanya nak add stock atau tidak
	string code, line;

	cout << endl << ifstream("interface/displayAdmin.txt").rdbuf() << endl;
	cout << "         ----------------------------> Welcome Admin " << adminUser << " <---------------------------------" << endl << endl;

	displayAdmin:
	cout << endl << ifstream("interface/displayAdminSelection.txt").rdbuf();
	cin >> adminSelect;
	if ((adminSelect != 1) && (adminSelect != 2) && (adminSelect != 3)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << setw(68) << "Please enter correct number selection!!" << endl;  //70
		goto displayAdmin;
	}

	if (adminSelect == 1) {
	stockAdmin:
		cout << endl << ifstream("interface/displayAdminStock.txt").rdbuf();
		cin >> selectStock;
		if ((selectStock != 1) && (selectStock != 2) && (selectStock != 3) && (selectStock != 4) && (selectStock != 5)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << setw(67) << "Please enter correct number selection!!" << endl;
			goto stockAdmin;
		}
		//display all stocks data
		cout << setw(82) << "=================================================================" << endl;
		cout << setw(82) << "| Gadget Code |         Gadget Name           |  No. of stocks  |" << endl;
		cout << setw(82) << "=================================================================" << endl;
		for (int i = 0; i < 10; i++) {
			if (selectStock == 1) {
				cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
			}
			else if (selectStock == 2) {
				if (gajet[i].type == "P") {
					cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 3) {
				if (gajet[i].type == "M") {
					cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 4) {
				if (gajet[i].type == "H") {
					cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
			else if (selectStock == 5) {
				if (gajet[i].type == "B") {
					cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stock << " |" << endl;
				}
			}
		}
		cout << setw(82) << "=================================================================" << endl << endl;
		//end of display all stocks data

		cout << setw(72) << "DO YOU WANT TO ADD GADGET ITEM STOCKS (1-YES) || (2-NO)" << endl;
		cout << setw(27) << "--------->";
		cin >> selectAddStock;

		if (selectAddStock == 1) {
			//Add stocks
			tambahStock:
			cout << endl << setw(66) << "TYPE GADGET CODE FOR ITEM YOU WANT TO ADD STOCKS " << endl;
			cout << setw(27) << "--------->";
			cin >> code;
			if ((code == "P01") || (code == "P02") || (code == "M01") || (code == "M02") || (code == "M03") || (code == "H01") || (code == "H02") || (code == "H03") || (code == "B01") || (code == "B02")) {
				for (int i = 0; i < 10; i++) {  //Kalau letak code salah, dia x keluar
					if (code == gajet[i].gadgetCode) {
						cout << endl << setw(63) << "Enter number of stocks to be added ---------> ";
						cin >> addStocks;
						gajet[i].stock = gajet[i].stock + addStocks;
						cout << endl << setw(46) << "STOCKS ADDED FOR GADGET CODE (" << gajet[i].gadgetCode << ") " << gajet[i].gadgetName;
						cout << endl << setw(52) << "NEW NUMBER OF STOCKS FOR ITEM CODE " << gajet[i].gadgetCode << " IS " << gajet[i].stock << endl;
					}
				}
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << setw(52) << "PLEASE ENTER CORRECT GADGET CODE !!" << endl;
				goto tambahStock;
			}
			//End of add stocks
		}
		else{ //Display sales
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
	}
	else if (adminSelect == 2) {

		int totalSold = 0;
		cout << setw(82) << "=================================================================" << endl;
		cout << setw(82) << "| Gadget Code |         Gadget Name           | No. Of Item Sold|" << endl;
		cout << setw(82) << "=================================================================" << endl;
		for (int i = 0; i < 10; i++) {
			cout << setw(18) << "|" << setw(12) << gajet[i].gadgetCode << " |" << setw(30) << gajet[i].gadgetName << " |" << setw(16) << gajet[i].stockSold << " |" << endl;
			totalSold = totalSold + gajet[i].stockSold;
		}
		cout << setw(82) << "=================================================================" << endl;
		cout << setw(64) << "|  TOTAL NO OF ITEMS SOLD :                   |" << setw(16) << totalSold << " |" << endl;
		cout << setw(82) << "=================================================================" << endl << endl;
	}else if (adminSelect == 3) { // Display total profit
		cout << endl << setw(49) << "TOTAL PROFIT : RM" << setprecision(2) << fixed << sumAllBuyer << endl << endl << endl;
	}
}

void discountFunc(double& sum, string& coupon, double& diskaun, int& haveDiscount) {

	if (coupon == "CODE06") {
		diskaun = sum * 0.06;
		sum = sum - diskaun;
		haveDiscount = 1;
	}
	else {
		haveDiscount = 0;
	}
}

void receipt(double sum, ifstream& readDisplay, double& diskaun, int& haveDiscount) { //receipt

	string line;

	cout << endl << ifstream("interface/receipt.txt").rdbuf()<<endl << endl << endl;

	cout << setw(80) << "                        RECEIPT                         " << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|         Gadget Name           |  Price(RM)  | Quantity |" << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|                               |             |          |" << endl;
	//Loop from receiptTemp.txt
	while (getline(readDisplay, line)) {
		// Output the text from the file
		cout << line << endl;
	}
	cout << setw(80) << "|                               |             |          |" << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|                                                        |" << endl;
	cout << setw(23) << "|" << "  Subtotal"    << setw(33) << "RM" << setw(10) << setprecision(2) << fixed << sum + diskaun << setw(4) << " |" << endl;
	cout << setw(23) << "|" << "  Discount"    << setw(33) << "RM" << setw(10) << setprecision(2) << fixed << diskaun       << setw(4) << " |" << endl;
	cout << setw(23) << "|" << setw(55) << "------------"  << " |" << endl;
	cout << setw(23) << "|" << "  Total price" << setw(30) << "RM" << setw(10) << setprecision(2) << fixed << sum           << setw(4) << " |" << endl;
	cout << setw(80) << "|                                                        |" << endl;
	cout << setw(80) << "==========================================================" << endl << endl << endl;
}