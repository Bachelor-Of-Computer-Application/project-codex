#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
 
using namespace std;
 
// Structure to store account details
struct Account {
    string username;
    string password;
    double balance;
};
 
// Map to store accounts (in real app, use database)
map<string, Account> accounts;
 
// Function declarations
void saveAccounts();
void loadAccounts();
void registerAccount();
void login();
void deposit(const string& username);
void withdraw(const string& username);
void checkBalance(const string& username);
void displayMenu();
 
// Load accounts from file
void loadAccounts() {
    ifstream infile("accounts.txt");
    if (infile.is_open()) {
        Account acc;
        while (infile >> acc.username >> acc.password >> acc.balance) {
            accounts[acc.username] = acc;
        }
        infile.close();
    }
}
 
// Save accounts to file
void saveAccounts() {
    ofstream outfile("accounts.txt");
    for (auto& pair : accounts) {
        outfile << pair.second.username << " "
                << pair.second.password << " "
                << fixed << setprecision(2) << pair.second.balance << "\n";
    }
    outfile.close();
}
 
// Register new account
void registerAccount() {
    string username, password;
    cout << "\n===== Register New Account =====\n";
    cout << "Enter username: ";
    cin >> username;
 
    // Check if username already exists
    if (accounts.find(username) != accounts.end()) {
        cout << "Username already exists! Please choose another.\n";
        return;
    }
 
    cout << "Enter password: ";
    cin >> password;
 
    Account newAccount = {username, password, 0.0};
    accounts[username] = newAccount;
    saveAccounts();
    cout << "Account registered successfully!\n";
}
 
// User login
void login() {
    string username, password;
    cout << "\n===== Login =====\n";
    cout << "Enter username: ";
    cin >> username;
 
    if (accounts.find(username) == accounts.end()) {
        cout << "Username not found!\n";
        return;
    }
 
    cout << "Enter password: ";
    cin >> password;
 
    if (accounts[username].password != password) {
        cout << "Incorrect password!\n";
        return;
    }
 
    cout << "Login successful! Welcome " << username << "!\n";
 
    // Display menu after successful login
    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1:
                checkBalance(username);
                break;
            case 2:
                deposit(username);
                break;
            case 3:
                withdraw(username);
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
 
// Display account menu
void displayMenu() {
    cout << "\n===== Account Menu =====\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Logout\n";
}
 
// Check balance
void checkBalance(const string& username) {
    cout << "\n===== Check Balance =====\n";
    cout << "Current Balance: Rs. " << fixed << setprecision(2)
         << accounts[username].balance << "\n";
}
 
// Deposit money
void deposit(const string& username) {
    double amount;
    cout << "\n===== Deposit Money =====\n";
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;
 
    if (amount <= 0) {
        cout << "Invalid amount! Amount must be positive.\n";
        return;
    }
 
    accounts[username].balance += amount;
    saveAccounts();
    cout << "Deposit successful!\n";
    cout << "New Balance: Rs. " << fixed << setprecision(2)
         << accounts[username].balance << "\n";
}
 
// Withdraw money
void withdraw(const string& username) {
    double amount;
    cout << "\n===== Withdraw Money =====\n";
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;
 
    if (amount <= 0) {
        cout << "Invalid amount! Amount must be positive.\n";
        return;
    }
 
    if (amount > accounts[username].balance) {
        cout << "Insufficient balance!\n";
        cout << "Current Balance: Rs. " << fixed << setprecision(2)
             << accounts[username].balance << "\n";
        return;
    }
 
    accounts[username].balance -= amount;
    saveAccounts();
    cout << "Withdrawal successful!\n";
    cout << "Remaining Balance: Rs. " << fixed << setprecision(2)
         << accounts[username].balance << "\n";
}
 
// Main function
int main() {
    loadAccounts();
    int choice;
 
    while (true) {
        cout << "\n============================================\n";
        cout << "      Welcome to Simple Banking System\n";
        cout << "============================================\n";
        cout << "1. Login\n";
        cout << "2. Register New Account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                cout << "Thank you for using our banking system!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
 
    return 0;
}