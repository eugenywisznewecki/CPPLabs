#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
	int tabelNumber;
	char FIO[101];
	int hoursPerMonth;
	int hourlyRate;
};

//char* fileName = new char[101];
char* fileName = "d:\\employees.txt";

void createFile(void);
void viewFile(void);
void editFile(void);
void runTask(void);

Employee createItem(void);
void editItem(void);
void deleteItem(void);

int isTableNumUnique(int tableNum);
void askAndWritingToFile(Employee employee);
void addItem(void);
int countItems();
void writeToFile(Employee employee);
int findTableNumber(int tableNumber);
int getTNId(int tableNumber);

void main(void) {
	setlocale(LC_ALL, "Russian");
	int choose;

	while (true) {
		system("cls");
		printf_s("Menu:\n");
		printf_s("Enter 1 for creating new file,\n");
		printf_s("Enter 2 for viewing your file,\n");
		printf_s("Enter 3 for editing your file,\n");
		printf_s("Enter 4 for running task,\n");
		printf_s("Enter 5 for exit.\n");

		fflush(stdin);
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			createFile();
			break;
		case 2:
			viewFile();
			break;
		case 3:
			editFile();
			break;
		case 4:
			runTask();
			break;
		case 5:
			printf_s("Work is finished!");
			_getch();
			break;
		default:
			printf_s("Choose value from 1 to 5!");
			_getch();
			break;
		}
	}
}

void createFile(void) {
	FILE *file;
	Employee empl;

	printf_s("Creating file...\n");

	if (!(file = fopen(fileName, "w+"))) {
		printf_s("Cannot create file, sorry!\n");
		return;
	}

	printf_s("The file was successfully created! It is empty by now!\n");
	fclose(file);
	int count;
	printf_s("How many employees you want to enter?\n");
	scanf_s("%d", &count);

	printf_s("Starting entering emplyoes!\n");
	int i = 0;
	for (int i = 0; i < count; i++) {
		printf_s("%d: \n", i);
		empl = createItem();
		if (isTableNumUnique(empl.tabelNumber)) {
			askAndWritingToFile(empl);
		}
		else {
			printf_s("All table numbers should be unique! Info was not written!\n");
			i--;
			_getch();
		}
	}
	_getch();
}


void viewFile(void) {
	printf_s("Viewing file...\n");
	FILE *f;
	Employee empl;
	if (!(f = fopen(fileName, "r+"))) {
		printf_s("Opening failed!\n");
		return;
	}
	int num = 1;
	while (fread(&empl, sizeof(Employee), 1, f)) {
		if (feof(f)) break;
		printf_s("N%d\nTableNumber = %d\nname = %shours per month = %d \nhourly rate = %d\n", num, empl.tabelNumber, empl.FIO, empl.hoursPerMonth, empl.hourlyRate);
		num++;
	}

	fclose(f);

	_getch();
}

void editFile(void) {
	int choose;
	while (true) {
		system("cls");
		printf_s("Editing file...\n");
		printf_s("Menu:\n");
		printf_s("Enter 1 for creating new item,\n");
		printf_s("Enter 2 for editing existing item,\n");
		printf_s("Enter 3 for deleting item,\n");
		printf_s("Enter 0 for returning to menu,\n");

		fflush(stdin);
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			addItem();
			break;
		case 2:
			editItem();
			break;
		case 3:
			deleteItem();
			break;
		case 0:
			printf_s("Going to menu...\n");
			_getch();
			return;
		default:
			printf_s("Incorrect number!\n");
			_getch();
			break;
		}
	}
}

void addItem() {
	FILE *f;
	if (!(f = fopen(fileName, "a+"))) {
		printf_s("Opening failed!");
	}

	Employee empl = createItem();
	printf_s("%d", empl.tabelNumber);
	if (!(isTableNumUnique(empl.tabelNumber))) {
		printf_s("There already exists employee with such a tableNumber. Try again!");
		_getch();
		return;
	}
	writeToFile(empl);
	//fwrite(&empl, sizeof(Employee), 1, f);
	//fclose(f);
}

