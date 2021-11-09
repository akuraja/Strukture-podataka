#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position Head);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position Head, char* surname);
int DeleteAfter(Position Head, char* surname);

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

int main(int argc, char** argv)
{
	Person Head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position p = &Head;
	Position temp = NULL;

	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;

	int izbor = 1;

	while (izbor != 0)
	{
		PrintList(p->next);
		printf("\nUnos studenta na pocetak liste-1\n");
		printf("Unos studenta na kraj liste-2\n");
		printf("Pretrazivanje studenata po prezimenu-3\n");
		printf("Brisanje elementa iz liste-4\n");
		printf("Vas odabir: ");
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("Unesite ime i prezime studenta kojeg zelite dodati na pocetak liste:  ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodenja: ");
			scanf(" %d", &birthYear);
			PrependList(p, name, surname, birthYear);
			break;

		case 2:
			printf("Unesite ime i prezime studenta kojeg zelite dodati na kraj liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodenja: ");
			scanf(" %d", &birthYear);
			AppendList(p, name, surname, birthYear);
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
			break;

		default:
			printf("Vas izbor je nemoguc!\n");
			break;
		}

	}
	return EXIT_SUCCESS;
}