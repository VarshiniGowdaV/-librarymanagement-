#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50

struct student {
    int student_id;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    struct student* next;
};

// Function declarations
struct student* create_student_node(const char* name, int student_id, const char* dept);
struct student* add_student(struct student* head, const char* name, int student_id, const char* department);
void delete_student(struct student* head, int student_id);
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department);
struct student* search_student(struct student* head, int student_id);
void view_students(struct student* head);
int count_students(struct student* head);

#endif
