#include "LinkedList.h"
#include "Node.h"
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
//--------------------------------------------------------------
LinkedList::LinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}
//--------------------------------------------------------------
LinkedList::LinkedList(std::string&name, int&number, int counter, float&wholesale_cost, float&price, bool&wholesale_bool, char&save_option, char&wholesale_option)
{
    do
        {
    cout << "\n-------- Item #" << ++counter << ": --------\n";
    cout << "Item: ";
    cin.ignore();
    getline(cin,name);

    cout << "\nWould you like to include \nwholesale cost of item (Y/N) ? ";
    cin >> wholesale_option; wholesale_option = toupper(wholesale_option);
    
    while(wholesale_option!='Y' && wholesale_option!='y' && wholesale_option!='N' && wholesale_option!='n')
    {
        cout << "\nInvalid entry, please re-enter: ";
        cin >> wholesale_option; wholesale_option = toupper(wholesale_option);
    }
    
    if(wholesale_option=='Y')
    {
        cout << "\nWholesale Cost: $";
        cin >> wholesale_cost;
    }
    
    cout << "\nNumber of items \nadded to machine: ";
    cin >> number;
    
    cout << "\nRe-sale price each item: $";
    cin >> price;
    
    cout << "\nWould you like to save \ninformation ? (Y/N) ? ";
    cin >> save_option; save_option = toupper(save_option);
    
    while(save_option!='Y' && save_option!='y' && save_option!='N' && save_option!='n')
    {
        cout << "\nInvalid entry, please re-enter: ";
        cin >> save_option; save_option = toupper(save_option);
    }
            if(save_option=='N') cout << "\nPlease re-input information. \n";
    
}while(save_option=='N');
}
//--------------------------------------------------------------
Node* LinkedList::Input()
{
    int number;
    //'number,' represents the number of items the users chooses to select.
    
    int counter; //Includes the amount of items the user adds.
    
    string name;
    //Represents the name of item.
    
    float price,wholesale_cost;
    //'price' represents the cost of each item.
    //'wholesale_cost' represents the cost the user paid for each item.
    
    char option, wholesale_option,save_option,insert_option,delete_option;
    //'option' allows the user to insert a new item within the switch statement
    //'wholesale_option' gives the user the option to add a whole sale amount as their expense.
    // 'save_option' gives the user the option to save the inputted infomation.  If they choose 'yes' the information will be automatically stored within the Linked List.  If they choose 'no' the information not be saved and as a result the user will be prompted to re-input the necessary information.
    //'insert_option' gives the user the option to create new node.
    // 'delete_option' gives the user the choice to delete the selected information by typing in the name of the item.
    
    bool wholesale_bool=false, delete_bool=false;
    //'wholesale_bool' determines if wholesale price needs to be accounted for in linked list.
    //'delete_bool' determines if the determined Node has been deleted.  If it has, then delete_bool will remain false.  Otherwise, it will be assigned as 'true' and will automatically give the user the option to re-do deletion.
    
    float Gross, Net;
    //'Gross' represents the total amount the user is projected to make for each item.  However, this amount excludes the wholesale cost of the particular item. Formula: gross_total = (price * number)
    //'Net' represents the total amount the user is projected to make for each item minus the wholesale cost.  Formula: net_total = (price * number) - wholesale_cost
    //'price' represents the cost of each item.
    if(this->GetSize()<=0) Node*head=NULL;
    else head = this->head;
    LinkedList *link;
    
    do
    {
        counter = this->GetSize();
  LinkedList list(name,number,counter,wholesale_cost,price,wholesale_bool,save_option,wholesale_option);
        
        Gross = GetGross(number,price);
        Net = GetNet(number,wholesale_cost,price,WholeSaleBool(wholesale_option));

        WholeSaleBool(wholesale_option) ? head = Insert(head,name,number,wholesale_cost,Gross,Net,price,true) : head = Insert(head,name,number,wholesale_cost,Gross,Net,price,false);
     
        cout << "\nItem successfully added.\n";
        
        Search(name); //prints information.
        
        cout << "Would you like to insert \nan additional item (Y/N) ? ";
        cin >> insert_option; insert_option = toupper(insert_option);
        
        while(insert_option!='Y' && insert_option!='y' && insert_option!='N' && insert_option!='n')
        {
            cout << "\nInvalid entry, please re-enter: ";
            cin >> insert_option; insert_option = toupper(insert_option);
        }
        
        if(insert_option=='N') cout << "\nRe-directing back to menu\n";
 
    }while(insert_option=='Y');
    
   // wholesale_bool==false; //This will reset the wholesale_bool.  Therefore, the user will have the option insert a wholesale cost for future items.
    
    return head;
}
//--------------------------------------------------------------
Node*LinkedList::Insert(Node*node,std::string title,int num, float wholesale, float gross_profit, float net_profit, float amount,bool wholesale_bool)
{
    
    if(node==NULL)
    {
        node=new Node(title,num,wholesale,gross_profit,net_profit,amount,wholesale_bool);
        this->head=node;
        this->tail=node;
        this->size++;
    }
    else
    {
        Node *NewNode = new Node(title,num,wholesale,gross_profit,net_profit,amount,wholesale_bool);
        tail->SetNext(NewNode);
        tail = NewNode;
        this->size++;
    }
    
    return node;
}
//--------------------------------------------------------------
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
        cout << endl << title << " has been successfully deleted.\n";
    }
    else {del = false;}
}
//--------------------------------------------------------------
int LinkedList::GetSize() const
{
    return size;
}
//--------------------------------------------------------------
bool LinkedList::WholeSaleBool(char wholesale_option)
{
    if(wholesale_option=='Y')
    return true; return false;
}
//--------------------------------------------------------------
bool LinkedList::Search(std::string title)
{
    Node *NodePointer = this->head;
    
    while(NodePointer!=NULL)
    {
        if(NodePointer && NodePointer->GetName() == title)
        {
            cout << "\nInformation found.\n";
            NodePointer->PrintNode();
            return true;
        }
        NodePointer = NodePointer->GetNext();
    }
    cout << endl << title << " not found. \n";
    return false;
}
//--------------------------------------------------------------
float LinkedList::GetGross(int number, float price){float gross = number * price; return gross;}
//--------------------------------------------------------------
float LinkedList::GetNet(int number, float wholesale_cost, float price, bool wholesale_bool)
{
    float net;
    (wholesale_bool) ? net = (number * price) - wholesale_cost : (net = 0, wholesale_cost = 0);
    return net;
}
//--------------------------------------------------------------
