#include <iostream>
#include <fstream>
#include <random>
#include <pthread.h>
#include <mutex>
#include <iomanip>
#include "Bitset.h"
#include "Sorting.h"
#include "helperFunctions.h"

// Namespace:
using namespace std;

int main(int argc, char **argv)
{

    i_N = -1;

    if(argc > 0)
    {
        i_N = atoi(argv[0]);

        if(i_N < 1)
        {
            i_N = userInput(positiveMatrix, minMatrix, maxMatrix);\
		}
    }
    else
    {
        i_N = userInput(positiveMatrix, minMatrix, maxMatrix);
    }

    srand(unsigned(time(nullptr)));

    // Variables:
    int  i_numThreads = 0;
    int  i_choice     = 0;

    init();

        i_choice = userInput(inputChoice, mChoice, mxChoice);


        switch(i_choice) {
            case 1 : cout << '1'; // prints "1"
                i_numThreads = userInput(threads, mThreads, mxThreads);
                executeP1(i_N, i_numThreads);
                break;       // and exits the switch
            case 2 : cout << '2';
                i_numThreads = userInput(threads, mThreads, mxThreads);
                runProblem2(i_N, i_numThreads);
                break;
            case 3 :
                cout << endl << "Bye." << endl;
                break;
            default:
                printError(errorMessage, i_choice);
        }

    return EXIT_SUCCESS;
}

