#include <stdio.h>
#include <string.h>
#define MAX 100
struct User {
    char username[50];
    char password[50];
    float balance;
};

struct User users[MAX];
int userCount = 0;

void signUp() {
    struct User u;
    printf("Enter username: ");
    scanf("%s", u.username);
    printf("Enter password: ");
    scanf("%s", u.password);
    u.balance = 0;
    users[userCount] = u;
    userCount++;
    printf("Account created successfully!!\n");
}

int login() {
    char username[50], password[50];
    int i;
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return i;
        }
    }
    printf("Invalid username or password.\n");
    return -1;
}

