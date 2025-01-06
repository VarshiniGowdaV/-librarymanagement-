#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// Function to add a new staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position)
{
    struct staff* new_staff = malloc(sizeof(struct staff));
    if (!new_staff)
    {
        printf("Memory allocation failed.\n");
        return head;
    }
    strcpy(new_staff->staff_name, name);
    strcpy(new_staff->department, department);
    strcpy(new_staff->position, position);
    new_staff->staff_id = id;
    new_staff->next = head;
    return new_staff;
}

void delete_staff(struct staff* head, int id)
{
    struct staff *temp = head, *prev = NULL;

    // Check if the head itself holds the staff to be deleted
    if (temp != NULL && temp->staff_id == id) {
        head = temp->next; // Move the head to the next staff member
        free(temp);        // Free the memory of the old head
        printf("Staff deleted successfully.\n");
        return;
    }

    // Search for the staff to delete
    while (temp != NULL && temp->staff_id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the staff with the given ID was not found
    if (temp == NULL) {
        printf("Staff with ID %d not found.\n", id);
        return;
    }

    // Unlink the staff node from the linked list
    prev->next = temp->next;
    free(temp);
    printf("Staff deleted successfully.\n");
}


// Function to update a staff member's details
void update_staff(struct staff* head, int id)
{
    struct staff* temp = head;

    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Staff with ID %d not found.\n", id);
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", temp->staff_name);
    printf("Enter new department: ");
    scanf(" %[^\n]", temp->department);
    printf("Enter new position: ");
    scanf(" %[^\n]", temp->position);

    printf("Staff updated successfully .\n");

    FILE* file = fopen("staff.txt", "r+");
    if (!file) {
        perror("Error opening staff file");
        return;
    }

    struct staff file_staff;
    long pos;
    int found = 0;

    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,]\n", &file_staff.staff_id, file_staff.staff_name, file_staff.department, file_staff.position) != EOF) {
        pos = ftell(file);

        if (file_staff.staff_id == id) {
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, pos - sizeof(file_staff), SEEK_SET);
        fprintf(file, "%d,%s,%s,%s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
        printf("Staff updated successfully in file.\n");
    } else {
        printf("Staff ID %d not found in file.\n", id);
    }

    fclose(file);
}

// Function to search for a staff member by ID
struct staff* search_staff(struct staff* head, int id) {
    struct staff* temp = head;
    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }
    return temp;
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

// Function to count the number of staff members in the list
int count_staff(struct staff* head) {
    int count = 0;
    struct staff* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}
