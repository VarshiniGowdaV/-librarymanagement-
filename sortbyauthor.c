#include "sortbyauthor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct sortbyauthor* author_head;

struct sortbyauthor* create_author_node(const char* author_name)
{
    struct sortbyauthor* new_node = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    if (new_node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(new_node->author_name, author_name, MAX_AUTHOR_NAME_LENGTH);
    new_node->author_name[MAX_AUTHOR_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    return new_node;
}

struct sortbyauthor* add_author(struct sortbyauthor* head, const char* author_name)
{
    struct sortbyauthor* new_node = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    if (new_node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(new_node->author_name, author_name, MAX_AUTHOR_NAME_LENGTH);
    new_node->author_name[MAX_AUTHOR_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    if (head == NULL)
    {
        return new_node;
    }
    struct sortbyauthor* temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;

    return head;
}

void view_authors(struct sortbyauthor* head)
{
    if (head == NULL) {
        printf("No authors in the list.\n");
        return;
    }

    struct sortbyauthor* current = head;
    printf("Author List:\n");
    while (current != NULL)
    {
        printf("%s\n", current->author_name);
        current = current->next;
        printf("---------------\n");
    }
}

void sort_authors()
{
    merge_sort(&author_head);
    printf("Authors list sorted successfully.\n");
}

struct sortbyauthor* split_list(struct sortbyauthor* head)
{
    struct sortbyauthor *fast, *slow;
    slow = head;
    fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct sortbyauthor* second_half = slow->next;
    slow->next = NULL;

    return second_half;
}

struct sortbyauthor* merge(struct sortbyauthor* first, struct sortbyauthor* second)
{
    struct sortbyauthor* dummy = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    struct sortbyauthor* tail = dummy;
    while (first != NULL && second != NULL)
    {
        if (strcmp(first->author_name, second->author_name) <= 0)
        {
            tail->next = first;
            first = first->next;
        } else {
            tail->next = second;
            second = second->next;
        }
        tail = tail->next;
    }
    if (first != NULL)
    {
        tail->next = first;
    }
    else
    {
        tail->next = second;
    }

    struct sortbyauthor* merged_head = dummy->next;
    free(dummy);
    return merged_head;
}
void merge_sort(struct sortbyauthor* head)
{
    if (head == NULL || head->next == NULL)
    {
    }
    struct sortbyauthor* second_half = split_list(head);
    merge_sort(head);
    merge_sort(second_half);
    head = merge(head, second_half);
}

struct sortbyauthor* merge_sorted_lists(struct sortbyauthor* left, struct sortbyauthor* right)
{
    if (left == NULL) return right;
    if (right == NULL) return left;
    if (strcmp(left->author_name, right->author_name) < 0)
    {
        left->next = merge_sorted_lists(left->next, right);
        return left;
    }
    else
    {
        right->next = merge_sorted_lists(left, right->next);
        return right;
    }
}
