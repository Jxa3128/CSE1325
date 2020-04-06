// Serge Zaatar Antor 1001623346

#ifndef SNACK_MACHINE_H
#define SNACK_MACHINE_H

#include <iostream>
#include <string>
#include "SnackLib.h"

enum Status
{
    GOOD_CHANGE,
    GOOD_EXACT,
    GOOD_INVENTORY,
    BAD_NOFUNDS,
    BAD_NOCHANGE ,
    BAD_UNKNOWN, 
    BAD_INVENTORY,
    BAD_RANOUT,
    ZERO,
    INVALID
};

Status status {};

class SnackMachine
{
    friend std::ostream& operator<<(std::ostream& output, const SnackMachine &MySnackMachine);
    friend std::string CreateSnackOutputLine(const SnackMachine &MySnackMachine);
    private:
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity = 5000;
        int SnackPrice;
        int inventoryLevel;
        int maxInventoryCapacity = 100;
    public:
        SnackMachine (std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100):
            machineName{name},
            SnackPrice{cost},
            changeLevel{change},
            inventoryLevel{inventory};

        std::string getMachineName();

        bool buyASnack(int &payment, std::string &change, int &status);

        int getInventoryLevel();

        int getMaxInventoryCapacity();

        bool incrementInventory(int amountToAdd);

        std::string getChangeLevel();
        
        bool incrementChangeLevel(int amountToAdd);

        std::string getMaxChangeCapacity();

        std::string getSnackPrice();

        std::string displayMoney(int amount);

        void setMachineName(std::string newMachineName);

        std::string getMachineName();

        void setSnackPrice(std::string newSnackPrice);
};

#endif