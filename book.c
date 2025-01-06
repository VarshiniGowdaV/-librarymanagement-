#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "filehanding.h"

#define BOOKS_FILE "books.txt"

struct book* head = NULL;

void add_book()
{
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    if (new_book == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    // Prompt user for book information
    printf("Enter Book ID: ");
    scanf("%d", &new_book->book_id);
    getchar();  // To clear the newline character left by scanf

    printf("Enter Book Name: ");
    fgets(new_book->name, sizeof(new_book->name), stdin);
    new_book->name[strcspn(new_book->name, "\n")] = '\0';  // Remove newline character

    printf("Enter Author Name: ");
    fgets(new_book->author, sizeof(new_book->author), stdin);
    new_book->author[strcspn(new_book->author, "\n")] = '\0';  // Remove newline character

    printf("Enter Total Copies: ");
    scanf("%d", &new_book->total_copies);

    new_book->available_copies = new_book->total_copies;
    new_book->next = head;
    head = new_book;  // Add the new book at the beginning of the list

    // Save all books to the file immediately after adding
    save_books_to_file(head);
    printf("Book added successfully.\n");
}


void update_book_record(int book_id, const char* new_name, const char* new_author, int total_copies, int available_copies)
{
    struct book* current = head;
    int book_found = 0;

    while (current)
    {
        if (current->book_id == book_id)
        {
            // Update book details in the linked list
            strncpy(current->name, new_name, sizeof(current->name) - 1);
            current->name[sizeof(current->name) - 1] = '\0';  // Ensures null termination

            strncpy(current->author, new_author, sizeof(current->author) - 1);
            current->author[sizeof(current->author) - 1] = '\0'; // Ensures null termination

            current->total_copies = total_copies;
            current->available_copies = available_copies;

            // Mark the book as found
            book_found = 1;
            break;
        }
        current = current->next;
    }

    if (book_found)
    {
        // Save the updated list to the file immediately after update
        save_books_to_file(head);

        // Provide feedback to the user
        printf("Book with ID %d updated successfully.\n", book_id);
    }
    else
    {
        // If the book was not found
        printf("Book with ID %d not found.\n", book_id);
    }
}


void remove_book(int book_id)
{
    struct book* current = head;
    struct book* prev = NULL;

    while (current != NULL && current->book_id != book_id)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    if (prev == NULL)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    free(current);
    save_books_to_file(head);
    printf("Book with ID %d removed successfully.\n", book_id);
}

void display_books()
{
    struct book* current = head;
    if (!current)
    {
        printf("No books available.\n");
        return;
    }

    while (current)
    {
        printf("ID: %d, Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               current->book_id, current->name, current->author, current->total_copies, current->available_copies);
        current = current->next;
    }
}

struct book* search_book(const char* book_name)
{
    struct book* current = head;
    while (current)
    {
        if (strcmp(current->name, book_name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct book* search_book_by_id(int book_id)
{
    struct book* current = head;
    while (current)
    {
        if (current->book_id == book_id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void save_books_to_file(struct book* head)
{
    FILE* file = fopen(BOOKS_FILE, "w");
    if (file == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    struct book* current = head;
    while (current)
    {
        long position = ftell(file);  // Get the current position in the file

        // Write the book's data to the file
        fprintf(file, "%d,%s,%s,%d,%d\n", current->book_id, current->name, current->author, current->total_copies, current->available_copies);

        fseek(file, position, SEEK_SET);

        current = current->next;
    }

    fclose(file);
}



void load_books_from_file()
{
    FILE* file = fopen(BOOKS_FILE, "r");
    if (file == NULL)
    {
        printf("No books file found. Starting fresh.\n");
        return;
    }

    struct book* new_book;
    long position;  // Variable to hold file position
    while (1)
    {
        position = ftell(file);  // Get the current file position before reading

        new_book = (struct book*)malloc(sizeof(struct book));
        if (new_book == NULL)
        {
            printf("Memory allocation failed while loading books.\n");
            break;
        }

        // Try reading a book record
        if (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n",
                   &new_book->book_id, new_book->name, new_book->author,
                   &new_book->total_copies, &new_book->available_copies) == 5)
        {
            // Insert the new book at the beginning of the list
            new_book->next = head;
            head = new_book;

            // Move the file pointer back to the position if needed (optional)
            fseek(file, position, SEEK_SET);  // Returning to the previous position
        }
        else
        {
            free(new_book);
            break;  // Break the loop when the file reading is done
        }
    }

    fclose(file);

    // Debugging: Print loaded books to check if they are properly loaded
    struct book* current = head;
    printf("Books loaded from file:\n");
    while (current)
    {
        printf("ID: %d, Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               current->book_id, current->name, current->author, current->total_copies, current->available_copies);
        current = current->next;
    }
}
