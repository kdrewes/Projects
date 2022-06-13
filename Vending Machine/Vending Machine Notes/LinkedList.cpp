#include "LinkedList.h"
#include "Node.h"
#include<iostream>
#include<iomanip>
#include<string>

//--------------------------------------------------------------
//Default Constructor
LinkedList::LinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}
//--------------------------------------------------------------
//Paramaterized Constructor
LinkedList::LinkedList(std::string &name, int &number, int counter, double &wholesaleCost, double &price, bool &wholesaleBool, char &saveOption, char &wholesaleOption)
{
    do
        {
    std::cout << "\n-------- Item #" << ++counter << ": --------\n";
    std::cout << "Item: ";
    std::cin.ignore();
    getline(std::cin,name);

    std::cout << "\nWould you like to include \nwholesale cost of item (Y/N) ? ";
    std::cin >> wholesaleOption; wholesaleOption = toupper(wholesaleOption);
    
    while(wholesaleOption!='Y' && wholesaleOption!='y' && wholesaleOption!='N' && wholesaleOption!='n')
    {
        std::cout << "\nInvalid entry, please re-enter: ";
        std::cin >> wholesaleOption; wholesaleOption = toupper(wholesaleOption);
    }
    
    if(wholesaleOption=='Y')
    {
        std::cout << "\nWholesale Cost: $";
        std::cin >> wholesaleCost;
    }
    
        std::cout << "\nNumber of items \nadded to machine: ";
        std::cin >> number;
    
        std::cout << "\nRe-sale price each item: $";
        std::cin >> price;
    
        std::cout << "\nWould you like to save \ninformation ? (Y/N) ? ";
        std::cin >> saveOption; saveOption = toupper(saveOption);
    
    while(saveOption!='Y' && saveOption!='y' && saveOption!='N' && saveOption!='n')
    {
        std::cout << "\nInvalid entry, please re-enter: ";
        std::cin >> saveOption; saveOption = toupper(saveOption);
    }
            if(saveOption=='N') std::cout << "\nPlease re-input information. \n";
    
}while(saveOption=='N');
}
//--------------------------------------------------------------
//Input data
Node* LinkedList::Input()
{
    //'number,' represents the number of items the users chooses to select.
    int number;
    
    //Includes the amount of items the user adds.
    int counter;
    
    //Represents the name of item.
    std::string name;
    
    //'price' represents the cost of each item.
    //'wholesaleCost' represents the cost the user paid for each item.
    double price,
           wholesaleCost;
    
    //'option' allows the user to insert a new item within the switch statement
    //'wholesaleOption' gives the user the option to add a whole sale amount as their expense.
    // 'saveOption' gives the user the option to save the inputted infomation.  If they choose 'yes' the information will be automatically stored within the Linked List.  If they choose 'no' the information not be saved and as a result the user will be prompted to re-input the necessary information.
    //'insertOption' gives the user the option to create new node.
    // 'deleteOption' gives the user the choice to delete the selected information by typing in the name of the item.
    char option,
         wholesaleOption,
         saveOption,
         insertOption,
         deleteOption;
 
    //'wholesaleBool' determines if wholesale price needs to be accounted for in linked list.
    //'deleteBool' determines if the determined Node has been deleted.  If it has, then deleteBool will remain false.  Otherwise, it will be assigned as 'true' and will automatically give the user the option to re-do deletion.
    bool wholesaleBool = false,
         deleteBool = false;
    
    //'gross' represents the total amount the user is projected to make for each item.  However, this amount excludes the wholesale cost of the particular item. Formula: grossTotal = (price * number)
    //'net' represents the total amount the user is projected to make for each item minus the wholesale cost.  Formula: net_total = (price * number) - wholesaleCost
    //'price' represents the cost of each item.
    double gross,
           net;

    if(this->GetSize()<=0) Node*head=NULL;
    else head = this->head;
    LinkedList *link;
    
    do
    {
        counter = this->GetSize();
  LinkedList list(name,number,counter,wholesaleCost,price,wholesaleBool,saveOption,wholesaleOption);
        
        gross = Getgross(number,price);
        net = Getnet(number,wholesaleCost,price,WholeSaleBool(wholesaleOption));

        WholeSaleBool(wholesaleOption) ? head = Insert(head,name,number,wholesaleCost,gross,net,price,true) : head = Insert(head,name,number,wholesaleCost,gross,net,price,false);
     
        std::cout << "\nItem successfully added.\n";
        
        Search(name);
        
        std::cout << "Would you like to insert \nan additional item (Y/N) ? ";
        std::cin >> insertOption; insertOption = toupper(insertOption);
        
        while(insertOption!='Y' && insertOption!='y' && insertOption!='N' && insertOption!='n')
        {
            std::cout << "\nInvalid entry, please re-enter: ";
            std::cin >> insertOption; insertOption = toupper(insertOption);
        }
        
        if(insertOption=='N') std::cout << "\nRe-directing back to menu\n";
 
    }while(insertOption=='Y');
    
    return head;
}
//--------------------------------------------------------------
//Inserts item
Node*LinkedList::Insert(Node*node,std::string title,int num, double wholesale, double grossProfit, double netProfit, double amount,bool wholesaleBool)
{
    
    if(node==NULL)
    {
        node=new Node(title,num,wholesale,grossProfit,netProfit,amount,wholesaleBool);
        this->head=node;
        this->tail=node;
        this->size++;
    }
    else
    {
        Node *NewNode = new Node(title,num,wholesale,grossProfit,netProfit,amount,wholesaleBool);
        tail->SetNext(NewNode);
        tail = NewNode;
        this->size++;
    }
    
    return node;
}
//--------------------------------------------------------------
//Prints content of all nodes
void LinkedList::Print()
{
    Node*NodePointer = this->head;
    
    while(NodePointer!=NULL)
    {
        NodePointer->PrintNode();
        
        NodePointer = NodePointer->GetNext();
    }
}
//--------------------------------------------------------------
//Removes data
void LinkedList::Remove(std::string title, bool& del)
{
    Node* current = head;
    Node* previous = NULL;
    bool valid = false;

    while ((current != NULL) && (valid == false))
    {
        if (current->GetName() == title)
        {
            valid = true;
            del = true;
            break;
        }
        else
        {
            previous = current;
            current = current->GetNext();
        }
    }
    if (valid == true)
    {
        if (previous != NULL){previous->SetNext(current->GetNext());}
        else {head = current->GetNext();}
        
        if(previous->GetNext()==NULL) {tail = previous;}
        
        delete current;
        size--;
        std::cout << std::endl << title << " has been successfully deleted.\n";
    }
    else {del = false;}
}
//--------------------------------------------------------------
//Keeps track of size of linked list
int LinkedList::GetSize() const
{
    return size;
}
//--------------------------------------------------------------
//Determines if user wishes to input whole sale option
bool LinkedList::WholeSaleBool(char wholesaleOption)
{
    if(wholesaleOption=='Y')
    return true; return false;
}
//--------------------------------------------------------------
//Searches for name of item
bool LinkedList::Search(std::string title)
{
    Node *NodePointer = this->head;
    
    while(NodePointer!=NULL)
    {
        if(NodePointer && NodePointer->GetName() == title)
        {
            std::cout << "\nInformation found.\n";
            NodePointer->PrintNode();
            return true;
        }
        NodePointer = NodePointer->GetNext();
    }
    std::cout << std::endl << title << " not found. \n";
    return false;
}
//--------------------------------------------------------------
//Accessor for gross profit
double LinkedList::Getgross(int number, double price){double gross = number * price; return gross;}
//--------------------------------------------------------------
//Accessor for net profit
double LinkedList::Getnet(int number, double wholesaleCost, double price, bool wholesaleBool)
{
    double net;
    (wholesaleBool) ? net = (number * price) - wholesaleCost : (net = 0, wholesaleCost = 0);
    return net;
}
//--------------------------------------------------------------
