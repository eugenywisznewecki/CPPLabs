#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <process.h>
#include <math.h>

struct Item {
	int key;
	char* string;
	Item* left;
	Item* right;
};

void createTree(Item ** root);
int addElement(Item ** tree);
void findByKey(Item** root);
void deleteByKey(Item** root);
void viewTree(Item* tree, int level);
int runTask(Item* root, int depth);
void finishWork(Item** root);

void main(void){
	setlocale(LC_ALL, "Russian");
	int task;

	Item * binaryTree = NULL;

	while (true) {
		system("cls");
		printf_s("Choose task to work with: \n");
		printf_s("1- Create new Binary Tree\n");
		printf_s("2- Add element to Binary Tree\n");
		printf_s("3- Search info by key\n");
		printf_s("4- Delete element by key\n");
		printf_s("5- Viewing tree\n");
		printf_s("6- Running task\n");
		printf_s("7- Exit\n");
		fflush(stdin);
		scanf_s("%d", &task);

		switch (task) {
		case 1:
			createTree(&binaryTree);
			break;
		case 2:
			addElement(&binaryTree);
			break;
		case 3:
			findByKey(&binaryTree);
			break;
		case 4:
			deleteByKey(&binaryTree);
			break;
		case 5:
			printf_s("Your tree!\n");
			viewTree(binaryTree, 0);
			_getch();
			break;
		case 6:
			printf_s("Running task!\n");
			if (!binaryTree) {
				printf_s("Create tree before searching!\n");
			}
			printf_s("Your tree depth = %d\n", runTask(binaryTree, 0));
			_getch();
			break;
		case 7:
			printf_s("Work is finished");
			finishWork(&binaryTree);
			binaryTree = NULL;
			_getch();
			break;
		default:
			printf_s("Enter valid number!\n");
			_getch();
			break;
		}
	}	
}

void createTree(Item ** root) {
	if (*root != NULL) {
		printf_s("Tree already exists!\n");
		_getch();
		return;
	}
	printf_s("Creating tree!\n");
	int count;
	printf_s("How many items do you want to add?\n");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++) {
		int a = addElement(root);
		if (a < 0) {
			i--;
		}
	}
	_getch();
}
int addElement(Item ** root) {
	printf_s("Creating item!\n");

	int key, find;
	char* string = new char[256];
	fflush(stdin);
	Item* t = *root;

	if (*root == NULL){
		printf_s("Input Root Key:\n");
		scanf_s("%d", &key);

		t = new Item;
		t->key = key;
		t->left = t->right = NULL;
		fflush(stdin);
		printf_s("Input root Value String:\n");
		gets(string);
		t->string = string;
		*root = t;
	}
	else {
		printf_s("Input Key:\n");
		scanf_s("%d", &key);
		
		Item* t = *root;
		Item* prev = t;

		find = 0;
		while (t && !find) {
			prev = t;
			if (key == t->key) {
				find = 1;
			}
			else {
				if (key < t->key) {
					t = t->left;
				}
				else {
					t = t->right;
				}
			}
		}
		if (!find){
			t = new Item;
			t->key = key;
			t->left = t->right = NULL;
			fflush(stdin);
			printf_s("Input Value String:\n");
			gets(string);
			t->string = string;

			if (prev != NULL) {
				if (key < prev->key){
					prev->left = t;
				}
				else {
					prev->right = t;
				}
			}
			//*root = t;

		}
		else {
			printf_s("Your elements should have unique keys!");
			return -1;
		}
	}

	_getch();
	return 1;
}
void findByKey(Item** root) {
	printf_s("Searching item!\n");

	if (*root == NULL) {
		printf_s("Create tree before searching!\n");
		_getch();
		return;
	}

	Item* t = *root;		
	int key;
	fflush(stdin);
	printf_s("Enter key for searching!\n");
	scanf_s("%d", &key);
	int find = 0;

	while (t && !find) {
		if (key == t->key) {
			find = 1;
			printf_s("Your element key = %d, value = %s", t->key, t->string);
		}
		else {
			if (key < t->key) {
				t = t->left;
			}
			else {
				t = t->right;
			}
		}
	}

	if (!find) {
		printf_s("Your tree doesn't contain element with key = %d", key);
	}

	_getch();
}
void deleteByKey(Item** root) {
	printf_s("Deleting item!\n");

	if (*root == NULL) {
		printf_s("Create tree before deleting items!\n");
		_getch();
		return;
	}

	int key;
	fflush(stdin);
	printf_s("Enter key for deleting!\n");
	scanf_s("%d", &key);
	
	Item* forDel, *forDelParent, *forSubst,  *forSubstParent;
	forDel = *root;
	forDelParent = NULL;

	while ((forDel) && (forDel->key != key)){
		forDelParent = forDel;
		if (forDel->key > key) {
			forDel = forDel->left;
		}
		else {
			forDel = forDel->right;
		}
		
		if (!forDel){
			printf_s("Your tree doesn't contain element with key = %d", key);
			_getch();
			return;
		}
	}

	if (!(forDel->right)) {
		forSubst = forDel->left;
	}
	else if (!(forDel->left)) {
		forSubst = forDel->right;
	}
	else {
		forSubstParent = forDel;
		forSubst = forDel->left;
		while (forSubst->right != NULL) {
			forSubstParent = forSubst;
			forSubst = forSubst->right;
		}

		if (forSubstParent == forDel) {
			forSubst->right = forDel->right;
		}
		else {
			forSubst->right = forDel->right;
			forSubstParent->right = forSubst->left;
			forSubst->left = forSubstParent;
		}
	}

	if (forDel == *root) {
		*root = forSubst;
	}
	else {
		if (forDel->key < forDelParent->key) {
			forDelParent->left = forSubst;
		}
		else {
			forDelParent->right = forSubst;
		}
		delete forDel;
	}

	_getch();
}
void viewTree(Item* tree, int level) {
	if (tree) {
		viewTree(tree->right, level + 1);
		for (int i = 0; i < level; i++)
		{
			printf("   ");
		}
		printf("%d | %s\n", tree->key, tree->string);
		viewTree(tree->left, level + 1);
	}	
}
int runTask(Item* root, int depth){
	if (!root) {
		return depth;
	}
	int right = runTask(root->right, depth + 1);
	int left = runTask(root->left, depth + 1);

	return (right > left) ? right : left;
}
void finishWork(Item** root){
	if (*root != NULL) {
		finishWork(&(*root)->left);
		finishWork(&(*root)->right);
		delete *root;
	}	
}