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
    Node();
    Node(std::string, int, double, double, double, double, bool);
    
    void SetName(std::string);
    void SetNext(Node*);
    void PrintNode();
    
    std::string GetName();
    Node* GetNext();
};

#endif
