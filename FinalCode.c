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
	int i,j;
    FILE *fp = fopen("bankdata.txt", "w");

    if (fp == NULL)
        return;

    fprintf(fp, "%d\n", userCount);

    for ( i = 0; i < userCount; i++) {

        fprintf(fp, "%s\n", users[i].username);
        fprintf(fp, "%s\n", users[i].password);
        fprintf(fp, "%.2f\n", users[i].balance);
        fprintf(fp, "%d\n", users[i].transCount);

        for ( j = 0; j < users[i].transCount; j++) {
            fprintf(fp, "%.2f\n", users[i].history[j]);
        }
    }
    printf("Data saved!\n");
    fclose(fp);
}

void loadData() {
	int i,j;
    FILE *fp = fopen("bankdata.txt", "r");

    if (fp == NULL)
        return;

    fscanf(fp, "%d", &userCount);

    for ( i = 0; i < userCount; i++) {

        fscanf(fp, "%s", users[i].username);
        fscanf(fp, "%s", users[i].password);
        fscanf(fp, "%f", &users[i].balance);
        fscanf(fp, "%d", &users[i].transCount);

        for ( j = 0; j < users[i].transCount; j++) {
            fscanf(fp, "%f", &users[i].history[j]);
        }
    }

    fclose(fp);
}
void signUp() {
	int i;
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
    for ( i = 0; i < userCount; i++) {
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
	int i;
    clearScreen();
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    for (i = 0; i < userCount; i++) {
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
void addBalance(int index) {
    float amount;
    clearScreen();
    printf("Enter amount to add: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    users[index].balance += amount;
    if (users[index].transCount < MAX_TRANS) {
        users[index].history[
            users[index].transCount
        ] = amount;
        users[index].transCount++;
        saveData();
    }
    printf("\nBalance updated successfully!\n");
    printf("Current Balance: %.2f\n",
           users[index].balance);
    pauseScreen();
    clearScreen();
}
void checkBalance(int index) {
    clearScreen();
    printf("\n===== ACCOUNT BALANCE =====\n");
    printf("Current Balance: %.2f\n",
           users[index].balance);
    pauseScreen();
    clearScreen();
}
void viewHistory(int index) {
	int i;
    clearScreen();
    printf("\n===== TRANSACTION HISTORY =====\n");
    if (users[index].transCount == 0) {
        printf("No transactions available.\n");
    }
    else {
        for (i = 0;i < users[index].transCount; i++) {
            printf("%d. Added %.2f\n",
                   i + 1,
                   users[index].history[i]);
        }
    }
    pauseScreen();
    clearScreen();
}
void changePassword(int index) {
    char oldPass[50];
    char newPass[50];
    clearScreen();
    printf("Enter current password: ");
    scanf("%s", oldPass);
    if (strcmp(users[index].password, oldPass) != 0) {
        printf("\nIncorrect password!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    printf("Enter new password: ");
    scanf("%s", newPass);
    strcpy(users[index].password, newPass);
    saveData();
    printf("\nPassword changed successfully!\n");
    pauseScreen();
    clearScreen();
}
int deleteAccount(int index) {
	int i;
    char confirm;
    clearScreen();
    printf("Are you sure you want to delete your account? (Y/N): ");
    scanf(" %c", &confirm);
    if (confirm != 'Y' &&
        confirm != 'y') {
        printf("\nAccount deletion cancelled.\n");
        pauseScreen();
        clearScreen();
        return 0;
    }
    for ( i = index;i < userCount - 1;i++) {

        users[i] = users[i + 1];
    }
    userCount--;
    saveData();
    printf("\nAccount deleted successfully!\n");
    pauseScreen();
    clearScreen();
    return 1;
}
void userMenu(int index) {
    int choice;
    while (1) {
        clearScreen();
        printf("===== USER MENU =====\n");
        printf("1. Add Balance\n");
        printf("2. Check Balance\n");
        printf("3. View History\n");
        printf("4. Change Password\n");
        printf("5. Delete Account\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBalance(index);
                break;
            case 2:
                checkBalance(index);
                break;
            case 3:
                viewHistory(index);
                break;
            case 4:
                changePassword(index);
                break;
            case 5:
                if (deleteAccount(index)) {
                    return;
                }
                break;
            case 6:
                printf("\nLogging out...\n");
                pauseScreen();
                clearScreen();
                return;
            default:
                printf("\nInvalid choice!\n");
                pauseScreen();
                clearScreen();
        }
    }
}
int main() {
	    loadData();
    int choice;
    while (1) {
        clearScreen();
        printf("===== SIMPLE BANKING SYSTEM =====\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                signUp();
                break;
            case 2: {
                int index = login();
                if (index != -1) {
                    userMenu(index);
                }
                break;
            }
            case 3:
                clearScreen();
                printf("Thank you for using the banking system.\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
                pauseScreen();
        }
    }
    return 0;
}
