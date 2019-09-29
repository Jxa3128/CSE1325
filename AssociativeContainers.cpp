// Jorge Avila 1001543128
/*
  Problem Statement: In this program that I created. will illustrate common set operators and
  how associative containers work, I have commented and tried cleaning the program up to better
  help you understand.
*/
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <ctime>

/* These below includes are what are most useful for this program */

#include <set>
#include <map>
#include <stack>
#include <queue>

using namespace std; // not always the best but ya know.

int MenuChoice()
{
  cout<< "\tNow allow me to make a function.\n\tChoose from the Menu!" <<endl;
  cout<<endl;
  cout << "0.\tExit" <<endl;
  cout << "1.\tCreate your set." <<endl;
  cout << "2.\tDelete something from your set." <<endl;
  cout << "3.\tPrint your set." <<endl;
  int result;
  cin >> result;

  while (cin.fail())
  {
    cin.clear();
    cin.ignore(50,'\n');
    cout <<"Enter a numeric value please" <<endl;
    cin >> result;
  }

  while (result < -1 || result > 3)
  {
    cout<<" Invalid menu choice, try again." <<endl;
    cin >> result;
  }

  return result;
}





int main (int args, char * argv[])
{
  /*
      associative container is just a container
     that holds sorted data.

  */

    set<int> set1 {5,4,3,2,1,1}; // This is not unique (numbers repeat, what does that do?)
    // well it gets rid of repeating numbers, may that come in handy IDK
    // in our head we count 6 values, but the compiler took it out and counted 5

    // useful operator is .insert() because we can play around with this.

    set1.insert(0); // adds zero to the start which will mean that the size will change


    cout << "Size : " << set1.size() << endl;


    /*
    cout << set1[0];
    When we want to print out or get a specific value in these set array looking things
    we cannot do that with the code that I tried doing above because it prints this message:

    'set<int>' does not provide a subscript operator
    cout << set1[0];

    Therefore we do something else.
    */

    set<int>::iterator it = set1.begin(); // A way that you make a temp set to access things (set it at beggining)
    it++;
    cout<< "2nd Value : " << *it << endl; // you have to derefrence the iterator

    if(!set1.empty()) // if our set is not empty then print it out
    {
      for (auto it: set1)
      cout<< it << endl;
    }
      cout<<"\t=======================================" << endl;
      cout<<"\t\t The Start of Jorge's Program" << endl;
      cout<<"\t=======================================" << endl;

    int choice;
    choice = MenuChoice();
    set<int>UserSet;
    int UserSetAmount;
    int amount;
    int earseValue;

    while (choice!=0)
    {
      switch(choice)
      {
        case(1):
        {
          cout<<"How long is your set going to be: ";
          cin >> amount;
          for (int i=0; i < amount; i++)
          {
            cout<<"Enter your " <<amount-i<<" numbers consecutively: ";
            cin >> UserSetAmount;
            UserSet.insert(UserSetAmount);
          }
          break;
        }
        case(2):
        {

          cout << "Which number do you want to earse specifically: ";
          cin >> earseValue;
          UserSet.erase(earseValue);

          break;
        }
        case(3):
        {
          // Start of Case 3

          set<int>::iterator ittyBitty = UserSet.begin();
          ittyBitty++;
          cout<<"Here are your sorted set!" <<endl;
          for( auto ittyBitty:UserSet)
          {
            cout << ittyBitty <<endl;
          }
            break;
        }

      }

      choice = MenuChoice(); // will keep displaying until they wanna exit.
    }

    cout << "Exiting...\n";
  return 0;
}
