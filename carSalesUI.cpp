#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//CAR CLASS////////////////////////////////////////////////////////////////////
class car {
public:
	//GETTERS
	string getStoreID();
	string getMake();
	string getModel();
	int getYear();
	double getPrice();
	//SETTERS
	void setStoreID(string id);
	void setMake(string mk);
	void setModel(string mdl);
	void setYear(int y);
	void setPrice(double p);
	//PRINT AND CONSTRUCTORS
	virtual void printCar();
	car(int); //ALLOWS USER TO ENTER ON DECLARATION
	car();
private:
	string storeID;
	string make;
	string model;
	int year;
	double basePrice;
};
string car::getStoreID()
{
	return storeID;
}

string car::getMake()
{
	return make;
}

string car::getModel()
{
	return model;
}

int car::getYear()
{
	return year;
}

double car::getPrice()
{
	return basePrice;
}

void car::setStoreID(string id)
{
	storeID = id;
}

void car::setMake(string mk)
{
	make = mk;
}

void car::setModel(string mdl)
{
	model = mdl;
}

void car::setYear(int y)
{
	year = y;
}

void car::setPrice(double p)
{
	basePrice = p;
}

void car::printCar()
{
	cout << "ID: " << storeID << endl;
	cout << "Make: " << make << endl;
	cout << "Model: " << model << endl;
	cout << "Year: " << year << endl;
	cout << "Price: $" << basePrice << endl;
}

car::car(int)
{
	
	cout << "Assign Store ID (0-49999 for new 50000-99999 for used): ";
	cin >> storeID;
	cout << "Make: ";
	cin >> make;
	cout << "Model: ";
	cin >> model;
	cout << "Year: ";
	cin >> year;
	cout << "Assign Price: ";
	cin >> basePrice;

}

car::car()
{
	storeID = "12345";
	make = "MAKE";
	model = "MODEL";
	year = 9999;
	basePrice = 9999.99;
}

//NEW CAR CLASS////////////////////////////////////////////////////////////////
class newCar : public car {
public:
	char getWarranty();
	void setWarranty(char w);
	void printCar();
	newCar(int);
	newCar();
private:
	char warrantyType;
};

char newCar::getWarranty()
{
	return warrantyType;
}

void newCar::setWarranty(char w) {
	warrantyType = w;
}

void newCar::printCar()
{
	car::printCar();
	cout << "Warranty Type: " << warrantyType << endl;
}

newCar::newCar(int) : car(1)
{
	cout << "Warranty: ";
	cin >> warrantyType;
}

newCar::newCar()
{
	warrantyType = 'N';
}
//USED CAR CLASS////////////////////////////////////////////////////////////////
class usedCar : public car {
public:
	int getMileage();
	void setMileage(int m);
	void printCar();
	usedCar(int);
	usedCar();
private:
	int mileage;
};

int usedCar::getMileage()
{
	return mileage;
}

void usedCar::setMileage(int m)
{
	mileage = m;
}

void usedCar::printCar()
{
	car::printCar();
	cout << "Mileage: " << mileage << endl;
}

usedCar::usedCar(int) : car(1)
{
	cout << "Mileage: ";
	cin >> mileage;
}

usedCar::usedCar()
{
	mileage = 9999;
}

//PROTOTYPES////////////////////////////////////////////////////////////////////
void mainMenu(vector<newCar> newInv, vector<usedCar> usedInv);			//MENU SYSTEM THAT LEADS TO SUB MENUS
void inventoryMenu(vector<newCar> newInv, vector<usedCar> usedInv);		//MENU SYSTEM THAT LEADS TO DISPLAYING AND SEARCHING INVENTORY
void salesMenu(vector<newCar> newInv, vector<usedCar> usedInv);			//MENU SYSTEM THAT LEADS TO SELLING, LEASING, AND RETURNING CARS
void purchaseMenu(vector<newCar> newInv, vector<usedCar> usedInv);		// MENU SYSTEM THAT LEADS TO ADDING A CAR OR MULTIPLE CARS TO THE INVENTORY
void fileInventory(vector<newCar> newInv, vector<usedCar> usedInv);		//LOADS FILE INTO INVENTORY VECTOR
void displayInventory(vector<newCar> newInv, vector<usedCar> usedInv);	//DISPLAYS INVENTORY BY ID/PRICE/YEAR
void searchInventory(vector<newCar> newInv, vector<usedCar> usedInv);	//SEARCH INVENTORY BY ID/PRICE/MAKE
void sellCar(vector<newCar> newInv, vector<usedCar> usedInv);			//SELLS CAR OUT OF INVENTORY
void leaseCar(vector<newCar> newInv, vector<usedCar> usedInv);			//LEASES CAR OUT OF INVENTORY AND INTO LEASE FILE
void returnLease(vector<newCar> newInv, vector<usedCar> usedInv);		//RETURNS CAR FROM LEASE FILE TO INVENTORY
void purchaseCar(vector<newCar> newInv, vector<usedCar> usedInv);		//ADDS ONE CAR TO INVENTORY
void readInvoice(vector<newCar> newInv, vector<usedCar> usedInv);		//ADDS MULTIPLE CARS TO INVENTORY BY FILE
bool duplID(vector<newCar> newInv, vector<usedCar> usedInv, string ID);	//CHECKS INVENTORY TO MAKE SURE ID IS UNIQUE

