#include "SpamAndHam.h"
#include<iostream>
#include<sstream>
//-----------------------------------------------------------------------------
SpamAndHam :: SpamAndHam()
{
    numerator = 0;
    denominator = 0;
    total = 0.0;
}
//-----------------------------------------------------------------------------
SpamAndHam :: SpamAndHam(std::string fraction)
{
    this -> numerator = ConvertNumerator(fraction);
    this -> denominator = ConvertDenominator(fraction); Simplify(numerator,denominator);
    this -> total = (double(GetNumerator()) / double(GetDenominator()));
}
//-----------------------------------------------------------------------------
int SpamAndHam :: ConvertNumerator(std::string fraction) const
{
    std::stringstream s;
    int numerator;
    std::size_t index = fraction.find('/');
    s.str(fraction.substr(0,index));
    s >> numerator;
    s.clear();
    s.str("");
    return numerator;
}
//-----------------------------------------------------------------------------
int SpamAndHam :: ConvertDenominator(std::string fraction) const
{
    std::stringstream s;
    int denominator;
    std::size_t index = fraction.find('/');
    s.str(fraction.substr(index+1,fraction.size()));
    s >> denominator;
    s.str("");
    s.clear();
    return denominator;
}
//-----------------------------------------------------------------------------
SpamAndHam SpamAndHam :: operator *= (SpamAndHam& o)
{
    this -> numerator *= o.numerator;
    this -> denominator *= o.denominator;
    SetTotal(double(numerator)/double(denominator));
    return *this;
}
//-----------------------------------------------------------------------------
SpamAndHam SpamAndHam :: operator * (SpamAndHam& o)
{
    SpamAndHam product;
    product.numerator = numerator * o.numerator;
    product.denominator = denominator * o.denominator;
    product.total = (double(numerator * o.numerator) / double(denominator * o.denominator));
    
    return product;
}
//-----------------------------------------------------------------------------
std::ostream &operator << (std::ostream &output, SpamAndHam &obj)
{
    output << obj.total << std::endl;
    return output;
}
//-----------------------------------------------------------------------------
void SpamAndHam :: Simplify(int numerator,int denominator)
{
    int commonFactor = 0;
    
    for(int i = 1; i <= denominator; i++)
        if( (numerator % i == 0) && (denominator % i == 0) )
            commonFactor = i;
            SetNumerator(numerator/commonFactor);
            SetDenominator(denominator/commonFactor);
}
//-----------------------------------------------------------------------------
void SpamAndHam :: SetNumerator(int numerator)
{
    this -> numerator = numerator;
}
//-----------------------------------------------------------------------------
void SpamAndHam :: SetDenominator(int denominator)
{
    this -> denominator = denominator;
}
//-----------------------------------------------------------------------------
void SpamAndHam:: SetTotal(double total)
{
    this -> total = total;
}
//-----------------------------------------------------------------------------
int SpamAndHam :: GetNumerator() const
{
    return numerator;
}
//-----------------------------------------------------------------------------
int SpamAndHam :: GetDenominator() const
{
    return denominator;
}
//-----------------------------------------------------------------------------
double SpamAndHam :: GetTotal() const
{
    return total;
}
//-----------------------------------------------------------------------------
