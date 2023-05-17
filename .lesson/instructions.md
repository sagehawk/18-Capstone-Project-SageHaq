# Instructions  

  ** Polymorphism **

## Assignment Details ##

In this assignment we are going to build a small banking system.

Create a class called Account which will be an abstract class for three other classes called CheckingAccount, SavingsAccount and BusinessAccount.  Create get/set methods as appropriate.

# Main Program Functionality # 

On program start, the system will load an existing file of accounts and their transactions from account.txt.
If it doesn't exist, it will continue on without error.

The main program will present a repeating menu with the following options:

1.  Create a new account
    - Creates a new account store it in a vector.
2.  Manage Accounts
    - Lists the person's name as a menu selection.
    - When person chooses a selection they get a sub menu to:
        1.  Deposit
        2.  Withdraw
        3.  Get Balance
        4.  List Transactions
        5.  Back to Main Menu
        On "Back to main menu": (5)
            - Save the account information for all accounts entered, including transactions
            - Be sure to:
                   1.  Distinguish between account types
                   2.  Distinguish between transaction types
3. Print Account Summary Report
   -  Print a report containing all accounts:
  - For each account, print out
     -    Account
     -    Account Type
     -    Balance
     -    Number of Transactions
     -    Total of Deposits
     -    Total of Withdrawels
    -    Average Size of Transaction
4. Exit

# Account Class Breakdown #

## Base Class ##
### Class: Account ###
This is the abstract account base class.  Actual instances must be of a subclass.

#### Data members ####
1.  Account Id - some identifier representing the account.  It can be whatever type you want
2.  Customer Name - name of the customer
3.  Transaction List - A list of historical transactions.  This will also be a hierarchy

#### Methods (Virtual) #### 
1.  Deposit(amount) - Deposits into an account with rules appropriate to the account type
    * You must prevent negative deposits.

2.  Withdraw(amount) - Withdraws an ammount and reduces the balance on that account
    
    * You must validate the data to ensure it is positive.

3.  Get Balance - get the current balance
4.  Print Summary - Print the customer id, name, balance and number of transactions
5.  Print Statement - Print the customer id, namem balance and number of transactions.
                    - Print a list of all the transactions including transaction type, date and amount 

## Child Classes ##
### Class: CheckingAccount ###
This represents a no fee, no penalty checking account


#### Data members ####
1.  Account Id - some identifier representing the account.  It can be whatever type you want
2.  Customer Name - name of the customer
3.  Balance - Current Balance
4.  Transaction List - A list of historical transactions.  This will also be a hierarchy

#### Methods (Virtual) #### 
1.  Deposit(amount) - Deposits into an account 
    * You must prevent negative deposits.

2.  Withdraw(amount) - Withdraws an ammount and reduces the balance on that account
    
    * You must validate the data to ensure it is positive.

3.  Get Balance - get the current balance
4.  Print Summary - Print the customer id, name, balance and number of transactions
5.  Print Statement - Print the customer id, namem balance and number of transactions.
                    - Print a list of all the transactions including transaction type, date and amount 

### Savings Account ###

#### Additional Data Members ##

1. Interest rate - The annual interest rate 
2. Deposit bonus - A small bonus paid per deposit based on certain conditions 
3. Withdrawal Penalty - A small penalty per withdrawel based on certain conditions 


####  Methods ####
1. Deposit(amount) - Add an interest charge to each transaction (.10)
2. Withdrawal (amount) - Withdraw the amount if available
3. Print Summary
4. Print Statement.

## Child Classes ##
### Business Account ###

#### Additional Data Members ####
1. Transaction cost - Every transaction has a transaction cost, whether depositing or withdrawing 
2. Business Name

####  Methods ####
1. Constructor taking transaction fee as a parameter
2. Deposit(amount) - Deposit to account, apply transaction fee
3. Withdrawel (amount) - Withdraw From account, apply transaction fee
4. Print Summary
5. Print Statement.


# Transaction Class Breakdown #
## Base Class ##
### Class: Transaction ###
This represents the minimum for a transaction.  Certain transaction types must have more information.
Note that you do NOT ever need a transaction type, as that's what subclasses are for.

#### Data members ####
1.  Transaction date - Date of transaction
2.  Transaction amount - Transaction amount. May be positive or negative based on the transaction


### Methods ###
1.  Print - Prints out the transaction type, date, amount and new balance
2.  Balance Snap shot - Balance AFTER this transaction.

##  Child Classes ##
### Class: Savings Account ###
#### Data Members ####
No new data members
#### Methods ####
1. Print - Prints out the transaction type, date, amount and new balance


### Class: Business Account ###
#### Data Members ####
No new data members
#### Methods ####
1. Print - Prints out the transaction type, date, amount and new balance




