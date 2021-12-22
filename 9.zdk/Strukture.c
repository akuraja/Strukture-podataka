#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN 10
#define MAX 70

struct _tree;
typedef struct _tree* treeP;
typedef struct _tree {
	int number;
	treeP left;
	treeP right;
} tree;

struct _list;
typedef struct _list* Position;
typedef struct _list {
	int number;
	Position next;
} list;

treeP CreatetreeP(int);
int InOrderPrint();
int InOrderPrintToList(Position, treeP);
treeP Insert(int, treeP);
int Replace(treeP);
int RandomTree(treeP);
int FindRandomnmbr(int, int);
int UpisDat(treeP, char*);

Position CreateList();
int DodavanjeNaKraj(int, Position);
int DeleteList(Position);

int main() {
	srand(time(NULL));
	int length = 0, i = 0, nmbr = 0;
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	treeP root = NULL;

	length = sizeof(niz) / sizeof(int);
	for (i = 0; i < length; i++) {
		root = Insert(niz[i], root);
	}

	printf("Pocetno stablo: ");
	InOrderPrint(root);
	printf("\n");

	UpisDat(root, "dat.txt");

	printf("Sum: ");
	Replace(root);
	InOrderPrint(root);
	printf("\n");

	UpisDat(root, "dat.txt");

	printf("Random: ");
	RandomTree(root);
	InOrderPrint(root);

	UpisDat(root, "dat.txt");

	return EXIT_SUCCESS;
}

int UpisDat(treeP p, char* filename) {
	Position head = NULL;
	head = CreateList();

	InOrderPrintToList(head, p);


	FILE* dat = NULL;
	dat = fopen(filename, "a");
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	while (head->next != NULL) {
		head = head->next;
		fprintf(dat, "%d ", head->number);
	}
	fprintf(dat, "\n");
	fclose(dat);
	DeleteList(head);
	return 0;
}

int InOrderPrintToList(Position head, treeP p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {

		InOrderPrintToList(head, p->left);
		DodavanjeNaKraj(p->number, head);
		InOrderPrintToList(head, p->right);
	}
	return EXIT_SUCCESS;
}

int DodavanjeNaKraj(int number, Position head) {
	Position q = NULL;
	q = CreateList();

	while (head->next != NULL) {
		head = head->next;
	}

	q->number = number;
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int DeleteList(Position head) {
	Position tmp = NULL;
	while (head->next) {
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}
	return EXIT_SUCCESS;
}

Position CreateList() {
	Position q = malloc(sizeof(list));
	if (!q) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->number = 0;
	q->next = NULL;
	return q;
}

int RandomTree(treeP p) {
	if (p == NULL) {
		return 0;
	}
	p->number = FindRandomnmbr(MIN, MAX);
	if (p->left) {
		RandomTree(p->left);
	}
	if (p->right) {
		RandomTree(p->right);
	}
}

int FindRandomnmbr(int min, int max) {
	int r = (rand() % (max - min + 1)) + min;
	return r;
}

int Replace(treeP p) {
	int tmp = 0;
	if (p == NULL) {
		return 0;
	}
	tmp = p->number;
	p->number = Replace(p->left) + Replace(p->right);
	return p->number + tmp;
}

treeP CreatetreeP(int number) {
	treeP q = malloc(sizeof(tree));
	if (!q) {
		printf("Can't allocate memory!");
		return NULL;
	}
	q->number = number;
	q->left = NULL;
	q->right = NULL;
	return q;
};

treeP Insert(int number, treeP p) {
	if (p == NULL) {
		p = CreatetreeP(number);
	}
	else {
		if (number == p->number) {
			p->left = Insert(number, p->left);
		}
		if (number < p->number) {
			p->right = Insert(number, p->right);
		}
		if (number > p->number) {
			p->left = Insert(number, p->left);
		}
	}
	return p;
}

int InOrderPrint(treeP p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {

		InOrderPrint(p->left);
		printf("%d\t", p->number);
		InOrderPrint(p->right);
	}
	return EXIT_SUCCESS;
}