//MAIN////////////////////////////////////////////////////////////////////////
int main()
{
	//VARIABLES TO READ FILE
	string txt;
	int num;
	char t;
	double cost;

	//VARIABLES TO STORE INVENTORY
	vector<newCar> newInventory(0);
	vector<usedCar> usedInventory(0);
	newCar nc = newCar();
	usedCar uc = usedCar();

	//DOWNLOADING INVENTORY FROM FILE
	ifstream fileA("Inventory.txt");
	while (!fileA.eof()) {
		fileA >> txt;
		if (stoi(txt) > 50000) { //USED CARS ID > 50000
			uc.setStoreID(txt);
			fileA >> txt;
			uc.setMake(txt);
			fileA >> txt;
			uc.setModel(txt);
			fileA >> num;
			uc.setYear(num);
			fileA >> cost;
			uc.setPrice(cost);
			fileA >> num;
			uc.setMileage(num);
			usedInventory.push_back(uc);
		}
		else { //NEW CAR ID < 50000
			nc.setStoreID(txt);
			fileA >> txt;
			nc.setMake(txt);
			fileA >> txt;
			nc.setModel(txt);
			fileA >> num;
			nc.setYear(num);
			fileA >> cost;
			nc.setPrice(cost);
			fileA >> t;
			nc.setWarranty(t);
			newInventory.push_back(nc);
		}
	}
	fileA.close();
	//////////////////////////////////////////////////
	mainMenu(newInventory, usedInventory); //GIVES CONTROL TO USER
}

//MENU FUNCTIONS//////////////////////////////////////////////////////////////
void mainMenu(vector<newCar> newInv, vector<usedCar> usedInv) {
	cout << endl;
	int key;
	cout << "1) Inventory Managment" << endl;
	cout << "2) Sales/Lease Managment" << endl;
	cout << "3) Purchase Management" << endl;
	cout << "4) Save and Exit" << endl;
	cout << "Enter Choice: ";
	cin >> key;

	if (key == 1) {
		inventoryMenu(newInv, usedInv);
	}
	else if (key == 2) {
		salesMenu(newInv, usedInv);
	}
	else if (key == 3) {
		purchaseMenu(newInv, usedInv);
	}
	else if (key == 4) {
		fileInventory(newInv, usedInv);
	}
	else {
		cout << "Error! Invalid Choice!" << endl;;
		mainMenu(newInv, usedInv);
	}
}

void inventoryMenu(vector<newCar> newInv, vector<usedCar> usedInv) {
	cout << endl;
	int key;
	cout << "1) Display Inventory" << endl;
	cout << "2) Search Inventory" << endl;
	cout << "3) Return to Main Menu" << endl;
	cout << "Enter Choice: ";
	cin >> key;

	if (key == 1) {
		displayInventory(newInv, usedInv);
	}
	else if (key == 2) {
		searchInventory(newInv, usedInv);
	}
	else if (key == 3) {
		mainMenu(newInv, usedInv);
	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Main Menu....."<< endl;
		mainMenu(newInv, usedInv);
	}
}

void salesMenu(vector<newCar> newInv, vector<usedCar> usedInv) {
	cout << endl;
	int key;
	cout << "1) Finalize Sale" << endl;
	cout << "2) Finalize Lease" << endl;
	cout << "3) Return Lease" << endl;
	cout << "4) Return to Main Menu" << endl;
	cout << "Enter Choice: ";
	cin >> key;

	if (key == 1) {
		sellCar(newInv, usedInv);
	}
	else if (key == 2) {
		leaseCar(newInv, usedInv);
	}
	else if (key == 3) {
		returnLease(newInv, usedInv);
	}
	else if (key == 4) {
		mainMenu(newInv, usedInv);
	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Main Menu....." << endl;
		mainMenu(newInv, usedInv);
	}
}

