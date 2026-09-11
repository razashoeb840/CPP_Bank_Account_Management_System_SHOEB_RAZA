#include "3_SavingsAccount.h"

SavingsAccount::SavingsAccount(int accountNumber,string name,double balance,double interestRate)
    :Account(accountNumber,name,balance)
{
    this->interestRate=interestRate;
}

void SavingsAccount::addInterest()
{
    double interest=balance*interestRate/100.0;
    balance+=interest;
    addTransaction("Interest added "+to_string(interest));
    cout<<"Interest added successfully."<<endl;
}

void SavingsAccount::showDetails()
{
    Account::showDetails();
    cout<<"Interest Rate: "<<interestRate<<"%"<<endl;
}

string SavingsAccount::getAccountType()
{
    return "Savings";
}
