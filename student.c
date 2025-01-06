#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Function to create a new student node
struct student* create_student_node(const char* name, int student_id, const char* dept) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    new_student->student_id = student_id;
    strncpy(new_student->name, name, MAX_NAME_LENGTH);
    strncpy(new_student->department, dept, MAX_DEPT_LENGTH);
    new_student->next = NULL;
    return new_student;
}

// Function to add a new student at the beginning of the list
struct student* add_student(struct student* head, const char* name, int student_id, const char* department) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    new_student->student_id = student_id;
    strcpy(new_student->name, name);
    strcpy(new_student->department, department);
    new_student->next = head;

    return new_student;
}

// Function to delete a student by student_id
void delete_student(struct student* head, int student_id) {
    if (head == NULL) {
        printf("No students to delete.\n");
        return;
    }

    struct student* temp = head;
    struct student* prev = NULL;

    if (temp != NULL && temp->student_id == student_id) {
        head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->student_id != student_id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", student_id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student deleted successfully.\n");
}

// Function to update student details
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department) {
    struct student* temp = head;
    while (temp != NULL) {
        if (temp->student_id == student_id) {
            strncpy(temp->name, new_name, MAX_NAME_LENGTH);
            strncpy(temp->department, new_department, MAX_DEPT_LENGTH);
            printf("Student information updated in memory.\n");

            FILE* file = fopen("students.txt", "r+");
            if (!file) {
                perror("Error opening students file");
                return;
            }

            struct student file_student;
            long pos;
            int found = 0;
            while (fscanf(file, "%d,%99[^,],%49[^,]\n", &file_student.student_id, file_student.name, file_student.department) != EOF) {
                pos = ftell(file);

                if (file_student.student_id == student_id) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                fseek(file, pos - sizeof(file_student), SEEK_SET);
                fprintf(file, "%d,%s,%s\n", student_id, new_name, new_department);
                printf("Student information updated in file.\n");
            } else {
                printf("Student ID %d not found in file.\n", student_id);
            }

            fclose(file);
            return;
        }
        temp = temp->next;
    }

    printf("Student with ID %d not found.\n", student_id);
}

// Function to search for a student by student_id
struct student* search_student(struct student* head, int student_id) {
    struct student* temp = head;

    while (temp != NULL) {
        if (temp->student_id == student_id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

// Function to view all students
void view_students(struct student* head) {
    if (head == NULL) {
        printf("No students available.\n");
        return;
    }

    struct student* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Department: %s\n", temp->student_id, temp->name, temp->department);
        temp = temp->next;
    }
}
