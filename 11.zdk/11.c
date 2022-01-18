#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define max (80)
#define hashSize 11

struct _tree;
typedef struct _tree* treeposition;
typedef struct _tree{
	char city[max];
	int population;
	treeposition L;
	treeposition D;
}tree;

struct _list;
typedef struct _list* listPosition;
typedef struct _list{
	char country[max];
	treeposition tree;
	listPosition next;
}list;

struct _table;
typedef struct _table* hashTab;
typedef struct _table
{
	listPosition* hashLists;
}table;

int ReadDatCountries(hashTab H, char* dat);
int InsertSorted(listPosition p, char* country_ime, char* country_dat);
treeposition createtree(treeposition root, char* city, int population);
int print(listPosition p);
int inorder(treeposition S);
int InOrderPrintBiggerThan(treeposition p, int number);
listPosition CreateListElement(listPosition p);
listPosition CreateListElementAllocation();
listPosition FindCountry(hashTab H, char* country);
treeposition ReadDatCities(treeposition root, char* country_dat);

hashTab InitializeHashTab();
int AddToTable(char* country, char* country_dat, hashTab H);
int HashFun(char* country);


int main()
{
	listPosition  p = NULL;
	hashTab HashTab = NULL;
	char dat[max] = "drzave.txt", c = { 0 }, country[max] = { 0 };
	int x = 1, number = 0;

	HashTab = InitializeHashTab();
	p = CreateListElement(p);

	ReadDatCountries(HashTab, dat);

	printf("\n1)Choose country\n2)Exit\n");
	while (x)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Choose country:");
			scanf(" %s", country);
			p = FindCountry(HashTab, country);
			if (p == NULL)
			{
				printf("Choosen country is not in file!.");
				return EXIT_FAILURE;
			}
			printf("\nCities with more citizens than you entered will be shown. Enter number: ");
			scanf("%d", &number);
			InOrderPrintBiggerThan(p->tree, number);
			break;
		case '2':
			printf("Exit.\n");
			x = 0;
			break;
		}
	}
	return 0;
}

hashTab InitializeHashTab()
{
	hashTab H = NULL;
	int i = 0;

	H = (hashTab)malloc(sizeof(table));
	if (H == NULL)
	{
		printf("Initialization error.\n");
		return NULL;
	}

	H->hashLists = (listPosition*)malloc(sizeof(listPosition) * hashSize);
	if (H->hashLists == NULL)
	{
		printf("Initialization error.\n");
		return NULL;
	}

	for (i = 0;i < hashSize;i++)
		H->hashLists[i] = CreateListElementAllocation();

	return H;
}

int AddToTable(char* country, char* country_dat, hashTab H)
{
	int index = 0;
	index = HashFun(country);

	InsertSorted(H->hashLists[index], country, country_dat);

	return 0;
}

int HashFun(char* country)
{
	int lenght = 0, remainder = 0, sum = 0, i = 0;
	lenght = strlen(country);

	for (i = 0; i < lenght || i < 5; i++)
		sum += country[i];

	remainder = sum % hashSize;

	return remainder;
}

listPosition CreateListElement(listPosition p)
{
	p = (listPosition)malloc(sizeof(list));
	if (p == NULL)
	{
		printf("Cant't allocate head element's memory!\n");
		return -3;
	}
	strcpy(p->country, "");
	p->next = NULL;
	p->tree = NULL;

	return p;
}

listPosition CreateListElementAllocation()
{
	listPosition p = NULL;
	p = (listPosition)malloc(sizeof(list));
	if (p == NULL)
	{
		printf("Cant't allocate memory!\n");
		return NULL;
	}
	strcpy(p->country, "");
	p->next = NULL;
	p->tree = NULL;

	return p;
}

int ReadDatCountries(hashTab H, char* dat)
{
	FILE* file = NULL;
	char country_ime[max] = { 0 }, country_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Can't open file!");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", country_ime, country_dat);
		AddToTable(country_ime, country_dat, H);
	}

	fclose(file);
	return 0;
}

int InsertSorted(listPosition p, char* country_ime, char* country_dat)
{
	listPosition q = NULL;
	char pom[max] = { 0 };

	q = (listPosition)malloc(sizeof(list));
	if (q == NULL)
	{
		printf("Can't allocate memory!");
		return -2;
	}

	strcpy(q->country, country_ime);
	q->tree = NULL;
	q->tree = ReadDatCities(q->tree, country_dat);
	strcpy(pom, country_ime);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(pom, p->next->country) < 0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}
	return 0;
}
treeposition ReadDatCities(treeposition root, char* country_dat)
{
	FILE* file = NULL;
	char city[max] = { 0 };
	int population = 0;

	file = fopen(country_dat, "r");
	if (file == NULL)
	{
		printf("Can't open file!\n.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", city, &population);
		root = createtree(root, city, population);
	}
	fclose(file);
	return root;
}
treeposition createtree(treeposition S, char* city, int population)
{
	if (S == NULL)
	{
		S = (treeposition)malloc(sizeof(tree));
		if (S == NULL)
		{
			printf("Can't allocate memory!");
			return NULL;
		}
		strcpy(S->city, city);
		S->population = population;
		S->L = NULL;
		S->D = NULL;
	}
	else if (population == S->population)
	{
		if (strcmp(city, S->city) < 0)
			S->L = createtree(S->L, city, population);
		else if (strcmp(city, S->city) > 0)
			S->D = createtree(S->D, city, population);
	}
	else
	{
		if (population < S->population)
			S->L = createtree(S->L, city, population);
		else if (population > S->population)
			S->D = createtree(S->D, city, population);
	}
	return S;
}
int print(listPosition p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->country);
		inorder(p->tree);
		p = p->next;
	}
}
int inorder(treeposition S)
{
	if (S == NULL)
		return 0;

	inorder(S->L);
	printf(" %s-%d ", S->city, S->population);
	inorder(S->D);

	return 0;
}
listPosition FindCountry(hashTab H, char* country)
{
	int index = 0;
	index = HashFun(country);
	listPosition p = H->hashLists[index];

	while (p->next != NULL)
	{
		if (strcmp(country, p->next->country) == 0)
			return p->next;
		else
			p = p->next;
	}
	return NULL;
}
int InOrderPrintBiggerThan(treeposition p, int number)
{
	if (p == NULL)
		return 0;

	InOrderPrintBiggerThan(p->L, number);

	if (number < p->population)
		printf("%s %d\n", p->city, p->population);

	InOrderPrintBiggerThan(p->D, number);

	return 0;
}