void runTask(void) {
	struct EmplWithSalary{
		int tabelNumber;
		char FIO[101];
		int hoursPerMonth;
		int hourlyRate;
		double salary;
	};

	int n = countItems();
	EmplWithSalary* employees = new EmplWithSalary[n];
	FILE* f;
	Employee empl;

	printf_s("Running task...\n");

	if (!(f = fopen(fileName, "r+"))) {
		printf_s("Opening failed!\n");
		return;
	}	
	
	int i = 0;
	while (fread(&empl, sizeof(Employee), 1, f)) {
		if (feof(f)) break;
		int mainHours = 0;
		int doubleHours = 0;

		strcpy((*(employees + i)).FIO, empl.FIO);
		(*(employees + i)).hourlyRate = empl.hourlyRate;
		(*(employees + i)).hoursPerMonth = empl.hoursPerMonth;
		(*(employees + i)).tabelNumber = empl.tabelNumber;

		if (empl.hoursPerMonth <= 144) {
			mainHours = empl.hoursPerMonth;
		}
		else {
			mainHours = 144;
			doubleHours = empl.hoursPerMonth - 144;
		}
		double salary = 0.9 * (mainHours * empl.hourlyRate + doubleHours * empl.hourlyRate * 2);
		
		(*(employees + i)).salary = salary;
		i++;
	}
	fclose(f);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {			
			if ((*(employees + i)).salary < (*(employees + j)).salary) {
				EmplWithSalary tmp = *(employees + i);
				*(employees + i) = *(employees + j);
				*(employees + j) = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		printf_s("N%d\nTableNumber = %d\nName = %sSalary = %.2lf\n", i, (*(employees + i)).tabelNumber, (*(employees + i)).FIO, (*(employees + i)).salary);
	}

	_getch();

}

Employee createItem(void){
	Employee employee;

	printf_s("\nEnter table number, FIO, HoursPerMonth, hourlyRate of your new employee\n");
	fflush(stdin);
	printf_s("Tabel number: ");
	scanf_s("%d", &employee.tabelNumber);

	fflush(stdin);
	printf_s("FIO: ");
	fgets(&employee.FIO[0], 30, stdin);

	printf_s("Work hours: ");
	fflush(stdin);
	scanf_s("%d", &employee.hoursPerMonth);

	printf_s("Hourly rate: ");
	fflush(stdin);
	scanf_s("%d", &employee.hourlyRate);

	//printf_s("\nYour new employee:\nName - %stable Number - %d\nhours per month - %d\nhourly rate - %d\n", employee.FIO, employee.tabelNumber, employee.hoursPerMonth, employee.hourlyRate);
	return employee;
}

void askAndWritingToFile(Employee employee) {
	/*printf_s("Do you want to write this in the file? (y/n)\n");

	fflush(stdin);
	if (_getch() == 'y') {*/
	writeToFile(employee);
	/*}
	else {
	printf_s("Information was not written!\n");
	}
	_getch();*/
}

void editItem(void){
	int tableNumber;
	printf_s("Enter Tabel Number of employee you want to edit\n");
	scanf_s("%d", &tableNumber);

	int id = findTableNumber(tableNumber);

	if (id < 0) {
		printf_s("There is no element with this tableNumber!");
		_getch();
		return;
	}

	int num = countItems();	

	FILE *f;
	f = fopen(fileName, "r+");

	Employee* employees = new Employee[num];
	for (int i = 0; i < num; i++) {
		fread((employees + i), sizeof(Employee), 1, f);
	}
	fclose(f);

	printf_s("Enter new parameters of your employee: ");
	Employee empl = createItem();

	if ((!(isTableNumUnique(empl.tabelNumber)))&&(id != getTNId(tableNumber))) {
		printf_s("There already exists another employee with such table number! Try again!\n");
		_getch();
		return;
	}

	printf_s("\nYour new employee:\nName - %stable Number - %d\nhours per month - %d\nhourly rate - %d\n", empl.FIO, empl.tabelNumber, empl.hoursPerMonth, empl.hourlyRate);
	strcpy((employees+id)->FIO, empl.FIO);
	(*(employees + id)).tabelNumber = empl.tabelNumber;
	(*(employees + id)).hourlyRate = empl.hourlyRate;
	(*(employees + id)).hoursPerMonth = empl.hoursPerMonth;

	if (!(f = fopen(fileName, "w+"))) {
		printf_s("Error opening file!");
	}
	for (int i = 0; i < num; i++) {		
		fwrite((employees + i), sizeof(Employee), 1, f);
	}
	fclose(f);
	//delete[] employees;

	printf_s("Element was successfully edited!");
	_getch();
}
int getTNId(int tableNumber){
	FILE* f;
	if (!(f = fopen(fileName, "r+"))) {
		printf_s("Error opening file!");
		_getch();
		return -1;
	}
	Employee empl;
	int result = 0;
	while (true) {
		fread(&empl, sizeof(Employee), 1, f);
		if (tableNumber == empl.tabelNumber) {
			return result;
		}
		if (feof) break;
		result++;
	}	
	return -1;
}

void deleteItem(void){
	int tableNumber;
	printf_s("Enter Tabel Number employee you want to delete\n");	
	scanf_s("%d", &tableNumber);

	int id = findTableNumber(tableNumber);

	if (id < 0) {
		printf_s("There is no element with this tableNumber!");
		return;
	}
	
	int num = countItems();
	
	FILE *f;
	f = fopen(fileName, "r+");

	Employee* employees = new Employee[num];
	for (int i = 0; i < num; i++) {
		fread((employees + i), sizeof(Employee), 1, f);
	}
	fclose(f);	

	f = fopen(fileName, "w+");
	for (int i = 0; i < num; i++) {
		if (i == id) {
			continue;
		}
		fwrite((employees + i), sizeof(Employee), 1, f);
	}
	fclose(f);
	delete[] employees;
	printf_s("Element was successfully deleted!");
	_getch();
}

void writeToFile(Employee employee) {
	printf_s("Writing to file....\n");
	FILE *f;
	if (f = fopen(fileName, "a+")) {
		fwrite(&employee, sizeof(Employee), 1, f);
		printf_s("New employee was added!\n");		
	}
	else {
		printf_s("An error occurs!\n");
	}
	fclose(f);
	_getch();
}

int isTableNumUnique(int tableNum){
	FILE *f;
	Employee empl;
	int result = 1;

	if (!(f = fopen(fileName, "r+"))) {
		printf_s("Opening failed");
		result = 0;
		return result;
	}
	
	while (fread(&empl, sizeof(Employee), 1, f)) {
		if (feof(f)) break;
		//printf_s("! %d ", empl.tabelNumber);
		if (empl.tabelNumber == tableNum) {
			result = 0;
		}		
	}	
	fclose(f);
	return result;
}

int countItems(){
	FILE *f;
	Employee empl;

	if (!(f = fopen(fileName, "r+b"))) {
		printf_s("Error opening file!");
	}

	int num = 0;
	while (fread(&empl, sizeof(Employee), 1, f)) {
		if (feof(f)) break;		
		num++;
	}
	return num;
}

int findTableNumber(int tableNumber) {
	FILE *f;
	Employee empl;

	if (!(f = fopen(fileName, "r+"))) {
		printf_s("Error opening file!");
	}

	int id= 0;
	while (fread(&empl, sizeof(Employee), 1, f)) {
		if (feof(f)) break;
		if (empl.tabelNumber == tableNumber) {
			return id;
		}
		id++;
	}
	return -1;
}

void askForFileName(){

}