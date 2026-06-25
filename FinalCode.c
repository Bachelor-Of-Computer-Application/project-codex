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
