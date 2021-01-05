#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <limits> //semata nak buat error
#undef max //semata nak buat error

using namespace std;

//struct
struct gadget { //syariff
	string gadgetName;
	string desc1;
	string desc2;
	string desc3;
	string desc4;
	int stock=0;
	double price=0;
	string gadgetCode;
};

//function prototype
int homeDisplay();
int gadgetTypeSelection();
string buyersMenu(int , gadget [], gadget[], gadget[], gadget[]);
void kiraDuit(string, gadget[], gadget[], gadget[], gadget[],double&, int&);
void assignReceipt(string, gadget[], gadget[], gadget[], gadget[]);
void adminPage(int &);
void displayAdminPage(double);
void receipt(string, double, gadget[], gadget[], gadget[], gadget[]);


int main() {
	//fixed console size   //syariff
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top,950, 600, TRUE); // 950 width, 600 height
	//end of fixed console size


	int status, selection, count=0;
	char homepage;
	double sum=0.00,sumAllBuyer = 0.00; //sum tu total harga buyer beli, sumAllBuyer tu total semua pembelian with receipt berlainan
	string code;
	gadget pendrive[2] = { //syariff
		//{gadgetName, desc1, desc2, desc3, desc4, stock, price, gadgetCode};
		{"Kingston 32 gb","32GB","70MB/s read","60mm x 21.2mm x 10mm","0",2,15.50,"P01"},
		{"Kingston 64 gb","64GB","100MB/s read","60mm x 21.2mm x 10mm","0",150,28.00,"P02"}
	};
	gadget mouse[3] = { // natasha
		{"HP","LED","WIRELESS","115mm x 45mm x 60mm","0",200,39.90,"M01"}, 
		{"Logitech","LASER","WIRELESS","115mm x 45mm x 60mm","0",150,59.00,"M02"}, 
		{"Dell","BALL","WIRED","115mm x 45mm x 60mm","0",180,30.00,"M03"} 
	};
	gadget headphones[3] = { // natasha 
		{"SONY","WIRELESS","188mm x 208mm x 90mm","0","0",100,189.80,"H01"}, 
		{"JBL","WIRELESS","188mm x 208mm x 85mm","0","0",70,250.00,"H02"}, 
		{"BOSE","WIRED","170mm x 200mm x 85mm","0","0",48,200.00,"H03"} 
	};
	gadget powerbank[2] = { // natasha
		{"XIAOMI","4000mAH","3","140mm x 62mm x 21mm","223",200,49.90,"B01"}, 
		{"PINENG","2000mAH","4","130mm x 60mm x 17mm","200",120,69.00,"B02"} 
	};


	do { // syariff
		home:
		status=homeDisplay();
		if (status == 1) { //BUYERS PAGE
			back:
			int hehe = 0;
			selection = gadgetTypeSelection();
			code = buyersMenu(selection,pendrive, mouse, headphones, powerbank);
			kiraDuit(code,pendrive, mouse, headphones, powerbank,sum,hehe);
			if (hehe == 5) { // bila input salah
				system("pause");
				system("cls");
				goto back;
			}

			assignReceipt(code, pendrive, mouse, headphones, powerbank);
			//KENA ADA FUNCTION UNTUK MASUKKAN INFO DALAM ARRAY LAIN SUPAYA RECEIPT KELUAR SEMUA
			
			cout << "\nDo you want to buy another gadget? Click 1 if yes || Click 2 if no : ";
			cin >> hehe;
			if (hehe == 1) { //bila input 1/yes
				system("cls");
				goto back;
			}
			else {
				system("cls");
			}
			receipt(code,sum, pendrive, mouse, headphones, powerbank);
			system("pause");
			system("cls");
		}
		else if (status == 2) { // ADMIN PAGE
			adminPage(count);
			if (count == 3) {
				count = 0;
				goto home;
			}
			displayAdminPage(sumAllBuyer);  //will put function for admin(check stocks/check total profit)
			
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

		sumAllBuyer = sumAllBuyer + sum;
		sum = 0.00;
		cout << "\nBack to homepage ?(Y|N) " << endl;
		cout << endl << " -----> :  ";
		cin >> homepage;
		system("cls");
	} while ((homepage == 'Y') || (homepage == 'y'));     //after all the buyers dah beli barang, boleh tekan Y, gi hompage and tukar kepada admin

	return 0;
} //syariff

 
int homeDisplay() { // homepage //dida & natasha

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

string buyersMenu(int selection,gadget pendrive[], gadget mouse[], gadget headphones[], gadget powerbank[]) {
	 
	string c;
	
	if (selection == 1) { //syariff
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -PENDRIVE-                    " << endl << endl;
		for (int i = 0; i < 2; i++) {
			cout << "Name : " << pendrive[i].gadgetName << endl;
			cout << "Capacities : " << pendrive[i].desc1 << endl;
			cout << "Speed : " << pendrive[i].desc2 << endl;
			cout << "Dimensions : " << pendrive[i].desc3 << endl;
			if (pendrive[i].stock == 0) {
				cout << "Stock : " << "UNAVAILABLE" << endl;
			}
			else {
				cout << "Stock : " << pendrive[i].stock << endl;
			}
			cout << "Price : " << setprecision(2) << fixed << pendrive[i].price << endl;
			cout << "Code : " << pendrive[i].gadgetCode << endl << endl;
		}
	}else if (selection == 2) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -MOUSE-                    " << endl << endl;
		for (int i = 0; i < 3; i++) {
			cout << "Name : " << mouse[i].gadgetName << endl;
			cout << "Capacities : " << mouse[i].desc1 << endl;
			cout << "Speed : " << mouse[i].desc2 << endl;
			cout << "Dimensions : " << mouse[i].desc3 << endl;
			if (mouse[i].stock == 0) {
				cout << "Stock : " << "UNAVAILABLE" << endl;
			}
			else {
				cout << "Stock : " << mouse[i].stock << endl;
			}
			cout << "Price : " << setprecision(2) << fixed << mouse[i].price << endl;
			cout << "Code : " << mouse[i].gadgetCode << endl << endl;
		}
	}
	else if (selection == 3) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -HEADPHONES-                    " << endl << endl;
		for (int i = 0; i < 3; i++) {
			cout << "Name : " << headphones[i].gadgetName << endl;
			cout << "Existence of wires : " << headphones[i].desc1 << endl;
			cout << "Dimension : " << headphones[i].desc2 << endl;
			if (headphones[i].stock == 0) {
				cout << "Stock : " << "UNAVAILABLE" << endl;
			}
			else {
				cout << "Stock : " << headphones[i].stock << endl;
			}
			cout << "Price : " << setprecision(2) << fixed << headphones[i].price << endl;
			cout << "Code : " << headphones[i].gadgetCode << endl << endl;
		}
	}
	else if (selection == 4) { //natasha
		cout << " **************** CATEGORIES OF GADGET  **************** " << endl;
		cout << "                        -POWER BANK-                    " << endl << endl;
		for (int i = 0; i < 2; i++) {
			cout << "Name : " << powerbank[i].gadgetName << endl;
			cout << "Battery Capacities : " << powerbank[i].desc1 << endl;
			cout << "Amount of Ports : " << powerbank[i].desc2 << endl;
			cout << "Dimensions : " << powerbank[i].desc3 << endl;
			cout << "Weight : " << powerbank[i].desc4 << endl;
			if (powerbank[i].stock == 0) {
				cout << "Stock : " << "UNAVAILABLE" << endl;
			}
			else {
				cout << "Stock : " << powerbank[i].stock << endl;
			}
			cout << "Price : " << setprecision(2) << fixed << powerbank[i].price << endl;
			cout << "Code : " << powerbank[i].gadgetCode << endl << endl;
		}
	}
	
	cout << "ENTER PRODUCT CODE FOR ITEMS YOU WANT TO BUY " << endl; //syariff
	cout << endl << " -----> :  ";
	cin.ignore();
	getline(cin,c);

	return c;
}

