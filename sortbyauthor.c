#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbyauthor.h"

// Create a new author node
struct sortbyauthor* create_author_node(const char* author_name) {
    struct sortbyauthor* new_node = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    if (new_node != NULL) {
        strncpy(new_node->author_name, author_name, MAX_AUTHOR_NAME_LENGTH);
        new_node->author_name[MAX_AUTHOR_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
        new_node->next = NULL;
    }
    return new_node;
}

// Add a new author to the list in sorted order
struct sortbyauthor* add_author(struct sortbyauthor* head, const char* author_name) {
    struct sortbyauthor* new_node = create_author_node(author_name);
    if (new_node == NULL) {
        return head; // Memory allocation failed
    }

    // If the list is empty or the new author should be placed at the beginning
    if (head == NULL || strcmp(author_name, head->author_name) < 0) {
        new_node->next = head;
        return new_node;
    }

    // Traverse the list to find the correct position
    struct sortbyauthor* current = head;
    while (current->next != NULL && strcmp(author_name, current->next->author_name) > 0) {
        current = current->next;
    }

    // Insert the new author in sorted position
    new_node->next = current->next;
    current->next = new_node;

    return head;
}

// View all authors in the list
void view_authors(struct sortbyauthor* head) {
    struct sortbyauthor* current = head;
    while (current != NULL) {
        printf("%s\n", current->author_name);
        current = current->next;
    }
}

