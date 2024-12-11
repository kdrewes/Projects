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

#ifndef Profile_hpp
#define Profile_hpp

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class Profile
{

protected:

                            /* Purpose of using typedef is to be able to identify each datatype */
    //-----------------------------------------------------------------------------------------------------------------------------
    typedef std::string id, name, location, url;        // id = id_str, name = name, location = location, url = pic_url

    typedef std::size_t size;                           // Size_t datatype used to represent size
    
    typedef int count;                                  // int datatype used to represent counters
    
    typedef std::pair<id,name>ID_NAME;                  // Pair Datatype used to store id and name

    typedef std::vector<ID_NAME>FollowVector;           // Vector used to store user id and name
    
    typedef std::vector<ID_NAME>mutual_friends;         // stores mutual friends for each user
    
    typedef std::vector<Profile>storage;                // Vector used to paramaterized objects
    
    typedef std::map<ID_NAME,storage>storage_map;       /* Map used to store network data
                                                           Key = pair<id,name>,
                                                           value = storage vector */
    typedef std::map<ID_NAME,
    std::vector<ID_NAME> >network_map;                   /* Map used to store network data
                                                           Key = pair<id,name>,
                                                           value = std::vector<ID_NAME> */
                                            
    //-----------------------------------------------------------------------------------------------------------------------------
    
    id id_str;                                          // Represents the user's identification number, or id_str within json file
    
    name userName;                                      // Represents user's name within json file
    
    location userLocation;                              // Represents the user's location within json file
    
    url pic_url;                                        // Represents the url of the profile picture within json file
    
    size numberOfAccounts;                              // Represents the amount of user profiles
    
    FollowVector Follows;                               // Contains id's of all profiles user is following
     
    FollowVector Followers;                             //  Contains id's of all profiles user is being followed by
    
    mutual_friends Mutual_Friends;                      /*  Holds multual friends for each profile.
                                                            Key = id, value = Profile class object */
    
    //-----------------------------------------------------------------------------------------------------------------------------

public:
    
    Profile();                                          // Default Constructor;
    
    Profile
    (id,name,location,url,FollowVector,
     FollowVector,mutual_friends);                      // Paramatarized Constructor
                                                         
    void SetID(id);                                     // Mutator for id_str
    
    void SetName(name);                                 // Mutator for userName
    
    void SetLocation(location);                         // Mutator for userLocation
    
    void SetURL(url);                                   // Mutator for pic_url
    
    void SetFollows(FollowVector);                      // Mutator for Follows
    
    void SetFollowers(FollowVector);                    // Mutator for Followers
    
    void SetMutualFriends(mutual_friends);              // Mutator for Mutual_Friends
    
    //---------------------------------------------------------------------------------
    
    id GetID() const;                                   // Accessor for id number
    
    name GetName() const;                               // Accessor for name of each user
    
    location GetLocation() const;                       // Acessor for userLocation
    
    url GetURL() const;                                 // Accessor for picture url
            
    FollowVector GetFollows() const;                    // Accessor for Follows
    
    FollowVector GetFollowers() const;                  // Accessor for Followers
    
    mutual_friends GetMutualFriends() const;            // Accessor for Mutual_Friends
    
    //---------------------------------------------------------------------------------
};

#endif
