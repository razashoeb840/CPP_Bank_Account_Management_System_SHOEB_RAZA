#include "5_CurrentAccount.h"

CurrentAccount::CurrentAccount(int accountNumber,string name,double balance,double overdraftLimit)
    :Account(accountNumber,name,balance)
{
    this->overdraftLimit=overdraftLimit;
}

bool CurrentAccount::withdraw(double amount)
{
    if(amount<=0)
    {
        cout<<"Invalid withdrawal amount."<<endl;
        return false;
    }
    if(amount>balance+overdraftLimit)
    {
        cout<<"Withdrawal exceeds overdraft limit."<<endl;
        return false;
    }
    balance-=amount;
    addTransaction("Withdrawn "+to_string(amount));
    cout<<"Amount withdrawn successfully."<<endl;
    return true;
}

void CurrentAccount::showDetails()
{
    Account::showDetails();
    cout<<"Overdraft Limit: "<<overdraftLimit<<endl;
}

string CurrentAccount::getAccountType()
{
    return "Current";
}
