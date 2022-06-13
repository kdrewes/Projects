#include"Node.h"
#include"LinkedList.h"
#include<iostream>
#include<iomanip>
#include<string>

//--------------------------------------------------------------
//Defult Constructor
Node::Node()
{
    name = "";
    number = 0;
    price = 0.0;
    wholesale = 0.0;
    gross = 0.0;
    net = 0.0;
    price = 0.0;
    wholesaleBool;
    next = NULL;
}
//--------------------------------------------------------------
//Paramaterized Constructor
Node::Node(std::string name,int number, double wholesale, double gross, double net, double price,
bool wholesaleBool)
{
    this->name  = name;
    this->number = number;
    this->price = price;
    this->wholesale = wholesale;
    this->gross = gross;
    this->net = net;
    this->wholesaleBool = wholesaleBool;
    next = NULL;
}
//--------------------------------------------------------------
//Mutator for next pointer
 void Node:: SetNext(Node* n)
{
     next = n;
}
//--------------------------------------------------------------
//Accessor for next pointer
 Node* Node::GetNext()
{
     return next;
}
//--------------------------------------------------------------
//Mutator for name
void Node::SetName(std::string n)
{
    name = n;
}
//--------------------------------------------------------------
//Accessor for name
std::string Node::GetName()
{
    return name;
}
//--------------------------------------------------------------
//Prints content for particular node
void Node::PrintNode()
{
        if(wholesaleBool==true)
        {
            std::cout << std::setprecision(2) << std::fixed;
            
            name[0] = toupper(name[0]);
            
            std::cout << "\n--------------------- " << name << ": ---------------------\n";
            
            std::cout << "Item Name: " << name  << "\t\t\tPrice: $" << price  << std::left << std::endl;
            
            std::cout << "\nNumber of Items: " << number << "\t\t\tWholesale Cost: $" << wholesale << std::left << std::endl;
            
            std::cout << "\nGross Profit: $" << gross << "\t\tNet Profit: $" <<  net << std::left;
        }
        else
        {
            std::cout << std::setprecision(2) << std::fixed;
            
            name[0] = toupper(name[0]);
            
            std::cout << "\n------------------- " << name << ": -------------------\n";
            
            std::cout << "Item Name: " << name  << "\t\t\tNumber of items: " << number  << std::left << std::endl;

            std::cout << "\nPrice: $" << price << "\t\t\t\tProfit: $" << gross << std::left;
            
        }
    std::cout << std::endl << std::endl;
}
//--------------------------------------------------------------
