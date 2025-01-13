#ifndef BOOK_H
#define BOOK_H

#define MAX_NAME_LENGTH 50
#define MAX_DEPT_LENGTH 30
#define MAX_AUTHOR_LENGTH 100
#define MAX_TITLE_LENGTH 150
//#define RECORD_SIZE sizeof(struct Book)
#define RECORD_SIZE (10 + MAX_NAME_LENGTH + MAX_AUTHOR_LENGTH + MAX_TITLE_LENGTH + 4 + 4)
struct book {
    int book_id;
    char name[MAX_NAME_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char title[MAX_TITLE_LENGTH];
    int total_copies;
    int available_copies;
    int deleted;
    struct book* next;
};
extern struct book* book_head;

struct book* add_book(struct book* book_head, char* name, char* title, int book_id, char* author);
void update_book();
void delete_book();
void display_books();
void remove_book(int book_id);
struct book* search_book_by_id(int book_id);

#endif // BOOK_H
