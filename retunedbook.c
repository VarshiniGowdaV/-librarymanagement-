#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retunedbook.h"

// Initialize the head of the returned books list as NULL
struct returnedbook* returned_books_head = NULL;

// Function to create and add a new returned book record
struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id, const char* date) {
    // Allocate memory for a new returned book node
    struct returnedbook* new_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));

    if (new_book == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    // Initialize the fields of the new returned book
    new_book->returned_id = rand();  // You can replace rand() with your own unique ID generation logic
    new_book->student_id = student_id;
    new_book->book_id = book_id;
    strncpy(new_book->returned_date, date, MAX_DATE_LENGTH);
    new_book->next = NULL;

    // If the list is empty, new book becomes the head
    if (head == NULL) {
        head = new_book;
    } else {
        // Otherwise, traverse the list to find the last node and append the new book
        struct returnedbook* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_book;
    }

    return head;
}

// Function to record a returned book
void record_returned_book() {
    int student_id, book_id;
    char returned_date[MAX_DATE_LENGTH];

    // Input student_id, book_id, and returned_date from the user
    printf("Enter Student ID: ");
    scanf("%d", &student_id);
    printf("Enter Book ID: ");
    scanf("%d", &book_id);
    printf("Enter Returned Date (YYYY-MM-DD): ");
    scanf("%s", returned_date);

    // Add the returned book record to the list
    returned_books_head = add_returned_book(returned_books_head, student_id, book_id, returned_date);
    printf("Returned book recorded successfully.\n");
}

// Function to view all returned books (to print them)
void view_returned_books() {
    if (returned_books_head == NULL) {
        printf("No returned books to display.\n");
        return;
    }

    struct returnedbook* temp = returned_books_head;
    while (temp != NULL) {
        printf("Returned ID: %d, Student ID: %d, Book ID: %d, Returned Date: %s\n",
               temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }
}

// Function to print the list of all returned books
void print_returned_books() {
    if (returned_books_head == NULL) {
        printf("No returned books to display.\n");
        return;
    }

    struct returnedbook* temp = returned_books_head;
    while (temp != NULL) {
        printf("Returned ID: %d, Student ID: %d, Book ID: %d, Returned Date: %s\n",temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }
}
