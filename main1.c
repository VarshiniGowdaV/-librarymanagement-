#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "student.h"
#include "filehanding.h"
#include "book.h"
#include "borrowedbook.h"
#include "staff.h"

int staff_id;

typedef enum {
    // Student Management
    ADD_STUDENT = 1,
    DELETE_STUDENT,
    UPDATE_STUDENT,
    SEARCH_STUDENT,
    VIEW_STUDENTS,
    LOAD_STUDENT,
    ADD_STUDENT_IN_FILE,
    UPDATE_STUDENT_IN_FILE,
    DELETE_STUDENT_IN_FILE,

    // Book Management
    ADD_BOOK,
    DELETE_BOOK,
    UPDATE_BOOK,
    SEARCH_BOOK,
    VIEW_BOOKS,
    LOAD_BOOKS,
    ADD_BOOK_IN_FILE,
    UPDATE_BOOK_IN_FILE,
    DELETE_BOOK_IN_FILE,

    // Staff Management
    ADD_STAFF,
    DELETE_STAFF,
    UPDATE_STAFF,
    SEARCH_STAFF,
    VIEW_STAFF,
    LOAD_STAFF,
    ADD_STAFF_IN_FILE,
    UPDATE_STAFF_IN_FILE,
    DELETE_STAFF_IN_FILE,

    // Borrowed Book Management
    RECORD_BORROWED_BOOK,
    VIEW_BORROWED_BOOKS,
    SAVE_BORROWED_BOOKS_TO_FILE,

    // Returned Book Management
    RECORD_RETURNED_BOOK,
    VIEW_RETURNED_BOOKS,
    SAVE_RETURNED_BOOKS_TO_FILE,
    LOAD_RETURNED_BOOKS_FROM_FILE,

    EXIT
} MenuOption;


// Function to display the main menu
void display_menu() {
    printf("\nLibrary Management System\n");
    printf("******Student Management******:\n");
    printf("   1. Add Student\n");
    printf("   2. Delete Student\n");
    printf("   3. Update Student\n");
    printf("   4. Search Student\n");
    printf("   5. View Students\n");
    printf("   6. Load Students from File\n");
    printf("   7. Add Student to File\n");
    printf("   8. Update Student in File\n");
    printf("   9. Delete Student from File\n");

    printf("******Book Management******:\n");
    printf("   10. Add Book\n");
    printf("   11. Delete Book\n");
    printf("   12. Update Book\n");
    printf("   13. Search Book\n");
    printf("   14. View Books\n");
    printf("   15. Load Books from File\n");
    printf("   16. Add Book to File\n");
    printf("   17. Update Book in File\n");
    printf("   18. Delete Book from File\n");

    printf("******Staff Management******:\n");
    printf("   19. Add Staff\n");
    printf("   20. Delete Staff\n");
    printf("   21. Update Staff\n");
    printf("   22. Search Staff\n");
    printf("   23. View Staff\n");
    printf("   24. Load Staff from File\n");
    printf("   25. Add Staff to File\n");
    printf("   26. Update Staff in File\n");
    printf("   27. Delete Staff from File\n");

    printf("******Borrowed Books Management******:\n");
    printf("   28. Record Borrowed Book\n");
    printf("   29. View Borrowed Books\n");
    printf("   30. Save Borrowed Books to File\n");

    printf("******Returned Books Management******:\n");
    printf("   31. Record Returned Book\n");
    printf("   32. View Returned Books\n");
    printf("   33. Save Returned Books to File\n");

    printf("   34. Exit\n");
    printf("Enter your choice: ");
}

