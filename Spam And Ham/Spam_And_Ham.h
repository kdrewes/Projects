#ifndef Bayes_h
#define Bayes_h
#include<iostream>

class Bayes
{
    
private:
    int numerator,
        denominator;
     
    double total;

    
public:
    Bayes();
    Bayes(std::string);
    
    Bayes operator *= (Bayes&);
    Bayes operator * (Bayes&);
    
    friend std::ostream &operator
    << (std::ostream&, Bayes&);
    
    void Simplify(int,int);
    void SetNumerator(int);
    void SetDenominator(int);
    void SetTotal(double);
    
    int ConvertNumerator(std::string) const;
    int ConvertDenominator(std::string) const;
    int GetNumerator() const;
    int GetDenominator() const;
    
    double GetTotal() const;
};

#endif
