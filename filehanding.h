#ifndef FILEHANDING_H
#define FILEHANDING_H

#include "book.h"
#include "student.h"
#include "staff.h"
#include "borrowedbook.h"
#include "returnedbook.h"

#define BOOKS_FILE "books.txt"
#define STUDENTS_FILE "students.txt"
#define STAFF_FILE "staff.txt"
#define BORROWED_BOOKS_FILE "borrowed_books.txt"
#define RETURNED_BOOKS_FILE "returned_books.txt"
// struct book* load_books_from_file();
// struct student* load_students_from_file();
// struct staff* load_staff_from_file();
// struct borrowedbook* load_borrowed_books_from_file();
// struct returnedbook* load_returned_books_from_file();

// void save_books_to_file(struct book* head);
// void load_books_from_file();
void save_students_to_file(struct student* student_head);
void load_students_from_file();
void save_staff_to_file(struct staff* staff_head);
void load_staff_from_file();
void rewrite_file(struct student* head);
void rewrite_file_staff(struct staff* head);
void save_borrowed_books_to_file(struct borrowedbook* borrowed_books_head);
void load_borrowed_books_from_file();
void save_returned_books_to_file(struct returnedbook* returned_books_head);
void load_returned_books_from_file();

#endif // FILEHANDING_H
