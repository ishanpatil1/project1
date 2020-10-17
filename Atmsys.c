#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Credentials
{
    char Name[10];
    int AccountNumber;
    unsigned long long CardNum;
    int PIN;
    int Amount;
}Credentials;   

Credentials Log[10];

int saveinfo=0;

Credentials createaccount(struct Credentials C1)
{
    
    printf("\n Enter your full name:- ");
    fscanf( stdin, " %s", C1.Name );
    printf("\n Enter your 16-digit card number:- ");
    fscanf( stdin, " %llu", &C1.CardNum);
    C1.PIN=(C1.CardNum*rand())%10000;
    C1.Amount=(C1.CardNum*rand())%1000000;
    C1.AccountNumber=(rand()*C1.PIN)%1000000;
    printf("\n Your Entered Information is:- ");
    printf("\n Name:- %s ", C1.Name);
    printf("\n Account Number:- %d ", C1.AccountNumber);
    printf("\n Card Number:- %llu ", C1.CardNum);
    printf("\n PIN Number:- %d ", C1.PIN);
    printf("\n Account Balance:- %d ",C1.Amount);

    return C1;
}

int CashWithdrawal(int amount)
{
    int acctype,debit;

    printf("\n Amount= %d ",amount);

    printf("\n Enter the type of withdrawal:- 1)Current 2)Savings ");
    scanf("%d",&acctype);
    while(acctype!=2)
    {
        printf("\n\tYour account is of Savings type. Choose the correct option. ");
        scanf("%d",&acctype);
    }
    if (acctype==2)
    {
        printf("\nEnter amount to be withdrawn:- ");
        scanf("%d",&debit);
        while (debit<=100||debit>=25000)
        {
            printf("\nYou cannot withdraw cash above Rs.25000 or below Rs.100! Please Enter amount again");
            printf("\nEnter amount to be withdrawn:- ");
            scanf("%d",&debit);
        } 
        amount-=debit;
        printf("\n %d",amount);
        return(amount);
        //Print Receipt showing the Amount deducted with the orinal and final balance and the account number
    }
    return(amount);
}

int Transfer(int Balance)
{
    int trans,accnum;
    printf("\nEnter account number to which the money will be transfered(Eg.123456):- ");
    scanf("%d",&accnum);
    printf("\nEnter amount to be transfered:- ");
    scanf("%d",&trans);
    while (Balance-1000<trans)
    {
        printf("\nThe transfer amount must be Rs.1000 less than the account balance, Enter amount again:- ");
        scanf("%d",&trans);
    }
    Balance=Balance-trans;
    printf("\n%d",Balance);
    return Balance;
    //Print a receipt with the amount deducted and the account number it was sent to with the remaining balance
}

int ChangePIN(int PIN)
{
    int newpin,check;
    printf("\nEnter your existing PIN:- ");
    scanf("%d",&check);
    while (check!=PIN)
    {
        printf("\nEnter the correct PIN:- ");
        scanf("%d",&check);
    }
    printf("\nEnter the new PIN Number:- ");
    scanf("%d",&newpin);
    while (newpin==check||newpin/10000>0)
    {
        if (newpin==check)
        {
            printf("\nNew PIN cannot be the old PIN, Enter again:- ");
            scanf("%d",&newpin);
        }
        if(newpin/10000>0)
        {
            printf("\nPIN must be of 4 digits, Enter again:-");
            scanf("%d",&newpin);
        }
    }
    printf("\nYour New PIN is:- %d",newpin);
    
    return(newpin);
}

void AccountDetails(int entrynum)
{
    printf("\nAccount Holder Name:- %s ",Log[entrynum].Name);
    //puts(Name);
    printf("\nAccount Number:- %d ",Log[entrynum].AccountNumber);
    printf("\nCard Number:- %llu ",Log[entrynum].CardNum);
    printf("\nAccount PIN Number:- %d ",Log[entrynum].PIN);
    printf("\nAccount Balance:- %d ",Log[entrynum].Amount);
}

void ViewLog(int login)
{
    printf("\nSr.No.\tAccount Number\t Name");
    printf("\n-------------------------------------------------------------------");
    for (int i=0; i <= login; i++)
    {
        printf("\n%d ",i+1);
        printf("\t%d ",Log[login].AccountNumber);
        printf("\t\t %s ",Log[login].Name);
    }
}

char Rerun()
{
    char cont;
    printf("\n\n\t\t Do you wish to enter again?(y/n) ");
    fscanf(stdin,"%s", &cont);
    if (cont=='y')
    {
        return(cont);
    }
    else
    {
        if (cont=='n')
        {
            printf("\n\n\n\tThank you for banking with us! ");
            return(cont);
        }
    }  
    return('n');
}

char Newlogin()
{
    char temp;
    printf("\nDo you wish to Make a new Entry?(Y/N) ");
    scanf("%s",&temp);
    
    if (temp=='Y')
    {
        return('Y');
    }
    else
    {
        if (temp=='N')
        {
            printf("\n\n\n\tThank you for banking with us! ");
            return('N');
        }
    }
    return('N');
}

Credentials record(int size)
{
    char cont,Reenter;
    int PINCheck,choice,flag;
    struct Credentials Data;
    do
    {
        Data=createaccount(Data);
        Log[saveinfo]=Data;
        //clrscr(); //Use this while writing code in msdos when implementing graphics
        do
        {
            printf("\n\n\n Enter your PIN:- ");
            scanf("%d",&PINCheck);
            if(PINCheck==Data.PIN)
            {
                do
                {
                    printf("\nSelect your choice:-\n\t1)CashWithdrawal\n\t2)Transfer\n\t3)Change PIN\n\t4)Account Details\n\t5)Exit \n\tChoice:- ");
                    fscanf(stdin,"%d",&choice);
                    switch (choice)
                    {
                        case 1:{
                            Log[saveinfo].Amount=CashWithdrawal(Log[saveinfo].Amount);
                            cont=Rerun();
                            if(cont=='n')
                            {
                                flag=0;
                                Reenter=Newlogin();
                            }
                            break;
                        }
                        case 2:{
                            Log[saveinfo].Amount=Transfer(Log[saveinfo].Amount);
                            cont=Rerun();
                            if(cont=='n')
                            {
                                flag=0;
                                Reenter=Newlogin();
                            }                            
                            break;
                        }
                        case 3:{
                            Log[saveinfo].PIN=ChangePIN(Log[saveinfo].PIN);
                            cont=Rerun();
                            if(cont=='n')
                            {
                                flag=0;
                                Reenter=Newlogin();
                            }                            
                            break;
                        }
                        case 4:{
                            AccountDetails(saveinfo);
                            cont=Rerun();
                            if(cont=='n')
                            {
                                flag=0;
                                Reenter=Newlogin();
                            }                            
                            break;
                        }
                        case 5:{
                            flag=0;
                            cont='n';
                            Reenter=Newlogin();
                            break;
                        }
                        default:{
                            printf("\n\t\tChoose a valid Option!!!!! ");
                        }
                    }
                }while(cont=='y');
            }
            else
            {
                flag=1;
            }
        }while (flag==1);
        if (Reenter=='Y')
        {
            size++;
            saveinfo++;
            //Log[size]= record(size);
        }
    }while(Reenter=='Y');
    //return  Data;
}

int main()
{
    char check;    
    
   
    record(saveinfo);  
    
    //Code to show the the user log from the show log function

    printf("\nDo you wish to see the use log? (y/n) ");
    fscanf(stdin, "%s",&check);
    if(check=='y')
    {
        ViewLog(saveinfo);
    }

}
