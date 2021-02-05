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
    std::string name;
    int number;
    float wholesale,gross,net,price,gross_total,net_total;
    bool wholesale_bool;
    struct Node*next;
public:
    Node();
    Node(std::string title,
                      int num, 
                   float _wholesale, 
                   float gross_profit, 
                   float net_profit,
                   float amount,
                   bool wholesale_bool);
    std::string GetName();
    void SetName(std::string title);
    
    void SetNext(Node*);
    Node* GetNext();
   
    void PrintNode();


      
};

#endif
