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
