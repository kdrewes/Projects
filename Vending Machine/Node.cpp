#include"Node.h"
#include"LinkedList.h"
#include<iostream>
#include<iomanip>
#include<string>

using namespace std;
//--------------------------------------------------------------
Node::Node()
{
    name = "UNKNOWN";
    number = 0;
    price = 0.0;
    wholesale = 0.0;
    gross = 0.0;
    net = 0.0;
    price = 0.0;
    wholesale_bool;
    next = NULL;
}
//--------------------------------------------------------------
Node::Node(std::string title,
                              int num,
                           float _wholesale,
                           float gross_profit,
                           float net_profit,
                           float amount,
                           bool wholesale_bool)
{
        name  = title;
        number = num;
        price = amount;
        wholesale = _wholesale;
        gross = gross_profit;
        net = net_profit;
        price = amount;
        this->wholesale_bool = wholesale_bool;
        next = NULL;
}
//--------------------------------------------------------------
 void Node:: SetNext(Node* n)
{
     next = n;
}
//--------------------------------------------------------------
 Node* Node::GetNext()
{
     return next;
}
//--------------------------------------------------------------
void Node::SetName(std::string n)
{
    name = n;
}
//--------------------------------------------------------------
std::string Node::GetName()
{
    return name;
}
//--------------------------------------------------------------
void Node::PrintNode()
{
        if(wholesale_bool==true)
        {
            cout << setprecision(2) << fixed;
            
            name[0] = toupper(name[0]);
            
            cout << "\n--------------------- " << name << ": ---------------------\n";
            
            cout << "Item Name: " << name  << "\t\t\tPrice: $" << price  << left << endl;
            
            cout << "\nNumber of Items: " << number << "\t\t\tWholesale Cost: $" << wholesale << left << endl;
            
            cout << "\nGross Profit: $" << gross << "\t\tNet Profit: $" <<  net << left;
        }
        else
        {
            cout << setprecision(2) << fixed;
            
            name[0] = toupper(name[0]);
            
            cout << "\n------------------- " << name << ": -------------------\n";
            
            cout << "Item Name: " << name  << "\t\t\tNumber of items: " << number  << left << endl;

            cout << "\nPrice: $" << price << "\t\t\t\tProfit: $" << gross << left;
            
        }
    cout << endl << endl;
}
//--------------------------------------------------------------
