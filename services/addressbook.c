// #########################################
//                                         #
//                Rubrica                  #
//                                  v0.45  #
// #########################################
// #########################################
//  02/05/15
//  Fabrizio Armango
// ###################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"

void headerf()
{
    int i = 0;
    printf("\n");
    for (i = 0; i < 80; i++)
        printf("-");
}
void header()
{
    int i = 0;
    for (i = 0; i < 40; i++)
        printf("- ");
}

person *ab_find_person_by_surname_and_name(
    person *addressbook,
    int num_persons,
    person_surname surname,
    person_name name)
{
    for (int i = 0; i < num_persons; i++)
    {
        if (strcmp(addressbook[i].surname, surname) == 0 && strcmp(addressbook[i].name, name) == 0)
            return &addressbook[i];
    }
    return NULL;
}

void ab_print_person(person *p)
{
    printf("Surname: %s\n", p->surname);
    printf("Name: %s\n", p->name);
    printf("Date of birth: %d/%d/%d \n", p->date.day, p->date.month, p->date.year);
    printf("Street: %s\n", p->address.street);
    printf("City: %s\n", p->address.city);
    printf("ZIP: %s\n", p->address.zip);
    printf("Phone: %s\n", p->phone);
    printf("Mobile Phone: %s\n", p->mobile_phone);
    printf("\n");
}

void ab_sort_by_surname_and_name(person **addressbook, int size)
{
    person t;
    int i = 0;
    int j = 0;

    for (i = 1; i < size; i++)
        for (j = 1; j < size; j++)
        {
            int surname_cmp = strcmp((*addressbook)[j - 1].surname, (*addressbook)[j].surname);
            if (surname_cmp < 0)
                continue;
            int name_cmp = strcmp((*addressbook)[j - 1].name, (*addressbook)[j].name) > 0;
            if (surname_cmp > 0 || name_cmp > 0)
            {
                t = (*addressbook)[j - 1];
                (*addressbook)[j - 1] = (*addressbook)[j];
                (*addressbook)[j] = t;
            }
        }
}

void ab_print_addressbook(person *addressbook, int size)
{
    for (int i = 0; i < size; i++)
        ab_print_person(&addressbook[i]);
}

person *ab_add_new_person(
    person **addressbook,
    int *num_persons,
    person_surname surname,
    person_name name,
    person_phone phone,
    person_mobile_phone mobile_phone)
{
    int new_person_idx = *num_persons;
    int new_num_persons = *num_persons + 1;
    *addressbook = (person *)realloc(*addressbook, sizeof(person) * (new_num_persons));
    strcpy((*addressbook)[new_person_idx].surname, surname);
    strcpy((*addressbook)[new_person_idx].name, name);
    strcpy((*addressbook)[new_person_idx].phone, phone);
    strcpy((*addressbook)[new_person_idx].mobile_phone, mobile_phone);
    *num_persons = new_num_persons;
    return &(*addressbook)[new_person_idx];
}