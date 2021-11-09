#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
typedef struct _polinom {
    int koeficijent, eksponent;
    struct _polinom* next;
}polinom;

int citajIzDatoteke(polinom* head1, polinom* head2, char* imedatoteke); //
int umetniSortirano(polinom* sum_head, int koeficijent, int eksponent); //
int procitajRedak(polinom* head, char* buffer); //
int zbrojiPol(polinom* head1, polinom* head2, polinom* sum_head); //
int pomnoziPol(polinom* head1, polinom* head2, polinom* produkt_head);
int freenullelements(polinom* head); //
int ispis(polinom* head); //

int main() {
    polinom * head1 = (polinom*)malloc(sizeof(polinom));
    polinom* head2 = (polinom*)malloc(sizeof(polinom));
    polinom* sum_head = (polinom*)malloc(sizeof(polinom));
    polinom* produkt_head = (polinom*)malloc(sizeof(polinom));

    if (!head1 || !head2 || !sum_head || !produkt_head)
        return -1;

    head1->next = NULL;
    head2->next = NULL;
    sum_head->next = NULL;
    produkt_head->next = NULL;
    char* imedatoteke = "polinomi.txt";

    citajIzDatoteke(head1, head2, imedatoteke);

    printf("\nPrvi polinom je: \n\t");
    ispis(head1);
    printf("\nDrugi polinom je: \n\t");
    ispis(head2);

    zbrojiPol(head1, head2, sum_head);
    printf("\nZbroj polinoma je: \n\t");
    ispis(sum_head);
    pomnoziPol(head1, head2, produkt_head);
    printf("\nUmnozak polinoma je: \n\t");
    ispis(produkt_head);

    return EXIT_SUCCESS;
}

int citajIzDatoteke(polinom* head1, polinom* head2, char* imedatoteke) {

    FILE* fp = NULL;
    char buffer[MAX_LINE] = "";
    fp = fopen(imedatoteke, "r");

    fgets(buffer, MAX_LINE, fp);
    procitajRedak(head1, buffer);
    fgets(buffer, MAX_LINE, fp);
    procitajRedak(head2, buffer);

    fclose(fp);
    return 0;
}

int procitajRedak(polinom* head, char* buffer) {

    buffer[strlen(buffer)] = 0;
    int koeficijent = 0;
    int eksponent = 0;
    char* pbuff = buffer;

    do {
        int br = 0;

        sscanf(pbuff, " %d %d %n", &koeficijent, &eksponent, &br);
        pbuff += br;

        umetniSortirano(head, koeficijent, eksponent);
    } while (strlen(pbuff) > 1);

    return 0;
}

int umetniSortirano(polinom* sum_head, int koeficijent, int eksponent) {

    polinom* p = sum_head;

    while (p->next != NULL && p->next->eksponent > eksponent)
        p = p->next;

    if (p->next != NULL && p->next->eksponent == eksponent) {
        p->next->koeficijent += koeficijent;
    }
    else {
        polinom* newelement = (polinom*)malloc(sizeof(polinom));

        if (!newelement)
            return -1;

        newelement->next = p->next;
        p->next = newelement;

        newelement->koeficijent = koeficijent;
        newelement->eksponent = eksponent;
    }

    return 0;
}

int zbrojiPol(polinom* head1, polinom* head2, polinom* sum_head)
{
    polinom* p1 = head1->next;
    polinom* p2 = head2->next;

    while (p1 != NULL) {
        umetniSortirano(sum_head, p1->koeficijent, p1->eksponent);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        umetniSortirano(sum_head, p2->koeficijent, p2->eksponent);
        p2 = p2->next;
    }

    freenullelements(sum_head);

    return 0;
}

int pomnoziPol(polinom* head1, polinom* head2, polinom* produkt_head) {

    polinom* p1 = head1->next;
    polinom* p2 = head2->next;

    while (p1 != NULL) {
        p2 = head2->next;
        while (p2 != NULL) {
            umetniSortirano(produkt_head, p1->koeficijent * p2->koeficijent, p1->eksponent + p2->eksponent);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    freenullelements(produkt_head);

    return 0;
}

int freenullelements(polinom* head) {

    polinom* p = head;
    polinom* temp;

    while (p->next != NULL) {
        if (!p->next->koeficijent) {
            temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        p = p->next;
    }

    return 0;

}

int ispis(polinom* head)
{
    polinom* p = head->next;

    while (p != NULL) {
        printf("%dx^%d", p->koeficijent, p->eksponent);
        if (p->next != NULL)
            printf(" + ");
        p = p->next;
    }

    return 0;
}