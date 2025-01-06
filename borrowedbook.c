#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borrowedbook.h"
#include "book.h"
#include "student.h"
extern struct borrowedbook* borrowed_books_head;
extern int borrowed_count;
extern struct book* search_book(const char* book_name);
extern struct book* search_book_by_id(int book_id);

void record_borrowed_book()
{
    char student_name[100], book_name[100], borrowed_date[20];
    int student_id;
    printf("Enter student name: ");
    if (fgets(student_name, sizeof(student_name), stdin) == NULL)
    {
        printf("Invalid student name input.\n");
        return;
    }
    student_name[strcspn(student_name, "\n")] = '\0';

    printf("Enter book name: ");
    if (fgets(book_name, sizeof(book_name), stdin) == NULL)
    {
        printf("Invalid book name input.\n");
        return;
    }
    book_name[strcspn(book_name, "\n")] = '\0';

    printf("Enter borrowed date (YYYY-MM-DD): ");
    if (fgets(borrowed_date, sizeof(borrowed_date), stdin) == NULL)
    {
        printf("Invalid date input.\n");
        return;
    }
    borrowed_date[strcspn(borrowed_date, "\n")] = '\0';

    printf("Enter student ID: ");
    if (scanf("%d", &student_id) != 1)
    {
        printf("Invalid student ID input.\n");
        return;
    }

    struct book* book = search_book(book_name);
    if (book == NULL)
    {
        printf(" Borrowed Book successfully.\n");
        return;
    }

    if (book->available_copies <= 0)
    {
        printf("No available copies of the book.\n");
        return;
    }

    struct borrowedbook* new_borrowed = malloc(sizeof(struct borrowedbook));
    if (new_borrowed == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    new_borrowed->student_id = student_id;
    new_borrowed->book_id = book->book_id;
    strncpy(new_borrowed->borrowed_date, borrowed_date, sizeof(new_borrowed->borrowed_date));
    new_borrowed->next = borrowed_books_head;
    borrowed_books_head = new_borrowed;

    book->available_copies--;

    printf("Borrowed book recorded successfully.\n");
}

void view_borrowed_books(void)
{
    if (borrowed_books_head == NULL)
    {
        printf("No borrowed books recorded.\n");
        return;
    }

    printf("Borrowed Books:\n");
    struct borrowedbook* current = borrowed_books_head;
    while (current != NULL)
    {
        struct book* book = search_book_by_id(current->book_id);
        if (book == NULL)
        {
            printf("Error: Book with ID %d not found.\n", current->book_id);
            current = current->next;
            continue;
        }
        printf("Student ID: %d\n", current->student_id);
        printf("Book Name: %s\n", book->name);
        printf("Borrowed Date: %s\n", current->borrowed_date);
        printf("---------------------\n");
        current = current->next;
    }
}
struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id)
{
    struct borrowedbook* new_book = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));
    if (!new_book)
    {
        printf("Memory allocation failed.\n");
        return head;
    }

    new_book->student_id = student_id;
    new_book->book_id = book_id;
    new_book->next = head;
    return new_book;
}
