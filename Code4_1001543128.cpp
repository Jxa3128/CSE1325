// Jorge Avila 1001543128

#include <iostream> //standard
#include <vector> // enable the vector usage
#include <iomanip> // enable setw() and other manipulations
#include <map> 	//enables map usage
#include <thread>	//enables thread usage and in make file -pthread flag is used
#include <chrono>	//enables time manipulation
#include <mutex>	//enables mutual exclusions for threads
#include <sstream>	//enables string manipulation
#include <cstring>	//enables c standard string manipulation
#include <bits/stdc++.h>	//c library (includes all basically)
#include <fstream>	//enables file manipulation
#include <string>	//enables c++ string library
#include "House.h"	//French's House header file
#include "TrickOrTreater.h"	//French's TOT header file

using namespace std;
void get_command_line_params(int argc, char *argv[], string &inFile, string &outFile); //prototype

void get_command_line_params(int argc, char *argv[], string &fileOne, string &fileTwo,string &fileThree)
{

	if (argc <= 3)
	{
		throw invalid_argument("Missing command line parameters – - Usage : ./Code4 - (file) - (file) - (file)");
	}

    fileOne = argv[1]; // candy
	fileTwo = argv[2]; //houses
    fileThree = argv[3]; //TOT

}
int main (int argc, char ** argv)
{

    /********************* variable assignments ********************/
    string fileOne;
    string fileTwo;
    string fileThree;
    char *strtokPtr;
    char delimiter [] = {"|"};
    map<int,string>candyRanking;
    string _candyINFO;
    string _candyName;
    int _candyAmount;
    char _candyINFO_cstring [300]; // this is what we convert from string --> char []
    vector<House*> HousePtr;
    string _houseNames;
    ostringstream houseHeader;
    vector <TrickOrTreater> VectorOfTrickOrTreaters;
    string _TOT_info;
    /******** CODE ***** CODE ******** CODE ****** CODE ****** CODE *****/
    try
    {
        get_command_line_params(argc, argv, fileOne,fileTwo,fileThree);
    }
    catch(invalid_argument &message)
    {
        cout << message.what() << endl;
		exit(0);
    }
    ifstream TOTFile(fileOne); //Candy
    ifstream HousesFile(fileTwo); // Houses
    ifstream CandyFile(fileThree); // TOT
	houseHeader << "          "; // scootch the header over 11 spaces
    while(getline(CandyFile,_candyINFO))
    {
        strcpy(_candyINFO_cstring, _candyINFO.c_str());
        strtokPtr = strtok(_candyINFO_cstring,delimiter);
        _candyName =  strtokPtr;
        strtokPtr = strtok(NULL,delimiter);
        _candyAmount = atoi(strtokPtr);
        candyRanking.insert(make_pair(_candyAmount,_candyName));
    }


    // we know this works now - This is just to print out the map in candyRanking
    /*
    for (auto it : candyRanking)
    {
        cout << it.first << "\n" << it.second << endl;
    }
    */


	if (HousesFile.is_open())
	{
		/* Reading the Houses name into the variable _houseNames */
		while(getline(HousesFile,_houseNames))
	    {
			/* pushing back the object House in HousePtr*/
			/* the reason we use new is that mutex is not copyable nor movable - therefore we reserve memory */
	        int i;
	        HousePtr.push_back(new House{_houseNames,candyRanking}); //instatiate new HOUSE object pointers
	        houseHeader << _houseNames; // these are the names that inserted in here to thus create the "header"
	        for(i = 0; i < 11 - _houseNames.length(); i++)
	        houseHeader << " "; //formatting


	    }
	}
	else
	{
		cout <<"\r\n Did not open." <<endl;
		exit(0);
	}
    //ostringstream needs .str()
    // while getting the names of the TOT.txt push them back to the vector (use a temp object)
	if (TOTFile.is_open())
	{
		while (getline(TOTFile, _TOT_info))
	    {
	        //TrickOrTreater tempObject(_TOT_info, HousePtr);
	        VectorOfTrickOrTreaters.push_back(TrickOrTreater{_TOT_info,HousePtr}); // mas isso nao da
	        cout << _TOT_info << endl;
	    }
	}
	else
	{
		cout << "File did not open." <<endl;
		exit(0);
	}

	int LINES = 34;
	int start;
	
	HousesFile.close();
	TOTFile.close();
	CandyFile.close();
	/* after we got everything we wanted we START Thread */
	for (auto &it : VectorOfTrickOrTreaters)
	{
		it.startThread(); // you're sinceing "this" for each startThread()
	}
	/* while the int Imdone variable is not the size of Vector of TOT then keep printing out stuff */
	while (TrickOrTreater::ImDone != VectorOfTrickOrTreaters.size())
	{
		for (start =0; start <= LINES; start++)
		{
			cout << "\n";
		}
		cout << houseHeader.str() << endl; //print in between
		//loop over trick or treator vector
		for(auto &it : VectorOfTrickOrTreaters) //need the address since the iterator is a pointer
		{
			cout << it.getPath() << it.getName() << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	/******** HERE IS THE END OF THE PROGRAM SO WE GOTS TO CLEAN UP OUR THINGS MADE WITH "NEW" *********/
	for (auto &it : VectorOfTrickOrTreaters )
	{
		// we join our individual threads
		it.joinThread();
	}
	for (auto &it: VectorOfTrickOrTreaters)
	{
		// we are printing out what each person has
		cout << it;
		//each iteration is the actual TOT
		//and what makes a TOT is that they have a list of house and a names


	}
	// delete the vector of house ptr && vector of TOT ptr
	for (auto &it : HousePtr)
	{
		 delete it;
	}


	/* main has ended */
    return 0;
}
