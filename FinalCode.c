#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define MAX_TRANS 50
#define CLEAR "cls"
struct User {
    char username[50];
    char password[50];
    float balance;
    float history[MAX_TRANS];
    int transCount;
};
struct User users[MAX];
int userCount = 0;
void saveData();
void loadData();
void clearScreen() {
    system(CLEAR);
}
void pauseScreen() {
    system("pause");
}
void saveData() {
    FILE *fp = fopen("bankdata.txt", "w");

    if (fp == NULL)
        return;

    fprintf(fp, "%d\n", userCount);

    for (int i = 0; i < userCount; i++) {

        fprintf(fp, "%s\n", users[i].username);
        fprintf(fp, "%s\n", users[i].password);
        fprintf(fp, "%.2f\n", users[i].balance);
        fprintf(fp, "%d\n", users[i].transCount);

        for (int j = 0; j < users[i].transCount; j++) {
            fprintf(fp, "%.2f\n", users[i].history[j]);
        }
    }
    printf("Data saved!\n");
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("bankdata.txt", "r");

    if (fp == NULL)
        return;

    fscanf(fp, "%d", &userCount);

    for (int i = 0; i < userCount; i++) {

        fscanf(fp, "%s", users[i].username);
        fscanf(fp, "%s", users[i].password);
        fscanf(fp, "%f", &users[i].balance);
        fscanf(fp, "%d", &users[i].transCount);

        for (int j = 0; j < users[i].transCount; j++) {
            fscanf(fp, "%f", &users[i].history[j]);
        }
    }

    fclose(fp);
}
void signUp() {
    clearScreen();
    if (userCount >= MAX) {
        printf("User limit reached!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    struct User u;
    printf("Enter username: ");
    scanf("%s", u.username);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, u.username) == 0) {
            printf("\nUsername already exists!\n");
            pauseScreen();
            clearScreen();
            return;
        }
    }
    printf("Enter password: ");
    scanf("%s", u.password);
    u.balance = 0;
    u.transCount = 0;
    users[userCount] = u;
    userCount++;
    saveData();
    printf("\nAccount created successfully!\n");
    pauseScreen();
    clearScreen();
}
int login() {
    clearScreen();
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            printf("\nLogin successful!\n");
            pauseScreen();
            clearScreen();
            return i;
        }
    }
    printf("\nInvalid username or password!\n");
    pauseScreen();
    clearScreen();
    return -1;
}
