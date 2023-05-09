#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "SpamAndHam.h"

//-----------------------------------------------------------------------------
namespace command
{
    void space(std::size_t size)
    {
        for(size_t i = 0; i < size; i++)
            std::cout << std::endl;
    }
}
//-----------------------------------------------------------------------------
std::vector<char>ClassFunction(std::ifstream&);
std::vector<std::string>Words(std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>,bool);
std::vector<std::vector<std::string>> Document(std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>,bool);
std::vector<std::string>B1(std::vector<std::string>,std::vector<std::string>,std::vector<std::vector<std::string>>,bool);
std::vector<std::string>B2(std::vector<std::string>,std::vector<std::string>,std::vector<std::vector<std::string>>,bool);
std::vector<std::vector<std::string>> Email(std::vector<char>,std::ifstream&,bool);
std::vector<std::vector<std::string>> BinaryVectorFunction(std::ifstream&);
std::vector<std::string>Fraction(std::vector<std::string>,std::vector<std::string>,size_t,size_t,bool);

int ConvertNumerator(std::string);
int ConvertDenominator(std::string);
int StringToInt(char);

std::string BayesFormula(char,std::string);

void Simplify(int&,int&);

//-----------------------------------------------------------------------------
int main()
{
    std::ifstream read ("toy.class.txt", std::ios::in);
    
                         std::vector<char>Class;
    
                  std::vector<std::string>HamWords,
                                          SpamWords,
                                          HamFraction,
                                          SpamFraction,
                                          b1Spam,
                                          b1Ham,
                                          b2Spam,
                                          b2Ham;
                  
    std::vector<std::vector<std::string>> Ham,
                                          Spam,
                                          HamDocument,
                                          SpamDocument,
                                          BinaryVector;

        Class = ClassFunction(read);
        Ham = Email(Class,read,false);
        Spam = Email(Class,read,true);
        HamDocument = Document(Ham,Spam,false);
        SpamDocument = Document(Ham,Spam,true);
        BinaryVector = BinaryVectorFunction(read);
        HamWords = Words(HamDocument,SpamDocument,false);
        SpamWords = Words(HamDocument,SpamDocument,true);
        HamFraction = Fraction(HamWords,SpamWords,Ham.size(),Spam.size(),false);
        SpamFraction = Fraction(HamWords,SpamWords,Ham.size(),Spam.size(),true);
    
        b1Spam = B1(HamFraction,SpamFraction,BinaryVector,true);
        b1Ham = B1(HamFraction,SpamFraction,BinaryVector,false);
        b2Spam = B2(HamFraction,SpamFraction,BinaryVector,true);
        b2Ham = B2(HamFraction,SpamFraction,BinaryVector,false);
    
        SpamAndHam *SpamArray_b1 = new SpamAndHam[SpamFraction.size()];
        SpamAndHam *SpamArray_b2 = new SpamAndHam[SpamFraction.size()];
        SpamAndHam *HamArray_b1 = new SpamAndHam[HamFraction.size()];
        SpamAndHam *HamArray_b2 = new SpamAndHam[HamFraction.size()];
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamArray_b1[i] = b1Spam[i];
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamArray_b2[i] = b2Spam[i];
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamArray_b1[i] = b1Ham[i];
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamArray_b2[i] = b2Ham[i];
    
    SpamAndHam SpamTest1("1/1"),
               HamTest1("1/1"),
               SpamTest2("1/1"),
               HamTest2("1/1");
    
    SpamAndHam PS = (std::to_string(Spam.size()) + '/'
    + std::to_string(Spam.size() + Ham.size()));
    
    SpamAndHam PH = (std::to_string(Ham.size()) + '/'
    + std::to_string(Spam.size() + Ham.size()));
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamTest1 *= SpamArray_b1[i];
        SpamTest1 *= PS;
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamTest1 *= HamArray_b1[i];
        HamTest1 *= PH;
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamTest2 *= SpamArray_b2[i];
        SpamTest2 *= PS;
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamTest2 *= HamArray_b2[i];
        HamTest2 *= PH;
    
    std::cout << "Test case 1: \n\t\tP(S|b) = " << SpamTest1;
    std::cout << "\t\tP(H|b) = " << HamTest1;
    std::cout << "\nTest case 2: \n\t\tP(S|b) = " << SpamTest2;
    std::cout << "\t\tP(H|b) = " << HamTest2;
    
    delete [] SpamArray_b1;
    delete [] SpamArray_b2;
    delete [] HamArray_b1;
    delete [] HamArray_b2;
    
    command::space(2);
    
    return 0;
}
//-----------------------------------------------------------------------------
std::vector<char>ClassFunction(std::ifstream&read)
{
    assert(read);
    std::vector<char>Class;
    for(char stream; !read.eof() && (read >> stream);)
    Class.push_back(stream); read.close(); return Class;
}
//-----------------------------------------------------------------------------
std::vector<std::vector<std::string>> Email(std::vector<char> Class, std::ifstream& read, bool status)
{
                              std::string output;
    
    std::vector<std::vector<std::string>> Ham,
                                          Spam;
    
                std::vector<std::string> TempHam,
                                         TampSpam;
    
    read.open("toy.data.txt", std::ios::in);

    int count = 0;
    assert(read);
    for(std::string stream; !read.eof() && (read >> stream);)
    {
        output += stream;
        
        if(read.peek() == '\n')
        {
        
        if(Class.at(count) == '0')
        {
            TempHam.push_back(output);
            Ham.push_back(TempHam);
            TempHam.clear();
            output.clear();
        }
            
        else if(Class.at(count) == '1')
        {
            TampSpam.push_back(output);
            Spam.push_back(TampSpam);
            TampSpam.clear();
            output.clear();
        }
            count++;
        }
        
    }
    
    count = 0;
    read.close();
    
    if(status)
        return Spam;
    else
        return Ham;
}
//-----------------------------------------------------------------------------
std::vector<std::vector<std::string>> Document(std::vector<std::vector<std::string>>Ham, std::vector<std::vector<std::string>>Spam, bool status)
{
    if(status)
    {
        std::string output;
        std::vector<std::string>Temp;
        std::vector<std::vector<std::string>>SpamDocument;
       
        
        for(std::vector<std::string>::size_type i = 0; i < Spam[0][0].size(); i++)
        {
            for(std::vector<std::string>::size_type j = 0; j < Spam.size(); j++)
                output += Spam[j][0][i];
            
                Temp.push_back(output);
                SpamDocument.push_back(Temp);
                Temp.clear();
                output.clear();
        }
        
        return SpamDocument;
    }
    else
    {
        std::string output;
        std::vector<std::string>Temp;
        std::vector<std::vector<std::string>>HamDocument;
       
        for(std::vector<std::string>::size_type i = 0; i < Ham[0][0].size(); i++)
        {
            for(std::vector<std::string>::size_type j = 0; j < Ham.size(); j++)
                output += Ham[j][0][i];
            
                Temp.push_back(output);
                HamDocument.push_back(Temp);
                Temp.clear();
                output.clear();
        }
        
        return HamDocument;
    }
}
//-----------------------------------------------------------------------------
std::vector<std::vector<std::string>> BinaryVectorFunction(std::ifstream &read)
{
    read.open("toytest.data.txt");
    std::string output;
    std::vector<std::string>Temp;
    std::vector<std::vector<std::string>> BinaryVector;
    
    for(std::string stream; !read.eof() && (read >> stream);)
    {
        output += stream;
        if(read.peek() == '\n')
        {
            
            Temp.push_back(output);
            BinaryVector.push_back(Temp);
            output.clear();
            Temp.clear();
            command::space(1);
        }
    }
    read.close();
    return BinaryVector;
}
//-----------------------------------------------------------------------------
std::vector<std::string>Words(std::vector<std::vector<std::string>> HamDocument,std::vector<std::vector<std::string>> SpamDocument,bool status)
{
    if(status)
    {
        int count = 0;
        std::vector<std::string>SpamWords;
        for(std::vector<std::string>::size_type i = 0; i < SpamDocument.size(); i++)
        {
            for(std::vector<std::string>::size_type j = 0; j < SpamDocument[i][0].size(); j++)
                if(SpamDocument[i][0][j] == '1')
                        ++count;
                   
                SpamWords.push_back(std::to_string(count));
                count = 0;
        }
        return SpamWords;
    }
    
    else
    {
        int count = 0;
        std::vector<std::string>HamWords;
        for(std::vector<std::string>::size_type i = 0; i < HamDocument.size(); i++)
        {
            for(std::vector<std::string>::size_type j = 0; j < HamDocument[i][0].size(); j++)
                if(HamDocument[i][0][j] == '1')
                   ++count;
               
                HamWords.push_back(std::to_string(count));
                count = 0;
        }
        return HamWords;
    }
}
//-----------------------------------------------------------------------------
std::vector<std::string>Fraction(std::vector<std::string> HamWords,std::vector<std::string> SpamWords, size_t hamDenominator, size_t spamDenominator, bool status)
{
    if(status)
    {
        std::vector<std::string>SpamFraction;
        for(std::vector<std::string>::size_type i = 0; i < SpamWords.size(); i++)
            SpamFraction.push_back(SpamWords[i] + '/' + std::to_string(spamDenominator));
                return SpamFraction;
    }
    else
    {
        std::vector<std::string>HamFraction;
        for(std::vector<std::string>::size_type i = 0; i < HamWords.size(); i++)
            HamFraction.push_back(HamWords[i] + '/' + std::to_string(hamDenominator));
                return HamFraction;
    }
}

