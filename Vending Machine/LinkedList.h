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
    Node*head;
    Node*tail;
    int size;
    
    LinkedList();
    LinkedList(std::string&title, int&num, int counter, float&_wholesale,float&amount, bool&wholesale_bool,char&save_option, char&wholesale_option);
    
    Node* Input();
    Node* Insert(Node*head, std::string title,int num, float _wholesale, float gross_profit, float net_profit, float amount, bool wholesale_bool); //If user selects not to use wholesale
    
    void Remove(std::string title,bool &del);
    void Print();
    void DisplayNode() const;
    
    int GetSize() const;
    
    bool WholeSaleBool(char wholesale_option);
    bool Search(std::string title);
    
    float GetGross(int number,float price);
    float GetNet(int number, float wholesale_cost,float price,bool wholesale_bool);
    
};

#endif
