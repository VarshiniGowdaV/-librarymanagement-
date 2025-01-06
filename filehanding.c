#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filehanding.h"
#include "book.h"
#include "student.h"
#include "staff.h"
#include "borrowedbook.h"
#include "returnedbook.h"

extern struct book* book_head;
extern struct student* student_head;
extern struct staff* staff_head;
extern struct borrowedbook* borrowed_books_head;
extern struct returnedbook* returned_books_head;

void load_students_from_file()
{
    FILE* file = fopen("students.txt", "r+");
    if (!file) {
        perror("Error opening students file");
        return;
    }

    while (1) {
        char name[100], department[50];
        int student_id;

        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position

        if (fscanf(file, "%99s %d %49s", name, &student_id, department) != 3) {
            break;
        }
        student_head = add_student(student_head, name, student_id, department);
    }

    fclose(file);
}

void save_students_to_file(struct student* head)
{
    FILE* file = fopen("students.txt", "w+");
    if (!file)
    {
        perror("Error opening students file for writing");
        return;
    }

    for (struct student* current = head; current; current = current->next)
    {
        // Use fseek to set file pointer position
        long position = ftell(file); // Save position
        fprintf(file, "%s %d %s\n", current->name, current->student_id, current->department);
    }

    fclose(file);
}
// Function to delete a student by student_id
void rewrite_file(struct student* head) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct student* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s\n", temp->student_id, temp->name, temp->department);
        temp = temp->next;
    }

    fclose(file);
}
void load_staff_from_file() {
    FILE* file = fopen("staff.txt", "r+");
    if (!file)
    {
        perror("Error opening staff file");
        return;
    }

    while (1)
    {
        char staff_name[100], department[50], staff_position[50];
        int staff_id;

        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position

        if (fscanf(file, "%99s %d %49s %49s", staff_name, &staff_id, department, staff_position) != 4)
        {
            break;
        }
        staff_head = add_staff(staff_head, staff_name, staff_id, department, staff_position);
    }

    fclose(file);
}

void save_staff_to_file(struct staff* head) {
    FILE* file = fopen("staff.txt", "w+");
    if (!file)
    {
        perror("Error opening staff file for writing");
        return;
    }

    for (struct staff* current = head; current; current = current->next) {
        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position
        fprintf(file, "%s %d %s %s\n", current->staff_name, current->staff_id, current->department, current->position);
    }

    fclose(file);
}
void rewrite_staff_file(struct staff* head) {
    FILE *file = fopen("staffs.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct staff* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s,%s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
        temp = temp->next;
    }

    fclose(file);
}


void load_borrowed_books_from_file() {
    FILE* file = fopen("borrowed_books.txt", "r+");
    if (!file)
    {
        perror("Error opening borrowed books file");
        return;
    }

    while (1)
    {
        int student_id, book_id;

        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position

        if (fscanf(file, "%d %d", &student_id, &book_id) != 2)
        {
            break;
        }
        borrowed_books_head = add_borrowed_book(borrowed_books_head, student_id, book_id);
    }

    fclose(file);
}

void save_borrowed_books_to_file(struct borrowedbook* head)
{
    FILE* file = fopen("borrowed_books.txt", "w+");
    if (!file)
    {
        perror("Error opening borrowed books file for writing");
        return;
    }

    for (struct borrowedbook* current = head; current; current = current->next)
    {
        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position
        fprintf(file, "%d %d\n", current->student_id, current->book_id);
    }

    fclose(file);
}

void load_returned_books_from_file()
{
    FILE* file = fopen("returned_books.txt", "r+");
    if (!file)
    {
        perror("Error opening returned books file");
        return;
    }

    while (1)
    {
        int student_id, book_id;
        char returned_date[20];

        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position

        if (fscanf(file, "%d %d %19s", &student_id, &book_id, returned_date) != 3)
        {
            break;
        }
        returned_books_head = add_returned_book(returned_books_head, student_id, book_id, returned_date);
    }

    fclose(file);
}

void save_returned_books_to_file(struct returnedbook* head)
{
    FILE* file = fopen("returned_books.txt", "w+");
    if (!file)
    {
        perror("Error opening returned books file for writing");
        return;
    }

    for (struct returnedbook* current = head; current; current = current->next) {
        // Use fseek to set file pointer position
        long position = ftell(file); // Save current position
        fprintf(file, "%d %d %s\n", current->student_id, current->book_id, current->returned_date);
    }

    fclose(file);
}
