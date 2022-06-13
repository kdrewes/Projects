/**** **************************************************************************************************************************
 Overview
 In this project, you will employ Bayes Theorem and Bernoulli principle for automatically classifying if an email message is a spam or not.
 Given a dictionary of words [w1, w2, ..., wn] , an email message can be represented using a "feature vector" comprising of several binary elements [f1, f2, ..., fn] . A binary element fi takes value 1 if the corresponding word wi in dictionary is present and is 0 if the word wi is not present. For example, let a dictionary constitute of the following words: "internet", "free", "business", "email", "people". Then an email can be represented using a binary feature vector of [1 0 0 1 1] which indicates this email contains the word "internet", "email" and "people". Each email will also have an associated binary label indicating if email is spam or not. For example, 1 will indicate email is spam and 0 will indicate email is ham (not spam).

 Now, let D represent an email represented in form of a bit string (binary feature vector) = [f1, f2, ..., fn] where each fi is either 0 or 1 indicating the presence or absence of word wi.
 Let C represent the "class" of the email. That is whether it is spam or not. There are two classes: C = S indicates spam and C = H indicates that email is ham (not spam).
 The task of Spam Classification then reduces to figuring out which probability out of p(S | D) and p(H |D) is higher. If p(S | D) > p(H |D), then the email can be classified as spam, otherwise it can be classified as ham.
 How to compute these "posterior" probabilities
 Consider the probability p(C | D). Using Bayes Theorem, we get
 p(C|D) ∝ p(D|C)p(C).
 The proportional sign is there because the denominator is common between p(S | D) and p(H | D) and can be factored out when comparing the two.
  
 Estimating p(C): p(C) is what is called the prior probability (that is, how likely an email message is spam/ham without observing any evidence). This is typically determined by empirical evidence such as the number of email messages that are spam/ham divided by total number of email messages.
  
 Estimating p(D | C): To estimate the likelihood, p(D | C), we will use the "Naive Bayes" assumption (this is a new term but it is the same as assumption of  conditional independence between events that we have spoken about in class such as independence between sequence of coin tosses). In particular for this problem, the Naive Bayes assumption states that the probability of each word occurring in the email is independent of the occurrences of the other words (This assumption is often incorrect but has shown remarkable results in classification tasks). This means we can write the document likelihood P(D | C) in terms of the individual word likelihoods P(wt |C) where P(wt | C) is the probability of word wt occurring in a email of class C; the probability of wt not occurring in a email of this class is given by (1 − P(wt | C) ). If we think of each wt as a coin toss with outcome as heads or tails (heads if word is occurring in email of class C, tails if not), then using the Bernoulli principle P(D | C) = ∏ ftP(wt |C) + (1- ft)(1-P(wt |C), where the product (t = 1, 2, ..., n) is over all the words in the dictionary. If word wt is present, then ft = 1 and the required probability is P(wt|C); if word wt is not present, then ft=0 and the required probability is 1−P(wt|C).
 Estimating P(wt |C): This can be estimated from a "training" set of emails of a specific class C (Recall C is either S or H; so we will need to estimate both P(wt | C = S) and P(wt | C=H) ) by measuring the relative frequency of emails of class C that contain word wt. That is, the number of emails of the class C in which the word wt occurs divided by total number of emails of the class C.
  
 Summary
 Given a training set of emails (each labelled with a class), and a set of K classes, we can estimate a Bernoulli spam classification model as follows:
 1.    Define the dictionary (will be provided in this project); the number of words in the dictionary defines the dimension of the feature vectors
 2.    Count the following in the training set:
 • N the total number of emails
 • Nk the number of emails labelled with class C=k, for k=S, H (That is, number of emails known to be spam and ham, respectively)
 • nk (wt ) the number of emails of class C = k containing word wt for every class and for each word in the dictionary (That is, frequency of occurrence of word wt in spam/ham emails)
 3.    Estimate the likelihoods p(wt | C = k)  = nk (wt ) / Nk
 4.    Estimate the priors p(C = k) = Nk/ N
 To classify an unlabelled email Dnew, we estimate the posterior probability for each class p(C = k | Dnew) for k = S, H using the equation
 p(C|Dnew) ∝ p(Dnew|C)p(C)
          = p(C) ∏ ftp(wt |C) + (1- ft)(1-p(wt |C)
 and determine which out of p(C = S | Dnew) and p(C = H | Dnew) is higher.
 Note: Most of the material described above is taken from this resource. You are encouraged to consult and review it. Here is another resource that explains text classificationLinks to an external site. very well.
  
 Checkpoint A, 75 points (due as an in-person demo by Mon, May 02):
 Implement Bernoulli Naive Bayes classification model as described above and test it on toy example provided in this resource. Your program should read training data and corresponding class information from these 2 files: toy.data.txt and toy.class.txt. Note that the file toy.class.txt file contains labels 1 and 0, where 1 indicates the class S and 0 indicates the class I. Use the training data to compute prior probabilities p(S) and p(I) and to compute the likelihood probabilities p(wt | C = k) where k = S, I and t = 1 through 8 (because the toy example has 8 words).
 Your program should then read two test cases from toytest.data.txt and output the posterior probability p(S | Dtest) and p(I | Dtest) for each of them, as follows:
 Test case 1
     p(S|b) = 0.00561167
     p(I|b) = 9.30909e-06
 Test case 2
     p(S|b) = 0.000280584
     p(I|b) = 0.00804306

 ****************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "Bayes.h"

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
    
        Bayes *SpamArray_b1 = new Bayes[SpamFraction.size()];
        Bayes *SpamArray_b2 = new Bayes[SpamFraction.size()];
        Bayes *HamArray_b1 = new Bayes[HamFraction.size()];
        Bayes *HamArray_b2 = new Bayes[HamFraction.size()];
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamArray_b1[i] = b1Spam[i];
    
    for(int i = 0; i < SpamFraction.size(); i++)
        SpamArray_b2[i] = b2Spam[i];
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamArray_b1[i] = b1Ham[i];
    
    for(int i = 0; i < HamFraction.size(); i++)
        HamArray_b2[i] = b2Ham[i];
    
    Bayes SpamTest1("1/1"),
          HamTest1("1/1"),
          SpamTest2("1/1"),
          HamTest2("1/1");
    
    Bayes PS = (std::to_string(Spam.size()) + '/'
    + std::to_string(Spam.size() + Ham.size()));
    
    Bayes PH = (std::to_string(Ham.size()) + '/'
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
