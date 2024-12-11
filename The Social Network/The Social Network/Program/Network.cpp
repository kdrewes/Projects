/*
*************************************************************************
 Title: The Social Network
                                                                        
 Author: Kyle Drewes
                    
 Date: 10/8/2022
 
 Description: This program is designed to create a social network.
 The social network is establish through the JSON file "UserList.json"
 which contains the following attributes: name, location, picture url,
 and followers.  In this program, I have also include a list of users
 a particular profile is being followed by, as well as a list of
 the user profiles mutual friends.  Please let me know if you have
 any questions pertaining to this program.  Thank you
 *********************************************************************
 */

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cassert>
#include "Network.hpp"

//---------------------------------------------------------------------------------------------------------------------
Network :: Network()
{
    profileAmount = 0; capacityCount =  0;
    ParseVector.reserve(AssignSize());
    tempVector.reserve(AssignSize());
    Set_Profile_Amount(CountAccounts
    ("UserList.json")); Parse(); HTML();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: Parse()
{
    std::string file; count profile_iterator = 0, attribute_iterator = 0;
    
    do Tokenize(attributes[attribute_iterator],attribute_iterator,profile_iterator);
    while(++attribute_iterator < sizeof(attributes) / sizeof(attributes[0]));
    
    storage Temporary_Parse_Vector;
    
    for(int i = 0; i < Get_Profile_Amount(); i++)
    Temporary_Parse_Vector.push_back(
    Profile(tempVector[i].GetID(),
    tempVector[i].GetName(),
    tempVector[i].GetLocation(),
    tempVector[i].GetURL(),
    tempVector[i].GetFollows(),
    tempVector[i].GetFollowers(),
    tempVector[i].GetMutualFriends()));

    Set_Parse_Vector
    (Sort(Temporary_Parse_Vector));
    Temporary_Parse_Vector.clear();
    
    for(std::vector<Profile>::size_type i = 0; i < ParseVector.size(); i++)
    {
       std::cout << ParseVector[i].GetID() << ' ' << ParseVector[i].GetName() << ' ' <<  ParseVector[i].GetLocation() << std::endl;
    }
    
    
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: Tokenize(std::string attribute, count attribute_iterator, count profile_iterator)
{
    switch(static_cast<Properties>(attribute_iterator))
    {
        case ID:
            SetID(attribute,attribute_iterator,profile_iterator);
            break;
            
    //---------------------------------------------------------------------------------
       
        case NAME:
            
            SetName(attribute,attribute_iterator,profile_iterator);
            break;

    //---------------------------------------------------------------------------------
            
        case LOCATION:
        
            SetLocation(attribute,attribute_iterator,profile_iterator);
            break;
        
    //---------------------------------------------------------------------------------
            
        case PIC_URL:
        
            SetURL(attribute,attribute_iterator,profile_iterator);
            break;
        
    //---------------------------------------------------------------------------------
            
        case FOLLOWS:
        
            SetFollows(attribute,attribute_iterator,profile_iterator);
            SetFollowers(); SetMutualFriends();
            break;
        
    //---------------------------------------------------------------------------------
        default:
            std::cout << "\nInvalid Entry - Please re-enter: ";
    }
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: HTML()
{
            std::ofstream write("Index.html", std::ios::out );
            assert(write);
    
    //----------------------------- Create index.html -----------------------------
    
            write << "<!DOCTYPE html>";
            write << "<html>";
            write << "<head>";
            write << "<title>My Social Network</title>";
            write << "</head>";
            write << "<body>";
            write << "<h1>My Social Network: User List</h1>";
            write << "<ol>";

    
    for(std::vector<Profile> :: size_type i = 0; i < ParseVector.size(); i++)
        write << "<li><a href=" << "\"user" << std::to_string(i+1)
        << ".html\"" << ">" << ParseVector[i].GetName() << "</a></li>";
   
            write << "</ol>";
            write << "</body>";
            write << "</html>";
    
            write.close();
    
    //---------------------------- Create user html files ----------------------------
  
    for(std::vector<Profile> :: size_type i = 0; i < ParseVector.size(); i++)
    {
            std::ofstream write(ParseVector[i].GetName() + ".html", std::ios::out | std::ios::trunc);
            assert(write);
        
            write << "<!DOCTYPE html>";
            write << "<html>";
            write << "<head>";
            write << "<title>" << ParseVector[i].GetName()  << " Profile</title>";
            write << "</head>";
            write << "<body>";
            write << "<h1>" << ParseVector[i].GetName() << " in " << ParseVector[i].GetLocation() << "</h1>";
            write << "<img alt= \"Profile pic\" src=" << ParseVector[i].GetURL() << " />";
            write << "<h2>Follows</h2>";
            write << "<ul>";
        
            FollowVector Follows = ParseVector[i].GetFollows();
        
        for(std::vector<Profile> :: size_type x = 0; x < Follows.size(); x++)
        {
            std::string user = "user";
            user += Follows[x].first + ".html";
            write << " <li><a href=" << user << ">" << Follows[x].second << "</a></li>";
        }   Follows.clear();
        
            write << "</ul>";
            write << "<h2>Followers</h2>";
            write << "<ul>";
        
            FollowVector Followers = ParseVector[i].GetFollowers();
        
        for(std::vector<Profile> :: size_type x = 0; x < Followers.size(); x++)
        {
            std::string user = "user";
            user += Followers[x].first + ".html";
            write << " <li><a href=" << user << ">" << Followers[x].second << "</a></li>";
        }   Followers.clear();
        
            write << "</ul>";
            write << "<h2>Mutuals</h2>";
            write << "<ul>";
       
            mutual_friends MutualFriends = ParseVector[i].GetMutualFriends();
        
        for(std::vector<Profile> :: size_type x = 0; x < MutualFriends.size(); x++)
        {
            std::string user = "user";
            user += MutualFriends[x].first + ".html";
            write << " <li><a href=" << user << ">" << MutualFriends[x].second << "</a></li>";
        }   Followers.clear();
        
            write << "</ul>";
            write << "</body>";
            write << "</html>";
   
            write.close();
        
    }
}
//---------------------------------------------------------------------------------------------------------------------

Network :: name Network :: FindName(id id_str)
{
    name findName;
    for(std::vector<int> :: size_type i = 0; i < Get_Profile_Amount(); i++)
        if(tempVector[i].GetID() == id_str)
            findName = tempVector[i].GetName();
                return findName;
               
}
//---------------------------------------------------------------------------------------------------------------------
Network :: size Network :: CountAccounts(std::string fileName)
{
    std::ifstream read (fileName);
    count amount_of_profiles = 0;
    
    for(std::string output; !read.eof() && getline(read,output);)
        
    if(output.find("id_str") != std::string::npos)
        ++amount_of_profiles; read.close();
    
    return amount_of_profiles;
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetID(std::string attribute, count attribute_iterator, count profile_iterator)
{
    std::string scope = "",
                temp = "";
    
    std::ifstream read ("UserList.json");
    
    for(std::string output; !read.eof() && getline(read,output);)
    {
    if(output.find(attribute) != std::string::npos)
    {
        std::size_t index = output.find(':');
        scope = output;
        
        scope = scope.substr(index+2,scope.size());
        
        for(int i = 0; i < scope.size()-1; i++)
        {
           if(scope[i] != '"' && scope[i] != ' ')
              temp+=scope[i];
        }
        
        tempVector[profile_iterator++].SetID(temp);
        temp.clear(); scope.clear();
    }
        
    }
        read.close();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetName(std::string attribute, count attribute_iterator, count profile_iterator)
{
    std::string scope = "",
                temp = "";
    
    std::ifstream read ("UserList.json");
    
    for(std::string output; !read.eof() && getline(read,output);)
    {
    if(output.find(attribute) != std::string::npos)
    {
        std::size_t index = output.find(':');
        scope = output;
        
        scope = scope.substr(index+2,scope.size());
        
        for(int i = 0; i < scope.size()-1; i++)
        {
           if(scope[i] != '"' && scope[i] != ' ')
              temp+=scope[i];
        }
        
        tempVector[profile_iterator++].SetName(temp);
        temp.clear(); scope.clear();
    }
    }
        read.close();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetLocation(std::string attribute, count attribute_iterator, count profile_iterator)
{
    std::string scope = "",
                temp = "";
    
    std::ifstream read ("UserList.json");
   
    for(std::string output; !read.eof() && getline(read,output);)
    {
    if(output.find(attribute) != std::string::npos)
    {
        std::size_t index = output.find(':');
        scope = output;
        
        scope = scope.substr(index+2,scope.size());
        
        for(int i = 0; i < scope.size()-1; i++)
        {
           if(scope[i] != '"' && scope[i] != ' ')
              temp+=scope[i];
        }

        tempVector[profile_iterator++].SetLocation(temp);
        temp.clear(); scope.clear();
    }
        
    }
    
    read.close();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetURL(std::string attribute, count attribute_iterator, count profile_iterator)
{
    std::string scope = "",
                temp = "";
    
    std::ifstream read ("UserList.json");
    
    for(std::string output; !read.eof() && getline(read,output);)
    {
    if(output.find(attribute) != std::string::npos)
    {
        std::size_t index = output.find(':');
        scope = output;
        
        scope = scope.substr(index+2,scope.size());
        
        for(int i = 0; i < scope.size()-1; i++)
        {
           if(scope[i] != '"' && scope[i] != ' ')
              temp+=scope[i];
        }
        
        tempVector[profile_iterator++].SetURL(temp);
        temp.clear(); scope.clear();
    }
        
    }
    
        read.close();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetFollows(std::string attribute, count attribute_iterator, count profile_iterator)
{
    std::string scope = "",
                temp = "";
    
    std::vector<ID_NAME>tempPair;
    
    std::ifstream read ("UserList.json");
    
    for(std::string output; !read.eof() && getline(read,output);)
    {
    if(output.find(attribute) != std::string::npos)
    {
        std::size_t index = output.find(':');
        scope = output;
        
        scope = scope.substr(index+2,scope.size());
        
        for(int i = 0; i < scope.size()-1; i++)
        {
           if(scope[i] != '"' && scope[i] != ' ' && scope[i] !=
              '[')
              temp+=scope[i];
        }
        
        std::stringstream s(temp);
        while(s.good())
        {
            getline(s,temp,',');
            
            ID_NAME id_name
            {temp,FindName(temp)};
            
            tempPair.push_back(id_name);
        }

        tempVector[profile_iterator++].
        SetFollows(tempPair);
        
        s.str("");
        s.clear();
        tempPair.clear();
        temp.clear();
        scope.clear();
        
    }
        
    }
    
    read.close();
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetFollowers()
{
    FollowVector FollowerTEMP, tempPair;  ID_NAME id_name;
    
    for(std::vector<Profile> :: size_type i = 0; i < Get_Profile_Amount(); i++)
    {
            for(std::vector<Profile> :: size_type x = 0; x < Get_Profile_Amount(); x++)
            {
                FollowerTEMP = tempVector[x].GetFollows();
                        
                if(tempVector[i].GetID() != tempVector[x].GetID())
                    
                    for(std::vector<Profile> :: size_type j = 0; j < FollowerTEMP.size(); j++)
                        
                        if(tempVector[i].GetID() == FollowerTEMP[j].first)
                        {
                            id_name
                            = {tempVector[x].GetID(),
                                
                            FindName(tempVector[x].GetID())};
                            
                            tempPair.push_back(id_name);
                        }
             }
                            tempVector[i].SetFollowers(tempPair);
        
                            tempPair.clear();
      }
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: SetMutualFriends()
{
    ID_NAME id_name; FollowVector FollowerTEMP; mutual_friends collect;
    
    std::map<ID_NAME,std::vector<ID_NAME>>::iterator it; network_map FollowMap;
    
    //Insert values inside map. Key = ID_NAME, Value = std::vector<ID_NAME>>
    for(std::vector<Profile>::size_type i = 0; i < Get_Profile_Amount(); i++)
    FollowMap [ {tempVector[i].GetID(),tempVector[i].GetName()} ] =  tempVector[i].GetFollows();
    
    for(std::vector<Profile>::size_type i = 0; i < FollowMap.size(); i++)
    {
        FollowerTEMP = tempVector[i].GetFollows();
        std::string name = tempVector[i].GetName();
        
        for(std::vector<Profile>::size_type x = 0; x < FollowerTEMP.size(); x++)
        {
            if(tempVector[i].GetID() != tempVector[x].GetID())
            {
                it = FollowMap.find({FollowerTEMP[x].first,FollowerTEMP[x].second});
                
                for(auto i : it->second)
                    if(i.second == name)
                    {
                       ID_NAME id_name{FollowerTEMP[x].first,FollowerTEMP[x].second};
                       collect.push_back(id_name);
                    }
            }
        }
        
        tempVector[i].SetMutualFriends(collect);
        collect.clear();
    }
}
//---------------------------------------------------------------------------------------------------------------------
void Network :: Set_Parse_Vector(storage ParseVector){ this -> ParseVector = ParseVector; }
//---------------------------------------------------------------------------------------------------------------------
void Network :: Set_Profile_Amount(count profileAmount) { this -> profileAmount = profileAmount; }
//---------------------------------------------------------------------------------------------------------------------
Network :: size Network :: AssignSize() { return (10000 * capacityCount++); }
//---------------------------------------------------------------------------------------------------------------------
Network :: size Network :: Get_Profile_Amount() const { return profileAmount; }
//---------------------------------------------------------------------------------------------------------------------
Network :: storage Network :: Get_Parse_Vector() const { return ParseVector; }
//---------------------------------------------------------------------------------------------------------------------
Network :: storage Network :: Sort(storage Previous_Vector) const
{
    storage Enhanced_Vector;
    
    std::map<std::string,
    Profile>mapSORTER;
    
    for(std::vector<Profile> :: size_type i  = 0; i < Previous_Vector.size(); i++)
    mapSORTER[Previous_Vector[i].GetID()] = Profile(Previous_Vector[i].GetID(),
    Previous_Vector[i].GetName(),Previous_Vector[i].GetLocation(),Previous_Vector[i].GetURL(),
    Previous_Vector[i].GetFollows(), Previous_Vector[i].GetFollowers(), Previous_Vector[i].GetMutualFriends());
    
    std::map<std::string,Profile> ::
    iterator it = mapSORTER.begin();
    
    for(std::vector<Profile> :: size_type i  = 1; i <= Previous_Vector.size(); i++)
    {
        it = mapSORTER.find(std::to_string(i));
        
        if(it != mapSORTER.end())
            Enhanced_Vector.push_back(it->second);
    }
        
    return Enhanced_Vector;
}
//---------------------------------------------------------------------------------------------------------------------