void kiraDuit(string code, gadget pendrive[], gadget mouse[], gadget headphones[], gadget powerbank[], double& sum, int& hehe) { //syariff

	if ((code == "P01") /*|| (code == "p01")*/) { //option pendrive
		if (pendrive[0].stock == 0) {
			cout << "THE ITEM FOR CODE " << code << " (" << pendrive[0].gadgetName<<") IS UNAVAILABLE" << endl;
		}
		else {
			pendrive[0].stock = pendrive[0].stock - 1;
			sum = sum + pendrive[0].price;
		}
	}
	else if ((code == "P02") /*|| (code == "p02")*/) {
		pendrive[1].stock = pendrive[1].stock - 1;
		sum = sum + pendrive[1].price;
	}
	else if ((code == "M01") /*|| (code == "m01")*/) { //option mouse
		mouse[0].stock = mouse[0].stock - 1;
		sum = sum + mouse[0].price;
	}
	else if ((code == "M02") /*|| (code == "m02")*/) {
		mouse[1].stock = mouse[1].stock - 1;
		sum = sum + mouse[1].price;
	}
	else if ((code == "M03") /*|| (code == "m03")*/) {
		mouse[2].stock = mouse[2].stock - 1;
		sum = sum + mouse[2].price;
	}
	else if ((code == "H01") /*|| (code == "h01")*/) { //option headphones
		headphones[0].stock = headphones[0].stock - 1;
		sum = sum + headphones[0].price;
	}
	else if ((code == "H02") /*|| (code == "h02")*/) {
		headphones[1].stock = headphones[1].stock - 1;
		sum = sum + headphones[1].price;
	}
	else if ((code == "H03") /*|| (code == "h03")*/) {
		headphones[2].stock = headphones[2].stock - 1;
		sum = sum + headphones[2].price;
	}
	else if ((code == "B01") /*|| (code == "b01")*/) {
		powerbank[0].stock = powerbank[0].stock - 1;
		sum = sum + powerbank[0].price;
	}
	else if ((code == "B02") /*|| (code == "b02")*/) {
		powerbank[1].stock = powerbank[1].stock - 1;
		sum = sum + powerbank[1].price;
	}
	else {
		cout << "Wrong code, try again. ";
		hehe = 5;
	}
}
void assignReceipt(string code, gadget pendrive[], gadget mouse[], gadget headphones[], gadget powerbank[]) {

	string displayReceipt[50];

	for (int i = 0; i < 2; i++) { //for loop i < 2 sebab these gadget ada 2 selection barang
		if (code == pendrive[i].gadgetCode) { //syariff
			
		}
		/*else if (code == powerbank[i].gadgetCode) { //dida
			powerbank[i].gadgetName;
			powerbank[i].desc1;
			powerbank[i].desc2;
			powerbank[i].desc3;
			powerbank[i].desc4;
		}*/
	}

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {
			displayReceipt[j] = pendrive[i].gadgetName;
			displayReceipt[j] = pendrive[i].desc1;
			displayReceipt[j] = pendrive[i].desc2;
			displayReceipt[j] = pendrive[i].desc3;
		}

}

