#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;
struct account
{
	string name;
	int pin = 0;
	long int number = 0;
	long int balance = 0;
}acc[3];
fstream client, myfile, file, utb;
void bill(int a)
{
	int choice, rbill[10], verify = 0;
	long int  amount, finalbalance;
	long long rid[10], consumernum;
	utb.open("utilitybills.txt", ios::in);
	for (int i = 0; i < 10; i++)
	{
		utb >> rid[i];
		utb >> rbill[i];
	}
	cin >> consumernum;
	for (int i = 0; i < 10; i++)
	{
		if (consumernum == rid[i])
		{
			if (rbill[i] > 0)
			{
				cout << "\tAmount Payable: RS" << rbill[i] << endl;
				cout << "\tPress 1 to Pay\n\tPress 2 to Cancel\n";
				cin >> choice;
				if (choice == 1)
				{
					amount = rbill[i];
					if (amount > acc[a].balance)
					{
						cout << "\tError! Your transaction amount exceeds your bank balance!\n";
						break;
					}
					else
					{
						finalbalance = acc[a].balance - amount;
						acc[a].balance = finalbalance;
						cout << "\t * BILL PAYMENT SUCCESSFUL * " << endl << endl;
						cout << "\tYou have paid the bill of RS: " << amount << endl << endl;
						rbill[i] = 0;
						utb.close();

						utb.open("utilitybills.txt", ios::out);
						for (int j = 0; j < 10; j++)
						{
							utb << rid[j] << endl;
							utb << rbill[j] << endl;
						}
						utb.close();
						break;
					}
				}
				if (choice == 2)
				{
					break;
				}
			}
			else
			{
				cout << "\tThere is not outstanding bill to be paid against this Account ID.\n";
				break;
			}
		}
		else if (consumernum != rid[i])
		{
			verify = verify + 1;
		}
		if (verify == 10)
		{
			cout << "\tInvalid Bill ID Entered!\n";
			break;
		}
	}
}

