#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"
struct staff* staff_head = NULL;

struct staff* add_staff(struct staff* staff_head, const char* name, int staff_id, const char* department) {
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (!new_staff) {
        printf("Memory allocation failed!\n");
        return staff_head;
    }

    // Set values for the new staff member
    strncpy(new_staff->name, name, MAX_NAME_LENGTH - 1);
    new_staff->name[MAX_NAME_LENGTH - 1] = '\0';
    new_staff->staff_id = staff_id;
    strncpy(new_staff->department, department, MAX_DEPARTMENT_LENGTH - 1);
    new_staff->department[MAX_DEPARTMENT_LENGTH - 1] = '\0';
    new_staff->next = NULL;

    // Add the new staff member to the list
    if (staff_head == NULL) {
        staff_head = new_staff;
    } else {
        struct staff* current = staff_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_staff;
    }

    return staff_head;
}


// Delete a staff member by ID
void delete_staff(struct staff* head, int id) {
    struct staff *current = head, *previous = NULL;
    while (current != NULL) {
        if (current->staff_id == id) {
            if (previous == NULL) {
                head = current->next;  // If the staff to be deleted is the head
            } else {
                previous->next = current->next;  // Bypass the staff node
            }
            free(current);
            printf("Staff with ID %d deleted.\n", id);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", id);
}

void update_staff(struct staff* head, int staff_id, const char* staff_name, const char* staff_department) {
    struct staff* current = head;
    while (current != NULL) {
        if (current->staff_id == staff_id) {
            strncpy(current->name, staff_name, MAX_NAME_LENGTH);
            strncpy(current->department, staff_department, MAX_DEPT_LENGTH);
            printf("Staff updated: ID: %d, Name: %s, Department: %s\n",
                   current->staff_id, current->name, current->department);
            return;
        }
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", staff_id);
}


// Search for a staff member by ID
struct staff* search_staff(struct staff* head, int id) {
    struct staff* current = head;
    while (current != NULL) {
        if (current->staff_id == id) {
            return current;  // Return the found staff member
        }
        current = current->next;
    }
    return NULL;  // Staff not found
}

// View all staff members
void view_staff(struct staff* head) {
    struct staff* current = head;
    if (current == NULL) {
        printf("No staff records available.\n");
        return;
    }

    printf("Staff details:\n");
    while (current != NULL) {
        // Corrected: Use 'name' instead of 'staff_name'
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n",
               current->staff_id, current->name, current->department, current->position);
        current = current->next;
    }
}


// Sort staff by name (alphabetical order)
void sortStaffByName(struct staff* head) {
    struct staff *current, *next_node;
    char temp_name[MAX_NAME_LENGTH], temp_department[MAX_DEPARTMENT_LENGTH], temp_position[50];
    int temp_id;

    for (current = head; current != NULL; current = current->next) {
        for (next_node = current->next; next_node != NULL; next_node = next_node->next) {
            // Use 'name' instead of 'staff_name'
            if (strcmp(current->name, next_node->name) > 0) {
                // Swap staff data
                temp_id = current->staff_id;
                current->staff_id = next_node->staff_id;
                next_node->staff_id = temp_id;

                strncpy(temp_name, current->name, sizeof(temp_name));
                strncpy(current->name, next_node->name, sizeof(current->name));
                strncpy(next_node->name, temp_name, sizeof(next_node->name));

                strncpy(temp_department, current->department, sizeof(temp_department));
                strncpy(current->department, next_node->department, sizeof(current->department));
                strncpy(next_node->department, temp_department, sizeof(next_node->department));

                strncpy(temp_position, current->position, sizeof(temp_position));
                strncpy(current->position, next_node->position, sizeof(current->position));
                strncpy(next_node->position, temp_position, sizeof(next_node->position));
            }
        }
    }
}
// Sort staff by ID (ascending order)
void sortStaffById(struct staff* head) {
    struct staff *current, *next_node;
    int temp_id;
    char temp_name[MAX_NAME_LENGTH], temp_department[MAX_DEPARTMENT_LENGTH], temp_position[50];

    for (current = head; current != NULL; current = current->next) {
        for (next_node = current->next; next_node != NULL; next_node = next_node->next) {
            if (current->staff_id > next_node->staff_id) {
                // Swap staff data
                temp_id = current->staff_id;
                current->staff_id = next_node->staff_id;
                next_node->staff_id = temp_id;

                // Use 'name' instead of 'staff_name'
                strncpy(temp_name, current->name, sizeof(temp_name));
                strncpy(current->name, next_node->name, sizeof(current->name));
                strncpy(next_node->name, temp_name, sizeof(next_node->name));

                strncpy(temp_department, current->department, sizeof(temp_department));
                strncpy(current->department, next_node->department, sizeof(current->department));
                strncpy(next_node->department, temp_department, sizeof(next_node->department));

                strncpy(temp_position, current->position, sizeof(temp_position));
                strncpy(current->position, next_node->position, sizeof(current->position));
                strncpy(next_node->position, temp_position, sizeof(next_node->position));
            }
        }
    }
}

// Get the total number of staff members
int getTotalStaffCount(struct staff* head) {
    int count = 0;
    struct staff* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
