// Jorge Avila
#include <iostream>
#include "TrickOrTreater.h"
#include "House.h"
/*
    *   How does static work?
    *   static means "unchanging"
    *   it is shared by all these member funtions in class TrickOrTreater
    *   And they have a scope till the program lifetime
    *
*/
int TrickOrTreater::ImDone = 0;

std::ostream& operator<<(std::ostream& out, TrickOrTreater& TOT)
{
    out << TOT.name;
    for (auto element : TOT.Bucket)
    {
        out << "|" << element.first << "|" << element.second;

    }
    std::cout << std::endl;
    return out;
}
//constructor
TrickOrTreater::TrickOrTreater(std::string person, std::vector<House*>HouseVectorPointer):
name{person},ListOfHouses{HouseVectorPointer}
{

}
std::string TrickOrTreater::getName()
{
    return name;
}
void TrickOrTreater::startThread()
{
    TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating,this);
}
void TrickOrTreater::joinThread()
{
    /* range based for loop that we are gonna have to call to join all threads */
    this->TOTThreadPtr->join();
    delete this->TOTThreadPtr;
    // so if we take the "this->" out then it would not know what instance of thread to join() ??
}
void TrickOrTreater::GoTrickOrTreating()
{
    // GoTrickOrTreating is the START of all of this when startThread() is initiated
    /*
    Member function GoTrickOrTreating() is the function called when the thread is started. It controls everything else the trick or treater does.
This function moves the trick or treater between houses, rings the doorbell at each house and increments the chosen candy in the trick or treater’s candy bucket.
Inside a range based for loop,
a speed is determined by picking a random number between 1 and 500.
Walk() is called and is passed speed
ringDoorbell() is called and is passed path. The return value of ringDoorbell() is the name of the candy randomly chosen and that name is used to key on that candy in Bucket and increment it.
After completing the loop over all TrickOrTreater’s, increment ImDone to show that this thread has visited all houses and is done trick or treating.
    */
    std::string nameCandy;
    int upperLimit = 500; // a range btw 1 and 500
    int speed;
    for (auto it : ListOfHouses)
    {
        // call rand % 500 + 1
        speed = ((rand() % upperLimit) + 1); // that plus one shifts everything one
        // call walk
        Walk(speed);

        nameCandy = it->ringDoorbell(path);
        Bucket[nameCandy]++;
    }

    //thus the variable returned is then incremented the chosen candy into it's bucket
    // increment ImDone
    ImDone++;
}
void TrickOrTreater::Walk(int walk_speed)
{
    /*
    Member function Walk() uses a for loop to stream single dots ‘.’ into ostringstream path one at a time.
     Between outputting each dot, the thread sleeps for the speed value passed into Walk() from
      GoTrickOrTreating(). See Step 7A for more information on how speed is calculated in GoTrickOrTreating().

    */
    int walking;
    for (walking = 0; walking < 10; walking ++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(walk_speed));
        path << '.';
    }

}
std::string TrickOrTreater::getPath()
{
    return path.str(); //ostringstream --> .str() is needed
}
