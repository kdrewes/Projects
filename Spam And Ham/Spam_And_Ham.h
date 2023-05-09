#ifndef Bayes_h
#define Bayes_h
#include<iostream>

class SpamAndHam
{
    
private:
    int numerator,
        denominator;
     
 double total;

    
public:
    SpamAndHam();
    SpamAndHam(std::string);
    
    SpamAndHam operator *= (SpamAndHam&);
    SpamAndHam operator * (SpamAndHam&);
    
    friend std::ostream &operator
    << (std::ostream&, SpamAndHam&);
    
    SpamAndHam Multiply(SpamAndHam&) const;
 
    void Simplify(int,int);
    void SetNumerator(int);
    void SetDenominator(int);
    void SetTotal(double);
    
    int GetNumerator() const;
    int GetDenominator() const;
    int ConvertNumerator(std::string) const;
    int ConvertDenominator(std::string) const;
    
    double GetTotal() const;
};

#endif
