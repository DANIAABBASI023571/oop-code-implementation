#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Account {

private:

    int accountNumber;
    static int nextAccountNumber;

    string accountType;
    double balance;

    vector<string> history;

    double profitRate;
    double overdraftLimit;
    double overdraftFee;
    double withdrawalLimit;
    
    string convertAmount(double amount) const {

        stringstream ss;
        ss << amount;

        return ss.str();
    }

public:
    Account(string type, double amount) {

        accountNumber = nextAccountNumber++;

        accountType = type;
        balance = amount;

        profitRate = 0.05;
        overdraftLimit = 10000;
        overdraftFee = 500;
        withdrawalLimit = 5000;

        history.push_back(
            "Account opened with Rs. " + convertAmount(amount)
        );
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    string getAccountType() const {
        return accountType;
    }

    void deposit(double amount) {

        if (amount <= 0) {

            cout << "Invalid deposit amount!" << endl;
            return;
        }

        balance = balance + amount;

        history.push_back(
            "Deposited Rs. " + convertAmount(amount)
        );

        cout << "Deposit successful!" << endl;
    }
    
    void withdraw(double amount) {

        if (amount <= 0) {

            cout << "Invalid withdrawal amount!" << endl;
            return;
        }

        if (accountType == "Saving") {

            if (amount > balance) {

                cout << "Insufficient balance!" << endl;
                return;
            }

            balance = balance - amount;
        }

        else if (accountType == "Current") {

            double newBalance = balance - amount;

            if (newBalance < 0) {

                newBalance = newBalance - overdraftFee;
            }

            if (newBalance < -overdraftLimit) {

                cout << "Overdraft limit exceeded!" << endl;
                return;
            }

            balance = newBalance;

            if (balance < 0) {

                history.push_back(
                    "Overdraft fee charged: Rs. " +
                    convertAmount(overdraftFee)
                );

                cout << "Overdraft fee charged!" << endl;
            }
        }
        else if (accountType == "Student") {

            if (amount > withdrawalLimit) {

                cout << "Maximum withdrawal limit is Rs. "
                     << withdrawalLimit << endl;

                return;
            }

            if (amount > balance) {

                cout << "Insufficient balance!" << endl;
                return;
            }

            balance = balance - amount;
        }

        history.push_back(
            "Withdrawn Rs. " + convertAmount(amount)
        );

        cout << "Withdrawal successful!" << endl;
    }
    
    void applyProfit() {

        if (accountType == "Saving") {

            double profit = balance * profitRate;

            balance = balance + profit;

            history.push_back(
                "Profit added: Rs. " + convertAmount(profit)
            );

            cout << "Profit added successfully!" << endl;
            cout << "Profit: Rs. " << profit << endl;
        }

        else {

            cout << "Profit is only for Saving Account!" << endl;
        }
    }

    void printStatement() const {

        cout << "\n========== ACCOUNT STATEMENT ==========" << endl;

        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: Rs. " << balance << endl;

        cout << "\nTransaction History:" << endl;

        for (int i = 0; i < (int)history.size(); i++) {

            cout << i + 1 << ". " << history[i] << endl;
        }

        cout << "=======================================" << endl;
    }
};

int Account::nextAccountNumber = 1001;

class Customer {

private:

    string name;
    string phone;

    vector<Account> accounts;

public:

    Customer(string n, string p) {

        name = n;
        phone = p;
    }

    string getName() const {
        return name;
    }

    void openAccount(string type, double amount) {

        if (amount < 0) {

            cout << "Invalid opening balance!" << endl;
            return;
        }

        Account newAccount(type, amount);

        accounts.push_back(newAccount);

        cout << "\nAccount opened successfully!" << endl;

        cout << "Account Number: "
             << accounts.back().getAccountNumber() << endl;
    }

    void depositToAccount(int number, double amount) {

        for (int i = 0; i < (int)accounts.size(); i++) {

            if (accounts[i].getAccountNumber() == number) {

                accounts[i].deposit(amount);
                return;
            }
        }

        cout << "Account not found!" << endl;
    }

