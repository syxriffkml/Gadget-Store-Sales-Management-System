// previous changes on the code can be checked here :  https://github.com/syxriffkml/Gadget-Store-Sales-Management-System 
#include <iostream>
#include <fstream> //text file
#include <sstream> // to use stringstream
#include <string> 
#include <conio.h> //to use _getch in login admin page
#include <iomanip> // for setw() and setprecision()
#include <windows.h> //mainly use for system("pause") and system("cls") - ONLY WORKS ON WINDOWS OS!!!!!!!!!!!!!!
#include <cstdlib> //for rand() function, used it to display coupon
#include <cstdio> // for rename function, to rename textfile
#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

//struct
struct gadget { //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	string type; //type as in Pendrive / Mouse / Headphones / Powerbank
	string gadgetName;
	string desc1;
	string desc2;
	string desc3;
	string desc4;
	int stock = 0;
	double price = 0;
	string gadgetCode;
	int stockSold = 0; // number of items sold for each gadget
};

//function prototype
string homeDisplay(); // display hompage and to select 1. Buyers page 2. Admin page 3. Exit
string gadgetTypeSelection(); // Function for user input for gadget type of choice (1.Pendrive / 2.Mouse / 3.Headphones / 4.Powerbank)
string buyersMenu(string, gadget[]); // Display gadgets and user can input gadget code based on gadget they want to buy
void getQuantity(string&, gadget[], double&, int&, ofstream&, int&); //To get user input quantity and also change the gadget stock's quantity
void discountFunc(double&, string&, double&); //calculation if user have coupon for discount, else if do not have coupon, ignore
void adminLogin(int&, string&); // admin login page
void displayAdminPage(double, string, gadget[], ifstream&, int&); // Admin can select for 1. Display/Add stocks, 2. Display gadget sold, 3. Display total profit
void receipt(double, ifstream&, double&); //read from text file (receiptTemp.txt) and display for receipt purposes
void writeIntoTemp(ofstream&, ifstream&, gadget[], ofstream&, ifstream&, ofstream&, ifstream&, double&, int&); // write data into textfile and close file


