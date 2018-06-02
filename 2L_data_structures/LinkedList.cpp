#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <process.h>
#include <string.h>

struct List {
	int info;
	List* next, *prev;
};

void createList(List **t, List **begin, List **end);
void addElementInListEnd(List **t, List **begin, List **end, int info);
void viewList(List *begin);
void runTask(List **begin);
void deleteList(List **begin);


void main(void) {
	setlocale(LC_ALL, "Russian");
	printf_s("Task two.\n\n");
	_getch();

	List *begin, *t, *end;
	begin = NULL;
	end = NULL;
	t = NULL;

	int subTask;
	while (true) {
		system("cls");
		printf_s("Choose 1 for creating list\nChoose 2 for adding element in a list\nChoose 3 for viewing list\nChoose 4 for running task\nChoose 0 finishing\n");
		fflush(stdin);
		scanf_s("%d", &subTask);

		switch (subTask) {
		case 1:
			createList(&t, &begin, &end);
			break;
		case 2:
			int info;
			printf_s("Enter element: \n");
			scanf_s("%d", &info);
			addElementInListEnd(&t, &begin, &end, info);
			_getch();
			break;
		case 3:
			viewList(begin);
			break;
		case 4:
			runTask(&begin);
			break;
		case 0:
			printf_s("Work is finished\n");
			deleteList(&begin);
			t = NULL;
			if (begin == NULL) {
				puts("Memory is Freed!");
			}
			_getch();
			break;
		default:
			printf_s("No!\n");
			_getch();
			break;
		}
	}
}

void createList(List **t, List **begin, List **end) {
	if (*t != NULL) {
		printf_s("List is already created!");
		_getch();
		return;
	}
	printf_s("Creating List: \n");
	int count;
	printf_s("Enter number of elements in your initial list: \n");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++) {
		addElementInListEnd(t, begin, end, i);
	}
	_getch();
}

void addElementInListEnd(List **t, List **begin, List **end, int info) {
	printf_s("Adding element: %d\n", info);

	if (*t == NULL) {
		*t = new List;
		(*t)->info = info;
		(*t)->prev = (*t)->next = NULL;
		*begin = *end = *t;
	}
	else {
		*t = new List;
		(*t)->info = info;
		(*t)->next = NULL;
		(*t)->prev = *end;
		(*end)->next = *t;
		*end = *t;
	}

}
void viewList(List *begin) {
	printf_s("Viewing List: From Beginning: \n");

	List *t = begin;
	if (begin == NULL){
		printf_s("List is empty! \n");
		_getch();
		return;
	}
	while (t != NULL){
		printf_s("Element: %d\n", t->info);
		t = t->next;
	}

	_getch();
}
void runTask(List **begin) {
	printf_s("Running task: \n");
	
	printf_s("Your initial List: \n");

	List *t = *begin;
	if (begin == NULL){
		printf_s("List is empty! \n");
		_getch();
		return;
	}
	viewList(*begin);

	while (t != NULL){
		List* t1 = t->next;
		while (t1 != NULL) {			
			if (t1->info > t->info) {				
				int tmp = t1->info;
				t1->info = t->info;
				t->info = tmp;
			}
			
			t1 = t1->next;
		}
		
		t = t->next;
	}	

	printf_s("Your result Stack: \n");
	viewList(*begin);

	_getch();
}

void deleteList(List **begin){
	List* t;
	while (*begin != NULL) {
		t = *begin;
		*begin = (*begin)->next;
		delete(t);
	}
}
