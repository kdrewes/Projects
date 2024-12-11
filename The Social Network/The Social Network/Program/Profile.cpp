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

#include "Network.hpp"
#include "Profile.hpp"
#include <iostream>
//---------------------------------------------------------------------------------------------------------------------
Profile :: Profile()
{
    id_str = "";
    userName = "";
    userLocation = "";
    pic_url = "";
}
//---------------------------------------------------------------------------------------------------------------------
Profile :: Profile
(id id_str,name userName,location userLocation,url pic_url,FollowVector Follows,FollowVector Followers,mutual_friends Mutual_Friends)
{
    SetID(id_str);
    SetName(userName);
    SetLocation(userLocation);
    SetURL(pic_url);
    SetFollows(Follows);
    SetFollowers(Followers);
    SetMutualFriends(Mutual_Friends);
}

//---------------------------------------------------------------------------------------------------------------------

//Mutator for id_str
void Profile :: SetID(id id_str) { this -> id_str = id_str; }

//Mutator for userName
void Profile :: SetName(name userName) { this -> userName = userName; }

//Mutator for userLocation
void Profile :: SetLocation(location userLocation) { this -> userLocation = userLocation; }

//Mutator for pic_url
void Profile :: SetURL(url pic_url) { this -> pic_url = pic_url; }

//Mutator for Follows
void Profile :: SetFollows(FollowVector Follows) { this -> Follows = Follows; }

//Mutator for Followers
void Profile :: SetFollowers(FollowVector Followers) { this -> Followers = Followers; }

//Mutator for Mutual_Friends
void Profile :: SetMutualFriends(mutual_friends Mutual_Friends) { this -> Mutual_Friends = Mutual_Friends; }
//---------------------------------------------------------------------------------------------------------------------
//Accessor for id_str
Profile :: id Profile :: GetID() const { return id_str; }

//Accessor for userName
Profile :: name Profile :: GetName() const { return userName; }

//Accessor for userLocation
Profile :: location Profile :: GetLocation() const { return userLocation; }

//Accessor for pic_url
Profile :: url Profile :: GetURL() const { return pic_url; }

//Accessor for Follows
Profile :: FollowVector Profile :: GetFollows() const { return Follows; }

//Accessor for Followers
Profile :: FollowVector Profile :: GetFollowers() const { return Followers; }

//Accessor for Mutual_Friends
Profile :: mutual_friends Profile :: GetMutualFriends() const { return Mutual_Friends; }

//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