void purchaseMenu(vector<newCar> newInv, vector<usedCar> usedInv) {
	cout << endl;
	int key;
	cout << "1) Finalize Single Purchase" << endl;
	cout << "2) Finalize Shipment Purchase" << endl;
	cout << "3) Return to Main Menu" << endl;
	cout << "Enter Choice: ";
	cin >> key;

	if (key == 1) {
		purchaseCar(newInv, usedInv);
	}
	else if (key == 2) {
		readInvoice(newInv, usedInv);
	}
	else if (key == 3) {
		mainMenu(newInv, usedInv);
	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Main Menu....." << endl;
		mainMenu(newInv, usedInv);
	}

}

//INVENTORY FUNCTIONS//////////////////////////////////////////////////////////////
void displayInventory(vector<newCar> newInv, vector<usedCar> usedInv) {
	int key;
	//COMBINES INVENTORY TO SORT ALL
	car* temp;
	vector<car*> inv(0); 
	for (int i = 0; i < newInv.size(); i++) {
		inv.push_back(&newInv[i]);
	}
	for (int i = 0; i < usedInv.size(); i++) {
		inv.push_back(&usedInv[i]);
	}
	//////////////////////////////////////
	cout << "Display Inventory By ID(1) Year(2) Price(3): ";
	cin >> key;
	cout << endl;
	//SORTING ALGORITHMS
	if (key == 1) {
		for (int i = 0; i < inv.size(); i++){
			for (int j = i + 1; j < inv.size(); j++){

				if (inv[i]->getStoreID() > inv[j]->getStoreID()){
					temp = inv[i];
					inv[i] = inv[j];
					inv[j] = temp;
				}
			}
		}
	}
	else if (key == 2) {
		for (int i = 0; i < inv.size(); i++) {
			for (int j = i + 1; j < inv.size(); j++) {

				if (inv[i]->getYear() > inv[j]->getYear()) {
					temp = inv[i];
					inv[i] = inv[j];
					inv[j] = temp;
				}
			}
		}
		
	}
	else if (key == 3) {
		for (int i = 0; i < inv.size(); i++) {
			for (int j = i + 1; j < inv.size(); j++) {

				if (inv[i]->getPrice() > inv[j]->getPrice()) {
					temp = inv[i];
					inv[i] = inv[j];
					inv[j] = temp;
				}
			}
		}

	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Inventory Menu.....";
		inventoryMenu(newInv, usedInv);
	}
	for (int i = 0; i < inv.size(); i++) {
		inv[i]->printCar();
		cout << endl;
	}
	system("pause");
	inventoryMenu(newInv, usedInv);
}

void searchInventory(vector<newCar> newInv, vector<usedCar> usedInv) {
	int key;
	vector<car*> match(0); //HOLDS MATCHES TO SEARCH
	//COMBINES INVENTORYS TO SEARCH ALL
	vector<car*> inv(0);
	for (int i = 0; i < newInv.size(); i++) {
		inv.push_back(&newInv[i]);
	}
	for (int i = 0; i < usedInv.size(); i++) {
		inv.push_back(&usedInv[i]);
	}
	/////////////////////////////////////
	cout << "Search By ID(1) Price(2) Make(3): ";
	cin >> key;

	//SEARCHING ALGORITHM
	if (key == 1) {
		string id;
		cout << "Enter ID to Search: ";
		cin >> id;
		for (int i = 0; i < inv.size(); i++) {
			if (id == inv[i]->getStoreID()) {
				match.push_back(inv[i]);
			}
		}
	}
	else if (key == 2) {
		int high;
		int low;
		cout << "Enter Low Price: ";
		cin >> low;
		cout << "Enter High Price: ";
		cin >> high;
		for (int i = 0; i < inv.size(); i++) {
			if (inv[i]->getPrice() > low && inv[i]->getPrice() < high) {
				match.push_back(inv[i]);
			}
		}
	}
	else if (key == 3) {
		string mk;
		cout << "Enter Make to Search: ";
		cin >> mk;
		for (int i = 0; i < inv.size(); i++) {
			if (mk == inv[i]->getMake()) {
				match.push_back(inv[i]);
			}
		}
	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Inventory Menu.....";
		inventoryMenu(newInv, usedInv);
	}

	//PRINT OUTPUT
	if (match.empty()) {
		cout << "No Matches Found. Please Refine Search and Try Again"<< endl;
		system("pause");
		inventoryMenu(newInv, usedInv);
	}
	else {
		cout << endl;
		for (int i = 0; i < match.size(); i++) {
			match[i]->printCar();
			cout << endl;
		}
		system("pause");
		inventoryMenu(newInv, usedInv);
	}
}

