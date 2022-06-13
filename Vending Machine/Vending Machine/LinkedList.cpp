#include "LinkedList.h"
#include "Node.h"
#include<iostream>
#include<iomanip>
#include<string>

//--------------------------------------------------------------
LinkedList::LinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}
//--------------------------------------------------------------
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
Node* LinkedList::Input()
{
    int number;
    
    int counter;
    
    std::string name;
    
    double price,wholesaleCost;
    
    char option, wholesaleOption, saveOption, insertOption, deleteOption;
 
    bool wholesaleBool = false, deleteBool = false;
    
    double gross, net;

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
        std::cout << std::endl << title << " has been successfully deleted.\n";
    }
    else {del = false;}
}
//--------------------------------------------------------------
int LinkedList::GetSize() const
{
    return size;
}
//--------------------------------------------------------------
bool LinkedList::WholeSaleBool(char wholesaleOption)
{
    if(wholesaleOption=='Y')
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
double LinkedList::Getgross(int number, double price){double gross = number * price; return gross;}
//--------------------------------------------------------------
double LinkedList::Getnet(int number, double wholesaleCost, double price, bool wholesaleBool)
{
    double net;
    (wholesaleBool) ? net = (number * price) - wholesaleCost : (net = 0, wholesaleCost = 0);
    return net;
}
//--------------------------------------------------------------