    void withdrawFromAccount(int number, double amount) {

        for (int i = 0; i < (int)accounts.size(); i++) {

            if (accounts[i].getAccountNumber() == number) {

                accounts[i].withdraw(amount);
                return;
            }
        }

        cout << "Account not found!" << endl;
    }

    void printAccountStatement(int number) const {

        for (int i = 0; i < (int)accounts.size(); i++) {

            if (accounts[i].getAccountNumber() == number) {

                accounts[i].printStatement();
                return;
            }
        }

        cout << "Account not found!" << endl;
    }

    void displayAccounts() const {

        cout << "\nCustomer Name: " << name << endl;
        cout << "Phone: " << phone << endl;

        if (accounts.empty()) {

            cout << "No accounts found!" << endl;
            return;
        }

        cout << "\nCustomer Accounts:" << endl;

        for (int i = 0; i < (int)accounts.size(); i++) {

            cout << "\nAccount Number: "
                 << accounts[i].getAccountNumber() << endl;

            cout << "Account Type: "
                 << accounts[i].getAccountType() << endl;

            cout << "Balance: Rs. "
                 << accounts[i].getBalance() << endl;
        }
    }

    void closeAccount(int number) {

        for (int i = 0; i < (int)accounts.size(); i++) {

            if (accounts[i].getAccountNumber() == number) {

                accounts.erase(accounts.begin() + i);

                cout << "Account closed successfully!" << endl;
                cout << "Transaction history removed!" << endl;

                return;
            }
        }

        cout << "Account not found!" << endl;
    }

    void applySavingProfit() {

        for (int i = 0; i < (int)accounts.size(); i++) {

            accounts[i].applyProfit();
        }
    }
};

int main() {
    Customer customer("Dania", "03001234567");

    int choice;

    do {

        cout << "\n\n======= BANK ACCOUNT MANAGEMENT =======" << endl;

        cout << "\n1. Teller Menu" << endl;
        cout << "2. Open New Account" << endl;
        cout << "3. Display Customer Accounts" << endl;
        cout << "4. Close Account" << endl;
        cout << "5. Apply Saving Profit" << endl;
        cout << "6. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {

                int tellerChoice;
                int number;
                double amount;

                cout << "\n========== TELLER MENU ==========" << endl;

                cout << "1. Deposit Money" << endl;
                cout << "2. Withdraw Money" << endl;
                cout << "3. Print Account Statement" << endl;

                cout << "\nEnter choice: ";
                cin >> tellerChoice;

                if (tellerChoice == 1) {

                    cout << "Enter Account Number: ";
                    cin >> number;

                    cout << "Enter Deposit Amount: ";
                    cin >> amount;

                    customer.depositToAccount(number, amount);
                }

                else if (tellerChoice == 2) {

                    cout << "Enter Account Number: ";
                    cin >> number;

                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;

                    customer.withdrawFromAccount(number, amount);
                }

                else if (tellerChoice == 3) {

                    cout << "Enter Account Number: ";
                    cin >> number;

                    customer.printAccountStatement(number);
                }

                else {

                    cout << "Invalid teller choice!" << endl;
                }

                break;
            }

            case 2: {

                int type;
                double amount;

                cout << "\nSelect Account Type:" << endl;

                cout << "1. Saving Account" << endl;
                cout << "2. Current Account" << endl;
                cout << "3. Student Account" << endl;

                cout << "Enter account type: ";
                cin >> type;

                cout << "Enter opening balance: ";
                cin >> amount;

                if (type == 1) {

                    customer.openAccount("Saving", amount);
                }

                else if (type == 2) {

                    customer.openAccount("Current", amount);
                }

                else if (type == 3) {

                    customer.openAccount("Student", amount);
                }

                else {

                    cout << "Invalid account type!" << endl;
                }

                break;
            }
            case 3: {

                customer.displayAccounts();
                break;
            }
            case 4: {

                int number;

                cout << "Enter Account Number to close: ";
                cin >> number;

                customer.closeAccount(number);

                break;
            }
            case 5: {

                customer.applySavingProfit();
                break;
            }
            case 6: {

                cout << "Thank you for using our bank system!" << endl;
                break;
            }
            default: {

                cout << "Invalid choice!" << endl;
            }
        }

    } while (choice != 6);

    return 0;
}
