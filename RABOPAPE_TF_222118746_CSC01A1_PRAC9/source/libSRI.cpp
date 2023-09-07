#include<iostream>
#include"libSRI.h"
#include<sstream>
#include<cstdlib>
#include<cmath>


using namespace std;

namespace SRIspace{

    int convertToInt(char* charNum, char** argv){
        int convertedInt;

            stringstream myStream{charNum};
            myStream >> convertedInt;

            if(myStream.fail()){
                cerr << "Wrong data Type inputed" << endl;
                cerr<< "Please enter " << argv[0] << " <Enviro Size> <Infection chance> <Recovery chance> ";
                cerr << "<Immunity chance> <Num of people sucsceptible> <Num Infected> <Num Recovered>" << endl;
                exit(ERR_PARAM_DATA_TYPE);
            }

        return convertedInt;
    }

    void initEnviro(int intEnviroSize,int**& arrEnviro,int intNumPeopleSucsceptible,int intNumInfected,int intNumRecovered){
        arrEnviro = new int*[intEnviroSize];

        for(int row = 0; row < intEnviroSize; row++){
            arrEnviro[row] = new int[intEnviroSize];
            for(int col = 0; col < intEnviroSize; col++){
                arrEnviro[row][col] = EMPTY_SPACE_NUM;
            }
        }


        //init Num people sucsceptible
        initEnviroItems(intEnviroSize, arrEnviro, intNumPeopleSucsceptible, SUSCEPTIBLE_NUM);
        initEnviroItems(intEnviroSize, arrEnviro, intNumInfected, INFECTED_NUM);
        initEnviroItems(intEnviroSize, arrEnviro, intNumRecovered, RECOVERED);


    }


        void initEnviroItems(int intEnviroSize, int**& arrEnviro,int intNumItems, int item){

        for(int counter = 0; counter < intNumItems; counter++){
            //Generate a random position
            int randDrow = getRandom(0, intEnviroSize-1);
            int randDcol = getRandom(0, intEnviroSize-1);

            //test if the space is empty
            while(!isSpaceEmpty(arrEnviro, randDrow, randDcol)){
                randDrow = getRandom(0, intEnviroSize-1);
                randDcol = getRandom(0, intEnviroSize-1);
            }

            arrEnviro[randDrow][randDcol] = item;

        }

    }

    int getRandom(int intLow,int intHigh){
            int randomNum;
                int Range = intHigh - intLow + 1;
                randomNum = rand() % Range + intLow;
            return randomNum;
    }

       bool isSpaceEmpty(int** arrEnviro,int randDrow,int randDCol){
           bool isEmpty = true;

            if(!(arrEnviro[randDrow][randDCol] == EMPTY_SPACE_NUM)){
                isEmpty = false;
                return isEmpty;
            }

           return isEmpty;
       }

        void printEnvironment(int intEnviroSize,int** arrEnviro){
            for(int row = 0; row < intEnviroSize; row++){
                for(int col = 0; col < intEnviroSize; col++){

                    switch(arrEnviro[row][col]){
                        case EMPTY_SPACE_NUM:
                        {
                            cout << ENVIRO_ITEMS[EMPTY_SPACE_NUM] << " ";
                            break;
                        }
                        case SUSCEPTIBLE_NUM:
                        {
                            cout << ENVIRO_ITEMS[SUSCEPTIBLE_NUM] << " ";
                            break;
                        }
                        case INFECTED_NUM:
                        {
                            cout << ENVIRO_ITEMS[INFECTED_NUM] << " ";
                            break;
                        }
                        case RECOVERED:
                        {
                            cout << ENVIRO_ITEMS[RECOVERED] << " ";
                            break;
                        }
                        case IMMUNE_NUM:
                        {
                            cout << ENVIRO_ITEMS[IMMUNE_NUM] << " ";
                            break;
                        }
                    }

                }
                cout << endl;
            }
        }


    void pause(){
            cin.ignore(100, '\n');
            cin.clear();
            cout << "PRESS ENTER TO CONTINUE" << endl;
            cin.get();
    }

  void  HandleMovement(int intEnviroSize,int**& arrEnviro){
     //get any game element and move to random position
     for(int row = 0; row < intEnviroSize; row++){
         for(int col = 0; col < intEnviroSize; col++){

             if(!(arrEnviro[row][col] == EMPTY_SPACE_NUM)){
                  //if the next item is the same one
                 moveElement(intEnviroSize, arrEnviro, row, col);

             }


         }
     }
  }


   void moveElement(int intEnviroSize,int**& arrEnviro,int row,int& col){

       //generate random movement
       int movementDirection;
       int intDRow;
       int intDcol;

       bool blnisInRange = true;
       bool blnisThereItem = false;





         do{
             //First find a location within range
             //If the location is within range, check if there is an item in the location
             //If there is restart and find a new location until an empty location that is within range is found


             do{
                 //create a random location
                 //If the location is not withing the range, restart and generate another random location

                movementDirection = getRandom(1, 9);
                intDRow = row;
                intDcol = col;


               switch(movementDirection){

                   case 1:
                   {
                       intDRow--;
                       intDcol--;

                       break;
                   }
                   case 2:
                   {
                       intDRow--;

                       break;
                   }
                   case 3:
                   {
                       intDRow--;
                       intDcol++;

                       break;
                   }
                   case 4:
                   {
                       intDcol--;

                       break;
                   }
                   case 5:
                   {
                       //Do nothing, do not move

                       break;
                   }
                   case 6:
                   {
                       intDcol++;

                       break;
                   }
                   case 7:
                   {
                       intDRow++;
                       intDcol--;

                       break;
                   }
                   case 8:
                   {
                       intDRow++;

                       break;
                   }
                   case 9:
                   {
                       intDRow++;
                       intDcol++;

                       break;
                   }
                   default:{
                       cerr << "This line is not supposed to execute" << endl;
                   }
                }




                blnisInRange = isInRange(intDRow, intDcol, intEnviroSize);

            }while(!blnisInRange);


        //if the proposed location is in range, check if there is an element there
        //If so, restart and find a new location or accept the new location as a valid parameter
            blnisThereItem = isThereItem(intDRow, intDcol, intEnviroSize,arrEnviro);

         }while(blnisThereItem);



       //Move element to destination
       int element = arrEnviro[row][col];
       arrEnviro[row][col] = EMPTY_SPACE_NUM;
       arrEnviro[intDRow][intDcol] = element;
       arrEnviro[row][col] = EMPTY_SPACE_NUM;



       if(intDcol == col + 1){
           //jump the next col in
           col++;
        };
   }