void fileInventory(vector<newCar> newInv, vector<usedCar> usedInv) {
	//SAVES ALL CHANGES MADE TO INVENTORY DURING RUN
	ofstream fileC("Inventory.txt");
	for (int i = 0; i < newInv.size(); i++) {
		fileC << newInv[i].getStoreID() << "\t";
		fileC << newInv[i].getMake() << "\t";
		fileC << newInv[i].getModel() << "\t";
		fileC << newInv[i].getYear() << "\t";
		fileC << newInv[i].getPrice() << "\t";
		fileC << newInv[i].getWarranty();
		if (i != newInv.size()) {
			fileC << endl;
		}
	}
	for (int i = 0; i < usedInv.size(); i++) {
		if (i != usedInv.size()) {
			fileC << endl;
		}
		fileC << usedInv[i].getStoreID() << "\t";
		fileC << usedInv[i].getMake() << "\t";
		fileC << usedInv[i].getModel() << "\t";
		fileC << usedInv[i].getYear() << "\t";
		fileC << usedInv[i].getPrice() << "\t";
		fileC << usedInv[i].getMileage();
	}
	fileC.close();
	cout << "All Transactions Logged! Signing Off......" << endl;
}

//SALES FUNCTIONS//////////////////////////////////////////////////////////////
void sellCar(vector<newCar> newInv, vector<usedCar> usedInv) {
	string id;
	int sellPrice;
	int spot = -1;
	bool used;
	cout << "Enter Car's Store ID: ";
	cin >> id;

	//SEARCH FOR USER ENTER ID
	for (int i = 0; i < newInv.size(); i++) {
		if (id == newInv[i].getStoreID()) { //FOUND AND SELLING NEW CAR
			spot = i;
			used = false;
		}
	}
	for (int i = 0; i < usedInv.size(); i++) {
		if (id == usedInv[i].getStoreID()) {//FOUND AND SELLING USED CAR
			spot = i;
			used = true;
		}
	}

	//SEARCH RESULTS
	if (spot == -1) {
		cout << "Error ID not found! Reenter and Try Again!" << endl;
	}
	else {
		cout << "Enter Sell Price: ";
		cin >> sellPrice;
		if (used) {
			cout << "Base Price Discrepancy: " << sellPrice - usedInv[spot].getPrice() << endl;
			usedInv.erase(usedInv.begin()+spot); //REMOVE FROM USED INV
		}
		else {
			cout << "Base Price Discrepancy: " << sellPrice - newInv[spot].getPrice() << endl;
			newInv.erase(newInv.begin()+spot); //REMOVE FROM NEW INV
		}
	}
	system("pause");
	salesMenu(newInv, usedInv);
}