void fundtransfer(int a)
{
	long int accid, casht;
	int check = 0;
E:
	cout << "\tEnter the Account ID to transfer cash to: ";
	cin >> accid;
	for (int j = 0; j < 3; j++) 
	{
		if (accid == acc[j].number)
		{
			if (acc[j].number == acc[a].number)
			{
				cout << "\tError! You can't transfer money to your own account!\n";
				goto E;
			}
			cout << "\tEnter the amount you want to transfer to " << acc[j].name << " Rs: ";
			cin >> casht;
			if (casht > acc[a].balance)
			{
				cout << "\tError! Your transaction amount exceeds your bank balance!\n";
			}
			else
			{
				acc[a].balance = acc[a].balance - casht;
				acc[j].balance = acc[j].balance + casht;
				cout << "\t * FUNDTRANSFER SUCCESSFUL *" << endl << endl;
				cout << "\tCash Rs " << casht << " transferred to " << acc[j].name << "'s account!\n\n";
			}
			break;
		}
		else if (accid != acc[j].number)
		{
			check = check + 1;
		}
		if (check == 3)
		{
			cout << "\tInvalid Account ID! It does not exists!\n";
			goto E;
		}
	}
}
void balance_inquiry(int a)
{
	cout << "\n\tThe total amount of balance in your account is RS: " << acc[a].balance << endl << endl;
}
void withdraw(int a)
{
	long int withdraw, TOTAL;
	cout << "\tEnter the amount of cash you want to withdraw Rs: ";
	cin >> withdraw;
	if (acc[a].balance >= withdraw)
	{
		TOTAL = acc[a].balance - withdraw;
		acc[a].balance = TOTAL;
		cout << "\t * WITHDRAW SUCCESSFUL *" << endl << endl;
		cout << "\tYou have withdrawn RS: " << withdraw << endl << endl;
	}
	else
	{
		cout << "\tNot Enough Money In Your Account!\n";
		cout << endl;
	}
}
void deposit(int a)
{
	long int dep, finalbalance;
	cout << endl << "\tEnter the amount of cash you want to deposit RS: ";
	cin >> dep;
	finalbalance = acc[a].balance + dep;
	acc[a].balance = finalbalance;
	cout << "\t * DEPOSIT SUCCESSFUL * " << endl << endl;
	cout << "\tYou have deposited RS: " << dep << endl << endl;
}
void pinchange(int a)
{
	int pin, newpin, renewpin;
F:
	cout << "\tEnter current PIN : ";
	fstream file;
	file.open("pin.txt", ios::out);
	cin >> pin;
	if (pin == acc[a].pin)
	{
		cout << "\tEnter new PIN : ";
		cin >> newpin;
		if (newpin >= 1000 && newpin <= 9999)
		{
			cout << "\tAgain enter new PIN : ";
			cin >> renewpin;
			if (newpin == renewpin)
			{
				acc[a].pin = renewpin;
				cout << "\t * PIN CHANGE SUCCESSFUL * " << endl << endl;
				cout << "\tYour new PIN is : " << acc[a].pin << endl << endl;
				file << acc[0].pin << endl;
				file << acc[1].pin << endl;
				file << acc[2].pin << endl;
				file.close();
			}
			else
			{
				cout << "\tThe PINs do not match" << endl;
				goto F;
			}
		}
		else
		{
			cout << "\tYou failed to enter a 4 digit pin!\n";
		}
	}
	else
	{
		cout << "\tWRONG PIN!";
		goto F;
	}
}
void utilitybillpayment(int a)
{
	int option = 0;
	cout << endl << "    " << acc[a].name << " please select an option to proceed.\n";
	cout << "                        * MENU * " << endl;
	cout << "\t1. Gas\t          2. Electricity\n\t3. Water\t  4. Fee\n\t5. Internet\t  6. Telephone\n\t7. Mobile Phone\t  8. Exit\n";
	cin >> option;
	switch (option)
	{
	case 1:
	{
		cout << "\tGAS BILL" << endl;
		cout << "\tEnter your Consumer Number: ";
		bill(a);
		break;
	}
	case 2:
	{
		cout << "\tELECTRICITY BILL" << endl;
		cout << "\tEnter your Consumer Number: ";
		bill(a);
		break;
	}
	case 3:
	{
		cout << "\tWATER BILL" << endl;
		cout << "\tEnter your Consumer Number: ";
		bill(a);
		break;
	}
	case 4:
	{
		cout << "\tFEE BILL" << endl;
		cout << "\tEnter your Consumer Number: ";
		bill(a);
		break;
	}
	case 5:
	{
		cout << "\tINTERNET BILL" << endl;
		cout << "\tEnter your Consumer Number: ";
		bill(a);
		break;
	}
	case 6:
	{
		cout << "\tTELEPHONE BILL" << endl;
		cout << "\tEnter your Telephone Number: ";
		bill(a);
		break;
	}
	case 7:
	{
		cout << "\tMobile Bill" << endl;
		cout << "\tEnter your Mobile Number: ";
		bill(a);
		break;

	}
	case 8:
		cout << "\tReturning to Menu!\n";
		break;
	default:
	{
		cout << "\tInvalid Option!" << endl;
		break;
	}
	}

}
int main()
{
	acc[0].name = "Sofia Haider";
	acc[0].number = 57892122;
	acc[1].name = "Muhammad Isam";
	acc[1].number = 44229982;
	acc[2].name = "Zobia Gul";
	acc[2].number = 66945678;

	myfile.open("balance.txt", ios::in);
	myfile >> acc[0].balance;
	myfile >> acc[1].balance;
	myfile >> acc[2].balance;
	myfile.close();

	file.open("pin.txt", ios::in);
	file >> acc[0].pin;
	file >> acc[1].pin;
	file >> acc[2].pin;
	file.close();

	int accnum, accpin, choice;
	system("COLOR 70");
A:
	system("cls");
AB:
	cout << "\n\tWelcome to Bahria's ATM Machine\n";
	cout << "\tPlease enter your Account ID: ";
	cin >> accnum;
	int check = 0;
	for (int i = 0; i < 3; i++)
	{
		if (accnum == acc[i].number)
		{
		B:
			cout << "\tPlease enter your PIN: ";
			cin >> accpin;

			if (accpin == acc[i].pin)
			{
				int a = i;
			C:
				cout << endl << "    " << acc[i].name << " please select an option to proceed.\n";
				cout << "                        * MENU * " << endl;
				cout << "	1. Balance Inquiry\t  2. Withdraw\n	3. Deposit\t          4. Pin Change\n        5. Utility Bill Payment\t  6. Fund Transfer\n			  7. Exit\t\n";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					balance_inquiry(a);
					goto C;
				}
				case 2:
				{
					withdraw(a);
					goto C;
				}
				case 3:
				{
					deposit(a);
					goto C;
				}
				case 4:
				{
					pinchange(a);
					goto C;
				}
				case 5:
				{
					utilitybillpayment(a);
					goto C;
				}
				case 6:
				{
					fundtransfer(a);
					goto C;
				}
				case 7:
				{
					cout << "\tLogging out!\n\tLogging out!\n\tLogging out!\n\tLogging out!\n";
					myfile.open("balance.txt", ios::out);
					myfile << acc[0].balance << endl;
					myfile << acc[1].balance << endl;
					myfile << acc[2].balance << endl;
					myfile.close();

					client.open("client.txt", ios::out);
					for (int i = 0; i < 3; i++)
					{
						client << "Account name: " << acc[i].name << endl;
						client << "Account number: " << acc[i].number << endl;
						client << "Account pin: " << acc[i].pin << endl;
						client << "Account balance: Rs " << acc[i].balance << endl << endl;
					}
					client.close();

					goto A;
				}
				default:
					cout << "\tInvalid option entered!\n";
					goto C;
				}
			}
			else
			{
				cout << "\tWRONG PIN!\n";
				goto B;
			}
			break;

		}
		else
		{
			check = check + 1;
		}
		if (check == 3)
		{
			cout << "\tInvalid account ID!\n";
			goto AB;
		}
	}
	system("pause");
}