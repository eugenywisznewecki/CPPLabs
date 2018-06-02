#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <process.h>

struct Stack {
	int info;
	Stack* next;
};

void createStack(Stack **t, Stack **begin);
void addElementInStack(Stack **t, Stack **begin, int info);
void viewStack(Stack *begin);
void runTask(Stack **begin);
void deleteStack(Stack **begin);


void main(void) {
	setlocale(LC_ALL, "Russian");
	printf_s("Task one.\n\n");
	_getch();

	Stack *begin, *t;
	begin = NULL;
	t = NULL;

	int subTask;
	while (true) {
		system("cls");
		printf_s("Choose 1 for creating stack\nChoose 2 for adding element in a stack\nChoose 3 for viewing stack\nChoose 4 for running task\nChoose 0 finishing\n");
		fflush(stdin);
		scanf_s("%d", &subTask);

		switch (subTask) {
		case 1:
			createStack(&t, &begin);
			break;
		case 2:
			int info;
			printf_s("Enter element: \n");
			scanf_s("%d", &info);
			addElementInStack(&t, &begin, info);
			_getch();
			break;
		case 3:
			viewStack(begin);
			break;
		case 4:
			runTask(&begin);
			break;
		case 0:
			printf_s("Work is finished\n");
			deleteStack(&begin);
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

void createStack(Stack **t, Stack **begin) {
	if (*t != NULL) {
		printf_s("Stack is already created!");
		_getch();
		return;
	}
	printf_s("Creating Stack: \n");
	int count;
	printf_s("Enter number of elements in your initial stack: \n");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++) {
		addElementInStack(t, begin, i);
	}
	_getch();
}

void addElementInStack(Stack **t, Stack **begin, int info) {
	printf_s("Adding element: %d\n", info);

	if (*t == NULL) {		
		*t = new Stack;
		(*t)->info = info;
		(*t)->next = *begin;
		*begin = *t;
	}
	else {
		*t = new Stack;
		(*t)->info = info;
		(*t)->next = *begin;
		*begin = *t;
	}
	
}
void viewStack(Stack *begin) {
	printf_s("Viewing Stack: \n");

	Stack *t = begin;
	if (begin == NULL){
		printf_s("Stack is empty! \n");
		_getch();
		return;
	}
	while (t != NULL){
		printf_s("Element: %d\n", t->info);
		t = t->next;
	}

	_getch();
}
void runTask(Stack **begin) {
	printf_s("Running task: \n");
	printf_s("Your initial Stack: \n");
	viewStack(*begin);
	if (*begin == NULL)  {
		_getch();
		return;
	}

	int tmpBegin;
	int tmpEnd;
	Stack *t;
	t = *begin;
	tmpBegin = (*begin)->info;
	if (t->next == NULL) {
		printf_s("Your stack consists of 1 element!\n");
		_getch();
		return;
	}

	while (t->next != NULL) {
		t = t->next;
		if (t->next == NULL) {
			tmpEnd = t->info;
			t->info = tmpBegin;
		}
	} 	
	(*begin)->info = tmpEnd;
	printf_s("Your result Stack: \n");
	viewStack(*begin);

	_getch();
}

void deleteStack(Stack **begin){
	Stack* t;
	while (*begin != NULL) {
		t = *begin;
		*begin = (*begin)->next;
		delete(t);
	}	
}