void leaseCar(vector<newCar> newInv, vector<usedCar> usedInv) {
	//LOAD LEASE FILE
	ifstream fileL("Leased.txt");
	string txt;
	int num;
	double cost;
	vector<usedCar> leasedInventory(0);
	usedCar lc;
	while (!fileL.eof()) {
		fileL >> txt;
		lc.setStoreID(txt);
		fileL >> txt;
		lc.setMake(txt);
		fileL >> txt;
		lc.setModel(txt);
		fileL >> num;
		lc.setYear(num);
		fileL >> cost;
		lc.setPrice(cost);
		fileL >> num;
		lc.setMileage(num);
		leasedInventory.push_back(lc);
	}
	fileL.close();
	//////////////////////////////////////
	string id;
	int leasedMiles;
	int spot = -1;
	usedCar uc;
	vector<usedCar> usedInventory(0);
	cout << "Enter Car's Store ID: ";
	cin >> id;

	//SEARCH FOR USER ENTER ID
	for (int i = 0; i < newInv.size(); i++) {
		if (id == newInv[i].getStoreID()) {
			spot = i;
		}
	}

	//SEARCH RESULTS
	if (spot == -1) {
		cout << "Error ID not found! Reenter and Try Again!" << endl;
		salesMenu(newInv, usedInv);
	}
	else {
		cout << "Enter Leased Miles: ";
		cin >> leasedMiles;
		uc.setStoreID(newInv[spot].getStoreID());
		uc.setMake(newInv[spot].getMake());
		uc.setModel(newInv[spot].getModel());
		uc.setYear(newInv[spot].getYear());
		uc.setPrice(newInv[spot].getPrice());
		uc.setMileage(leasedMiles);
		newInv.erase(newInv.begin() + spot);
		leasedInventory.push_back(uc);
	}
	//SAVE LEASE CHANGES TO FILE
	ofstream fileOL("Leased.txt");
	for (int i = 0; i < leasedInventory.size(); i++) {
		fileOL << leasedInventory[i].getStoreID() << "\t";
		fileOL << leasedInventory[i].getMake() << "\t";
		fileOL << leasedInventory[i].getModel() << "\t";
		fileOL << leasedInventory[i].getYear() << "\t";
		fileOL << leasedInventory[i].getPrice() << "\t";
		fileOL << leasedInventory[i].getMileage();
		if (i != leasedInventory.size()-1) {
			fileOL << endl;
		}
	}
	fileOL.close();
	system("pause");
	salesMenu(newInv, usedInv);
}

void returnLease(vector<newCar> newInv, vector<usedCar> usedInv) {
	//LOAD LEASE FILE
	ifstream fileR("Leased.txt");
	string txt;
	int num;
	double cost;
	vector<usedCar> leasedInventory(0);
	usedCar lc;
	while (!fileR.eof()) {
		fileR >> txt;
		lc.setStoreID(txt);
		fileR >> txt;
		lc.setMake(txt);
		fileR >> txt;
		lc.setModel(txt);
		fileR >> num;
		lc.setYear(num);
		fileR >> cost;
		lc.setPrice(cost);
		fileR >> num;
		lc.setMileage(num);
		leasedInventory.push_back(lc);
	}
	fileR.close();
	string id;
	int leasedMiles;
	int spot = -1;
	usedCar uc;
	vector<usedCar> usedInventory(0);
	cout << "Enter Car's Store ID: ";
	cin >> id;

	//SEARCH USER ENTER ID
	for (int i = 0; i < leasedInventory.size(); i++) {
		if (id == leasedInventory[i].getStoreID()) {
			spot = i;
		}
	}

	//SEARCH RESULTS
	if (spot == -1) {
		cout << "Error ID not found! Reenter and Try Again!" << endl;
		salesMenu(newInv, usedInv);
	}
	else {
		try {//MAKE SURE PROPER ID IS ASSIGNED
			cout << "Enter Miles Driven: ";
			cin >> leasedMiles;
			cout << "PLease enter new store ID (MUST BE ABOVE 50000): ";
			cin >> id;
			if (stoi(id) < 50000 || duplID(newInv, usedInv, id)) {
				throw id;
			}
			leasedInventory[spot].setStoreID(id);
			uc.setStoreID(leasedInventory[spot].getStoreID());
			uc.setMake(leasedInventory[spot].getMake());
			uc.setModel(leasedInventory[spot].getModel());
			uc.setYear(leasedInventory[spot].getYear());
			uc.setPrice(leasedInventory[spot].getPrice());
			uc.setMileage(leasedMiles);
			leasedInventory.erase(leasedInventory.begin() + spot);
			usedInv.push_back(uc);
		}
		catch (string ID) {//INVALID ID ENTERED
			while (stoi(ID) < 50000 || duplID(newInv, usedInv, ID)) {
				cout << "ERROR! ID Out of Range Or Already Assigned" << endl;
				cout << "PLease enter new store ID (MUST BE ABOVE 50000): ";
				cin >> ID;
			}
		}	
	}
	//SAVE LEASE CHANGES
	ofstream fileOR("Leased.txt");
	for (int i = 0; i < leasedInventory.size(); i++) {
		fileOR << leasedInventory[i].getStoreID() << "\t";
		fileOR << leasedInventory[i].getMake() << "\t";
		fileOR << leasedInventory[i].getModel() << "\t";
		fileOR << leasedInventory[i].getYear() << "\t";
		fileOR << leasedInventory[i].getPrice() << "\t";
		fileOR << leasedInventory[i].getMileage();
		if (i != leasedInventory.size() - 1) {
			fileOR << endl;
		}
	}
	fileOR.close();
	system("pause");
	salesMenu(newInv, usedInv);

}

