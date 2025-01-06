#include <stdio.h>
#include <string.h>
#include "admin.h"

int authenticate_user(const char *correct_username, const char *correct_password, const char *role)
{
    char entered_username[50];
    char entered_password[50];

    printf("%s Login\n", role);
    printf("Enter username: ");
    scanf("%s", entered_username);
    printf("Enter password: ");
    scanf("%s", entered_password);

    if (strcmp(entered_username, correct_username) == 0 && strcmp(entered_password, correct_password) == 0)
    {
        printf("Login successful.\n");
        return 1;
    }
    else
    {
        printf("Invalid username or password.\n");
        return 0;
    }
}

int authenticate_admin()
{
    const char *correct_username = "admin";
    const char *correct_password = "password123";
    return authenticate_user(correct_username, correct_password, "Admin");
}

int authenticate_staff()
{
    const char *correct_username = "staff";
    const char *correct_password = "staff123";
    return authenticate_user(correct_username, correct_password, "Staff");
}

int authenticate_student()
{
    const char *correct_username = "student";
    const char *correct_password = "student123";
    return authenticate_user(correct_username, correct_password, "Student");
}
