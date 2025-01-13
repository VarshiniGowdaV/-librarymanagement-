#ifndef ADMIN_H
#define ADMIN_H

int authenticate_user(const char *correct_username, const char *correct_password, const char *role);
int authenticate_admin();
#endif
