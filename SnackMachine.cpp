#include <iostream>
#include <string>
#include <iomanip>
#include "SnackMachine.h"
#include "SnackLib.h"


std::ostream& operator<<(std::ostream& output, const SnackMachine &MySnackMachine)
{
    // output << "\n"<< MySnackMachine.getMachineName()<<endl
    //     << "\nCurrent Inventory Level "<<MySnackMachine.getInventoryLevel()
    //     << "Max Inventory Capacity "<<MySnackMachine.getMaxInventoryCapacity()
    //     << "\nCurrent Change Level "<<MySnackMachine.getChangeLevel()
    //     << "Max Change Capacity "<<MySnackMachine.getMaxChangeCapacity()
    //     << "\nCurrent Snack price is "<<MySnackMachine.getSnackPrice()<<endl<<endl;

    return "Name";
}

std::string CreateSnackOutputLine(const SnackMachine &MySnackMachine)
{
    return "Name";
}

void setMachineName(std::string newMachineName)
{
    machineName = newMachineName;
}

void setSnackPrice(std::string newSnackPrice)
{
    SnackPrice = newSnackPrice;
}

std::string getMachineName()
{
    return machineName;
}

bool buyASnack(int &payment, std::string &change, int &status)
{
    int newchange;
    newchange = payment - SnackPrice;

    if (newchange > changeLevel)
    {
        status = BAD_NOCHANGE;
        return false;
    }
    else if (inventoryLevel == 0)
    {
        status = BAD_RANOUT;
        return false;
    }
    else
    {
        if (payment == SnackPrice)
        {
            changeLevel += SnackPrice;
            change = std::to_string(newchange);
            inventoryLevel--;

            status = GOOD_EXACT;
            return true;
        }
        else if (payment < SnackPrice)
        {
            status = BAD_NOFUNDS;
            return false;
        }
        else
        {
            changeLevel += SnackPrice;
            change = displayMoney(newchange);
            inventoryLevel--;
            status = GOOD_CHANGE;
            return true;
        }
    }
}

int getInventoryLevel()
{
    return inventoryLevel;
}

int getMaxInventoryCapacity()
{
    return maxInventoryCapacity;
}

bool incrementInventory(int amountToAdd)
{
    if (amountToAdd < -1)
    {
        status = INVALID;
        return false;
    }
    else if (amountToAdd == 0)
    {
        status = ZERO;
        return false;
    }

    if ((amountToAdd + inventoryLevel) <= maxInventoryCapacity)
    {
        inventoryLevel += amountToAdd;
        status = GOOD_INVENTORY;
        return true;
    }
    else
    {
        status = BAD_INVENTORY;
        return false;
    }
}

std::string getChangeLevel()
{
    //return changeLevel;
    return (displayMoney(changeLevel));
}

bool incrementChangeLevel(int amountToAdd)
{
    if ((changeLevel + amountToAdd) > maxChangeCapacity)
    {
        return false;
    }
    else
    {
        changeLevel += amountToAdd;
        return true;
    }
}

std::string getMaxChangeCapacity()
{
    //return maxInventoryCapacity;
    return (displayMoney(maxChangeCapacity));
}

std::string getSnackPrice()
{
    //return SnackPrice;
    return displayMoney(SnackPrice);
}

std::string displayMoney(int amount)
{
    std::string dollars{std::to_string(amount / 100)};
    std::string cents{std::to_string(abs(amount % 100))};
    return "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}