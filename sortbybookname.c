#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbybookname.h"

#define MAX_BOOK_NAME_LENGTH 100

void swap_books(struct sortbybookname *a, struct sortbybookname *b)
{
    char temp[MAX_BOOK_NAME_LENGTH];
    strncpy(temp, a->book_name, MAX_BOOK_NAME_LENGTH);
    strncpy(a->book_name, b->book_name, MAX_BOOK_NAME_LENGTH);
    strncpy(b->book_name, temp, MAX_BOOK_NAME_LENGTH);
}
struct sortbybookname* create_book_node(const char* book_name)
{
    struct sortbybookname* new_node = (struct sortbybookname*)malloc(sizeof(struct sortbybookname));
    if (new_node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(new_node->book_name, book_name, MAX_BOOK_NAME_LENGTH);
    new_node->book_name[MAX_BOOK_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;

    return new_node;
}

struct sortbybookname* add_book_name(struct sortbybookname* head, const char* book_name)
{
    // Create a new node with the given book name
    struct sortbybookname* new_node = create_book_node(book_name);

    // If the list is empty, return the new node as the head
    if (head == NULL)
    {
        return new_node;
    }

    // If the new book's name should be the first in the list
    if (strcmp(book_name, head->book_name) < 0)
    {
        new_node->next = head;
        return new_node;
    }

    // Traverse the list to find the insertion point
    struct sortbybookname* temp = head;
    while (temp->next != NULL && strcmp(book_name, temp->next->book_name) > 0)
    {
        temp = temp->next;
    }

    // Insert the new node at the correct position
    new_node->next = temp->next;
    temp->next = new_node;

    return head;
}


void add_book_name_sorting(struct sortbybookname *book_name_head, int sort_order)
{
    if (book_name_head == NULL)
    {
        return;
    }

    struct sortbybookname *current, *next_node;
    int swapped;

    do {
        swapped = 0;
        current = book_name_head;
        while (current != NULL && current->next != NULL)
        {
            next_node = current->next;
            if ((sort_order == 1 && strcmp(current->book_name, next_node->book_name) > 0) || (sort_order == 0 && strcmp(current->book_name, next_node->book_name) < 0))
            {
                swap_books(current, next_node);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}
void view_books_by_name(struct sortbybookname* head)
{
    if (head == NULL)
    {
        printf("No books available.\n");
        return;
    }

    printf("Books List:\n");
    struct sortbybookname* current = head;
    while (current != NULL)
    {
        printf("%s\n", current->book_name);
        current = current->next;
        printf("---------------\n");
    }
}

void sort_books_by_name(struct sortbybookname* head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int swapped;
    struct sortbybookname *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        // Loop through the list to compare and swap adjacent nodes
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->book_name, ptr1->next->book_name) > 0)
            {
                char temp[MAX_BOOK_NAME_LENGTH];
                strncpy(temp, ptr1->book_name, MAX_BOOK_NAME_LENGTH);
                strncpy(ptr1->book_name, ptr1->next->book_name, MAX_BOOK_NAME_LENGTH);
                strncpy(ptr1->next->book_name, temp, MAX_BOOK_NAME_LENGTH);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
