#ifndef RETURNEDBOOK_H
#define RETURNEDBOOK_H

#define MAX_DATE_LENGTH 11  // For date format YYYY-MM-DD

// Structure definition for returned book
struct returnedbook {
    int returned_id;
    int student_id;
    int book_id;
    char returned_date[MAX_DATE_LENGTH];
    struct returnedbook* next;
};

// Declare the global head for the returned books list (extern ensures this is only declared, not defined here)
extern struct returnedbook* returned_books_head;

// Function declarations
struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id, const char* date);
void record_returned_book();
void view_returned_books();
void print_returned_books();

#endif  // RETURNEDBOOK_H
