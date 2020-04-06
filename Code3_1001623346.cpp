// Serge Zaatar Antor 1001623346

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include "SnackMachine.h"
#include "SnackLib.h"
using namespace std;

void DisplayMenu(int &choice)
{
	//cout << "\nPlease choose from the following options\n\n\n";
	cout << "0. Walk away\n";
	cout << "1. Buy a snack\n";
	cout << "2. Restock machine\n";
	cout << "3. Add change\n";
	cout << "4. Display Machine Info\n";
	cout << "5. Update Machine Name\n";
	cout << "6. Update Snack Price\n\n";
	cin >> choice;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(50, '\n');
		cout << "\nInput must be numeric. Please reenter.";
		cin >> choice;
	}

	while (choice < 0 || choice > 6)
	{
		cout << "Invalid option. Please try again.";
		cin >> choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "\nInput must be numeric. Please reenter.";
			cin >> choice;
		}
	}
}

void get_command_line_params(int argc, char *argv[], string &inFile, string &outFile)
{
	inFile = argv[1];
	outFile = argv[2];

	if (argc <= 2 /*|| inFile == NULL || outFile == NULL*/)
	{
		throw invalid_argument("Missing command line parameters – - Usage : input^filename output^filename");
	}
}

int main(int argc, char *argv[])
{
	int choice = -1, machineChoice = -1;
	int payment, change, addend, product;
	string changeString, newMachineName, inFile, outFile, newSnackPrice;
	int buystatus, i;
	vector<SnackMachine> SetOfSnackMachines;
	vector<string> ConstructorValues(4);
	int second, third, fourth;
	string first;
	//SnackMachine MySnackMachine {"CSE 1325 Snack Machine", 50, 500, 100};
	//cout << "CSE 1325 Snack Machine\n\n";

	//File Handling
	try
	{
		get_command_line_params(argc, argv, inFile, outFile);
	}
	catch (invalid_argument &say)
	{
		cout << say.what() << endl;
		exit(0);
	}

	ifstream SnackInputFile(inFile);
	ofstream SnackOutputFile(outFile, ios::out);
	string SnackMachineLine;

	if (SnackInputFile.is_open())
	{
		while (getline(SnackInputFile, SnackMachineLine))
		{
			if (ParseSnackLine(SnackMachineLine, ConstructorValues))
			{
				second = stoi(ConstructorValues.at(1));
				third = stoi(ConstructorValues.at(2));
				fourth = stoi(ConstructorValues.at(3));

				SnackMachine thisMachine{ConstructorValues.at(0), second, third, fourth};
				SetOfSnackMachines.push_back(thisMachine);
			}
			else
			{
				cout << "Unable to open file." << endl;
				exit(0);
			}
		}
	}
	else
	{
		cout << "Could not open In File" << endl;
		exit(0);
	}

	// End of File Handling

	do
	{
		cout << "\nPick a Snack Machine" << endl;

		for (i = -1; i < SetOfSnackMachines.size(); i++)
		{
			if (i < 0)
				cout << i + 1 << ". Exit" << endl;
			else
			{
				cout << i + 1 << ".";
				cout << SetOfSnackMachines.at(i).getMachineName();
				cout << endl;
			}
		}
		cout << "\nEnter choice ";
		cin >> machineChoice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "\nInput must be numeric. Please reenter." << endl;
			cin >> machineChoice;
		}

		if (machineChoice==0)
		{
			for(i=0; i<SetOfSnackMachines.size(); i++)
			{
				SnackOutputFile << CreateSnackOutputLine(SetOfSnackMachines.at(i)) <<endl;
			}

			cout << "Done.\n";
		}

		cout << SetOfSnackMachines[machineChoice-1].getMachineName() << endl;

		do
		{
			DisplayMenu(choice);

			if (choice < 0 || choice > 6)
				cout << "\nInvalid menu option.\n";

			switch (choice)
			{
				case 0:
					cout << "Are you sure you aren't really HUNGRY and need a Snack?\n";
					break;
				case 1:
					cout << "A snack cost " << SetOfSnackMachines.at(1).getSnackPrice() << endl;
					cout << "Insert payment: ";
					cin >> payment;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(50, '\n');
						cout << "\nInput must be numeric. Please reenter.";
						cin >> payment;
					}

					SetOfSnackMachines.at(1).buyASnack(payment, changeString, buystatus);

					switch (buystatus)
					{
						case (GOOD_CHANGE):
							cout << "Here's your Snack and your change of " << changeString << endl;
							break;
						case (GOOD_EXACT):
							cout << "Thank you for exact change" << endl;
							cout << "Here's your Snack" << endl
								<< endl;
							break;
						case (BAD_NOFUNDS):
							cout << "Insufficent payment...returning your payment" << endl;
							break;
						case (BAD_NOCHANGE):
							cout << "Unable to give change at this time...returning your payment" << endl;
							break;
						case (BAD_RANOUT):
							cout << "Not enough product. We need a refill." << endl;
							break;
						case (BAD_UNKNOWN):
							cout << "Unknown error occurred." << endl;
							break;
					}
					break;
				case 2:
					cout << "How much product are you adding to the machine? ";
					cin >> product;

					while (cin.fail())
					{
						cin.clear();
						cin.ignore(50, '\n');
						cout << "\nInput must be numeric. Please reenter." << endl;
						cin >> product;
					}

					SetOfSnackMachines.at(1).incrementInventory(product);

					switch (status)
					{
						case (GOOD_INVENTORY):
							cout << "Your machine has been restocked" << endl;
							cout << "Your inventory level is now " << SetOfSnackMachines.at(1).getInventoryLevel() << endl
								<< endl;
							break;
						case (BAD_INVENTORY):
							cout << "You have exceeded your machine's max capacity." << endl;

							cout << "Your inventory level is now " << SetOfSnackMachines.at(1).getInventoryLevel() << endl
								<< endl;
							break;
						case (ZERO):
							cout << "You have to enter something." << endl;
							cout << "Your inventory level is now " << SetOfSnackMachines.at(1).getInventoryLevel() << endl
								<< endl;
							break;
						case (INVALID):
							cout << "Invalid choice of restock quantity." << endl;
							cout << "Your inventory level is now " << SetOfSnackMachines.at(1).getInventoryLevel() << endl
								<< endl;
							break;
					}

					//cout << "The current inventory level is "<<endl;
					break;
				case 3:
					cout << "How much change are you adding to the machine? ";
					cin >> change;

					while (cin.fail())
					{
						cin.clear();
						cin.ignore(50, '\n');
						cout << "\nInput must be numeric. Please reenter." << endl;
						cin >> change;
					}

					if (SetOfSnackMachines.at(1).incrementChangeLevel(change))
					{
						cout << "Your change has been updated." << endl;
						cout << "Your change level is now " << SetOfSnackMachines.at(1).getChangeLevel() << endl
							<< endl;
					}
					else
					{
						cout << "We could not update the change." << endl;
						cout << "Your change level is now " << SetOfSnackMachines.at(1).getChangeLevel() << endl
							<< endl;
					}
					//cout << "The current change level is "<<   <<endl;
					break;
				case 4:
					cout << SetOfSnackMachines.at(1);
					// cout << "\n"<< getMachineName()<<endl;
					// cout << "\nCurrent Inventory Level "<<SetOfSnackMachines.at(1).getInventoryLevel()<<endl;
					// cout << "Max Inventory Capacity "<<SetOfSnackMachines.at(1).getMaxInventoryCapacity()<<endl;
					// cout << "\nCurrent Change Level "<<SetOfSnackMachines.at(1).getChangeLevel()<<endl;
					// cout << "Max Change Capacity "<<SetOfSnackMachines.at(1).getMaxChangeCapacity()<<endl;
					// cout << "\nCurrent Snack price is "<<SetOfSnackMachines.at(1).getSnackPrice()<<endl<<endl;

					break;
				case 5:
					cout << "Enter a new machine name ";
					getline(cin, newMachineName);
					SetOfSnackMachines.at(1).setMachineName(newMachineName);
					cout << "Machine name has ben updated.\n\n";
					break;
				case 6:
					cout << "Enter a new Snack price ";
					cin >> newSnackPrice;
					SetOfSnackMachines.at(1).setSnackPrice(newSnackPrice);
					cout << "Snack price has ben updated.\n\n";
					break;
			}
		} while (choice != 0);

	} while (machineChoice != 0);

	SnackInputFile.close();
	SnackOutputFile.close();
	return 0;
}