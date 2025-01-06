#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "borrowedbook.h"
#include "returnedbook.h"
#include "staff.h"
#include "student.h"
#include "sortbyauthor.h"
#include "sortbybookname.h"
#include "filehanding.h"

struct book* book_head = NULL;
struct borrowedbook* borrowed_books_head = NULL;
struct returnedbook* returned_books_head = NULL;
struct staff* staff_head = NULL;
struct student* student_head = NULL;
struct sortbyauthor* author_head = NULL;
struct sortbybookname* book_name_head = NULL;
extern int staff_count;
extern int books_count;  // Declare the variable as external

int books_count = 0;
int students_count = 0;
int staff_count = 0;
int borrowed_count = 0;
int returned_count = 0;

typedef enum
{
    // Book Management
    ADD_BOOK = 1,
    REMOVE_BOOK,
    UPDATE_BOOK,
    SEARCH_BOOK,
    VIEW_BOOKS,

    // Borrowed/Returned Book Management
    RECORD_BORROWED_BOOK,
    VIEW_BORROWED_BOOK,
    RECORD_RETURNED_BOOK,
    VIEW_RETURNED_BOOKS,

    // Author Management
    ADD_AUTHOR,
    VIEW_AUTHORS,
    SORT_AUTHORS,

    // Sorting Operations
    ADD_BOOK_NAME_SORTING,
    VIEW_BOOKS_BY_NAME,

    // User Management
    ADD_STUDENT,
    DELETE_STUDENT,
    UPDATE_STUDENT,
    SEARCH_STUDENT,
    VIEW_STUDENTS,
    ADD_STAFF,
    DELETE_STAFF,
    UPDATE_STAFF,
    SEARCH_STAFF,
    VIEW_STAFF,

    // Exit System
    EXIT
} MenuOption;

void display_menu() {
    printf("\nLibrary Management System\n");
    printf("1. Book Management:\n");
    printf("   1. Add Book\n");
    printf("   2. Remove Book\n");
    printf("   3. Update Book\n");
    printf("   4. Search Book\n");
    printf("   5. View Books\n");

    printf("2. Borrowed/Returned Book Management:\n");
    printf("   6. Record Borrowed Book\n");
    printf("   7. view Borrowed book\n");
    printf("   8. Record Returned Book\n");
    printf("   9. View Returned Books\n");

    printf("3. Author Management:\n");
    printf("   10. Add Author\n");
    printf("   11. View Authors\n");
    printf("   12. Sort Authors Alphabetically\n");

    printf("4. Sorting Operations:\n");
    printf("   13. Add Book Name for Sorting\n");
    printf("   14. View Books by Name\n");

    printf("5. User Management:\n");
    printf("   15. Add Student\n");
    printf("   16. delete student\n");
    printf("   17. update student\n");
    printf("   18. search student\n");
    printf("   19. View Students\n");
    printf("   20. Add Staff\n");
    printf("   21. delete staff\n");
    printf("   22. update staff\n");
    printf("   23. search staff\n");
    printf("   24. View Staff\n");

    printf("25. Exit\n");
    printf("Enter your choice: ");
}

int main_menu() {
    int choice;
    int login_status;
    int user_role;



    printf("Data loaded successfully!\n");
    printf("Books count: %d\n", books_count);
    printf("Students count: %d\n", students_count);
    printf("Staff count: %d\n", staff_count);
    printf("Borrowed books count: %d\n", borrowed_count);
    printf("Returned books count: %d\n", returned_count);

    // User login
    printf("Select your role to login:\n");
    printf("1. Admin\n2. Staff\n3. Student \n");
    printf("Enter your choice: ");
    scanf("%d", &user_role);

    if (user_role == 1)
    {
        login_status = authenticate_admin();
        if (!login_status)
        {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    }
    else if (user_role == 2)
    {
        login_status = authenticate_staff();
        if (!login_status)
        {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    }
    else if (user_role == 3)
    {
        login_status = authenticate_student();
        if (!login_status)
        {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    }
    else
    {
        printf("Invalid choice. Exiting...\n");
        return 0;
    }

    do {
        display_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        getchar();

        switch ((MenuOption)choice)
        {
        case ADD_BOOK:
            // Handle Add Book logic
            break;
        case REMOVE_BOOK:
            // Handle Remove Book logic
            break;
        case UPDATE_BOOK:
            // Handle Update Book logic
            break;
        case VIEW_BOOKS:
            // Handle View Books logic
            break;
        case ADD_STAFF:
        {
            char name[100], department[50], position[50];
            int id;
            printf("Enter staff ID: ");
            scanf("%d", &id);
            getchar();  // To consume the newline character after entering an integer

            printf("Enter staff name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';  // Remove newline character

            printf("Enter department: ");
            fgets(department, sizeof(department), stdin);
            department[strcspn(department, "\n")] = '\0';  // Remove newline character

            printf("Enter position: ");
            fgets(position, sizeof(position), stdin);
            position[strcspn(position, "\n")] = '\0';  // Remove newline character

            staff_head = add_staff(staff_head, name, id, department, position);
            printf("Staff data has been saved to staff_data.txt.\n");
            break;
        }

        case DELETE_STAFF:
        {
            int staff_id;
            printf("Enter staff ID to delete: ");
            scanf("%d", &staff_id);
            delete_staff(staff_head, staff_id);
            break;
        }

        case UPDATE_STAFF:
        {
            int staff_id;
            printf("Enter staff ID to update: ");
            scanf("%d", &staff_id);
            update_staff(staff_head, staff_id);
            break;
        }

        case SEARCH_STAFF:
        {
            int staff_id;
            printf("Enter staff ID to search: ");
            scanf("%d", &staff_id);

            // Call the search_staff function to search by staff_id
            struct staff* found_staff = search_staff(staff_head, staff_id);

            if (found_staff != NULL) {
                // If staff is found, display their details
                printf("Staff found: %s, Department: %s, Position: %s\n",
                       found_staff->staff_name,
                       found_staff->department,
                       found_staff->position);
            } else {
                // If staff is not found
                printf("Staff not found.\n");
            }
            break;
        }

        case VIEW_STAFF:
            view_staff(staff_head);
            break;


        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (1);

    return 0;
}
