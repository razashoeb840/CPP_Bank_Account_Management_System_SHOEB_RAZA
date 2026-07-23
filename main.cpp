#include "CurrentAccount.h"
#include "SavingsAccount.h"

#include <iostream>
#include <limits>
#include <memory>
#include <vector>

Account* findAccount(std::vector<std::unique_ptr<Account>>& accounts, int accountNumber) {
    for (const auto& account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return account.get();
        }
    }

    return nullptr;
}

void clearInvalidInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInvalidInput();
            return value;
        }

        std::cout << "Please enter a valid number.\n";
        clearInvalidInput();
    }
}

double readDouble(const std::string& prompt) {
    double value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInvalidInput();
            return value;
        }

        std::cout << "Please enter a valid amount.\n";
        clearInvalidInput();
    }
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void showMenu() {
    std::cout << "\n===== BANK MENU =====\n"
              << "1 Create Savings Account\n"
              << "2 Create Current Account\n"
              << "3 Deposit\n"
              << "4 Withdraw\n"
              << "5 Transfer\n"
              << "6 Show Details\n"
              << "7 Transaction History\n"
              << "8 Add Interest\n"
              << "0 Exit\n";
}

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    int choice;

    do {
        showMenu();
        choice = readInt("Enter choice: ");

        if (choice == 1 || choice == 2) {
            int number = readInt("Enter Number: ");

            if (findAccount(accounts, number)) {
                std::cout << "Account number already exists.\n";
                continue;
            }

            std::string name = readLine("Name: ");
            double balance = readDouble("Balance: ");

            if (choice == 1) {
                double interest = readDouble("Interest: ");
                accounts.push_back(std::make_unique<SavingsAccount>(number, name, balance, interest));
                std::cout << "Savings account created successfully.\n";
            } else {
                double overdraft = readDouble("Overdraft Limit: ");
                accounts.push_back(std::make_unique<CurrentAccount>(number, name, balance, overdraft));
                std::cout << "Current account created successfully.\n";
            }
        } else if (choice == 3) {
            int number = readInt("Enter Account Number: ");
            Account* account = findAccount(accounts, number);

            if (!account) {
                std::cout << "Account not found.\n";
                continue;
            }

            double amount = readDouble("Deposit Amount: ");
            account->deposit(amount);
        } else if (choice == 4) {
            int number = readInt("Enter Account Number: ");
            Account* account = findAccount(accounts, number);

            if (!account) {
                std::cout << "Account not found.\n";
                continue;
            }

            double amount = readDouble("Withdraw Amount: ");
            account->withdraw(amount);
        } else if (choice == 5) {
            int senderNumber = readInt("Sender Account Number: ");
            int receiverNumber = readInt("Receiver Account Number: ");
            Account* sender = findAccount(accounts, senderNumber);
            Account* receiver = findAccount(accounts, receiverNumber);

            if (!sender || !receiver) {
                std::cout << "Sender or receiver account not found.\n";
                continue;
            }

            double amount = readDouble("Transfer Amount: ");
            sender->transfer(*receiver, amount);
        } else if (choice == 6) {
            int number = readInt("Enter Account Number: ");
            Account* account = findAccount(accounts, number);

            if (account) {
                account->showDetails();
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 7) {
            int number = readInt("Enter Account Number: ");
            Account* account = findAccount(accounts, number);

            if (account) {
                account->showTransactionHistory();
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 8) {
            int number = readInt("Enter Savings Account Number: ");
            Account* account = findAccount(accounts, number);
            SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(account);

            if (savingsAccount) {
                savingsAccount->addInterest();
            } else {
                std::cout << "Savings account not found.\n";
            }
        } else if (choice != 0) {
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    std::cout << "Thank you for using the Bank Account Management System.\n";
    return 0;
}
