#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Initialize the head of the student linked list
struct student* student_head = NULL;

// Function to add a student
struct student* add_student(struct student* head, const char* name, int student_id, const char* department) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }

    new_student->student_id = student_id;
    strncpy(new_student->name, name, MAX_NAME_LENGTH - 1);
    new_student->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-terminated string
    strncpy(new_student->department, department, MAX_DEPT_LENGTH - 1);
    new_student->department[MAX_DEPT_LENGTH - 1] = '\0'; // Ensure null-terminated string
    new_student->next = head;

    return new_student;
}

// Function to update student details
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department) {
    struct student* current = head;

    while (current != NULL) {
        if (current->student_id == student_id) {
            strncpy(current->name, new_name, MAX_NAME_LENGTH - 1);
            current->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-terminated string
            strncpy(current->department, new_department, MAX_DEPT_LENGTH - 1);
            current->department[MAX_DEPT_LENGTH - 1] = '\0'; // Ensure null-terminated string
            return;
        }
        current = current->next;
    }

    printf("Student with ID %d  found\n", student_id);
}

// Function to view all students
void view_students(struct student* head) {
    struct student* current = head;

    while (current != NULL) {
        printf("Student ID: %d\n", current->student_id);
        printf("Name: %s\n", current->name);
        printf("Department: %s\n", current->department);
        printf("-----------------------\n");
        current = current->next;
    }
}

// Function to delete a student by ID
void delete_student(struct student* head, int student_id) {
    struct student* current = head;
    struct student* previous = NULL;

    // If the student to be deleted is the head of the list
    if (current != NULL && current->student_id == student_id) {
        head = current->next; // Move the head pointer
        free(current);
        return;
    }

    // Search for the student to be deleted
    while (current != NULL && current->student_id != student_id) {
        previous = current;
        current = current->next;
    }

    // If student not found
    if (current == NULL) {
        printf("Student with ID %d not found\n", student_id);
        return;
    }
    previous->next = current->next;
    free(current);
}

// Function to search for a student by ID
struct student* search_student(struct student* head, int student_id) {
    struct student* current = head;

    while (current != NULL) {
        if (current->student_id == student_id) {
            return current;
        }
        current = current->next;
    }

    return NULL; // Return NULL if student is not found
}

// Function to sort students by ID (ascending order)
void sortStudentsByID() {
    if (student_head == NULL) return;

    struct student* i = student_head;
    struct student* j = NULL;
    struct student temp;

    // Bubble sort by student ID
    while (i != NULL) {
        j = i->next;
        while (j != NULL) {
            if (i->student_id > j->student_id) {
                temp = *i;
                *i = *j;
                *j = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

// Function to sort students by name (alphabetical order)
void sortStudentsByName() {
    if (student_head == NULL) return;

    struct student* i = student_head;
    struct student* j = NULL;
    struct student temp;

    // Bubble sort by name
    while (i != NULL) {
        j = i->next;
        while (j != NULL) {
            if (strcmp(i->name, j->name) > 0) {
                temp = *i;
                *i = *j;
                *j = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

// Function to search for a student by ID and print their details
void searchStudentById(int id) {
    struct student* student = search_student(student_head, id);
    if (student != NULL) {
        printf("Student ID: %d\n", student->student_id);
        printf("Name: %s\n", student->name);
        printf("Department: %s\n", student->department);
    } else {
        printf("Student with ID %d not found\n", id);
    }
}

// Function to get the total number of students
int getTotalStudentCount() {
    int count = 0;
    struct student* current = student_head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
