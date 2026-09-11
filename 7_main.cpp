#include "5_CurrentAccount.h"
#include "3_SavingsAccount.h"

using namespace std;

Account* accounts[100];
string accountTypes[100];
int accountCount=0;

Account* findAccount(int number)
{
    for(int i=0;i<accountCount;i++)
    {
        if(accounts[i]->getAccountNumber()==number)
            return accounts[i];
    }
    return NULL;
}

SavingsAccount* findSavings(int number)
{
    for(int i=0;i<accountCount;i++)
    {
        if(accounts[i]->getAccountNumber()==number&&accountTypes[i]=="Savings")
            return (SavingsAccount*)accounts[i];
    }
    return NULL;
}

void showMenu()
{
    cout<<endl<<"===== BANK MENU ====="<<endl
        <<"1 Create Savings Account"<<endl
        <<"2 Create Current Account"<<endl
        <<"3 Deposit"<<endl
        <<"4 Withdraw"<<endl
        <<"5 Transfer"<<endl
        <<"6 Show Details"<<endl
        <<"7 Transaction History"<<endl
        <<"8 Add Interest"<<endl
        <<"0 Exit"<<endl;
}

int main()
{
    int choice;
    do
    {
        showMenu();
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1||choice==2)
        {
            int number;
            cout<<"Enter Number: ";
            cin>>number;

            if(findAccount(number))
            {
                cout<<"Account number already exists."<<endl;
                continue;
            }

            string name;
            double balance;
            cout<<"Name: ";
            cin>>name;
            cout<<"Balance: ";
            cin>>balance;

            if(choice==1)
            {
                double interest;
                cout<<"Interest: ";
                cin>>interest;
                accounts[accountCount]=new SavingsAccount(number,name,balance,interest);
                accountTypes[accountCount]="Savings";
                accountCount++;
                cout<<"Savings account created successfully."<<endl;
            }
            else
            {
                double overdraft;
                cout<<"Overdraft Limit: ";
                cin>>overdraft;
                accounts[accountCount]=new CurrentAccount(number,name,balance,overdraft);
                accountTypes[accountCount]="Current";
                accountCount++;
                cout<<"Current account created successfully."<<endl;
            }
        }
        else if(choice==3)
        {
            int number;
            cout<<"Enter Account Number: ";
            cin>>number;
            Account* account=findAccount(number);
            if(!account)
            {
                cout<<"Account not found."<<endl;
                continue;
            }
            double amount;
            cout<<"Deposit Amount: ";
            cin>>amount;
            account->deposit(amount);
        }
        else if(choice==4)
        {
            int number;
            cout<<"Enter Account Number: ";
            cin>>number;
            Account* account=findAccount(number);
            if(!account)
            {
                cout<<"Account not found."<<endl;
                continue;
            }
            double amount;
            cout<<"Withdraw Amount: ";
            cin>>amount;
            account->withdraw(amount);
        }
        else if(choice==5)
        {
            int senderNum,receiverNum;
            cout<<"Sender Account Number: ";
            cin>>senderNum;
            cout<<"Receiver Account Number: ";
            cin>>receiverNum;
            Account* sender=findAccount(senderNum);
            Account* receiver=findAccount(receiverNum);
            if(!sender||!receiver)
            {
                cout<<"Sender or receiver account not found."<<endl;
                continue;
            }
            double amount;
            cout<<"Transfer Amount: ";
            cin>>amount;
            sender->transfer(*receiver,amount);
        }
        else if(choice==6)
        {
            int number;
            cout<<"Enter Account Number: ";
            cin>>number;
            Account* account=findAccount(number);
            if(account)
                account->showDetails();
            else
                cout<<"Account not found."<<endl;
        }
        else if(choice==7)
        {
            int number;
            cout<<"Enter Account Number: ";
            cin>>number;
            Account* account=findAccount(number);
            if(account)
                account->showTransactionHistory();
            else
                cout<<"Account not found."<<endl;
        }
        else if(choice==8)
        {
            int number;
            cout<<"Enter Savings Account Number: ";
            cin>>number;
            SavingsAccount* sa=findSavings(number);
            if(sa)
                sa->addInterest();
            else
                cout<<"Savings account not found."<<endl;
        }
        else if(choice!=0)
        {
            cout<<"Invalid choice."<<endl;
        }
    }while(choice!=0);

    cout<<"Thank you for using the Bank Account Management System."<<endl;

    for(int i=0;i<accountCount;i++)
        delete accounts[i];

    return 0;
}



