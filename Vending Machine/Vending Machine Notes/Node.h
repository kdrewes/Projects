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

#ifndef NODE_h
#define NODE_h
#include<string>

class Node
{
private:
    std::string name;
    
    int number;
    
    double wholesale,
           gross,
           net,
           price,
           grossTotal,
           netTotal;
    
    bool wholesaleBool;
    
    struct Node*next;
    
public:
    //Default Constructor
    Node();
    
    //Paramaterized Constructor
    Node(std::string, int, double, double, double, double, bool);
    
    //Mutator for name
    void SetName(std::string);
    
    //Mutator for next
    void SetNext(Node*);
    
    //Prints content for particular node
    void PrintNode();
    
    //Accessor for name variable
    std::string GetName();
    
    //Accessor for next pointer
    Node* GetNext();
};

#endif
