#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60

struct _Directory;
typedef struct _Directory* PositionDir;
typedef struct _Directory {
	PositionDir child;
	PositionDir sibling;
	char name[MAX];
} Directory;

struct _Cvor;
typedef struct _Cvor* Position;
typedef struct _Cvor {
	PositionDir parent;
	Position next;
} Cvor;

int Push(Position, PositionDir);
int PrintIzbornik();
int InsertSorted(PositionDir, PositionDir);
int dir(PositionDir);
PositionDir cdparent(Position);
PositionDir Pop(Position);
PositionDir cd(Position, PositionDir, char*);
PositionDir CreateDirectory(char*);
PositionDir md(Position, PositionDir, char*);
Position CreatePosition();


int main() {
	char operation = '0';
	int isActive = 1;

	char name[MAX];
	Position stog = NULL;
	PositionDir root = NULL, current = NULL, result = NULL;


	stog = CreatePosition();
	root = CreateDirectory("C:");
	current = root;

	while (1) {
		PrintIzbornik();
		scanf(" %c", &operation);
		switch (operation) {
		case '1':
			printf("Your choice: md\n");
			printf("Name of new directory: ");
			scanf("%s", name);
			result = md(stog, current, name);
			if (!result) {
				printf("Error\n");
			}
			break;
		case '2':
			printf("Your choice: cd dir\n");
			printf("Name of directory: ");
			scanf("%s", name);
			result = cd(stog, current, name);
			if (!result) {
				printf("Error");
			}
			else {
				current = result;
			}
			break;
		case '3':
			printf("Your choice: cd..\n");
			result = cdparent(stog);
			if (!result) {
				printf("Ne moze se ici vise od korijena!");
			}
			else {
				current = result;
			}
			break;
		case '4':
			printf("Your choice: dir\n");
			dir(current);
			break;
		case '5':
			printf("Your choice: EXIT\n");
			isActive = 0;
			break;
		default:
			printf("Greška!");
			break;
		}
	}
	return 0;
}

int dir(PositionDir current) {
	PositionDir tmp = NULL;
	printf("%s\n", current->name);
	if (current->child != NULL) {
		tmp = current->child;
		while (tmp != NULL) {
			printf("\t%s", tmp->name);
			tmp = tmp->sibling;
		}
	}
	return 0;
};

PositionDir cd(Position stog, PositionDir current, char* name) {
	PositionDir q = NULL, tmp = NULL;
	if (current->child == NULL) {
		printf("Trenutni direktorij je prazan");
		return NULL;
	}
	tmp = current->child;
	while (tmp != NULL) {
		if (strcmp(name, tmp->name) == 0) {
			q = tmp;
		}
		tmp = tmp->sibling;
	}
	Push(stog, current);
	return q;
}

int InsertSorted(PositionDir current, PositionDir q) {
	PositionDir head = NULL, r = NULL;
	head = CreateDirectory(" ");
	r = head;


	if (current->child == NULL) {
		current->child = q;
		return 0;
	}

	head->sibling = current->child;
	while (r->sibling != NULL && strcmp(r->sibling->name, q->name) < 0) {
		r = r->sibling;
	}
	q->sibling = r->sibling;
	r->sibling = q;
	current->child = head->sibling;
	return 0;
};

PositionDir md(Position stog, PositionDir current, char* name) {
	PositionDir q = NULL;
	q = CreateDirectory(name);
	InsertSorted(current, q);
	return q;
}

int PrintIzbornik() {
	printf("Izbornik: \n\t 1. md-make directory \n\t 2. cd dir-change directory \n\t 3. cd.. -change directory to parent"
		"\n\t 4. dir-print content of choosen directory \n\t 5. exit\n");
	return 0;
}

Position CreatePosition() {
	Position q = malloc(sizeof(Cvor));
	if (!q) {
		printf("Can't allocate memory\n");
		return NULL;
	}
	q->next = NULL;
	return q;
}

PositionDir CreateDirectory(char* name) {
	PositionDir q = malloc(sizeof(Directory));
	if (!q) {
		printf("Can't allocate memory\n");
		return NULL;
	}
	q->sibling = NULL;
	q->child = NULL;
	strcpy(q->name, name);
	return q;
}
PositionDir Pop(Position stog) {
	Position tmp = NULL;
	PositionDir p = NULL;
	if (stog == NULL || stog->next == NULL) {
		return NULL;
	}
	tmp = stog->next;
	p = tmp->parent;
	stog->next = tmp->next;
	free(tmp);
	return p;
}

int Push(Position stog, PositionDir current) {
	Position q = NULL;
	q = CreatePosition();
	q->parent = current;
	q->next = stog->next;
	stog->next = q;
	return 0;
}

PositionDir cdparent(Position stog) {
	return Pop(stog);
}