#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"
#include "filehanding.h"
// Function to add a new staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = malloc(sizeof(struct staff));
    if (!new_staff) {
        printf("Memory allocation failed.\n");
        return head;
    }

    strcpy(new_staff->staff_name, name);
    strcpy(new_staff->department, department);
    strcpy(new_staff->position, position);
    new_staff->staff_id = id;
    new_staff->next = head;

    FILE* file = fopen("staff_data.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(new_staff);
        return head;
    }

    fprintf(file, "ID: %d, Name: %s, Department: %s, Position: %s\n", id, name, department, position);
    fclose(file);

    return new_staff;
}

void delete_staff(struct staff* head, int id) {
    if (head == NULL) {
        printf("No staff to delete.\n");
        return;
    }

    struct staff* temp = head;
    struct staff* prev = NULL;

    if (temp != NULL && temp->staff_id == id) {
        head = temp->next;
        free(temp);
        rewrite_file(head);

        printf("Staff deleted successfully.\n");
        return;
    }

    while (temp != NULL && temp->staff_id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Staff with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);

    rewrite_file(head);
    printf("Staff deleted successfully.\n");
}

void update_staff(struct staff* head, int id) {
    struct staff* temp = head;
    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Staff with ID %d not found in linked list.\n", id);
        return;
    }

    printf("Enter new name: ");
    scanf(" %[^\n]", temp->staff_name);
    printf("Enter new department: ");
    scanf(" %[^\n]", temp->department);
    printf("Enter new position: ");
    scanf(" %[^\n]", temp->position);

    printf("Staff updated successfully in the linked list.\n");

    FILE* file = fopen("staff_data.txt", "r+");
    if (!file) {
        perror("Error opening staff file");
        return;
    }

    struct staff file_staff;
    int found = 0;
    char temp_filename[] = "temp_staff.txt";
    FILE* temp_file = fopen(temp_filename, "w");

    if (!temp_file) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "ID: %d, Name: %99[^,], Department: %99[^,], Position: %99[^\n]\n",&file_staff.staff_id, file_staff.staff_name, file_staff.department, file_staff.position) != EOF) {
        if (file_staff.staff_id == id) {
            fprintf(temp_file, "ID: %d, Name: %s, Department: %s, Position: %s\n",temp->staff_id, temp->staff_name, temp->department, temp->position);
            found = 1;
        } else {
            fprintf(temp_file, "ID: %d, Name: %s, Department: %s, Position: %s\n", file_staff.staff_id, file_staff.staff_name, file_staff.department, file_staff.position);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove("staff_data.txt");
        rename(temp_filename, "staff_data.txt");
        printf("Staff updated successfully in the file.\n");
    } else {
        printf("Staff ID %d not found in file.\n", id);
    }
}
struct staff* search_staff(struct staff* head, int staff_id) {
    struct staff* current = head;

    while (current != NULL) {
        if (current->staff_id == staff_id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Function to view all staff members
void view_staff(struct staff* head) {
    struct staff* temp = head;
    if (!temp) {
        printf("No staff records available.\n");
        return;
    }
    printf("Staff Records:\n");
    while (temp) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
        temp = temp->next;
    }
}


int count_staff(struct staff* head) {
    int count = 0;
    struct staff* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}
