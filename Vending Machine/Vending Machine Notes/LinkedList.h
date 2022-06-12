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

#ifndef LinkedList_h
#define LinkedList_h
#include <string>
#include "Node.h"

class LinkedList
{
public:
    //Pointers variables used for Linked List
    Node*head;
    Node*tail;
    int size;
    
    //Default Constructor
    LinkedList();
    
    //Paramaterized Constructor
    LinkedList(std::string&, int&, int, double&, double&, bool&, char&, char&);
    
    //Input data
    Node* Input();
    
    //Insert node
    Node* Insert(Node *head, std::string, int, double, double, double, double, bool);
    
    //Remove node
    void Remove(std::string, bool&);
    
    //Print content
    void Print();
    
    //Used to display one node
    void DisplayNode() const;
    
    //Determine how many nodes exist
    int GetSize() const;
    
    //Determines if user wants to calculate whole sale price
    bool WholeSaleBool(char);
    
    //Seaches for nodes through name of item
    bool Search(std::string);
    
    //Accessor for gross profit
    double Getgross(int, double);
    
    //Accessor for net profit
    double Getnet(int, double, double, bool);
    
};

#endif
