#ifndef BORROWEDBOOK_H
#define BORROWEDBOOK_H
#include "book.h"
#include "student.h"
#define MAX_DATE_LENGTH 20
struct borrowedbook {
    int student_id;
    int book_id;
    char borrowed_date[20];
    struct borrowedbook* next;
};
extern struct borrowedbook* borrowedbook_head;
void record_borrowed_book(void);
void view_borrowed_books(void);
struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id, const char* borrowed_date);
#endif // BORROWEDBOOK_H
