#include "1_Account.h"

Account::Account(int accountNumber,string name,double balance)
{
    this->accountNumber=accountNumber;
    this->name=name;
    this->balance=balance;
    addTransaction("Account created with balance "+to_string(balance));
}

void Account::addTransaction(string transaction)
{
    transactionHistory.push_back(transaction);
}

int Account::getAccountNumber()
{
    return accountNumber;
}

string Account::getName()
{
    return name;
}

double Account::getBalance()
{
    return balance;
}

void Account::deposit(double amount)
{
    if(amount<=0)
    {
        cout<<"Invalid deposit amount."<<endl;
        return;
    }
    balance+=amount;
    addTransaction("Deposited "+to_string(amount));
    cout<<"Amount deposited successfully."<<endl;
}

bool Account::withdraw(double amount)
{
    if(amount<=0)
    {
        cout<<"Invalid withdrawal amount."<<endl;
        return false;
    }
    if(amount>balance)
    {
        cout<<"Insufficient balance."<<endl;
        return false;
    }
    balance-=amount;
    addTransaction("Withdrawn "+to_string(amount));
    cout<<"Amount withdrawn successfully."<<endl;
    return true;
}

bool Account::transfer(Account& receiver,double amount)
{
    if(&receiver==this)
    {
        cout<<"Cannot transfer to the same account."<<endl;
        return false;
    }
    if(!withdraw(amount))
    {
        return false;
    }
    receiver.balance+=amount;
    addTransaction("Transferred "+to_string(amount)+" to account "+to_string(receiver.getAccountNumber()));
    receiver.addTransaction("Received "+to_string(amount)+" from account "+to_string(accountNumber));
    cout<<"Amount transferred successfully."<<endl;
    return true;
}

void Account::showDetails()
{
    cout<<endl<<"Account Number: "<<accountNumber
        <<endl<<"Name: "<<name
        <<endl<<"Account Type: "<<getAccountType()
        <<endl<<"Balance: "<<balance<<endl;
}

string Account::getAccountType()
{
    return "General";
}

void Account::showTransactionHistory()
{
    cout<<endl<<"Transaction History for Account "<<accountNumber<<":"<<endl;
    if(transactionHistory.empty())
    {
        cout<<"No transactions found."<<endl;
        return;
    }
    for(int i=0;i<transactionHistory.size();i++)
    {
        cout<<transactionHistory[i]<<endl;
    }
}


