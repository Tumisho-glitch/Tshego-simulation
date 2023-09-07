#ifndef LIBSRI_H
#define LIBSRI_H

#include<iostream>

using namespace std;

namespace SRIspace{

    const int ERR_NUM_PARAMS = -1;
    const int ERR_PARAM_DATA_TYPE = -2;

    //Game items
    const int EMPTY_SPACE_NUM = 0;
    const int SUSCEPTIBLE_NUM = 1;
    const int INFECTED_NUM = 2;
    const int RECOVERED = 3;
    const int IMMUNE_NUM = 4;

    const char ENVIRO_ITEMS[5] = {'*','S','I','R','-'};

    int convertToInt(char* charNum, char** argv);
    void initEnviro(int intEnviroSize,int**& arrEnviro,int intNumPeopleSucsceptible,int intNumInfected,int intNumRecovered);
    void initEnviroItems(int intEnviroSize, int**& arrEnviroSize,int intNumItems, int item);
    int getRandom(int intLow,int intHigh);
    bool isSpaceEmpty(int** arrEnviro,int randDrow,int randDCol);
    void printEnvironment(int intEnviroSize,int** arrEnviro);
    void pause();
    void  HandleMovement(int intEnviroSize,int**& arrEnviro);
    void moveElement(int intEnroSize,int**& arrEnviro,int row,int& col);
    bool isThereItem(int intDRow,int intDcol,int intEnviroSize, int** arrEnviro);
    bool isInRange(int intDRow,int intDcol, int intEnviroSize);
    void   HandleInfection(int intEnviroSize,int**& arrEnviro, int intInfectionChance, int& NumberOfInfections);
    void infectElement(int row,int col,int intEnviroSize, int**& arrEnviro, int intInfectionChance,int& NumberOfInfections);
    void HandleRecoveryAndImmunity(int intEnviroSize,int**& arrEnviro,int intRecoverChance,int intImmunityChance);
    void testEndSimulation(int intEnviroSize,int** arrEnviro, bool& blnContinue);
    void  DeallocateMemory(int**& arrEnviro);
}

#endif
