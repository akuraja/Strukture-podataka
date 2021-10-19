#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_BRBOD 56

typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

student* alokacija(int brojStud, char* nazivDat) {
	int br = 0;
	FILE* fp = NULL;
	student* stud = NULL;

	stud = (student*)malloc(brojStud * sizeof(student));

	if (!stud) {
		printf("Neuspjesna alokacija memorije!\n");
		free(stud);
		return -1;
	}

	fp = fopen(nazivDat, "r");

	while (!feof(fp)) {
		fscanf(fp, "%s	%s	%lf\n", stud[br].ime, stud[br].prezime, &stud[br].bodovi);
		br++;
	}

	fclose(fp);

	return stud;
}

int ProcitajIzDatoteke(char* nazivDat) {
	int br = 0;
	FILE* fp = NULL;
	char niz[MAX_LINE] = { 0 };

	fp = fopen(nazivDat, "r");

	if (!fp) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		fgets(niz, MAX_LINE, fp);
		br++;
	}

	fclose(fp);

	return br;
}

int MaksBrojBodova(student* stud, int brojstudenata) {

	int maks = 0;
	int i;

	for (i = 1; i < brojstudenata; i++) {
		if (stud[maks].bodovi < stud[i].bodovi) {
			maks = i;
		}
	}
	return maks;
}

int IspisPodataka(student* stud, int brojstudenata) {

	int i;
	int maks = 0;

	maks = MaksBrojBodova(stud, brojstudenata);

	for (i = 0; i < brojstudenata; i++) {
		printf("%s %s %.2lf %.2lf\n", stud[i].ime, stud[i].prezime, stud[i].bodovi / MAX_BRBOD * 100, (stud[i].bodovi) / stud[maks].bodovi * 100);
	}

	return 1;
}


int main() {

	student* stud = NULL;
	char* studentskadatoteka = "nazivDat.txt";
	int brojstud = 0;

	brojstud = ProcitajIzDatoteke(studentskadatoteka);
	if (brojstud == -1)
		return 0;
	stud = alokacija(brojstud, studentskadatoteka);
	if (!stud)
		return 0;
	IspisPodataka(stud, brojstud);

	return 0;
}