//-----------------------------------------------------------------------------
std::vector<std::string>B1(std::vector<std::string>HamFraction,std::vector<std::string>SpamFraction,std::vector<std::vector<std::string>>BinaryVector,bool status)
{
    std::vector<std::string>B1;
    
    if(status)
    for(std::vector<std::string>::size_type i = 0; i < SpamFraction.size(); i++)
        B1.push_back(BayesFormula(BinaryVector[0][0][i],SpamFraction[i]));

    else
        for(std::vector<std::string>::size_type i = 0; i < HamFraction.size(); i++)
            B1.push_back(BayesFormula(BinaryVector[0][0][i],HamFraction[i]));
    
    return B1;
}
//-----------------------------------------------------------------------------
std::vector<std::string>B2(std::vector<std::string>HamFraction,std::vector<std::string>SpamFraction,std::vector<std::vector<std::string>>BinaryVector,bool status)
{
    std::vector<std::string>B2;
    
    if(status)
    for(std::vector<std::string>::size_type i = 0; i < SpamFraction.size(); i++)
        B2.push_back(BayesFormula(BinaryVector[1][0][i],SpamFraction[i]));

    else
        for(std::vector<std::string>::size_type i = 0; i < HamFraction.size(); i++)
            B2.push_back(BayesFormula(BinaryVector[1][0][i],HamFraction[i]));
    
    return B2;
}
//-----------------------------------------------------------------------------
int ConvertNumerator(std::string fraction)
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
int ConvertDenominator(std::string fraction)
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
int StringToInt(char word)
{
    std::string temp;
    int digit;
    temp.push_back(word);
    std::stringstream s(temp);
    s >> digit;
    
    return digit;
}
//-----------------------------------------------------------------------------
std::string BayesFormula(char binary,std::string fraction)
{
    int numerator,
        denominator;
    std::string bayesFormula;
    
    if(StringToInt(binary) * double(ConvertNumerator(fraction)) / double(ConvertDenominator(fraction)) == 0)
    {
        numerator = ConvertDenominator(fraction) - ConvertNumerator(fraction);
        Simplify(numerator,denominator = ConvertDenominator(fraction));
        return ( std::to_string(numerator) + '/' + std::to_string(denominator) );
       
    }
    else
    {
        Simplify(numerator = ConvertNumerator(fraction), denominator = ConvertDenominator(fraction));
        return ( std::to_string(numerator) + '/' + std::to_string(denominator) );
    }
}
//-----------------------------------------------------------------------------
void Simplify(int &numerator,int &denominator)
{
    int commonFactor = 0;
    
    for(int i = 1; i <= denominator; i++)
        if( (numerator % i == 0) && (denominator % i == 0) )
            commonFactor = i;
            numerator = (numerator/commonFactor);
            denominator = (denominator/commonFactor);
}
//-----------------------------------------------------------------------------
