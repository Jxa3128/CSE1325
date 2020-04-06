// Jorge Avila Code3_1001543128
#include <iostream>
#include "House.h"
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "TrickOrTreater.h"


House::House(std::string house, std::map<int, std::string>CopyCandyMap):
houseName{house}, CandyRankingMap{CopyCandyMap}
{

}
// a name is going to be essentially the value for the "key & value" in map of candyRanking
std::string House::ringDoorbell(std::ostringstream & path)
{
    door.lock(); // we got this door.lock() from our class
    path << '*'; // the address was sent so this sticks
    int randomPick;
    int upperLimit = CandyRankingMap.size();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    randomPick = ((rand() % upperLimit) + 1);

    door.unlock();

    // this is returning the value that is associated with that key.
    return CandyRankingMap[randomPick];
}
