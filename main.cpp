#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Transaction {
public:
  Transaction(double amount, double balance)
      : transaction_date(time(0)), transaction_amount(amount),
        balance_snapshot(balance) {}
  virtual void print() const {
    std::cout << "Transaction Date: " << asctime(localtime(&transaction_date))
              << "Amount: " << transaction_amount
              << " Balance: " << balance_snapshot << std::endl;
  }

protected:
  time_t transaction_date;
  double transaction_amount;
  double balance_snapshot;
};

class Account {
public:
  Account(const std::string &id, const std::string &name)
      : account_id(id), customer_name(name), balance(0) {}

  virtual void deposit(double amount) = 0;
  virtual void withdraw(double amount) = 0;
  double get_balance() const { return balance; }
  virtual void print_summary() const = 0;
  virtual void print_statement() const {
    print_summary();
    std::cout << "Transactions: \n";
    for (const auto &transaction : transaction_list) {
      transaction->print();
    }
  }

public:
  std::string account_id;
  std::string customer_name;
  double balance;
  std::vector<std::shared_ptr<Transaction>> transaction_list;
};

class CheckingAccount : public Account {
public:
  CheckingAccount(const std::string &id, const std::string &name)
      : Account(id, name) {}

  void deposit(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid deposit amount." << std::endl;
      return;
    }
    balance += amount;
    transaction_list.push_back(std::make_shared<Transaction>(amount, balance));
  }

  void withdraw(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid withdrawl amount." << std::endl;
      return;
    }
    balance -= amount;
    transaction_list.push_back(std::make_shared<Transaction>(-amount, balance));
  }

  void print_summary() const override {
    std::cout << "Checking Account - ID: " << account_id
              << " Name: " << customer_name << " Balance: " << balance
              << " Transactions: " << transaction_list.size() << std::endl;
  }
};

class SavingsAccount : public Account {
public:
  SavingsAccount(const std::string &id, const std::string &name,
                 double interest_rate, double deposit_bonus,
                 double withdrawal_penalty)
      : Account(id, name), interest_rate(interest_rate),
        deposit_bonus(deposit_bonus), withdrawal_penalty(withdrawal_penalty) {}
  void deposit(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid deposit amount." << std::endl;
      return;
    }
    balance += amount + deposit_bonus;
    transaction_list.push_back(
        std::make_shared<Transaction>(amount + deposit_bonus, balance));
  }

  void withdraw(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid withdrawal amount." << std::endl;
      return;
    }
    balance -= amount + withdrawal_penalty;
    transaction_list.push_back(
        std::make_shared<Transaction>(-(amount + withdrawal_penalty), balance));
  }

  void print_summary() const override {
    std::cout << "Savings Account - ID: " << account_id
              << " Name: " << customer_name << " Balance: " << balance
              << " Transactions: " << transaction_list.size() << std::endl;
  }

private:
  double interest_rate;
  double deposit_bonus;
  double withdrawal_penalty;
};

class BusinessAccount : public Account {
public:
  BusinessAccount(const std::string &id, const std::string &name,
                  const std::string &business_name, double transaction_cost)
      : Account(id, name), business_name(business_name),
        transaction_cost(transaction_cost) {}

  void deposit(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid deposit amount." << std::endl;
      return;
    }
    balance += amount - transaction_cost;
    transaction_list.push_back(
        std::make_shared<Transaction>(amount - transaction_cost, balance));
  }

  void withdraw(double amount) override {
    if (amount <= 0) {
      std::cout << "Invalid withdrawal amount." << std::endl;
      return;
    }
    balance -= amount + transaction_cost;
    transaction_list.push_back(
        std::make_shared<Transaction>(-(amount + transaction_cost), balance));
  }
  void print_summary() const override {
    std::cout << "Business Account - ID: " << account_id
              << " Name: " << customer_name
              << " Business Name: " << business_name << " Balance: " << balance
              << " Transactions: " << transaction_list.size() << std::endl;
  }

private:
  std::string business_name;
  double transaction_cost;
};

