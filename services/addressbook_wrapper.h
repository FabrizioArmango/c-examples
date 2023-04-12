#include "addressbook.h"
#include <stdbool.h>
void *add_new(person_surname surname, person_name name, person_phone phone, person_mobile_phone mobile_phone);
void display_menu();
void print_all();
bool update_surname(person_surname surname, person_name name, person_surname new_surname);
void sort();