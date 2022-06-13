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
    LinkedList(std::string&, int&, int, double&, double&, bool&, char&, char&);
    
    Node* Input();
    Node* Insert(Node *head, std::string, int, double, double, double, double, bool);
    
    void Remove(std::string, bool&);
    void Print();
    void DisplayNode() const;
    
    int GetSize() const;
    
    bool WholeSaleBool(char);
    bool Search(std::string);
    
    double Getgross(int, double);
    double Getnet(int, double, double, bool);
    
};

#endif
