/*   Jorge Avila
     CSE1325      mavID: 1001543128

*/

#define PencilPrice 60
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
std::string displayMoney(int amount);

enum STATUS
{
  OK_ChangeGiven,
  OK_NoChange,
  BAD_Insuff_Fund,
  BAD_Insuff_Change ,
  BAD_unknown,
  GOOD = 123,


};



bool buyPencils (int &pencilInventory, int &changeInventory, int &pencilQuantity, int &paymentInput, int &change, STATUS &status)
{
  // how much is it going to cost ????
  // pencilQuantity is how much the user wants to buy
  int cost_of_pencils;
  int Change_ifAny;

  cost_of_pencils = (pencilQuantity * PencilPrice); // how much pencils cost
  change = paymentInput -  cost_of_pencils;  // the change if needed for the customer
  //pencilInventory = pencilInventory - pencilQuantity; // pencil inventory once the bounds have been changed then it is (-)



  if (change > changeInventory)
  {
    /* Not enough change */
      /* BAD_Insuff_Change */
      status = BAD_Insuff_Change;
    return false;
  }
  else if (change == 0)
  {
    changeInventory = changeInventory + paymentInput;
    /* exact amount of money inputted */
      /* OK_NoChange */
      pencilInventory = pencilInventory - pencilQuantity; // recently added
      status = OK_NoChange;
    return true;
  }
  else if(paymentInput < cost_of_pencils)
  {
    /* payment is under of that the cost of pencils are */
      /* BAD_Insuff_Fund */
      status = BAD_Insuff_Fund;
      return false;
  }
  else if (change > 0 )
  {
    /* that means change was greater than zero and bounds were checked */
    // you give them change and purchase was taken in place
    changeInventory = changeInventory - change;
    changeInventory = changeInventory + paymentInput;
    status = OK_ChangeGiven;
    pencilInventory = pencilInventory - pencilQuantity;
    return false;

  }
  else
  {
    //status = BAD_unknown;
    // unknown
    return false;
  }

}

 std::string displayMoney(int amount)
{

  // Here the money will be displayed using the to_string() function
  std::string dollars{ std::to_string(amount/100) };
  std::string cents{ std::to_string(std::abs(amount%100)) };


  return "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}

int MenuChoice (int choiceResult)
{

    int result;
    cout<< "Welcome to my Pencil Machine"<<endl;
    cout<<"Please choose from the following options.\n";
    cout<<"0. No pencils for me today.\n";
    cout<<"1. Purchase pencils.\n";
    cout<<"2. Check inventory level.\n";
    cout<<"3. Check change level.\n";
    int choice;
    cin>>choice;

    while(cin.fail())
    {

      cin.clear();
      cin.ignore(50,'\n');
      cout<<"Input must be numeric. Try again\n";
      cin >> choice;

    }


    while (choice <= -1 || choice >= 4)
    {
      cout<<"Invalid Input.\n";
      cout<<"Try again from the menu: ";
      cin >>choice;
    }
      result = choice;

      return result;

}

int main ()
{
    int choiceResult;
    int pencilInventory = 100;
    int changeInventory = 500;
    int userPencils = 0;
    int paymentInput = 0;
    STATUS status = GOOD;
    choiceResult = MenuChoice(choiceResult); // a function that handles the menu and to call the options over and over again.
    int change = 0;

  /* Switch Statement with the Conditional While Loop */

  while (choiceResult != 0)
  {
    switch(choiceResult)
    {
        case (1):
        {
            if (pencilInventory == 0)
            {
              cout<<"\nWe ran out of pencils."<<endl;
              break;
            }
            cout<<"How many pencils would you like to purchase? ";
            cin >> userPencils;
            // IF letter is entered as Quantity of pencils

            while(cin.fail())
            {

              cin.clear();
              cin.ignore(50,'\n');
              cout<<"Input must be numeric. Try again\n";
              cin >> userPencils;

            }

           if (userPencils > pencilInventory || userPencils <= -1)
            {
              cout<<" Quantity asked for is not avaliable."<<endl;
              cout<<" Please choose again from the menu." <<endl;
              cout<<"\n";
              break;
            }
            if (userPencils == 0)
            {
              cout << "\nYou must purchase at least one pencil.\n" << endl;
              break;
            }

            else
            {
              int cost = (userPencils * PencilPrice);
              cout<<"\nThe cost of pencils will be " << displayMoney(cost) << endl;
              cout<<"\nEnter payment amount (cents): ";
              cin>>paymentInput;

              while(cin.fail())
              {

                cin.clear();
                cin.ignore(50,'\n');
                cout<<"Input must be numeric. Try again\n";
                cin >> paymentInput;

              }


              buyPencils(pencilInventory,changeInventory,userPencils,paymentInput,change,status); // actually inserted a payment
        /*

          the minute the function buyPencils() is finished I need to create another switch statment that ultimately
          decides what status was the purchase. I need to correctly identify it by returning that true/false from each enum.

        */
              switch (status)
              {
                  case(BAD_Insuff_Change):
                  {
                    cout<<endl;
                    cout<<"Oops, looks like we do not have enough change!"<<endl;
                  }
                  break;

                  case(OK_NoChange):
                  {
                    cout<<"\n Awesome, exact payment. Enjoy your pencils.\n";
                  }
                  break;
                  case (BAD_Insuff_Fund):
                  {
                    cout<<"\nOops, underpayment is not accepted.\n";
                  }
                  break;

                  case (OK_ChangeGiven):
                  {
                    cout<< "your change is "<<displayMoney(change)<<" ,enjoy your pencils."<<endl;
                  }
                  break;

                  case(BAD_unknown):
                  {
                    cout<<"Error, unknown error occured." <<endl;
                  }
                  break;
              }
            }


      }
      break;
      case (2):
      {

        cout<<" \nThis is the inventory pencil: "<< pencilInventory<<endl;


        break;
      }
      case (3):
      {
        cout<<" \nThis is the check change inventory: " <<changeInventory<<endl;


        break;
      }

    }
    cout<<"\n";
    choiceResult = MenuChoice(choiceResult);


  }

 return 0;
}
