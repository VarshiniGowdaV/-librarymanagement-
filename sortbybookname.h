#ifndef SORTBYBOOKNAME_H
#define SORTBYBOOKNAME_H

#define MAX_BOOK_NAME_LENGTH 100

// Structure for the book name list
struct sortbybookname {
    char book_name[MAX_BOOK_NAME_LENGTH];
    struct sortbybookname* next;
};

// Function prototypes
struct sortbybookname* create_book_node(const char* book_name);
struct sortbybookname* add_book_name(struct sortbybookname* head, const char* book_name);
void add_book_name_sorting(struct sortbybookname *book_name_head, int sort_order);
void view_books_by_name(struct sortbybookname* head);
void sort_books_by_name(struct sortbybookname* head);
#endif // SORTBYBOOKNAME_H
