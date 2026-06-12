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
    printf("Account created successfully!\n");
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

void addBalance(int index) {
    float amount;
    printf("Enter amount to add: ");
    scanf("%f", &amount);
    users[index].balance += amount;
    printf("Balance updated successfully!\n");
}

void checkBalance(int index) {
    printf("Your current balance: %.2f\n", users[index].balance);
}

void userMenu(int index) {
    int choice;
    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. Add Balance\n");
        printf("2. Check Balance\n");
        printf("3. Logout\n");
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
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Simple Banking System =====\n");
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
                printf("Thank you for using the bank system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
