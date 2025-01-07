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

#endif
