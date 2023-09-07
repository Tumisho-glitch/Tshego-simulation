#include<iostream>
#include"libSRI.h"
#include<cstdlib>
#include<ctime>

using namespace std;
using namespace SRIspace;

int main(int argc, char** argv){

    //seed random
    srand(time(nullptr));

    int intEnviroSize, intInfectionChance, intRecoverChance, intImmunityChance, intNumPeopleSucsceptible;
    int intNumInfected, intNumRecovered;
    int** arrEnviro;

    int NumberOfInfections;
    double avgNumberOfInfections;


    //check number of inputs and print error
    if(argc!=8){
        cerr<< "Please enter " << argv[0] << " <Enviro Size> <Infection chance> <Recovery chance> ";
        cerr << "<Immunity chance> <Num of people sucsceptible> <Num Infected> <Num Recovered>" << endl;
        exit(ERR_NUM_PARAMS);
    }

    intEnviroSize = convertToInt(argv[1],argv);
    intInfectionChance = convertToInt(argv[2],argv);
    intRecoverChance = convertToInt(argv[3],argv);
    intImmunityChance = convertToInt(argv[4],argv);
    intNumPeopleSucsceptible = convertToInt(argv[5],argv);
    intNumInfected = convertToInt(argv[6],argv);
    intNumRecovered = convertToInt(argv[7],argv);

    //Initialie environment
    initEnviro(intEnviroSize, arrEnviro, intNumPeopleSucsceptible, intNumInfected, intNumRecovered);


    bool blnContinue = true;

    do{

        #ifndef _WIN32
            system("clear");
        #else
            system("cls");
        #endif


         printEnvironment(intEnviroSize, arrEnviro);

         //Ask user choice
         cout << "A: CONTINUE SIMULATION \t Q: QUIT" << endl;
         char userChoice;
         cin>> userChoice;

         switch(userChoice){

             case 'A':
             case 'a':
             {

                        HandleInfection(intEnviroSize, arrEnviro, intInfectionChance, NumberOfInfections);
                        HandleRecoveryAndImmunity(intEnviroSize, arrEnviro, intRecoverChance, intImmunityChance);
                     HandleMovement(intEnviroSize, arrEnviro);

                     //test End of game
                     testEndSimulation(intEnviroSize, arrEnviro, blnContinue);


                 break;
             }
             case 'q':
             case 'Q':
             {
                 blnContinue = false;
                 break;
             }
             default:
             {
                cerr << "Invalid Input: Try again" << endl;
             }

         }


         pause();


    }while(blnContinue);

    avgNumberOfInfections = static_cast<double>(NumberOfInfections)/static_cast<double>(intNumInfected);
    cout << "The average number of infections is " << avgNumberOfInfections << endl;

    //Release memory
    DeallocateMemory(arrEnviro);


    return 0;
}
