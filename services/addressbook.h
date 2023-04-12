typedef char address_street[30];
typedef char address_city[20];

typedef struct
{
    address_street street;
    address_city city;
    char zip[10];
} address;

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef char person_surname[30];
typedef char person_name[30];
typedef char person_phone[30];
typedef char person_mobile_phone[30];

typedef struct
{
    person_surname surname;
    person_name name;
    person_phone phone;
    person_mobile_phone mobile_phone;
    address address;
    date date;
} person;

person *ab_add_new_person(person **addressbook, int *num_persons, person_surname surname, person_name name, person_phone phone, person_mobile_phone mobile_phone);
person *ab_find_person_by_surname_and_name(person *addressbook, int num_persons, person_surname surname, person_name name);
void ab_print_person(person *who);
void ab_sort_by_surname_and_name(person **addressbook, int size);
void ab_print_addressbook(person *addressbook, int size);

void headerf();
void header();