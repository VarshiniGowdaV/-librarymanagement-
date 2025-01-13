#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "borrowedbook.h"
#include "book.h"
#include "student.h"
struct borrowedbook* borrowedbook_head = NULL;
void record_borrowed_book(void) {
    int student_id, book_id;
    char borrowed_date[20];

    // Ask user for student ID, book ID, and borrowed date
    printf("Enter student ID: ");
    scanf("%d", &student_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter borrowed date (DD-MM-YYYY): ");
    scanf("%s", borrowed_date);

    // Add the borrowed book to the list
    borrowedbook_head = add_borrowed_book(borrowedbook_head, student_id, book_id, borrowed_date);

    // Print a confirmation message
    printf("The book has been recorded as borrowed.\n");
}

// Function to view all borrowed books
void view_borrowed_books(void) {
    struct borrowedbook* current = borrowedbook_head;
    if (current == NULL) {
        printf("No borrowed books available.\n");
        return;
    }

    // Loop through the borrowed books list and print the details
    printf("Student ID | Book ID | Borrowed Date\n");
    while (current != NULL) {
        printf("%d | %d | %s\n", current->student_id, current->book_id, current->borrowed_date);
        current = current->next;
    }
}

struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id, const char* borrowed_date) {
    struct borrowedbook* new_book = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));

    new_book->student_id = student_id;
    new_book->book_id = book_id;
    strncpy(new_book->borrowed_date, borrowed_date, MAX_DATE_LENGTH);
    new_book->next = NULL;

    if (head == NULL) {
        return new_book;
    } else {
        struct borrowedbook* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_book;
    }

    // Save to file after adding a new borrowed book
    save_Book_To_File();
    return head;
}
