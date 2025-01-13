#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filehanding.h"
#include "student.h"
#include "staff.h"
#include "book.h"
#include "borrowedbook.h"
#include "filehanding.h"
#include "retunedbook.h"
#define BORROWED_BOOKS_FILE "borrowed_books.txt"
static FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (!file) {
        file = fopen(filename, "w+");
        if (!file) {
            printf("Error opening file: %s\n", filename);
            exit(1);
        }
    }
    return file;
}


// Function to load students from the file
void loadStudentsFromFile() {
    FILE* file = openFile("students.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0) {
        struct student temp_student;
        while (fread(&temp_student, sizeof(struct student), 1, file)) {
            student_head = add_student(student_head, temp_student.name, temp_student.student_id, temp_student.department);
        }
    }
    fclose(file);
}


// Function to add a student to the file (append)
void addStudentToFile() {
    FILE* file = openFile("students.txt");

    struct student* new_student = student_head;
    fseek(file, 0, SEEK_END);
    while (new_student != NULL) {
        fprintf(file,"%5d %-99s %-49s\n",new_student->student_id ,new_student->name,new_student->department);
        new_student = new_student->next;
    }
    fclose(file);
}
void deleteStudentInFile(FILE *file, int studentIdToDelete) {
    FILE *tempFile = fopen("temp.txt", "w");  // Create a temporary file to write the updated records
    if (tempFile == NULL) {
        printf("Error: Could not create a temporary file.\n");
        return;
    }

    struct student tempStudent;
    int found = 0;

    // Read the file and write to the temporary file, skipping the student to delete
    while (fread(&tempStudent, sizeof(struct student), 1, file)) {
        if (tempStudent.student_id != studentIdToDelete) {
            fwrite(&tempStudent, sizeof(struct student), 1, tempFile);  // Write the student if not deleted
        } else {
            found = 1;  // Mark as found if the student matches
        }
    }

    if (!found) {
        printf("Student with ID %d not found in the file.\n", studentIdToDelete);
    } else {
        printf("Student with ID %d has been deleted from the file.\n", studentIdToDelete);
    }

    fclose(file);  // Close the original file
    fclose(tempFile);  // Close the temporary file

    // Remove the original file and rename the temporary file
    remove("StudentRecords.txt");  // Delete the original file
    rename("temp.txt", "StudentRecords.txt");  // Rename temp file to the original file name
}


// Function to find the position of a student in the file
long findStudentPosition(int student_id) {
    FILE* file = openFile("students.txt");
    fseek(file, 0, SEEK_SET);
    struct student temp_student;
    long position = 0;

    while (fread(&temp_student, sizeof(struct student), 1, file)) {
        if (temp_student.student_id == student_id) {
            fclose(file);
            return position;
        }
        position++;
    }
    fclose(file);
    return -1; // Return -1 if not found
}

