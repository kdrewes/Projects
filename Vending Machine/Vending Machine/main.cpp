#include "LinkedList.h"
#include <iostream>
#include <iomanip>
//--------------------------------------------------------------

int Menu()
{
    int menu;
    
    std::cout << "\n-------------- Menu: --------------\n";
    std::cout << "1) Add" << "\t\t\t\t\t2) Delete\n\n";
    std::cout << "3) Display" << "\t\t\t\t4) Exit\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Select: ";
    std::cin >> menu;

    return menu;
}
//--------------------------------------------------------------
int Process(int menu, LinkedList* VendingMachine)
{
    switch (menu)
    {
    case 1:
    {
        VendingMachine->Input();
        break;
    }
    case 2:
    {
      
        int number = 0;
        std::string name;
        
        double price = 0,
               wholesaleCost = 0;
        
         char option = 'Y',
              wholesaleOption = 'Y',
              saveOption = 'Y',
              insertOption = 'Y',
              deleteOption = 'Y';
        
         bool wholesaleBool = false,
              deleteBool = false;
        
        double gross, net;

        do
        {
            std::cout << "\nEnter name of item \nyou choose to delete: ";
            std::cin.ignore();
            std::getline(std::cin, name); name[0] = toupper(name[0]);

                VendingMachine->Remove(name,deleteBool);

                if (deleteBool == false)
                {
                    std::cout << "\nNo information was deleted\n";
                    std::cout << "Would you like to re-do deletion (Y/N) ? ";
                    std::cin >> deleteOption; deleteOption = toupper(deleteOption);

                    while (deleteOption != 'Y' && deleteOption != 'N')
                    {
                        std::cout << "\nInvalid entry, please re-enter: ";
                        std::cin >> deleteOption; deleteOption = toupper(deleteOption);
                    }
                }
                else if(deleteBool==true && VendingMachine->GetSize()>=1)
                {
                    
                    std::cout << "\nWould you like to \ndelete an additional item (Y/N) ? ";
                    std::cin >> deleteOption; deleteOption = toupper(deleteOption);
                }
                else if (deleteBool == true && VendingMachine->GetSize() == 0)
                {
                    deleteOption = 'N';
                    std::cout << "\nRe-directing back to menu";
                }
                    
        }while(deleteOption == 'Y');
        break;
        }
    case 3:
    {
        VendingMachine->Print();
        break;
    }

    case 4:
    {
        std::cout << "\nExit received.\n";
        std::cout << "Ending Program\n\n";
        break;
    }

    default:
        std::cout << "\nInvalid option, please re-enter: ";
        break;
    }
    return menu;
}
//--------------------------------------------------------------
int main()
{
    int menu=0;
    
    LinkedList *VendingMachine = new LinkedList ();
    
  while(menu!=4)
  {
        menu = Menu();

        Process(menu,VendingMachine);
  }
    
    return 0;
}
