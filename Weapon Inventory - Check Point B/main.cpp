
/**
 Checkpoint B
 In this phase of the project, you will extend code written in checkpoint A by adding more functions and performing more operations on weapon inventory.
 Write a function addWeapon to add a specific weapon to the current inventory.
 Your function must take the current weapon inventory, and the Weapon type to be added as parameters.
 Write a function removeWeapon to remove a specific weapon from the current inventory.
 Your function must take the current weapon inventory, and the Weapon type to be removed as parameters.
 Write a function toggleWeapon to toggle a specific weapon from the current inventory.
 Your function must take the current weapon inventory, and the Weapon type to be toggled as parameters.
 In the main function, continue onwards from checkpoint A where you displayed the current weapon inventory and perform the following operations:

 Toggle the weapon Poison from the current inventory and display the inventory.
 Toggle the weapon Fire from the current inventory and display the inventory.
 Check if the weapon Ice exists in the current inventory. If so, remove it from the inventory otherwise print a message indicating that the weapon doesn't exist (see sample output below). Then, display the inventory.
 Check if the weapon Melee does not exist in the current inventory. If so (i.e. if it doesn't exist), add it to the inventory otherwise print a message indicating that the weapon already exists (see sample output below). Then, display the inventory.
 Print out the final value of the variable representing the inventory (myweapon) as an integer and in binary (see sample output below).
 Sample Output for Final code (note: value for myweapon is generated randomly)

 Starting with myweapon = 12
 Binary representation: 00001100
 Your Weapons: Ice Poison
  
 ***Toggling Poison***
 Your Weapons: Ice
 ***Toggling Fire***
 Your Weapons: Fire Ice
 ***Found Ice.. removing it***
 Your Weapons: Fire
 ***Melee not found.. adding it***
 Your Weapons: Melee Fire

 Ending with myweapon = 3
 Binary representation: 00000011
 Starting with myweapon = 9
 Binary representation: 00001001
 Your Weapons: Melee Poison
  
 ***Toggling Poison***
 Your Weapons: Melee
 ***Toggling Fire***
 Your Weapons: Melee Fire
 ***Ice not found.. can't remove it***
 ***Melee already exists.. can't add it***

 Ending with myweapon = 3
 Binary representation: 00000011
 Starting with myweapon = 4
 Binary representation: 00000100
 Your Weapons: Ice
  
 ***Toggling Poison***
 Your Weapons: Ice Poison
 ***Toggling Fire***
 Your Weapons: Fire Ice Poison
 ***Found Ice.. removing it***
 Your Weapons: Fire Poison
 ***Melee not found.. adding it***
 Your Weapons: Melee Fire Poison
  
 Ending with myweapon = 11
 Binary representation: 00001011
 Starting with myweapon = 10
 Binary representation: 00001010
 Your Weapons: Fire Poison

 ***Toggling Poison***
 Your Weapons: Fire
 ***Toggling Fire***
 Your Weapons: None
 ***Ice not found.. can't remove it***
 ***Melee not found.. adding it***
 Your Weapons: Melee
  
 Ending with myweapon = 1
 
 Final code
 In this phase of the project, you will add a couple of functions to your checkpoint B code and submit your code for grading.
 
 Write a function getWeaponTypeFromString with the following prototype
 
 Weapon getWeaponTypeFromString(string weaponName)
 
 It takes a string as an input parameter and returns the corresponding Weapon type. For example, if weaponName is "Melee", it returns Weapon::Melee. The function works irrespective of the case of the letters in weaponName.
 
 If the user provides a weapon that is not among the 4 weapons that our assassin's inventory can hold, then the function returns Weapon::none
 
 Write a function loadWeapons that prompts the user to enter several weapons in a single line.
 
 It does not take any parameters.
 
 It reads each weapon name from that line, gets its weapon type, and adds that weapon to the inventory.
 
 It returns the unit8_t variable representing weapon inventory.
 
 Calls the function getWeaponTypeFromString to get the weapon type from weapon name.
 
 In the main function replace the random assignment to the variable myweapon (in checkpoint B) with a call to the function loadWeapons. (Essentially, this replaces random weapon inventory to the weapon inventory indicated by the user).
 */

#include <iostream>
#include <map>
#include <bitset>
#define INVENTORY 5
//---------------------------------------------------------------------------------------------
enum Weapon : uint8_t {

    None = 0b00000000,

    Melee = 0b00000001,

    Fire = 0b00000010,

    Ice = 0b00000100,

    Poison = 0b00001000

};
//---------------------------------------------------------------------------------------------
const uint8_t GetMaxWeapons();

const uint8_t maxWeapon = GetMaxWeapons();

bool checkWeapon(uint8_t currentWeapon, Weapon weapon);

void addWeapon(uint8_t& currentWeapon, Weapon weapon);

void removeWeapon(uint8_t& currentWeapon, Weapon weapon);

void toggleWeapon(uint8_t& currentWeapon, Weapon weapon);

void displayWeapon(uint8_t currentWeapon);

Weapon getWeaponTypeFromString(std::string weaponName);

std::map <std::string,uint8_t> CreateMap(const std::string[4]);

uint8_t loadWeapons();

