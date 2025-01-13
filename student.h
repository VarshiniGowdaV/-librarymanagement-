
#ifndef STUDENT_H
#define STUDENT_H
#define RECORD_SIZE 256
#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50
// Define the student structure
struct student {
    int student_id;             // Changed to student_id
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    char status;
    struct student* next;
};
extern struct student* student_head;

struct student* add_student(struct student* head, const char* name, int student_id, const char* department);
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department);
void view_students(struct student* head);
void delete_student(struct student* head, int student_id);
struct student* search_student(struct student* head, int student_id);
void sortStudentsByID();
void sortStudentsByName();
void searchStudentById(int id);
int getTotalStudentCount();
#endif // STUDENT_H
