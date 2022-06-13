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
