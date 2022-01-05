#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (120)

struct _tree;
typedef struct _tree* treeposition;
typedef struct _tree
{
	char city[max];
	int citizens;
	treeposition L;
	treeposition D;

}tree;

struct _list;
typedef struct _list* listposition;
typedef struct _list
{
	char country[max];

	treeposition tree;
	listposition next;

}list;


int ReadDatCountries(listposition p, char* dat);
int InsertSorted(listposition p, char* country_name, char* country_dat);
treeposition createtree(treeposition root, char* city, int citizens);
int print(listposition p);
int inorder(treeposition S);
int InOrderPrintBiggerThan(treeposition p, int number);
listposition CreateElement(listposition p);
listposition FindCountry(listposition p, char* country);
treeposition ReadDatCities(treeposition root, char* country_dat);


int main()
{
	listposition head = NULL, p = NULL;
	char dat[max] = "drzave.txt", c = { 0 }, country[max] = { 0 };
	int number = 0;
	int z = 1;

	head = CreateElement(head);
	p = CreateElement(p);

	ReadDatCountries(head, dat);
	print(head->next);

	printf("\n1) Choose country! \n2) Exit\n");
	while (z)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Choose country : ");
			scanf(" %s", country);
			p = FindCountry(head, country);
			if (p == NULL)
			{
				printf("Choosen country is not in file!\n");
				return EXIT_FAILURE;
			}
			printf("\nCities with more citizens than you entered will be shown. Enter number: \n");
			scanf("%d", &number);
			InOrderPrintBiggerThan(p->tree, number);
			break;
		case '2':
			printf("Exit.\n");
			z = 0;
			break;
		}
	}
	return 0;
}

listposition CreateElement(listposition p)
{
	p = (listposition)malloc(sizeof(list));
	if (p == NULL)
	{
		printf("Can't allocate memory!");
		return -3;
	}
	strcpy(p->country, "");
	p->next = NULL;
	p->tree = NULL;
}

int ReadDatCountries(listposition p, char* dat)
{
	FILE* file = NULL;
	char country_name[max] = { 0 }, country_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Can't open file!");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", country_name, country_dat);
		InsertSorted(p, country_name, country_dat);
	}

	fclose(file);
	return 0;
}
int InsertSorted(listposition p, char* country_name, char* country_dat)
{
	listposition q = NULL;
	char pom[max] = { 0 };

	q = (listposition)malloc(sizeof(list));
	if (q == NULL)
	{
		printf("Can't allocate memory!");
		return -2;
	}


	strcpy(q->country, country_name);
	q->tree = NULL;
	q->tree = ReadDatCities(q->tree, country_dat);
	strcpy(pom, country_name);

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
	int citizens = 0;

	file = fopen(country_dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", city, &citizens);
		root = createtree(root, city, citizens);
	}
	fclose(file);
	return root;
}
treeposition createtree(treeposition S, char* city, int citizens)
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
		S->citizens = citizens;
		S->L = NULL;
		S->D = NULL;
	}
	else if (citizens == S->citizens)
	{
		if (strcmp(city, S->city) < 0)
			S->L = createtree(S->L, city, citizens);
		else if (strcmp(city, S->city) > 0)
			S->D = createtree(S->D, city, citizens);
	}
	else
	{
		if (citizens < S->citizens)
			S->L = createtree(S->L, city, citizens);
		else if (citizens > S->citizens)
			S->D = createtree(S->D, city, citizens);
	}
	return S;
}
int print(listposition p)
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
	printf(" %s-%d ", S->city, S->citizens);
	inorder(S->D);

	return 0;
}
listposition FindCountry(listposition p, char* country)
{
	while (p->next != NULL && strcmp(country, p->country) != 0)
		p = p->next;

	return p;
}
int InOrderPrintBiggerThan(treeposition p, int number)
{
	if (p == NULL)
		return 0;

	InOrderPrintBiggerThan(p->L, number);

	if (number < p->citizens)
		printf("%s %d\n", p->city, p->citizens);

	InOrderPrintBiggerThan(p->D, number);

	return 0;
}