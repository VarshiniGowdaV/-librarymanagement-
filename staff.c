#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// Function to add a new staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = malloc(sizeof(struct staff));
    if (!new_staff) {
        printf("Memory allocation failed.\n");
        return head;
    }

    // Fill staff data
    strcpy(new_staff->staff_name, name);
    strcpy(new_staff->department, department);
    strcpy(new_staff->position, position);
    new_staff->staff_id = id;
    new_staff->next = head;

    // Open file in append mode to add staff details
    FILE* file = fopen("staff_data.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(new_staff);
        return head;
    }

    // Write staff data to the file
    fprintf(file, "ID: %d, Name: %s, Department: %s, Position: %s\n", id, name, department, position);
    fclose(file);

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


// Function to update staff data both in the linked list and file
void update_staff(struct staff* head, int id) {
    struct staff* temp = head;

    // Find the staff in the linked list by ID
    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Staff with ID %d not found in linked list.\n", id);
        return;
    }

    // Update staff data in the linked list
    printf("Enter new name: ");
    scanf(" %[^\n]", temp->staff_name);
    printf("Enter new department: ");
    scanf(" %[^\n]", temp->department);
    printf("Enter new position: ");
    scanf(" %[^\n]", temp->position);

    printf("Staff updated successfully in the linked list.\n");

    // Now update the staff data in the file
    FILE* file = fopen("staff.txt", "r+");
    if (!file) {
        perror("Error opening staff file");
        return;
    }

    struct staff file_staff;
    long pos;
    int found = 0;
    char temp_filename[] = "temp_staff.txt";  // Temporary file to store the updated content
    FILE* temp_file = fopen(temp_filename, "w");

    if (!temp_file) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    // Read and rewrite the file content with updated staff
    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,]\n", &file_staff.staff_id, file_staff.staff_name, file_staff.department, file_staff.position) != EOF) {
        // Check if we found the staff in the file
        if (file_staff.staff_id == id) {
            fprintf(temp_file, "%d,%s,%s,%s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
            found = 1; // Mark that the update was successful
        } else {
            fprintf(temp_file, "%d,%s,%s,%s\n", file_staff.staff_id, file_staff.staff_name, file_staff.department, file_staff.position);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace the old file with the updated one
    if (found) {
        remove("staff.txt");
        rename(temp_filename, "staff.txt");
        printf("Staff updated successfully in the file.\n");
    } else {
        printf("Staff ID %d not found in file.\n", id);
    }
}
struct staff* search_staff(struct staff* head, int staff_id) {
    struct staff* current = head;

    while (current != NULL) {
        if (current->staff_id == staff_id) {
            return current;  // Return the staff member if found
        }
        current = current->next;
    }

    return NULL;  // Return NULL if not found
}
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
