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