// Function to handle the main menu logic
void main_menu() {
    int choice;

    // Authenticate the admin first
    if (!authenticate_admin()) {
        printf("Authentication failed. Exiting...\n");
        return;
    }

    int student_id, book_id;
    char name[MAX_NAME_LENGTH], department[MAX_DEPT_LENGTH], author[MAX_AUTHOR_LENGTH], title[MAX_TITLE_LENGTH], staff_name[MAX_NAME_LENGTH];

    // Load students, books, and staff from the file initially
    loadStudentsFromFile();
    loadBooksFromFile();
    loadBorrowedBookFromFile();  // Load borrowed books initially
    loadStaffFromFile();  // Load staff information initially
    loadRetunedBookFromFile();

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar();  // Consume the newline character left by scanf

        switch (choice) {
        // Student Management
        case ADD_STUDENT:
            printf("Enter student name: ");
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';  // Remove the newline
            printf("Enter student ID: ");
            scanf("%d", &student_id);
            getchar();  // Consume the newline
            printf("Enter student department: ");
            fgets(department, MAX_DEPT_LENGTH, stdin);
            department[strcspn(department, "\n")] = '\0';  // Remove the newline
            student_head = add_student(student_head, name, student_id, department);
            break;

        case DELETE_STUDENT:
            printf("Enter student ID to delete: ");
            scanf("%d", &student_id);
            delete_student(student_head, student_id);
            break;

        case UPDATE_STUDENT:
            printf("Enter student ID to update (RAM only): ");
            scanf("%d", &student_id);
            getchar();  // Consume newline
            printf("Enter new name: ");
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';  // Remove newline
            printf("Enter new department: ");
            fgets(department, MAX_DEPT_LENGTH, stdin);
            department[strcspn(department, "\n")] = '\0';  // Remove newline
            update_student(student_head, student_id, name, department);
            printf("Student updated in RAM.\n");
            break;

        case SEARCH_STUDENT:
            printf("Enter student ID to search: ");
            scanf("%d", &student_id);
            searchStudentById(student_id);
            break;

        case VIEW_STUDENTS:
            view_students(student_head);
            break;

        case LOAD_STUDENT:
            loadStudentsFromFile();
            printf("Students loaded from file.\n");
            break;

        case ADD_STUDENT_IN_FILE:
            addStudentToFile();
            printf("Students added to file.\n");
            break;

        case UPDATE_STUDENT_IN_FILE:
            printf("Enter student ID to update (RAM and File): ");
            scanf("%d", &student_id);
            getchar();  // Consume newline
            printf("Enter new name: ");
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';  // Remove newline
            printf("Enter new department: ");
            fgets(department, MAX_DEPT_LENGTH, stdin);
            department[strcspn(department, "\n")] = '\0';  // Remove newline
            updateStudentInFile(student_head, student_id, name, department);
            break;

        case DELETE_STUDENT_IN_FILE:
            // Code to delete student from file
            break;

            // Book Management
        case ADD_BOOK:
            printf("Enter book ID: ");
            scanf("%d", &book_id);
            getchar(); // Consume newline
            printf("Enter book name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; // Remove newline

            printf("Enter book title: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0; // Remove newline

            printf("Enter author name: ");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = 0; // Remove newline

            book_head = add_book(book_head, name, title, book_id, author);
            break;

        case DELETE_BOOK:
            printf("Enter book ID to delete: ");
            scanf("%d", &book_id);
            delete_book(book_id);
            break;

        case UPDATE_BOOK:
            printf("Enter book ID to update: ");
            scanf("%d", &book_id);
            getchar();  // Consume newline
            printf("Enter new book name: ");
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';  // Remove newline
            printf("Enter new author name: ");
            fgets(author, MAX_AUTHOR_LENGTH, stdin);
            author[strcspn(author, "\n")] = '\0';  // Remove newline
            printf("Enter new book title: ");
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = '\0';  // Remove newline
            update_book(book_id, name, author, title);
            break;

        case SEARCH_BOOK:
            printf("Enter book ID to search: ");
            scanf("%d", &book_id);
            search_book_by_id(book_id);
            break;

        case VIEW_BOOKS:
            display_books();
            break;

        case LOAD_BOOKS:
            loadBooksFromFile();
            printf("Books loaded from file.\n");
            break;

            // Borrowed Books Management
        case RECORD_BORROWED_BOOK:
            record_borrowed_book();
            break;

        case VIEW_BORROWED_BOOKS:
            view_borrowed_books();
            break;

        case SAVE_BORROWED_BOOKS_TO_FILE:
            save_Borrowed_Book_To_File();
            printf("Borrowed books saved to file.\n");
            break;

        case ADD_STAFF:
            // Declare staff name and department variables if not already declared
            char staff_name[MAX_NAME_LENGTH];
            char staff_department[MAX_DEPT_LENGTH];

            printf("Enter staff name: ");
            fgets(staff_name, MAX_NAME_LENGTH, stdin);
            staff_name[strcspn(staff_name, "\n")] = '\0';  // Remove newline

            printf("Enter staff ID: ");
            scanf("%d", &staff_id);
            getchar();  // Consume the newline

            // Add staff department input
            printf("Enter staff department: ");
            fgets(staff_department, MAX_DEPT_LENGTH, stdin);
            staff_department[strcspn(staff_department, "\n")] = '\0';  // Remove newline

            staff_head = add_staff(staff_head, staff_name, staff_id, staff_department);
            break;

        case DELETE_STAFF:
            printf("Enter staff ID to delete: ");
            scanf("%d", &staff_id);
            delete_staff(staff_head, staff_id);  // Pass both staff_head and staff_id
            break;

        case UPDATE_STAFF:
            printf("Enter staff ID to update: ");
            scanf("%d", &staff_id);
            getchar();  // Consume newline
            printf("Enter new name: ");
            fgets(staff_name, MAX_NAME_LENGTH, stdin);
            staff_name[strcspn(staff_name, "\n")] = '\0';  // Remove newline

            // Add input for department as well
            printf("Enter new department: ");
            fgets(staff_department, MAX_DEPT_LENGTH, stdin);
            staff_department[strcspn(staff_department, "\n")] = '\0';  // Remove newline

            // Now call the update_staff function with the correct number of arguments
            update_staff(staff_head, staff_id, staff_name, staff_department);
            break;

        case SEARCH_STAFF:
            printf("Enter staff ID to search: ");
            scanf("%d", &staff_id);

            // Declare staff_member as a pointer to struct staff
            struct staff* staff_member = search_staff(staff_head, staff_id);

            if (staff_member != NULL) {
                // If staff member is found, display only the ID
                printf("Staff found: ID: %d\n", staff_member->staff_id);
            } else {
                // If staff member is not found, display a message
                printf("Staff with ID %d not found.\n", staff_id);
            }
            break;

        case VIEW_STAFF:
            view_staff(staff_head);
            break;

        case LOAD_STAFF:
            loadStaffFromFile();
            printf("Staff loaded from file.\n");
            break;

        case ADD_STAFF_IN_FILE:
            addStaffToFile();
            printf("Staff added to file.\n");
            break;

        case UPDATE_STAFF_IN_FILE:
            printf("Enter staff ID to update (RAM and File): ");
            scanf("%d", &staff_id);
            getchar();  // Consume newline
            printf("Enter new name: ");
            fgets(staff_name, MAX_NAME_LENGTH, stdin);
            staff_name[strcspn(staff_name, "\n")] = '\0';  // Remove newline
            updateStaffInFile(staff_head, staff_id, staff_name);
            break;

            // Case for deleting a staff member from the file
        case DELETE_STAFF_IN_FILE:
            printf("Enter staff ID to delete from the file: ");
            scanf("%d", &staff_id);

            // Open the staff file for reading
            FILE* file = fopen("StaffRecords.txt", "r+");
            if (file == NULL) {
                printf("Error: Could not open the staff file.\n");
            } else {
                deleteStaffInFile(file, staff_id);  // Call the function to delete the staff
            }
            break;

        case RECORD_RETURNED_BOOK:
            record_returned_book();
            break;

        case VIEW_RETURNED_BOOKS:
            view_returned_books();
            break;

        case SAVE_RETURNED_BOOKS_TO_FILE:
            save_Retuned_Book_To_File();
            break;

        case LOAD_RETURNED_BOOKS_FROM_FILE:
            loadRetunedBookFromFile();
            break;

        case EXIT:
            printf("Exiting...\n");
            return;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
