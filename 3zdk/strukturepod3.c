#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define MAX_LINE 1024

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

typedef struct _Sorted {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} _Sort;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position Head);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position Head, char* surname);
int DeleteAfter(Position Head, char* surname);
int DodajIza(Position Head, char* lastname, char* name, char* surname, int bYear);
int DodajIspred(Position Head, char* sur, char* name, char* surname, int bYear);
int InsertBefore(Position position, Position person, char* sur);
int UpisUDat(Position first, char* nazivDat);
int CitajIzDat(char* nazivDat);
int InsertSort(Position head, char* name, char* surname, int bYear);
Position FindPrevious(Position head, Position el);
int IspisDatoteke(char* imeDat);


int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("Name: %s, surname: %s, birthyear: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position Head)
{
	Position temp = Head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;
}

Position FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

Position FindBefore(Position Head, char* surname) {

	for (Position temp = Head; temp->next; temp = temp->next) {
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;
}

int DeleteAfter(Position Head, char* surname) {

	Position before = NULL;
	Position to_delete = NULL;

	before = FindBefore(Head, surname);
	if (before == NULL) {
		printf("Osoba se ne nalazi na listi\n");
	}
	else {
		to_delete = before->next;
		before->next = to_delete->next;
		free(to_delete);
	}
	return EXIT_SUCCESS;
}


Position FindPrevious(Position head, Position el)
{
	Position temp = head;

	while (temp->next != el)
		temp = temp->next;

	return temp;

}

int DodajIza(Position Head, char* sur, char* name, char* surname, int bYear)
{
	Position newP = NULL;
	Position position = NULL;

	newP = CreatePerson(name, surname, bYear);
	if (!newP)
		return 1;


	if (FindBySurname(Head->next, sur) != NULL)
		position = FindBySurname(Head->next, sur);
	else
		return 1;


	InsertAfter(position, newP);

	return NULL;
}

int DodajIspred(Position Head, char* sur, char* name, char* surname, int bYear) {
	Position newPer = NULL;
	Position position = NULL;


	newPer = CreatePerson(name, surname, bYear);
	if (!newPer)
		return 1;


	if (FindBefore(Head, sur) != NULL)
		position = FindBefore(Head, sur);
	else
		return 1;



	InsertAfter(position, newPer);

	return NULL;
}

int InsertBefore(Position position, Position person, char* sur)
{
	person->next = position->next;
	position->next = person;

	return EXIT_SUCCESS;
}

int UpisUDat(Position first, char* nazivDat)
{
	FILE* fp = NULL;
	fp = fopen(nazivDat, "w");
	Position temp = first;
	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}

	while (temp)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int CitajIzDat(char* nazivDat)
{
	FILE* fp = NULL;
	char niz[MAX_SIZE] = { 0 };
	int br = 0;
	fp = fopen(nazivDat, "r");
	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}

	while (!(feof(fp)))
	{
		fgets(niz, MAX_LINE, fp);
		br++;
	}
	fclose(fp);

	return br;

}


Position PronadiPrethodnog(Position first, char* surname){
	Position temp = first;

	for (temp; temp->next; temp = temp->next) {
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;
}

int InsertSort(Position head, char* name, char* surname, int bYear)
{
	Position person = NULL;

	person = CreatePerson(name, surname, bYear);
	if (!person)
		return 1;
	Position before = NULL;
	Position temp = head->next;

	if (!temp)
	{
		InsertAfter(head, person);
	}
	else
	{
		while (temp && strcmp(surname, temp->surname))
			temp = temp->next;

		before = FindPrevious(head, temp);
		InsertAfter(before, person);
	}

	return EXIT_SUCCESS;
}

int IspisDatoteke(char* imeDat)
{
	FILE* fp = NULL;
	char buffer;
	fp = fopen(imeDat, "r");
	if (!fp)
		return 1;

	while (!feof(fp))
	{
		buffer = fgetc(fp);
		printf("%c", buffer);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int main(int argc, char** argv){

	Person Head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	_Sort head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position p = &Head;
	Position s = &head;
	Position temp = NULL;

	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	char sur[MAX_SIZE] = {0};
	int birthYear=0;
	int br;
	char* file = "lista.txt";

	int izbor = 1;

	while (izbor != 0)
	{
		PrintList(p->next);
		printf("\nUnos studenta na pocetak liste-1\n");
		printf("Unos studenta na kraj liste-2\n");
		printf("Pretrazivanje studenata po prezimenu-3\n");
		printf("Brisanje elementa iz liste-4\n");
		printf("Dodaj element iza odredenog elementa-5\n");
		printf("Dodaj element ispred odredenog elementa-6\n");
		printf("Upis liste u datoteku-7\n");
		printf("Ispis liste iz datoteke-8\n");
		printf("Ispis sortirane liste-9\n");

		printf("Vas odabir: ");
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("Unesite ime i prezime studenta kojeg zelite dodati na pocetak liste:  ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodenja: ");
			scanf(" %d", &birthYear);
			if ((PrependList(p, name, surname, birthYear))==1)
					printf("Neuspjesno dodavanje\n");
			InsertSort(s, name, surname, birthYear);
			break;

		case 2:
			printf("Unesite ime i prezime studenta kojeg zelite dodati na kraj liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodenja: ");
			scanf(" %d", &birthYear);
			if (AppendList(p, name, surname, birthYear) == 1)
				printf("Neuspjesno dodavanje\n");
			InsertSort(s, name, surname, birthYear);
			break;

		case 3:
			printf("Unesite prezime studenta kojeg zelite pronaci: ");
			scanf(" %s", surname);
			temp = FindBySurname(p, surname);
			if (temp) {
				printf("Ime i prezime: %s %s\nGodina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
			}
			else {
				printf("Osoba se ne nalazi na listi.\n");
			}
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati: ");
			scanf(" %s", surname);
			DeleteAfter(p, surname);
			DeleteAfter(s, surname);
			break;

		case 5:
			printf("\nUnesite prezime osobe iza koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &birthYear);
			if (DodajIza(p, sur, name, surname, birthYear) == 1)
				printf("Neuspješno dodavanje elementa!\n");
			InsertSort(s, name, surname, birthYear);
			break;

		case 6:
			printf("\nUnesite prezime osobe ispred koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &birthYear);
			if (DodajIspred(p, sur, name, surname, birthYear) == 1)
				printf("Neuspješno dodavanje elementa!\n");
			InsertSort(s, name, surname, birthYear);
			break;

		case 7:
			UpisUDat(p->next, "lista.txt");
			break;

		case 8:
			br = CitajIzDat("lista.txt");
			IspisDatoteke("lista.txt");

			break;

		case 9:
			printf("Ispis sortirane liste: \n");
			PrintList(s->next);
			break;

		default:
			printf("Vas izbor je nemoguc!\n");
			break;
		}

	}
	return EXIT_SUCCESS;
}