#ifndef SORTBYAUTHOR_H
#define SORTBYAUTHOR_H

#define MAX_AUTHOR_NAME_LENGTH 100  // Define the maximum length for author names

struct sortbyauthor {
    char author_name[MAX_AUTHOR_NAME_LENGTH];
    struct sortbyauthor* next;
};

// Function declarations
struct sortbyauthor* create_author_node(const char* author_name);
struct sortbyauthor* add_author(struct sortbyauthor* head, const char* author_name);
void view_authors(struct sortbyauthor* head);
void sort_authors();
void merge_sort(struct sortbyauthor* head);
struct sortbyauthor* split_list(struct sortbyauthor* head);
struct sortbyauthor* merge_sorted_lists(struct sortbyauthor* left, struct sortbyauthor* right);

#endif
