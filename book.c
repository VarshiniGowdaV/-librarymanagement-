#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "filehanding.h"

#define BOOKS_FILE "books_data.txt"

struct book* head = NULL;

void add_book() {
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    if (new_book == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Book ID: ");
    if (scanf("%d", &new_book->book_id) != 1) {
        printf("Invalid input for Book ID.\n");
        free(new_book);
        return;
    }
    getchar();

    printf("Enter Book Name: ");
    if (fgets(new_book->name, sizeof(new_book->name), stdin) == NULL) {
        printf("Failed to read Book Name.\n");
        free(new_book);
        return;
    }
    new_book->name[strcspn(new_book->name, "\n")] = '\0';

    printf("Enter Author Name: ");
    if (fgets(new_book->author, sizeof(new_book->author), stdin) == NULL) {
        printf("Failed to read Author Name.\n");
        free(new_book);
        return;
    }
    new_book->author[strcspn(new_book->author, "\n")] = '\0';

    printf("Enter Total Copies: ");
    if (scanf("%d", &new_book->total_copies) != 1 || new_book->total_copies < 0) {
        printf("Invalid input for Total Copies.\n");
        free(new_book);
        return;
    }

    new_book->available_copies = new_book->total_copies;
    new_book->next = NULL;

    if (head == NULL) {
        head = new_book;
    } else {
        struct book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_book;
    }
    save_books_to_file(head);

    printf("Book added and saved to file successfully.\n");
}

void update_specific_field(struct book* head, int book_id, const char* field, const void* value) {
    struct book* book_to_update = search_book_by_id(book_id);

    if (book_to_update == NULL) {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    if (strcmp(field, "name") == 0) {
        strncpy(book_to_update->name, (char*)value, sizeof(book_to_update->name) - 1);
        book_to_update->name[sizeof(book_to_update->name) - 1] = '\0';
    } else if (strcmp(field, "author") == 0) {
        strncpy(book_to_update->author, (char*)value, sizeof(book_to_update->author) - 1);
        book_to_update->author[sizeof(book_to_update->author) - 1] = '\0';
    } else if (strcmp(field, "total_copies") == 0) {
        book_to_update->total_copies = *(int*)value;
        if (book_to_update->available_copies > book_to_update->total_copies) {
            book_to_update->available_copies = book_to_update->total_copies;
        }
    } else if (strcmp(field, "available_copies") == 0) {
        book_to_update->available_copies = *(int*)value;
        if (book_to_update->available_copies > book_to_update->total_copies) {
            printf("Available copies cannot exceed total copies. Adjusting available copies.\n");
            book_to_update->available_copies = book_to_update->total_copies;
        }
    } else {
        printf("Invalid field name: %s\n", field);
        return;
    }

    printf("Book with ID %d updated successfully in memory.\n", book_id);

    // Save updated data to the file
    save_books_to_file(head);
    printf("Book with ID %d updated successfully in file.\n", book_id);
}
void update_book_record(int book_id, const char* new_name, const char* new_author, int total_copies, int available_copies) {
    struct book* book_to_update = search_book_by_id(book_id);

    if (book_to_update == NULL) {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    if (new_name) {
        strncpy(book_to_update->name, new_name, sizeof(book_to_update->name) - 1);
        book_to_update->name[sizeof(book_to_update->name) - 1] = '\0';
    }

    if (new_author) {
        strncpy(book_to_update->author, new_author, sizeof(book_to_update->author) - 1);
        book_to_update->author[sizeof(book_to_update->author) - 1] = '\0';
    }

    book_to_update->total_copies = total_copies;

    if (available_copies > total_copies) {
        printf("Available copies cannot exceed total copies. Adjusting to total copies.\n");
        book_to_update->available_copies = total_copies;
    } else {
        book_to_update->available_copies = available_copies;
    }

    printf("Book with ID %d updated successfully.\n", book_id);
    save_books_to_file(head);
}

void remove_book(int book_id) {
    struct book* current = head;
    struct book* prev = NULL;

    while (current != NULL && current->book_id != book_id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    save_books_to_file(head);
    printf("Book with ID %d removed successfully.\n", book_id);
}

void display_books() {
    struct book* current = head;
    if (!current) {
        printf("No books available.\n");
        return;
    }

    while (current) {
        printf("ID: %d, Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               current->book_id, current->name, current->author, current->total_copies, current->available_copies);
        current = current->next;
    }
}

struct book* search_book(const char* book_name) {
    struct book* current = head;
    while (current) {
        if (strcmp(current->name, book_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct book* search_book_by_id(int book_id) {
    struct book* current = head;
    while (current) {
        if (current->book_id == book_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct book* load_books_from_file() {
    FILE* file = fopen(BOOKS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file for reading books.\n");
        return NULL;
    }

    struct book* head = NULL;
    struct book* temp = NULL;
    int book_id, total_copies, available_copies;
    char name[100], author[100];

    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d|%d\n", &book_id, name, author, &total_copies, &available_copies) == 5) {
        struct book* new_book = malloc(sizeof(struct book));
        new_book->book_id = book_id;
        strncpy(new_book->name, name, sizeof(new_book->name) - 1);
        new_book->name[sizeof(new_book->name) - 1] = '\0';
        strncpy(new_book->author, author, sizeof(new_book->author) - 1);
        new_book->author[sizeof(new_book->author) - 1] = '\0';
        new_book->total_copies = total_copies;
        new_book->available_copies = available_copies;
        new_book->next = NULL;

        if (head == NULL) {
            head = new_book;
        } else {
            temp->next = new_book;
        }
        temp = new_book;
    }

    fclose(file);
    return head;
}

void save_books_to_file(struct book* head) {
    FILE* file = fopen(BOOKS_FILE, "r+");
    if (file == NULL) {
        printf("Error opening file for saving books.\n");
        return;
    }

    struct book* current = head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                current->book_id, current->name, current->author,
                current->total_copies, current->available_copies);
        current = current->next;
    }

    fclose(file);
}
