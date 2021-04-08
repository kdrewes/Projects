/**
 Demonstrate your understanding of linked lists by selecting a problem that can be solved with the utilization of linked lists.
 You must use pointers in building your linked list (you must demonstrate your understanding of pointers within the implementation of your linked list).
 You MUST modularize your code ( meaning, there must be functions written for each piece of functionality that you write... at the very least, the following functions should be obvious.
 add(),
 delete(),
 print() and
 main()
 
 //Notes:
 In this program, I will be creating a vending machine which will allow the user to the create an inventory for their customers.  This program will also calculate the gross/net profit by prompting the user to input the wholesale cost of each item.  Please let me know if you have any quesitons.  Thank you
 */
#include "LinkedList.h"
#include <iostream>
#include <iomanip>
using namespace std;
//--------------------------------------------------------------
//Functions:
int Menu() //Main menu function
{
   
    int menu; //Allows user to select option.
    

        cout << "\n-------------- Menu: --------------\n";
        cout << "1) Add" << "\t\t\t\t\t2) Delete\n\n";
        cout << "3) Display" << "\t\t\t\t4) Exit\n";
        cout << "-----------------------------------\n";
        cout << "Select: ";
        cin >> menu;

    return menu;
}
//--------------------------------------------------------------
int Process(int menu, LinkedList* VendingMachine) //Process contains each individual menu option
{
    switch (menu)
    {
    case 1:
    {
        VendingMachine->Input(); //Allows user to input variables through the linked list.
        break;
    }
    case 2:
    {
        //Deletes an item from vending machine
        int number = 0;
        string name;
        float price = 0, 
              wholesale_cost = 0;
        char option = 'Y', 
             wholesale_option = 'Y', 
             save_option = 'Y', 
             insert_option = 'Y', 
             delete_option = 'Y';
        bool wholesale_bool = false,
             delete_bool = false;
        float Gross, Net;

        do
        {
                cout << "\nEnter name of item \nyou choose to delete: ";
                cin.ignore();
                getline(cin, name); name[0] = toupper(name[0]);

                VendingMachine->Remove(name,delete_bool);

                if (delete_bool == false)
                {
                    cout << "\nNo information was deleted\n";
                    cout << "Would you like to re-do deletion (Y/N) ? ";
                    cin >> delete_option; delete_option = toupper(delete_option);

                    while (delete_option != 'Y' && delete_option != 'N')
                    {
                        cout << "\nInvalid entry, please re-enter: ";
                        cin >> delete_option; delete_option = toupper(delete_option);
                    }
                }
                else if(delete_bool==true && VendingMachine->GetSize()>=1)
                {
                    
                    cout << "\nWould you like to \ndelete an additional item (Y/N) ? ";
                    cin >> delete_option; delete_option = toupper(delete_option);
                }
                else if (delete_bool == true && VendingMachine->GetSize() == 0)
                {
                    delete_option = 'N';
                    cout << "\nRe-directing back to menu";
                }
                    
        }while(delete_option == 'Y');
        break;
        }
    case 3:
    {
        VendingMachine->Print();
        break;
    }

    case 4:
    {
        cout << "\nExit received.\n";
        cout << "Ending Program\n\n";
        break;
    }

    default:
        cout << "\nInvalid option, please re-enter: ";
        break;
    }
    return menu;
}
//--------------------------------------------------------------
int main()
{
    int menu=0;    //'Menu' represents each menu option the user chooses to select. the variable,
    
    LinkedList *VendingMachine = new LinkedList ();//Object of Link List. The user will have the ability to add,delete and view all the stored information.
    
  while(menu!=4)
  {
        menu = Menu();

        Process(menu,VendingMachine);
  }
    
    return 0;
}
