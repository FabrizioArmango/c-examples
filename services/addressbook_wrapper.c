#include "addressbook_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

person *addressbook;
int num_persons = 0;

int main(void)
{
    display_menu();
}

void display_menu()
{
    headerf();
    printf("\n< AddressBook >\nList of available commands");
    headerf();

    char commands[4][80] = {
        "Insert new contact.\n\tadd_new(<surname>, <name>, <phone>, <mobile_phone>)",
        "Print all the contacts.\n\tprint_all()",
        "Search a contact by surname and name.\n\tsearch(<surname>, <name>)",
        "Sort all contacts by surname and name.\n\tsort()"};

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        printf("\n  [#]\t %s \n", commands[i]);
        if (i != 8)
            header();
    }
    headerf();
    printf("\n");

    person *new_p = ab_add_new_person(&addressbook, &num_persons, "Armango", "Fabrizio", "0000000", "+39333333333");
}

void print_all()
{
    ab_print_addressbook(addressbook, num_persons);
}

void *add_new(person_surname surname, person_name name, person_phone phone, person_mobile_phone mobile_phone)
{
    person *p = ab_add_new_person(&addressbook, &num_persons, surname, name, phone, mobile_phone);
    printf("Successfully added:\n");
    ab_print_person(p);
}

void sort()
{
    ab_sort_by_surname_and_name(&addressbook, num_persons);
}

person *find_person_by_surname_and_name(person_surname surname, person_name name)
{
    person *found_p = ab_find_person_by_surname_and_name(addressbook, num_persons, surname, name);
    if (found_p == NULL)
    {
        printf("Person not found.\n");
        return NULL;
    }
    ab_print_person(found_p);
    return found_p;
}

bool update_surname(person_surname surname, person_name name, person_surname new_surname)
{
    person *p = ab_find_person_by_surname_and_name(addressbook, num_persons, surname, name);
    if (p == NULL)
        return false;

    strcpy(p->surname, new_surname);
    return true;
}