void adminPage(int &count) { //admin page (need to login first) //syariff

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
				}
				goto wrong;if (count == 3) {
				
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

void displayAdminPage(double sumAllBuyer) { //admin page ( to display stocks, number of buyers and so on) //syariff

	cout << "_________________________________________________________________________________________________________" << endl;
	cout << setw(60) << "ADMIN PAGE " << endl;
	cout << "_________________________________________________________________________________________________________" << endl;
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
	cout << "Stocks ada 23" << endl; //dummy
	cout << "TOTAL PROFIT : RM" << sumAllBuyer << setprecision(2) << fixed << endl;
}

void receipt(string code, double sum, gadget pendrive[], gadget mouse[], gadget headphones[], gadget powerbank[]) { //receipt
	
	cout << "\n===== RECEIPT =====" << endl;
	for (int i = 0; i < 2; i++) { //for loop i < 2 sebab these gadget ada 2 selection barang
		if (code == pendrive[i].gadgetCode) { //syariff
			cout << "Name : " << pendrive[i].gadgetName << endl;
			cout << "Capacities : " << pendrive[i].desc1 << endl;
			cout << "Speed : " << pendrive[i].desc2 << endl;
			cout << "Dimensions : " << pendrive[i].desc3 << endl;
		}
		else if (code == powerbank[i].gadgetCode) { //dida
			cout << "Name : " << powerbank[i].gadgetName << endl;
			cout << "Battery Capacities : " << powerbank[i].desc1 << endl;
			cout << "Amount of Ports : " << powerbank[i].desc2 << endl;
			cout << "Dimensions : " << powerbank[i].desc3 << endl;
			cout << "Weight : " << powerbank[i].desc4 << endl;
		}
	}

	for (int i = 0; i < 3; i++) { //for loop i < 3 sebab these gadget ada 3 selection barang
		if (code == mouse[i].gadgetCode) { //syariff
			cout << "Name : " << mouse[i].gadgetName << endl;
			cout << "Capacities : " << mouse[i].desc1 << endl;
			cout << "Speed : " << mouse[i].desc2 << endl;
			cout << "Dimensions : " << mouse[i].desc3 << endl;
		}
		else if (code == headphones[i].gadgetCode) { //dida
			cout << "Name : " << headphones[i].gadgetName << endl;
			cout << "Existence of wires : " << headphones[i].desc1 << endl;
			cout << "Dimension : " << headphones[i].desc2 << endl;
		}
	}

	cout << "\nTotal harga kena bayar : RM" << setprecision(2) << fixed << sum << endl;
}