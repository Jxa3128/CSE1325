// Jorge Avila  1001543128  Code2_1001543128.cpp

/* preprocessors */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* remember COLE - Compiler compiles the object files which then the Linker links the objects
together to create an executable file  */

#include "SnackMachine2.h" // In this headerfile I will create the object

int MenuChoice(int &respuesta)
{

  cout << "0. Walk away" << endl;
  cout << "1. Buy a Snack" << endl;
  cout << "2. Restock Machine" << endl;
  cout << "3. Add change" << endl;
  cout << "4. Display Machine Info" << endl;
  cin >> respuesta;

  while (cin.fail())
  {
    cin.clear();
    cin.ignore(50, '\n');
    cout << "Input needs to be a numeric value please: " << endl;
    cin >> respuesta;
  }
  while (respuesta < -1 || respuesta > 5)
  {
    cout << "You must enter a value between 0 and 4.  Reenter your choice: ";
    cin >> respuesta;
  }
  return respuesta;
}

int main()
{
  cout << "Welcome to CSE 1325 Snack Machine" << endl;
  int choice{};
  int respuesta{};
  choice = MenuChoice(respuesta);
  int AddProduct;
  int pagamento;
  string cambio;
  int condition;
  int cambio_int;
  int AddingChange;
  // Instatiate my object
  SnackMachine MySnackMachine{"Jorge's Snack Machine", 50, 500, 100};

  while (choice != 0)
  {
    switch (choice)
    {
    case (1):
    {
      // add code here
      // still need to add status' here
      cout << "A snack cost " << MySnackMachine.getSnackPrice() << endl;
      cout << "Insert payment: ";
      cin >> pagamento;

      MySnackMachine.buyASnack(pagamento, cambio, condition); // will not work because of parameters but how

      //cambio_int = stoi(cambio);
      switch (condition)
      {
        case (OK_ChangeGiven):
        {
          cout << "Awesome, your change is " << cambio << endl;
          break;
        }
        case (OK_NoChange):
        {
          cout << "Amazing, exact change." << endl;
          break;
        }
        case (BAD_Insuff_Fund):
        {
          cout << "Insufficent payment... returning your payment." << endl;
          break;
        }
        case (BAD_unknown):
        {
          cout << "Unknown error occurred." << endl;
          break;
        }
        case (BAD_Insuff_Change):
        {
          cout << "I am sorry, we do not have enough change." << endl;
          break;
        }
        case (RAN_OUT):
        {
          cout << "Sorry, we ran out of product. Go ahead and refill it." << endl;
          break;
        }
      }
          break;
    }
    case (2):
    {
      // add code here
      cout << "How much product are you adding to your machine? ";
      cin >> AddProduct;

      // if wrong input is entered

      while (cin.fail())
      {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Input needs to be a numeric value please: " << endl;
        cin >> AddProduct;
      }

      MySnackMachine.incrementInventory(AddProduct);

      /* Switch base on the status ONLY for the RESTOCK section */
      switch (status)
      {
        case (BAD_InventoryExceed):
        {
          cout << "\nUnable to accept restock request (exceeds)" << endl;
          cout << "\n Your inventory level is now " << MySnackMachine.getInventoryLevel() << endl;
          break;
        }
        case (GOOD_InventoryLevel):
        {
          cout << "\nWe were able to receive your restock request." << endl;
          break;
        }
        case (Restock_zero):
        {
          cout << "\nYou have to at least enter one quantity." << endl;
          break;
        }
        case (Invalid_restock):
        {
          cout << "\nInvalid choice of restock quantity." << endl;
          break;
        }
      }

      break;
    }
    case (3):
    {
      bool DidItWork;
      // add code Here
      cout << "\nHow much change are you adding? " << endl;
      cin >> AddingChange;
      while (cin.fail())
      {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Input needs to be a numeric value please: " << endl;
        cin >> AddingChange;
      }
      DidItWork = MySnackMachine.IncrementChangeLevel(AddingChange);
      if (DidItWork == true)
      {
        cout << "Your change as been updated." << endl;
        cout << "Your change now is " << MySnackMachine.getChangeLevel() << endl;
      }
      else if (DidItWork == false)
      {
        cout << "I am sorry change exceeds maximum." << endl;
      }
      else
      {
        cout << "Incorrect input." << endl;
      }
      break;
    }
    case (4):
    {
      cout << MySnackMachine.getMachineName() << endl;
      cout << "Current Inventory Level\t" << setw(11) << MySnackMachine.getInventoryLevel() << endl;
      cout << "Max Inventory Capacity\t" << setw(11) << MySnackMachine.getMaxInventoryCapacity() << endl;
      cout << "Current Change Level\t" << setw(11) << MySnackMachine.getChangeLevel() << endl; // I still need to configure this
      cout << "Max Change Capacity\t" << setw(11) << MySnackMachine.getMaxChangeCapacity() << endl;
      cout << "Current Snack Price is " << setw(12) << MySnackMachine.getSnackPrice() << endl;
      // add code here
      break;
    }
    }
    cout << endl;
    choice = MenuChoice(respuesta);
  }

  cout << "Are you sure you aren't really HUNGRY and need a Snack? " << endl;

  return 0;
}