int main() {

	//MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	//fixed console size   
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 870, 800, TRUE); // 870 width, 800 height (only looks good on 24 inch monitor)
	//end of fixed console size

	//Receipt display text file //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	ofstream inOut("gadgetData/receiptTemp.txt", ios::trunc);  //write gadget receipt to be used later on for receipt
	ifstream readDisplay("gadgetData/receiptTemp.txt"); //read input gadgets to display on receipt
	//List of gadget & description  text file //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	ifstream gadgetList("gadgetData/gadget.txt"); //read gadget items
	ofstream tempGadget("gadgetData/tempGadget.txt"); //store gadget items then the file is renamed into main file
	//Admin text file //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	ifstream Admin("gadgetData/admin.txt"); //read admin.txt (only have sumAllBuyers info)
	ofstream TempAdmin("gadgetData/tempAdmin.txt"); //add total price into admin (only add sumAllBuyers info)

	int count = 0, adminRepeat, totalSales = 0, haveDiscount = 0;
	char homepage; 
	double sum = 0.00, sumAllBuyer = 0.00, diskaun = 0.00; // sum is the total amount the customer needs to pay, sumAllBuyer is total payment that the company gets from ther buyer
	string status, selection, code, haveCoupon, coupon, adminUser;

	gadget gajet[10]; // 10 gadgets fixed 


	string myString;
	string line;
	int i = 0;
	//loop to get data from textfile into struct
	//read line by line, and have a delimeter which is comma " , "
	while (getline(gadgetList, line)) {  //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
		stringstream ss(line); 
		getline(ss, gajet[i].type, ',');
		getline(ss, gajet[i].gadgetName, ',');
		getline(ss, gajet[i].desc1, ',');
		getline(ss, gajet[i].desc2, ',');
		getline(ss, gajet[i].desc3, ',');
		getline(ss, gajet[i].desc4, ',');
		getline(ss, myString, ','); //to get int stock
		gajet[i].stock = stoi(myString); // stoi = string to int
		getline(ss, myString, ',');  // to get double price
		gajet[i].price = stod(myString);  // stod = string to double
		getline(ss, gajet[i].gadgetCode, ',');
		getline(ss, myString, ','); //to get int stocks sold
		gajet[i].stockSold = stoi(myString);  // stoi = string to int
		i++;
	}
	// read data from textfile (only have one data only)
	Admin >> sumAllBuyer; //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN

	do { 
	home:
		status = homeDisplay();
		if (status == "1") { //BUYERS PAGE
		back:
			int hehe = 0;
			selection = gadgetTypeSelection();
			code = buyersMenu(selection, gajet);
			getQuantity(code, gajet, sum, hehe, inOut, totalSales);
			if (hehe == 5) { //when user input for gadget with unavailable stock
				system("pause");
				system("cls");
				goto back;
			}
			cout << "\nDO YOU WANT TO BUY ANOTHER GADGET? (1-YES) || (2-NO)" << endl; //syariff
			cout << endl << " ----->   ";
			cin >> hehe;
			if (hehe == 1) { //if user wants to buy another gaadget
				system("cls");
				goto back;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
			}
			cout << endl << ifstream("interface/couponPage.txt").rdbuf();
			cout << endl << endl << endl << setw(75) << "DO YOU HAVE COUPON CODE (1-YES) || (2-NO) ----->   ";
			cin >> haveCoupon;
			if (haveCoupon == "1") {
				int counter = 0;
				do {
					cout << endl << setw(72) << "ENTER COUPON CODE (CASE SENSITIVE)  ----->   ";
					cin >> coupon;
					counter++;
					if (counter == 3) {
						cout << endl << endl << setw(76) << "YOU HAVE ENTERED WRONG COUPON CODE FOR 3 TIMES," << endl;
						cout << endl << setw(81) << "THE PROGRAM WILL CONTINUE YOU PURCHASES WITHOUT DISCOUNT" << endl << endl << endl << endl;
						break;
					}
				} while ((coupon != "CODE06") && (coupon != "CODE12"));
				cout << endl << endl;
				system("pause");
				system("cls");
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
			}
			discountFunc(sum, coupon, diskaun);
			receipt(sum, readDisplay, diskaun);
			system("pause");
			system("cls");
		}
		else if (status == "2") { // ADMIN PAGE
			adminLogin(count, adminUser);
			if (count == 3) { // if admin entered wrong username or password for 3 times
				count = 0;
				goto home;
			}
			do {
				displayAdminPage(sumAllBuyer, adminUser, gajet, Admin, totalSales);  
				cout << endl << setw(60) << "BACK TO SELECTION AGAIN?  (1-YES) || (2-NO)" << endl;
				cout << setw(30) << " --------->   ";
				cin >> adminRepeat;
				if (adminRepeat == 1) { // if admin input 1 (admin wants to go back to admin selection menu)
					system("pause");
					system("cls");
				}
				else { //when admin input other than 1 (admin do not want to go to admin selection menu)
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("pause");
					system("cls");
				}
			} while (adminRepeat == 1);
		}
		else if (status == "3") { // EXIT PROGRAM 
			writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay, TempAdmin, Admin, sumAllBuyer, totalSales); // TO WRITE / CLOSE / REMOVE & RENAME TEXT FILE
			return 0;
		}
		else { // ERROR (WHEN AT HOMEPAGE, USER DID NOT INPUT 1 OR 2 OR 3)
			if (cin.fail() && (status != "1") && (status != "2") && (status != "3")) { //when input char on int variable 
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			Beep(1000, 500); //beep sound
			cout << endl << ifstream("interface/homepageError.txt").rdbuf();
			system("pause");
			system("cls");
		}

		sumAllBuyer = sumAllBuyer + sum;
		diskaun = 0.00;
		sum = 0.00;
		cout << endl << ifstream("interface/backToHomepage.txt").rdbuf();
		cin >> homepage;
		if (homepage == '1') {
			inOut.clear(); // .clear() to clear past customer's receipt display
			readDisplay.clear(); // .clear() to clear past customer's receipt display
		}
		system("cls");
	} while ((homepage == '1'));     //after the buyers have made transaction, they can press 1 to go to homepage again

	writeIntoTemp(tempGadget, gadgetList, gajet, inOut, readDisplay, TempAdmin, Admin, sumAllBuyer, totalSales); // TO WRITE / CLOSE/ REMOVE & RENAME TEXT FILE

	return 0;
}

