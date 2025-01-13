#ifndef FILEHANDING_H
#define FILEHANDING_H
#include "student.h"
#include "book.h"
#include "staff.h"
#include "student.h"
#include "borrowedbook.h"

extern FILE* studentFile;


void openStudentFileForReadingWriting();
void closeStudentFile();
void serializeStudentRecord(const struct student* student, char *buffer);
void deserializeStudentRecord(const char *buffer, struct student *student);
void loadStudentsFromFile();
void writeStudentsToFile();
void addStudentToFile();
void deleteStudentInFile(FILE *file, int studentIdToDelete);
long findStudentPosition();
void save_student_to_file();

//static FILE* openFile(const char* filename);
void loadBooksFromFile();
void writeBookstoFile();
void addBooksToFile();
void deleteBooksInFile();
long findBooksPosition();
void updateBooksInFile(int book_id, const char* new_title, const char* new_author, int new_total_copies);
void save_Book_To_File();

void loadStaffFromfile();
void writeStaffToFile();
void addStaffToFile();
void deleteStaffInFile(FILE* file, int staffIdToDelete);
long findStaffPosition();
void updateStaffInFile();
void saveStaffToFile(void);

void loadBorrowedBookFromFile();
void save_Borrowed_Book_To_File();

void loadRetunedBookFromFile();
void save_Retuned_Book_To_File();

#endif // FILEHANDING_H
