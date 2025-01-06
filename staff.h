#ifndef STAFF_H
#define STAFF_H

// Define the staff struct
struct staff {
    int staff_id;
    char staff_name[100];
    char department[50];
    char position[50];
    struct staff* next;
};

// Function declarations
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position);
void delete_staff(struct staff* head, int id);
void update_staff(struct staff* head, int id);
struct staff* search_staff(struct staff* head, int id);
void view_staff(struct staff* head);
int count_staff(struct staff* head);

#endif // STAFF_H
