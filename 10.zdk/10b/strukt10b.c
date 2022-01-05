#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (120)

struct _List;
typedef struct _List* ListPosition;
typedef struct _List
{
	char city[max];
	int citizens;
	ListPosition next;
}List;

struct _tree;
typedef struct _tree* treePosition;
typedef struct _tree
{
	char country[max];
	ListPosition List;
	treePosition L;
	treePosition D;
}tree;


treePosition CreateTreeElement(treePosition S);
treePosition ReadDatCountry(treePosition p, char* dat);
treePosition InsertTree(treePosition S, char* country, char* country_name);
treePosition FindCountry(treePosition S, char* country);
int inorder(treePosition S);
int CreateList(ListPosition p, char* city, int citizens);
ListPosition ReadDatCities(ListPosition p, char* dat);
int PrintList(ListPosition p);
ListPosition CreateListElement(ListPosition p);
int print(ListPosition p, int number);


int main()
{
	treePosition root = NULL, current = NULL;
	char dat[max] = "drzave.txt", country[max] = { 0 }, c = { 0 };
	int z = 1, number = 0;

	root = CreateTreeElement(root);

	root = ReadDatCountry(root, dat);
	inorder(root);

	printf("1) Choose country! \n 2) Exit\n");

	while (z)
	{
		printf("\nChoice:");
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Choose country: \n");
			scanf(" %s", country);
			current = FindCountry(root, country);
			if (current == NULL)
			{
				printf("Choosen country is not in file!");
				return 0;
			}
			printf("\nCities with more citizens than you entered will be shown. Enter number: \n");
			scanf("%d", &number);
			print(current->List, number);
			break;
		case '2':
			printf("Exit\n");
			z = 0;
			break;
		}
	}

	return 0;
}
ListPosition CreateListElement(ListPosition p)
{
	p = (ListPosition)malloc(sizeof(List));
	if (p == NULL) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(p->city, "");
	p->citizens = 0;
	p->next = NULL;

	return p;
}

treePosition CreateTreeElement(treePosition S)
{
	S = (treePosition)malloc(sizeof(tree));

	if (S == NULL)
	{
		printf("Can't allocate memory!");
		return -1;
	}

	S->L = NULL;
	S->D = NULL;
	S->List = NULL;
	strcpy(S->country, "");

	return S;
}
treePosition ReadDatCountry(treePosition p, char* dat)
{
	FILE* file = NULL;
	char country[max] = { 0 }, country_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Can't open file!");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", country, country_dat);
		p = InsertTree(p, country, country_dat);
	}

	fclose(file);
	return p;
}
treePosition InsertTree(treePosition S, char* country, char* country_dat)
{
	if (S == NULL)
	{
		S = CreateTreeElement(S);
		strcpy(S->country, country);
		S->List = NULL;
		S->List = ReadDatCities(S->List, country_dat);
	}
	else if (strcmp(S->country, country) > 0)
		S->L = InsertTree(S->L, country, country_dat);
	else if (strcmp(S->country, country) < 0)
		S->D = InsertTree(S->D, country, country_dat);

	return S;
}
ListPosition ReadDatCities(ListPosition p, char* dat)
{
	FILE* file = NULL;
	char city[max] = { 0 };
	int citizens = 0;

	p = CreateListElement(p);

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Can't open file!\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d", city, &citizens);
		CreateList(p, city, citizens);
	}

	fclose(file);
	return p;
}
int CreateList(ListPosition p, char* city, int citizens)
{
	ListPosition q = NULL;
	q = CreateListElement(q);

	strcpy(q->city, city);
	q->citizens = citizens;

	while (p->next != NULL)
	{
		if (q->citizens < p->next->citizens)
			break;
		else if (q->citizens == p->next->citizens)
		{
			if (strcmp(q->city, p->next->city) < 0)
				break;
			else if (strcmp(q->city, p->next->city) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;

}

int inorder(treePosition S)
{
	if (S == NULL)
		return 0;
	else
	{
		inorder(S->L);
		printf("\n%s:\n", S->country);
		PrintList(S->List);
		inorder(S->D);
	}
	return 0;
}

int PrintList(ListPosition p)
{
	if (p == NULL)
		return 0;
	else
	{
		p = p->next;
		while (p != NULL)
		{
			printf(" %s-%d ", p->city, p->citizens);
			p = p->next;
		}
		return 0;
	}
}

treePosition FindCountry(treePosition S, char* country)
{
	if (S == NULL)
		return NULL;
	else if (strcmp(country, S->country) == 0)
		return S;
	else if (strcmp(country, S->country) > 0)
		return FindCountry(S->D, country);

	return FindCountry(S->L, country);
}

int print(ListPosition p, int number)
{
	while (p != NULL)
	{
		if (number < p->citizens)
			printf(" %s-%d", p->city, p->citizens);
		p = p->next;
	}
	return 0;
}