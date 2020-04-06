// Jorge Avila 1001543128 SnackMachine.h
#include <iostream>
#include <string>

enum STATUS
{
  OK_ChangeGiven,
  OK_NoChange,
  BAD_Insuff_Fund,
  BAD_Insuff_Change,
  BAD_unknown,
  BAD_InventoryExceed,
  GOOD_InventoryLevel,
  Restock_zero,
  Invalid_restock,
  RAN_OUT
};

STATUS status{};

class SnackMachine
{
  /* Right here is my constructor */

public:
  SnackMachine(std::string name, int cost, int change, int inventory) :

      machineName{name},
      SnackPrice{cost},
      changeLevel{change},
      inventoryLevel{inventory}

  {
  }
  std::string getMachineName()
  {
    return machineName;
  }
  bool buyASnack(int &payment, std::string &change, int &status)
  {

    int change_tostring = payment - SnackPrice;
    // changeLevel = changeLevel + change_tostring;
    // change = to_string(change_tostring);
    if (change_tostring > /* maxChangeCapacity */ changeLevel)
    {

      status = BAD_Insuff_Change;
      return false;
    }
    else if (payment > SnackPrice)
    {

      /* If payment is above then SnackPrice then do the arthimetic */
      //int change_tostring = payment - SnackPrice;
      changeLevel = changeLevel + SnackPrice;
      change = displayMoney(change_tostring);
      inventoryLevel = inventoryLevel - 1;
      //cout << change << endl; // testing out if it works and it does give correct change
      // ok but change needs to be given
      status = OK_ChangeGiven;
      return true;
    }
    else if (payment < SnackPrice)
    {

      // not enough money was given
      status = BAD_Insuff_Fund;
      return false;
    }
    else if (payment == SnackPrice)
    {
      /* If payment is above then SnackPrice then do the arthimetic */

      int change_tostring = payment - SnackPrice;
      changeLevel = changeLevel + SnackPrice;
      change = to_string(change_tostring);
      inventoryLevel = inventoryLevel - 1;
      // good, but no change is given
      status = OK_NoChange;
      return true;
    }
    else if (inventoryLevel == 0)
    {
      status = RAN_OUT;
      return false;
    }
  }
  int getInventoryLevel()
  {
    // whatever current level that may be

    return inventoryLevel;
  }
  int getMaxInventoryCapacity()
  {
    return maxChangeCapacity;
  }
  bool incrementInventory(int amountToAdd)
  {
    if ((amountToAdd + inventoryLevel) > maxInventoryCapacity)
    {
      status = BAD_InventoryExceed;
      // It was way to big and need to return;
      return false;
    }
    else if ((amountToAdd + inventoryLevel) <= maxInventoryCapacity)
    {
      inventoryLevel = amountToAdd + inventoryLevel;
      status = GOOD_InventoryLevel;
      return true;
    }
    else if (amountToAdd < 0)
    {
      // they entered zero for a restock
      status = Restock_zero;
      return false;
    }
    else if (amountToAdd < -1)
    {
      // entered a negative number
      status = Invalid_restock;
      return false;
    }
  }

  std::string getMaxChangeCapacity()
  {
    return (displayMoney(maxChangeCapacity));
  }
  std::string getSnackPrice()
  {
    return displayMoney(SnackPrice);
  }
  std::string displayMoney(int amount)
  {
    std::string dollars{std::to_string(amount / 100)};
    std::string cents{std::to_string(std::abs(amount % 100))};
    return "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
  }
  bool IncrementChangeLevel(int amountToAdd)
  {
    if ((changeLevel + amountToAdd) <= maxChangeCapacity)
    {
      changeLevel = changeLevel + amountToAdd;
      return true;
    }
    else if ((changeLevel + amountToAdd) > maxChangeCapacity)
    {

      return false;
    }
  }
  std::string getChangeLevel()
  {

    return (displayMoney(changeLevel));
  }

private:
  std::string machineName;
  int changeLevel;
  int maxChangeCapacity = 5000;
  int SnackPrice;
  int inventoryLevel;
  int maxInventoryCapacity = 100;
};
