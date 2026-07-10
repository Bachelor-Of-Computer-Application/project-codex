#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define MAX_TRANS 50
#define CLEAR "cls"
#define P "\t\t\t\t\t\t"
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
    printf(P"Press any key to continue . . . ");
    fflush(stdout);
    getch();        
    printf("\n");
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
    printf(P"Data saved!\n");
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
        printf("\n"P"User limit reached!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    struct User u;
    printf(P"Enter username: ");
    scanf("%s", u.username);
    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, u.username) == 0) {
            printf("\n"P"Username already exists!\n");
            pauseScreen();
            clearScreen();
            return;
        }
    }
    printf(P"Enter password: ");
    scanf("%s", u.password);
    u.balance = 0;
    u.transCount = 0;
    users[userCount] = u;
    userCount++;
    saveData();
    printf("\n"P"Account created successfully!\n");
    pauseScreen();
    clearScreen();
}
int login() {
	int i;
    clearScreen();
    char username[50];
    char password[50];
    printf(P"Enter username: ");
    scanf("%s", username);
    printf(P"Enter password: ");
    scanf("%s", password);
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
           printf("\n"P"Login successful!\n");
            pauseScreen();
            clearScreen();
            return i;
        }
    }
    printf("\n"P"Invalid username or password!\n");
    pauseScreen();
    clearScreen();
    return -1;
}
void addBalance(int index) {
    float amount;
    clearScreen();
    printf(P"Enter amount to add: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf(P"Invalid amount!\n");
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
    printf("\n"P"Balance updated successfully!\n");
    printf(P"Current Balance: %.2f\n",
           users[index].balance);
    pauseScreen();
    clearScreen();
}
void checkBalance(int index) {
    clearScreen();
    printf("\n"P"===== ACCOUNT BALANCE =====\n");
    printf(P"Current Balance: %.2f\n",
           users[index].balance);
    pauseScreen();
    clearScreen();
}
void viewHistory(int index) {
	int i;
    clearScreen();
    printf("\n"P"===== TRANSACTION HISTORY =====\n");
    if (users[index].transCount == 0) {
        printf(P"No transactions available.\n");
    }
    else {
        for (i = 0;i < users[index].transCount; i++) {
            printf(P"%d. Added %.2f\n",
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
    printf(P"Enter current password: ");
    scanf("%s", oldPass);
    if (strcmp(users[index].password, oldPass) != 0) {
        printf("\n"P"Incorrect password!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    printf(P"Enter new password: ");
    scanf("%s", newPass);
    strcpy(users[index].password, newPass);
    saveData();
    printf("\n"P"Password changed successfully!\n");
    pauseScreen();
    clearScreen();
}
int deleteAccount(int index) {
	int i;
    char confirm;
    clearScreen();
    printf(P"Are you sure you want to delete your account? (Y/N): ");
    scanf(" %c", &confirm);
    if (confirm != 'Y' &&
        confirm != 'y') {
        printf("\n"P"Account deletion cancelled.\n");
        pauseScreen();
        clearScreen();
        return 0;
    }
    for ( i = index;i < userCount - 1;i++) {

        users[i] = users[i + 1];
    }
    userCount--;
    saveData();
    printf("\n"P"Account deleted successfully!\n");
    pauseScreen();
    clearScreen();
    return 1;
}
void userMenu(int index) {
    int choice;
    while (1) {
        clearScreen();
        printf(P"===== USER MENU =====\n");
        printf(P"1. Add Balance\n");
        printf(P"2. Check Balance\n");
        printf(P"3. View History\n");
        printf(P"4. Change Password\n");
        printf(P"5. Delete Account\n");
        printf(P"6. Logout\n");
        printf(P"Enter choice: ");
        scanf(P"%d", &choice);
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
                printf("\n"P"Logging out...\n");
                pauseScreen();
                clearScreen();
                return;
            default:
                printf("\n"P"Invalid choice!\n");
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
        printf(P"===== SIMPLE BANKING SYSTEM =====\n");
        printf(P"1. Sign Up\n");
        printf(P"2. Login\n");
        printf(P"3. Exit\n");
        printf(P"Enter choice: ");
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
                printf(P"Thank you for using the banking system.\n");
                printf(P"Goodbye!\n");
                return 0;
            default:
                printf("\n"P"Invalid choice!\n");
                pauseScreen();
        }
    }
    return 0;
}
