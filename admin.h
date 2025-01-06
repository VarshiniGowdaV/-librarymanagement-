#ifndef ADMIN_H
#define ADMIN_H

// Function prototypes
int authenticate_user(const char *correct_username, const char *correct_password, const char *role);
int authenticate_admin();
int authenticate_staff();
int authenticate_student();

#endif
