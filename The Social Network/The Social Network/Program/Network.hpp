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
#ifndef Network_hpp
#define Network_hpp

#include "Profile.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#define FIVE 5

enum Properties {ID, NAME, LOCATION, PIC_URL, FOLLOWS };

class Network : public Profile
{
    //-----------------------------------------------------------------------------------------------------------------------------
private:
    
    storage ParseVector;                // Vector which holds the parsed information for each user profile
    
    storage tempVector;                 // Vector which holds the parsed information for each user profile
    
    storage_map                         // Map which contains information of each user profile
    User_Profile;                       /* Key = pair<id,name>, value = ParseVector
                                           Used to serach for a particular user profile */
                                           
    const std::string                   // Used to locate each attribute inside json file
    attributes [FIVE]
    =  { "id_str",                      // Used to search for user id inside json file
        
         "name",                        // Used to search for user name inside json file
        
         "location",                    // Used to search for location inside json file
        
         "pic_url",                     // Used to search for pic url inside json file
        
         "follows"                      // Used to search for follows inside json file
       };
    
    size assignSize;                    // Assigns a certain amount of space within Profile *profile
    
    count capacityCount;                /* Used to increase the capacity of how many profiles can be
                                         
                                           utilized within the network */
    
    size profileAmount;                 // Determines amount of user profiles
    
    
    //-----------------------------------------------------------------------------------------------------------------------------
public:
    
    Network();                          // Network Constructure
    
    void Parse();                       // Used to parse file
    
    void Tokenize                       // Used to tokenize file content
    (std::string,count,count);
    
    void HTML();                        // Outputs html for each user
    
    void Set_Profile_Amount(count);     // Mutator for profileCount
    
    void SetID                          // Helper function for SetID(id)
    (std::string,count,count);
    
    void SetName                        // Helper function for SetName(name)
    (std::string,count,count);
    
    void SetLocation                    // Helper function for SetLocation(location)
    (std::string,count,count);
    
    void SetURL                         // Helper function for SetURL(url)
    (std::string,count,count);
    
    void SetFollows                     // Helper function for SetFollows(FollowVector)
    (std::string,count,count);
    
    void SetFollowers();                // Helper function for SetFollowers(FollowVector)
    
    void SetMutualFriends();            // Helper function for SetMutualFriends(mutual_friends)
    
    void Set_Parse_Vector(storage);     // Mutator for ParseVector
    
    name FindName(id);                  // Used to find profile name by using user id
    
    size AssignSize();                  // Assigns the total amount space available to use
    
    size CountAccounts(std::string);    // Used to Count user profiles
    
    size Get_Profile_Amount() const;    // Determines the Amount of user profiles in network
    
    storage Get_Parse_Vector() const;   // Accessor for storage ParseVector
    
    storage Sort(storage) const;        // Return sorted vector
    
};
    //-----------------------------------------------------------------------------------------------------------------------------

#endif 