// Updates both RAM and file
void updateStudentInFile(struct student* head, int student_id, const char* new_name, const char* new_department) {
    struct student* current = head;

    // Update the student in memory (RAM)
    while (current != NULL) {
        if (current->student_id == student_id) {
            strncpy(current->name, new_name, MAX_NAME_LENGTH - 1);
            current->name[MAX_NAME_LENGTH - 1] = '\0'; // Null-terminate
            strncpy(current->department, new_department, MAX_DEPT_LENGTH - 1);
            current->department[MAX_DEPT_LENGTH - 1] = '\0'; // Null-terminate
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with ID %d found in memory.\n", student_id);
        return;
    }

    // Update the student in the file
    FILE* file = fopen("students.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct student temp_student;
    while (fread(&temp_student, sizeof(struct student), 1, file)) {
        if (temp_student.student_id == student_id) {
            // Update file
            fseek(file, -sizeof(struct student), SEEK_CUR);
            fwrite(current, sizeof(struct student), 1, file);
            printf("Student with ID %d updated successfully in file.\n", student_id);
            fclose(file);
            return;
        }
    }

    printf("Student with ID %d  found in file.\n", student_id);
    fclose(file);
}


// Function to save the updated student data to file
void save_student_to_file() {
    FILE* file = openFile("students.txt");

    struct student* current = student_head;
    fseek(file, 0, SEEK_SET); // Ensure we overwrite the file from the beginning
    while (current != NULL) {
        fwrite(current, sizeof(struct student), 1, file);
        current = current->next;
    }

    fclose(file);
}
//***********************************************************************************************************************//

void loadBooksFromFile() {
    FILE* file = openFile("books.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0) {
        struct book temp_book;
        while (fread(&temp_book, sizeof(struct book), 1, file)) {
            // Pass book_head to add_book, which will return the updated head
            book_head = add_book(book_head, temp_book.name, temp_book.title, temp_book.book_id, temp_book.author);
        }
    }
    fclose(file);
}



void addBooksToFile() {
    FILE* file = openFile("books.txt");

    struct book* current = book_head;
    fseek(file, 0, SEEK_END);
    while (current != NULL) {
        fprintf(file, "%5d %-99s %-49s\n", current->book_id, current->title, current->author);
        current = current->next;
    }
    fclose(file);
}


void deleteBooksInFile(int book_id) {
    FILE *file = openFile("books.txt");
    if (file == NULL) {
        printf("Error: Could not open the file.");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");  // Create a temporary file to write the updated records
    if (tempFile == NULL) {
        printf("Error: Could not create a temporary file.\n");
        fclose(file);
        return;
    }

    struct book tempBook;
    int found = 0;

    // Read the file and write to the temporary file, skipping the book to delete
    while (fread(&tempBook, sizeof(struct book), 1, file)) {
        if (tempBook.book_id != book_id) {
            fwrite(&tempBook, sizeof(struct book), 1, tempFile);  // Write the book if not deleted
        } else {
            found = 1;  // Mark as found if the book matches
        }
    }

    if (!found) {
        printf("Book with ID %d not found in the file.\n", book_id);
    } else {
        printf("Book with ID %d has been deleted from the file.\n", book_id);
    }

    fclose(file);  // Close the original file
    fclose(tempFile);  // Close the temporary file

    // Remove the original file and rename the temporary file
    remove("books.txt");  // Delete the original file
    rename("temp.txt", "books.txt");  // Rename temp file to the original file name
}


// Function to find the position of a specific book in the file
long findBooksPosition(int book_id) {
    FILE* file = openFile("books.txt");
    fseek(file, 0, SEEK_SET);
    struct book temp_book;
    long position = 0;

    while (fread(&temp_book, sizeof(struct book), 1, file)) {
        if (temp_book.book_id == book_id) {
            fclose(file);
            return position;
        }
        position++;
    }
    fclose(file);
    return -1; // Return -1 if not found
}
// filehandling.c
void updateBooksInFile(int book_id, const char* new_title, const char* new_author, int new_total_copies) {
    struct book* current = book_head;

    // Update the book in memory (RAM)
    while (current != NULL) {
        if (current->book_id == book_id) {
            strncpy(current->title, new_title, MAX_TITLE_LENGTH - 1);
            current->title[MAX_TITLE_LENGTH - 1] = '\0'; // Null-terminate
            strncpy(current->author, new_author, MAX_AUTHOR_LENGTH - 1);
            current->author[MAX_AUTHOR_LENGTH - 1] = '\0'; // Null-terminate
            current->total_copies = new_total_copies;
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Book with ID %d not found in memory.\n", book_id);
        return;
    }

    // Update the book in the file
    FILE* file = fopen("books.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct book temp_book;
    while (fread(&temp_book, sizeof(struct book), 1, file)) {
        if (temp_book.book_id == book_id) {
            // Update file
            fseek(file, -sizeof(struct book), SEEK_CUR); // Move the file pointer back to the start of the book record
            fwrite(current, sizeof(struct book), 1, file);
            printf("Book with ID %d updated successfully in file.\n", book_id);
            fclose(file);
            return;
        }
    }

    printf("Book with ID %d not found in file.\n", book_id);
    fclose(file);
}

void save_Book_To_File() {
    FILE* file = openFile("books.txt");

    struct book* current = book_head;
    fseek(file, 0, SEEK_SET); // Ensure we overwrite the file from the beginning
    while (current != NULL) {
        fwrite(current, sizeof(struct book), 1, file);
        current = current->next;
    }

    fclose(file);
}

//*****************************************************************************************************************//

void loadStaffFromFile() {
    FILE* file = openFile("staff.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0) {
        struct staff temp_staff;
        while (fread(&temp_staff, sizeof(struct staff), 1, file)) {
            staff_head = add_staff(staff_head, temp_staff.name, temp_staff.staff_id, temp_staff.department);
        }
    }
    fclose(file);
}

void addStaffToFile() {
    FILE* file = openFile("staff.txt");

    struct staff* new_staff = staff_head;
    fseek(file, 0, SEEK_END);
    while (new_staff != NULL) {
        fprintf(file, "%5d %-99s %-49s\n", new_staff->staff_id, new_staff->name, new_staff->department);
        new_staff = new_staff->next;
    }
    fclose(file);
}

long findStaffPosition(int staff_id) {
    FILE* file = openFile("staff.txt");  // Open the staff file
    fseek(file, 0, SEEK_SET);  // Set file pointer to the beginning
    struct staff temp_staff;  // Assuming 'staff' is the struct type for staff
    long position = 0;

    while (fread(&temp_staff, sizeof(struct staff), 1, file)) {  // Read staff record
        if (temp_staff.staff_id == staff_id) {  // Compare staff id
            fclose(file);
            return position;  // Return the position if found
        }
        position++;
    }
    fclose(file);  // Close file
    return -1;  // Return -1 if not found
}

void deleteStaffInFile(FILE* file, int staffIdToDelete) {
    FILE* tempFile = fopen("temp.txt", "w");  // Create a temporary file to write the updated records
    if (tempFile == NULL) {
        printf("Error: Could not create a temporary file.\n");
        return;
    }

    struct staff tempStaff;
    int found = 0;

    // Read the file and write to the temporary file, skipping the staff to delete
    while (fread(&tempStaff, sizeof(struct staff), 1, file)) {
        if (tempStaff.staff_id != staffIdToDelete) {
            fwrite(&tempStaff, sizeof(struct staff), 1, tempFile);  // Write the staff if not deleted
        } else {
            found = 1;  // Mark as found if the staff matches
        }
    }

    if (!found) {
        printf("Staff member with ID %d not found in the file.\n", staffIdToDelete);
    } else {
        printf("Staff member with ID %d has been deleted from the file.\n", staffIdToDelete);
    }

    fclose(file);  // Close the original file
    fclose(tempFile);  // Close the temporary file

    // Remove the original file and rename the temporary file
    remove("StaffRecords.txt");  // Delete the original file
    rename("temp.txt", "StaffRecords.txt");  // Rename temp file to the original file name
}

void updateStaffInFile(int staff_id, const char* new_name, const char* new_department) {
    // Open the staff file for reading and writing
    FILE* file = fopen("staff.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct staff temp_staff;
    int found = 0;

    // Read the file and update the staff record in memory and file
    while (fread(&temp_staff, sizeof(struct staff), 1, file)) {
        if (temp_staff.staff_id == staff_id) {
            // Update staff in memory
            strncpy(temp_staff.name, new_name, MAX_NAME_LENGTH - 1);
            temp_staff.name[MAX_NAME_LENGTH - 1] = '\0';  // Null-terminate
            strncpy(temp_staff.department, new_department, MAX_DEPT_LENGTH - 1);
            temp_staff.department[MAX_DEPT_LENGTH - 1] = '\0';  // Null-terminate

            // Update the file
            fseek(file, -sizeof(struct staff), SEEK_CUR);  // Move file pointer to the position of the staff record
            fwrite(&temp_staff, sizeof(struct staff), 1, file);  // Write the updated staff record
            printf("Staff member with ID %d updated successfully in file.\n", staff_id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Staff member with ID %d not found in the file.\n", staff_id);
    }

    fclose(file);  // Close the file
}

void saveStaffToFile() {
    FILE* file = openFile("staff.txt");

    struct staff* current = staff_head;  // Assuming staff_head is the start of the linked list
    fseek(file, 0, SEEK_SET); // Ensure we overwrite the file from the beginning

    while (current != NULL) {
        fwrite(current, sizeof(struct staff), 1, file);  // Write each staff record
        current = current->next;  // Move to the next staff
    }

    fclose(file);  // Close the file after writing
}
//***********************************************************************************************************//
void loadBorrowedBookFromFile(void) {
    FILE* file = openFile(BORROWED_BOOKS_FILE);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0) {
        struct borrowedbook temp_borrowed_book;
        while (fread(&temp_borrowed_book, sizeof(struct borrowedbook), 1, file)) {
            borrowedbook_head = add_borrowed_book(borrowedbook_head, temp_borrowed_book.student_id, temp_borrowed_book.book_id, temp_borrowed_book.borrowed_date);
        }
    }

    fclose(file);
    printf("Borrowed books loaded successfully.\n");
}


void save_Borrowed_Book_To_File(){
    FILE* file = openFile(BORROWED_BOOKS_FILE);
    struct borrowedbook* current = borrowedbook_head;  // Assuming borrowedbook_head is the start of the linked list

    fseek(file, 0, SEEK_SET); // Overwrite the file with current data from the linked list

    while (current != NULL) {
        fwrite(current, sizeof(struct borrowedbook), 1, file);  // Write each borrowed book record
        current = current->next;  // Move to the next borrowed book
    }

    fclose(file);  // Close the file after writing
    printf("Borrowed books saved to file successfully.\n");
}
//*******************************************************************************************************************//

// Function to save the returned books list to a file
void save_Retuned_Book_To_File() {
    FILE* file = fopen("returned_books.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving returned books.\n");
        return;
    }

    struct returnedbook* temp = returned_books_head;
    while (temp != NULL) {
        fprintf(file, "%d %d %d %s\n", temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }

    fclose(file);
    printf("Returned books have been saved to the file.\n");
}

// Function to load the returned books list from a file
void loadRetunedBookFromFile() {
    FILE* file = fopen("returned_books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file for loading returned books.\n");
        return;
    }

    // Clear the current list in memory
    struct returnedbook* temp;
    while (returned_books_head != NULL) {
        temp = returned_books_head;
        returned_books_head = returned_books_head->next;
        free(temp);
    }

    // Read records from the file and populate the linked list
    int returned_id, student_id, book_id;
    char returned_date[MAX_DATE_LENGTH];

    while (fscanf(file, "%d %d %d %s", &returned_id, &student_id, &book_id, returned_date) == 4) {
        struct returnedbook* new_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));
        if (new_book == NULL) {
            printf("Memory allocation failed while loading returned books.\n");
            fclose(file);
            return;
        }

        new_book->returned_id = returned_id;
        new_book->student_id = student_id;
        new_book->book_id = book_id;
        strncpy(new_book->returned_date, returned_date, MAX_DATE_LENGTH);
        new_book->next = returned_books_head;  // Insert at the head of the list
        returned_books_head = new_book;
    }

    fclose(file);
    printf("Returned books have been loaded from the file.\n");
}