   bool isThereItem(int intDRow,int intDcol,int intEnviroSize, int** arrEnviro){
       bool blnisThereItem = false;

            if(arrEnviro[intDRow][intDcol] != EMPTY_SPACE_NUM){
                blnisThereItem = true;
                return blnisThereItem;
            }

       return blnisThereItem;
   }

   bool isInRange(int intDRow,int intDcol, int intEnviroSize){
       bool blnisInRange = true;


           if(intDRow < 0){
               blnisInRange = false;
           }
           if(intDcol < 0){
               blnisInRange = false;
           }
           if(intDRow > (intEnviroSize - 1)){
               blnisInRange = false;
           }
           if(intDcol > (intEnviroSize - 1)){
               blnisInRange = false;
           }

       return blnisInRange;
   }


   void   HandleInfection(int intEnviroSize,int**& arrEnviro, int intInfectionChance, int& NumberOfInfections){
       for(int row = 0; row < intEnviroSize; row++){
           for(int col = 0; col < intEnviroSize; col++){

               if(arrEnviro[row][col] == SUSCEPTIBLE_NUM || arrEnviro[row][col] == RECOVERED){
                   infectElement(row, col,intEnviroSize, arrEnviro, intInfectionChance, NumberOfInfections);
               }

           }
       }
   }


   void infectElement(int Erow,int Ecol,int intEnviroSize,int**& arrEnviro, int intInfectionChance, int& NumberOfInfections){

       int NumInfectedCloseby = 0;

       //check How many Infectious people there are around


               //Check if the element is in any of the surrounding rows
                    if(isInRange(Erow - 1, Ecol - 1, intEnviroSize) && arrEnviro[Erow - 1][Ecol - 1] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow - 1, Ecol, intEnviroSize) && arrEnviro[Erow - 1][Ecol] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow - 1, Ecol + 1, intEnviroSize) && arrEnviro[Erow - 1][Ecol + 1] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow, Ecol - 1, intEnviroSize) && arrEnviro[Erow][Ecol-1] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow, Ecol + 1, intEnviroSize) && arrEnviro[Erow][Ecol+1] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow + 1, Ecol - 1, intEnviroSize) && arrEnviro[Erow + 1][Ecol - 1] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow + 1, Ecol, intEnviroSize) && arrEnviro[Erow + 1][Ecol] == INFECTED_NUM){
                        NumInfectedCloseby++;
                    }
                    if(isInRange(Erow + 1, Ecol + 1, intEnviroSize) && arrEnviro[Erow + 1][Ecol + 1] == INFECTED_NUM){
                     NumInfectedCloseby++;
                    }



       //test if Element is infected
        if(NumInfectedCloseby > 0){
           int infectionChance = NumInfectedCloseby * intInfectionChance;

           if(getRandom(0, 100) <= infectionChance){
               //Infect Individual
               arrEnviro[Erow][Ecol] = INFECTED_NUM;
           }
       }


   }


   void HandleRecoveryAndImmunity(int intEnviroSize,int**& arrEnviro,int intRecoverChance,int intImmunityChance){
       for(int row = 0; row < intEnviroSize; row++){
           for(int col = 0; col < intEnviroSize; col++){
               if(arrEnviro[row][col] == INFECTED_NUM){

                   //Attempt recovery
                   if(getRandom(0, 100) <= intRecoverChance){
                       //Recover Individual
                       arrEnviro[row][col] = RECOVERED;

                       if(getRandom(0, 10) <= intImmunityChance){
                           arrEnviro[row][col] = IMMUNE_NUM;
                       }
                   }

               }
           }
       }
   }

   void testEndSimulation(int intEnviroSize,int** arrEnviro,bool& blnContinue){
       int numInfected = 0;
       for(int row = 0; row < intEnviroSize; row++){
           for(int col = 0; col < intEnviroSize; col++){

               if(arrEnviro[row][col] == INFECTED_NUM){
                   numInfected++;
               }

           }
       }


       if(numInfected == 0){

           #ifndef _WIN32
            system("clear");
           #else
            system("cls");
           #endif

           printEnvironment(intEnviroSize, arrEnviro);


           cout << "--------------------------------------------------------" << endl;
           cout << "----------THERE ARE NO MORE INFECTED INDIVIDUALS--------" << endl;
           cout << "--------------------------------------------------------" << endl;
           blnContinue = false;
       }
   }

   void  DeallocateMemory(int**& arrEnviro){
       delete [] arrEnviro;
       arrEnviro = nullptr;
   }

}