// write data into textfile and close file  //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
void writeIntoTemp(ofstream& tempGadget, ifstream& gadgetList, gadget gajet[], ofstream& inOut, ifstream& readDisplay, ofstream& TempAdmin, ifstream& Admin, double& sumAllBuyer, int& totalSales) {

	for (int i = 0; i < 10; i++) {  //write gadget data into file
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
	TempAdmin << sumAllBuyer; // write data sumAllBuyer into file (only one data) 

	//close all file
	Admin.close();
	TempAdmin.close();
	inOut.close();
	readDisplay.close();
	gadgetList.close();
	tempGadget.close();

	//for updating files (if close program, when start over there are still data from previous transactions)
	remove("gadgetData/gadget.txt");  //delete test file  for gadget description
	remove("gadgetData/admin.txt");  //delete test file  for admin file(sumALLbuyers)
	int result1 = rename("gadgetData/tempGadget.txt", "gadgetData/gadget.txt"); //rename the temp to text  for gadget description
	int result2 = rename("gadgetData/tempAdmin.txt", "gadgetData/admin.txt"); //rename the temp to text   for admin file(sumALLbuyers)
	if (result1 == 0 && result2 == 0) // if the files are renamed successfully
		cout << endl << ifstream("interface/endProgram.txt").rdbuf();
	else
		perror("Error renaming file");
}

// display hompage and to select 1. Buyers page 2. Admin page 3. Exit
string homeDisplay() { //NUR KHALIDA KHALISHA BINTI KHALID and NATASHA SHAFIQA BINTI A NAJEBUDIN

	string s;
	cout << endl << ifstream("interface/homeDisplay.txt").rdbuf(); 
	cin >> s;
	system("cls");

	return s;
}

// Function for user input for gadget type of choice (1.Pendrive / 2.Mouse / 3.Headphones / 4.Powerbank)
string gadgetTypeSelection() {

	string selection;

	//randomly display coupon code  //NUR KHALIDA KHALISHA BINTI KHALID
	srand(time(0));
	int random = (rand() % 5);
	if ((random == 3) || (random == 5)) {
		cout << "*******************************************************************************************************" << endl;
		cout << "                               USE COUPON CODE : CODE06 FOR 6% DISCOUNT!                               ";
	}
	else if (random == 2) {
		cout << "*******************************************************************************************************" << endl;
		cout << "                               USE COUPON CODE : CODE12 FOR 12% DISCOUNT!                               ";
	}

	do {
		cout << endl << ifstream("interface/gadgetTypeSelection.txt").rdbuf();
		cin >> selection;
		system("cls");
	} while ((selection != "1") && (selection != "2") && (selection != "3") && (selection != "4"));

	return selection;
}

// Display gadgets and user can input gadget code based on gadget they want to buy
string buyersMenu(string selection, gadget gajet[]) {

	string c;

	//randomly display coupon code //NUR KHALIDA KHALISHA BINTI KHALID
	srand(time(0));
	int random = (rand() % 5);
	if ((random == 3) || (random == 5)) {
		cout << "*******************************************************************************************************" << endl;
		cout << "                               USE COUPON CODE : CODE06 FOR 6% DISCOUNT!                               ";
	}
	else if (random == 2) {
		cout << "*******************************************************************************************************" << endl;
		cout << "                               USE COUPON CODE : CODE12 FOR 12% DISCOUNT!                               ";
	}

	cout << endl << ifstream("interface/buyersMenu.txt").rdbuf() << endl << endl;
	if (selection == "1") { //MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
		cout << "-------------------" << endl;
		cout << "TYPE --> PENDRIVE /" << endl;
		cout << "------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "P") {
				cout << "============================================================" << endl;
				cout << "Name        : " << gajet[i].gadgetName << endl;
				cout << "Capacities  : " << gajet[i].desc1 << endl;
				cout << "Speed       : " << gajet[i].desc2 << endl;
				cout << "Dimensions  : " << gajet[i].desc3 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock       : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock       : " << gajet[i].stock << endl;
				}
				cout << "Price       : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Gadget Code : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "2") { //NATASHA SHAFIQA BINTI A NAJEBUDIN
		cout << "----------------" << endl;
		cout << "TYPE --> MOUSE /" << endl;
		cout << "---------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "M") {
				cout << "============================================================" << endl;
				cout << "Name               : " << gajet[i].gadgetName << endl;
				cout << "Sensing Type       : " << gajet[i].desc1 << endl;
				cout << "Existence of wire  : " << gajet[i].desc2 << endl;
				cout << "Dimensions         : " << gajet[i].desc3 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock              : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock              : " << gajet[i].stock << endl;
				}
				cout << "Price              : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Gadget Code        : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "3") { //NATASHA SHAFIQA BINTI A NAJEBUDIN
		cout << "---------------------" << endl;
		cout << "TYPE --> HEADPHONES /" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "H") {
				cout << "============================================================" << endl;
				cout << "Name               : " << gajet[i].gadgetName << endl;
				cout << "Existence of wires : " << gajet[i].desc1 << endl;
				cout << "Dimension          : " << gajet[i].desc2 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock              : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock              : " << gajet[i].stock << endl;
				}
				cout << "Price              : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Gadget Code        : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	else if (selection == "4") { //NATASHA SHAFIQA BINTI A NAJEBUDIN
		cout << "---------------------" << endl;
		cout << "TYPE --> POWER BANK /" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (gajet[i].type == "B") {
				cout << "============================================================" << endl;
				cout << "Name               : " << gajet[i].gadgetName << endl;
				cout << "Battery Capacities : " << gajet[i].desc1 << endl;
				cout << "Amount of Ports    : " << gajet[i].desc2 << endl;
				cout << "Dimensions         : " << gajet[i].desc3 << endl;
				cout << "Weight             : " << gajet[i].desc4 << endl;
				if (gajet[i].stock == 0) {
					cout << "Stock              : " << "UNAVAILABLE" << endl;
				}
				else {
					cout << "Stock              : " << gajet[i].stock << endl;
				}
				cout << "Price              : " << setprecision(2) << fixed << gajet[i].price << endl;
				cout << "Gadget Code        : " << gajet[i].gadgetCode << endl;
				cout << "============================================================" << endl << endl;
			}
		}
	}
	cin.ignore();
	do {
		cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY (MAKE SURE THE CODES IN CAPITAL LETTER)" << endl;  //NUR KHALIDA KHALISHA BINTI KHALID
		cout << endl << " ----->   ";
		getline(cin, c);
		if ((c != "P01") && (c != "P02") && (c != "M01") && (c != "M02") && (c != "M03") && (c != "H01") && (c != "H02") && (c != "H03") && (c != "B01") && (c != "B02")) {
			cout << "Please enter correct product code!!" << endl << endl;
		}
	} while ((c != "P01") && (c != "P02") && (c != "M01") && (c != "M02") && (c != "M03") && (c != "H01") && (c != "H02") && (c != "H03") && (c != "B01") && (c != "B02"));

	return c;

}