//PURCHASE FUNCTIONS//////////////////////////////////////////////////////////////
void purchaseCar(vector<newCar> newInv, vector<usedCar> usedInv) {
	int iInput;
	cout << "New Car(1) or Used Car(2): ";
	cin >> iInput;
	if (iInput == 1) {
		newCar nc(1);
		try {//MAKE SURE PROPER ID IS ASSIGNED
			if (stoi(nc.getStoreID()) > 50000 || duplID(newInv, usedInv, nc.getStoreID())) {
				throw nc.getStoreID();
			}
			newInv.push_back(nc);
		}
		catch (string ID) {//INVALID ID
			while (stoi(ID) > 50000 || duplID(newInv, usedInv, ID)) {
				cout << "ERROR! ID Out of Range Or Already Assigned" << endl;
				cout << "PLease enter new store ID (MUST BE BELOW 50000): ";
				cin >> ID;
			}
			nc.setStoreID(ID);
			newInv.push_back(nc);
		}
	}
	else if (iInput == 2) {
		usedCar uc(1);
		try {//MAKE SURE PROPER ID IS ASSIGNED
			if (stoi(uc.getStoreID()) < 50000 || duplID(newInv, usedInv, uc.getStoreID())) {
				throw uc.getStoreID();
			}
			usedInv.push_back(uc);
		}
		catch (string ID) {//INVALID ID
			while (stoi(ID) < 50000 || duplID(newInv, usedInv, ID)) {
				cout << "ERROR! ID Out of Range Or Already Assigned" << endl;
				cout << "PLease enter new store ID (MUST BE ABOVE 50000): ";
				cin >> ID;
			}
			uc.setStoreID(ID);
			usedInv.push_back(uc);
		}
	}
	else {
		cout << "Error! Invalid Choice! Redirecting Back to Purchase Menu.....";
		purchaseMenu(newInv, usedInv);
	}
	system("pause");
	purchaseMenu(newInv, usedInv);
}

void readInvoice(vector<newCar> newInv, vector<usedCar> usedInv) {
	string invoice;
	string txt;
	int num;
	char t;
	double cost;
	newCar nc = newCar();
	usedCar uc = usedCar();
	//READ INCOMING CARS INTO INVENTORY
	ifstream fileB("Invoice.txt");
	while (!fileB.eof()) {
		fileB >> txt;
		if (stoi(txt) > 50000) {//USED CAR ID > 50000
			uc.setStoreID(txt);
			while (duplID(newInv, usedInv, uc.getStoreID())) {//INVOICED CAR ID SAMES AS INVENTROY CAR ID
				int n = stoi(uc.getStoreID());
				n++;
				uc.setStoreID(to_string(n));
				//Prevent Invoiced Duplicate IDs by adding 1 to ID
			}
			fileB >> txt;
			uc.setMake(txt);
			fileB >> txt;
			uc.setModel(txt);
			fileB >> num;
			uc.setYear(num);
			fileB >> cost;
			uc.setPrice(cost);
			fileB >> num;
			uc.setMileage(num);
			usedInv.push_back(uc);
		}
		else {//NEW CAR ID < 50000
			nc.setStoreID(txt);
			while (duplID(newInv, usedInv, nc.getStoreID())) {//INVOICED CAR ID SAMES AS INVENTROY CAR ID
				int n = stoi(nc.getStoreID());
				n++;
				nc.setStoreID(to_string(n));
			//Prevent Invoiced Duplicate IDs by adding 1 to ID
			}
			fileB >> txt;
			nc.setMake(txt);
			fileB >> txt;
			nc.setModel(txt);
			fileB >> num;
			nc.setYear(num);
			fileB >> cost;
			nc.setPrice(cost);
			fileB >> t;
			nc.setWarranty(t);
			newInv.push_back(nc);
		}
	}
	fileB.close();
	cout << "Invoice Filed Successfully" << endl;
	system("pause");
	purchaseMenu(newInv, usedInv);
}

bool duplID(vector<newCar> newInv, vector<usedCar> usedInv, string ID) {
	bool found = false;
	for (int i = 0; i < newInv.size(); i++) {
		if (ID == newInv[i].getStoreID()) {
			found = true; 
		}
	}
	for (int i = 0; i < usedInv.size(); i++) {
		if (ID == usedInv[i].getStoreID()) {
			found = true;
		}
	}
	if (found) {
		return true;
	}
	else {
		return false;
	}
}
