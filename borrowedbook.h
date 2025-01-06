#ifndef BORROWEDBOOK_H
#define BORROWEDBOOK_H

#include "book.h"
#include "student.h"

extern struct borrowedbook* borrowed_books_head;
extern int borrowed_count;

struct borrowedbook {
    int student_id;
    int book_id;
    char borrowed_date[20];
    struct borrowedbook* next;
};

void record_borrowed_book(void);
void view_borrowed_books(void);
struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id);
#endif