//To get user input quantity and also change the gadget stock's quantity 
void getQuantity(string& code, gadget gajet[], double& sum, int& hehe, ofstream& inOut, int& totalSales) { 

	int quantity = 0;

startQuantity:
	for (int i = 0; i < 10; i++) {
		if (gajet[i].type == "P") { //PENDRIVE MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
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
					if ((gajet[i].stock - quantity) < 0) { //when user input quantity more than stock
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {  //wrong input, user did not enter number
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					//write data into file to create receipt
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "M") { //MOUSE  NATASHA SHAFIQA BINTI A NAJEBUDIN
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
					if ((gajet[i].stock - quantity) < 0) { //when user input quantity more than stock
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {  //wrong input, user did not enter number
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					//write data into file to create receipt
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "H") { //HEADPHONES  NATASHA SHAFIQA BINTI A NAJEBUDIN
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
					if ((gajet[i].stock - quantity) < 0) {  //when user input quantity more than stock
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {  //wrong input, user did not enter number
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					//write data into file to create receipt
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
		else if (gajet[i].type == "B") { //POWERBANK  NATASHA SHAFIQA BINTI A NAJEBUDIN
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
					if ((gajet[i].stock - quantity) < 0) { //when user input quantity more than stock
						cout << "Please re-enter quantity because stock is not enough!" << endl << endl;
						goto startQuantity;
					}
					else if (cin.fail()) {  //wrong input, user did not enter number
						cout << "Please enter an actual number for quantity!" << endl << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						goto startQuantity;
					}
					gajet[i].stock = gajet[i].stock - quantity;
					gajet[i].stockSold = gajet[i].stockSold + quantity;
					sum = sum + (gajet[i].price * quantity);
					//write data into file to create receipt
					inOut << setw(23) << "|" << setw(30) << gajet[i].gadgetName << " |" << setw(12) << setprecision(2) << fixed << gajet[i].price << " |" << setw(9) << quantity << " |" << endl;
				}
			}
		}
	}
}

// admin login page
void adminLogin(int& count, string& adminUser) { // login page MUHAMMAD SYARIFF KAMIL BIN SYPUDIN

	int ch;
	string adminPassword = "";

	wrong:
	cout << endl << ifstream("interface/adminLogin.txt").rdbuf() << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << setw(57) << "ADMIN USERNAME ---> ";
	cin >> adminUser;
	cout << endl << setw(57) << "ADMIN PASSWORD ---> ";

	while (ch = _getch()) { //assign ASCII value to ch
		if (ch == 13) {  //13 is ENTER key in ASCII
			if ((adminPassword == "abc123" && adminUser == "Tasha") || (adminPassword == "qwerty123" && adminUser == "Syarep") || (adminPassword == "Dida123" && adminUser == "Dida")) { 
				//correct password
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
					cout << endl << ifstream("interface/errorLogin.txt").rdbuf() << endl << endl << endl << endl;
					system("pause");
					system("cls");
					goto wrong;
				}
			}
		}
		else if (ch == 8) { //8 is BACKSPACE key in ASCII
			if (adminPassword.length() > 0) { //set condition blocking error while input
				cout << "\b \b"; //delete * everytime user click backspace
				adminPassword.erase(adminPassword.length() - 1); //erase string length
			}
		}
		else {
			//make password cannot be seen, when input it display as pasword : ************
			cout << "*";
			adminPassword += ch;
		}
	}

}

// Admin can select for 1. Display/Add stocks, 2. Display gadget sold, 3. Display total profit
void displayAdminPage(double sumAllBuyer, string adminUser, gadget gajet[], ifstream& Admin, int& totalSales) { //admin page ( to display stocks, number of buyers and so on) 

	int addStocks = 0; //to add stock gadget
	int selectStock = 0; //tp select to display for all stock or just for specific gadget type of stocks
	int adminSelect = 0; // to select either 1. view/add stocks , 2. view gadget sold, 3. Total Profit
	int selectAddStock = 0; //to select to either add stocks or not
	string code, line;

	cout << endl << ifstream("interface/displayAdmin.txt").rdbuf() << endl;
	cout << "         ----------------------------> Welcome Admin " << adminUser << " <---------------------------------" << endl << endl;

displayAdmin:
	cout << endl << ifstream("interface/displayAdminSelection.txt").rdbuf();
	cin >> adminSelect;
	if ((adminSelect != 1) && (adminSelect != 2) && (adminSelect != 3)) {  //wrong adminSelect input NUR KHALIDA KHALISHA BINTI KHALID
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << setw(68) << "Please enter correct number selection!!" << endl;
		goto displayAdmin;
	}

	if (adminSelect == 1) { //Display or add stock MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	stockAdmin:
		cout << endl << ifstream("interface/displayAdminStock.txt").rdbuf();
		cin >> selectStock;
		if ((selectStock != 1) && (selectStock != 2) && (selectStock != 3) && (selectStock != 4) && (selectStock != 5)) { //wrong selectStock input
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
			cout << endl << setw(82) << "TYPE GADGET CODE FOR ITEM YOU WANT TO ADD STOCKS (CAPITAL LETTER)" << endl;
			cout << setw(27) << "--------->";
			cin >> code;
			if ((code == "P01") || (code == "P02") || (code == "M01") || (code == "M02") || (code == "M03") || (code == "H01") || (code == "H02") || (code == "H03") || (code == "B01") || (code == "B02")) {
				for (int i = 0; i < 10; i++) {  //if user entered correct gadget code
					if (code == gajet[i].gadgetCode) {
						cout << endl << setw(63) << "ENTER NUMBER OF STOCKS TO BE ADDED ---------> ";
						cin >> addStocks;
						gajet[i].stock = gajet[i].stock + addStocks;
						cout << endl << setw(47) << "STOCKS ADDED FOR GADGET CODE (" << gajet[i].gadgetCode << ") " << gajet[i].gadgetName;
						cout << endl << setw(52) << "NEW NUMBER OF STOCKS FOR ITEM CODE " << gajet[i].gadgetCode << " IS " << gajet[i].stock << endl;
					}
				}
			}
			else { // if wrong input/lowercase gadget code
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << setw(52) << "PLEASE ENTER CORRECT GADGET CODE !!" << endl;
				goto tambahStock;
			}
			//End of add stocks
		}
		else { //if user do not want to add stocks
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
	}
	else if (adminSelect == 2) { //Display number of item sold MUHAMMAD SYARIFF KAMIL BIN SYPUDIN

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
	}
	else if (adminSelect == 3) { // Display total profit MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
		cout << endl << setw(49) << "TOTAL PROFIT : RM" << setprecision(2) << fixed << sumAllBuyer << endl << endl << endl;
	}
}

//calculation if user have coupon for discount, else if do not have coupon, ignore
void discountFunc(double& sum, string& coupon, double& diskaun) { //NUR KHALIDA KHALISHA BINTI KHALID

	if (coupon == "CODE06") { //discount 6%
		diskaun = sum * 0.06;
		sum = sum - diskaun;
	}
	else if (coupon == "CODE12") { ////discount 12%
		diskaun = sum * 0.12;
		sum = sum - diskaun;
	}
}

//read from text file (receiptTemp.txt) and display for receipt purposes
void receipt(double sum, ifstream& readDisplay, double& diskaun) { 

	string line;

	cout << endl << ifstream("interface/receipt.txt").rdbuf() << endl << endl << endl;
	// Display receipt with cool looking table NATASHA SHAFIQA BINTI A NAJEBUDIN
	cout << setw(80) << "                        RECEIPT                         " << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|         Gadget Name           |  Price(RM)  | Quantity |" << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|                               |             |          |" << endl;
	//Loop from receiptTemp.txt  MUHAMMAD SYARIFF KAMIL BIN SYPUDIN
	while (getline(readDisplay, line)) {
		// Output the text from the file(receiptTemp.txt)
		cout << line << endl;
	}
	cout << setw(80) << "|                               |             |          |" << endl;
	cout << setw(80) << "==========================================================" << endl;
	cout << setw(80) << "|                                                        |" << endl;
	cout << setw(23) << "|" << "  Subtotal" << setw(33) << "RM" << setw(10) << setprecision(2) << fixed << sum + diskaun << setw(4) << " |" << endl;
	cout << setw(23) << "|" << "  Discount" << setw(33) << "RM" << setw(10) << setprecision(2) << fixed << diskaun << setw(4) << " |" << endl;
	cout << setw(23) << "|" << setw(55) << "------------" << " |" << endl;
	cout << setw(23) << "|" << "  Total price" << setw(30) << "RM" << setw(10) << setprecision(2) << fixed << sum << setw(4) << " |" << endl;
	cout << setw(80) << "|                                                        |" << endl;
	cout << setw(80) << "==========================================================" << endl << endl << endl;
}