std::string GetWeapon(Weapon);
//---------------------------------------------------------------------------------------------
namespace command
{
    void space(std::size_t size)
    {
        for(size_t i = 0; i < size; i++)
            std::cout << std::endl;
    }
}
int main() {

    uint8_t myweapon;

    myweapon = loadWeapons();
    
    std::cout << "\nMy weapon " << static_cast<int>(myweapon) << std::endl;
    std::cout << "Starting with myweapon = " << int(myweapon) << std::endl;
    std::cout << "Binary representation: " << std::bitset<sizeof(myweapon) * 8>(myweapon) << std::endl;
    displayWeapon(myweapon);

    std::cout << "\n***Toggling Poison***" << std::endl;
    toggleWeapon(myweapon, Poison);
    displayWeapon(myweapon);

    std::cout << "\n***Toggling Fire***" << std::endl;
    toggleWeapon(myweapon, Fire);
    displayWeapon(myweapon);

    if (checkWeapon(myweapon, Ice))
    {
        std::cout << "\n***Found Ice.. removing it***" << std::endl;
        removeWeapon(myweapon, Ice);
        displayWeapon(myweapon);

    }

    else
        std::cout << "\n***Ice not found.. can't remove it***" << std::endl;

    if (!checkWeapon(myweapon, Melee))
    {
        std::cout << "\n***Melee not found.. adding it***" << std::endl;
        addWeapon(myweapon, Melee);
        displayWeapon(myweapon);
    }

    else
        std::cout << "***Melee already exists.. can't add it***" << std::endl;

        std::cout << "\nEnding with myweapon = " << int(myweapon) << std::endl;
        std::cout << "Binary representation: " << std::bitset<sizeof(myweapon) * 8>(myweapon) << std::endl;

    command::space(1);
    return 0;

}
//---------------------------------------------------------------------------------------------
bool checkWeapon(uint8_t currentWeapon, Weapon weapon)
{
    return (currentWeapon & weapon);
}
//---------------------------------------------------------------------------------------------
void addWeapon(uint8_t& currentWeapon, Weapon weapon)
{
    currentWeapon |= weapon;
}
//---------------------------------------------------------------------------------------------
void removeWeapon(uint8_t& currentWeapon, Weapon weapon)

{
    currentWeapon &= ~weapon;
}
//---------------------------------------------------------------------------------------------
void toggleWeapon(uint8_t& currentWeapon, Weapon weapon)
{
    currentWeapon ^= weapon;
}
//---------------------------------------------------------------------------------------------
void displayWeapon(uint8_t currentWeapon)

{
    std::cout << "Your Weapons: ";

    if (currentWeapon == None)

        std::cout << "None";

       if (checkWeapon(currentWeapon, Melee))

           std::cout << "Melee ";

       if (checkWeapon(currentWeapon, Fire))

           std::cout << "Fire ";

       if (checkWeapon(currentWeapon, Ice))

           std::cout << "Ice ";

       if (checkWeapon(currentWeapon, Poison))

           std::cout << "Poison";

    std::cout << std::endl;

}
//---------------------------------------------------------------------------------------------
const uint8_t GetMaxWeapons()

{

    uint8_t maxWeapons = 0;

    int count = 0;

    bool flag = false;

    do

    {

        uint8_t weapon = static_cast<Weapon>(count++);

        switch(weapon)

        {

            case None:
            {
                maxWeapons += Weapon::None;
                break;
            }

            case Melee:
            {
                maxWeapons += Weapon::Melee;
                break;
            }

            case Fire:
            {
                maxWeapons += Weapon::Fire;
                break;
            }

            case Ice:
            {
                maxWeapons += Weapon::Ice;
                break;
            }

            case Poison:
            {
                maxWeapons += Weapon::Poison;
                flag = true;
                break;
            }
        }
    }while(!flag);

    return maxWeapons;

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string GetWeapon(Weapon weapon)

{
    switch(weapon)

    {
        case None:
            return{};

        case Melee:
            return "Melee ";

        case Fire:
            return "Fire ";

        case Ice:
            return "Ice ";

        case Poison:
            return "Poison ";

    }

    return "";
}
//---------------------------------------------------------------------------------------------
uint8_t loadWeapons()
{
    std::string weaponList[INVENTORY] = {"None","Melee","Fire","Ice","Poison"};
    
        uint8_t strength [INVENTORY] = {0,1,2,4,8};
    
        uint8_t myweapon = 0;
    
    std::string weapon,
                temp;
    
           bool loop = true;
    
   std::map<std::string,uint8_t> Map;
    
   for(int i = 0; i < sizeof(weaponList)/sizeof(weaponList[0]); i++)
       Map.insert(std::pair<std::string,uint8_t>(weaponList[i],strength[i]));
    
    std::cout << "Enter all your weapons in a single line: ";
    std::getline(std::cin,weapon);
    
    size_t weaponSize = weapon.size(),
           index = 0;
    
    do
    {
        for(size_t i = index; i < weaponSize; i++)
        {
            if(weapon[i] != ' ')
                temp += weapon[i];
            
            else
            {
                ++index;
                  break;
            }
            
            if(i == weaponSize - 1)
                loop = false;
        }
        
        std::map<std::string,uint8_t> :: iterator it = Map.find(temp);
        
        if(it != Map.end())
            myweapon += getWeaponTypeFromString(it->first);
        
            temp.clear();
        
    }while(loop);

    return myweapon;
    
}
//---------------------------------------------------------------------------------------------
Weapon getWeaponTypeFromString(std::string weaponName)
{
    std::string weaponList[INVENTORY] = {"None","Melee","Fire","Ice","Poison"};
    
    if(weaponList[1] == weaponName)
        return Weapon::Melee;
    
    else if(weaponList[2] == weaponName)
        return Weapon::Fire;
    
    else if(weaponList[3] == weaponName)
        return Weapon::Ice;
    
    else if(weaponList[4] == weaponName)
        return Weapon::Poison;
    
        return Weapon::None;
}
//---------------------------------------------------------------------------------------------