class Bank {
public:
  void create_account(const std::string &type, const std::string &id,
                      const std::string &name) {
    if (type == "checking") {
      accounts.push_back(std::make_shared<CheckingAccount>(id, name));
    } else if (type == "savings") {
      accounts.push_back(
          std::make_shared<SavingsAccount>(id, name, 0.01, 0.10, 0.50));
    } else if (type == "business") {
      accounts.push_back(
          std::make_shared<BusinessAccount>(id, name, name + " Inc.", 0.50));
    } else {
      std::cout << "Invalid account type." << std::endl;
    }
  }

  void list_accounts() const {
    for (size_t i = 0; i < accounts.size(); ++i) {
      std::cout << i + 1 << ". " << accounts[i]->get_balance() << std::endl;
    }
  }

  std::shared_ptr<Account> get_account(size_t index) const {
    if (index < accounts.size()) {
      return accounts[index];
    }
    return nullptr;
  }

  void load_accounts(const std::string &filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
      std::cout << "Unable to open file: " << filename << std::endl;
      return;
    }
    std::string line;
    while (std::getline(input_file, line)) {
      std::istringstream iss(line);
      std::string type, id, name;
      iss >> type >> id >> name;

      create_account(type, id, name);
    }

    input_file.close();
  }

  void save_accounts(const std::string &filename) const {
    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
      std::cout << "Unable to open file: " << filename << std::endl;
      return;
    }

    for (const auto &account : accounts) {
      char type_char = account->account_id[0];
      std::string type;
      if (type_char == 'C' || type_char == 'c')
        type = "checking";
      else if (type_char == 'S' || type_char == 's')
        type = "savings";
      else if (type_char == 'B' || type_char == 'b')
        type = "business";
      else {
        std::cout << "Unknown account type: " << type_char << std::endl;
        continue;
      }

      output_file << type << " " << account->account_id << " "
                  << account->customer_name << std::endl;
    }

    output_file.close();
  }

private:
  std::vector<std::shared_ptr<Account>> accounts;
};

int main() {
  Bank bank;

  bank.load_accounts("accounts.txt");

  while (true) {
    std::cout << "Menu:\n"
              << "1. Create a new account\n"
              << "2. Manage accounts\n"
              << "3. Print account summary report\n"
              << "4. Exit\n"
              << "Please enter your choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
      std::string type, id, name;
      std::cout << "Enter account type (checking, savings, business): ";
      std::cin >> type;
      std::cout << "Enter account ID: ";
      std::cin >> id;
      std::cout << "Enter customer name: ";
      std::cin.ignore();
      std::getline(std::cin, name);
      bank.create_account(type, id, name);
    } else if (choice == 2) {
      bank.list_accounts();
      std::cout << "Select account to manage: ";
      size_t index;
      std::cin >> index;
      std::cin.ignore();
      auto account = bank.get_account(index - 1);
      if (account != nullptr) {
        while (true) {
          std::cout << "Account Menu:\n"
                    << "1. Deposit\n"
                    << "2. Withdraw\n"
                    << "3. Get Balance\n"
                    << "4. List Transactions\n"
                    << "5. Back to Main Menu\n"
                    << "Please enter your choice: ";
          int sub_choice;
          std::cin >> sub_choice;
          std::cin.ignore();

          if (sub_choice == 1) {
            double amount;
            std::cout << "Enter deposit amount: ";
            std::cin >> amount;
            std::cin.ignore();
            account->deposit(amount);
          } else if (sub_choice == 2) {
            double amount;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> amount;
            std::cin.ignore();
            account->withdraw(amount);
          } else if (sub_choice == 3) {
            std::cout << "Current balance: " << account->get_balance()
                      << std::endl;
          } else if (sub_choice == 4) {
            account->print_statement();
          } else if (sub_choice == 5) {
            break;
          } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
          }
        }
      } else {
        std::cout << "Invalid account. Please try again." << std::endl;
      }
    } else if (choice == 3) {
      for (const auto &account : bank.get_accounts()) {
        account->print_summary();
      }
    } else if (choice == 4) {
      break;
    } else {
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  bank.save_accounts("accounts.txt");

  return 0;
}