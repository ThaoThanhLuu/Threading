//
// Created by Development Environment on 4/29/19.
//

#ifndef LAB3_1_HELPERFUNCTIONS_H
#define LAB3_1_HELPERFUNCTIONS_H

// Defines:
#ifndef _MIN
#define _MIN(a,b) (a < b? a : b)
#endif // !_MIN
#ifndef _MAX
#define _MAX(a,b) (a > b? a : b)
#endif // !_MAX

// Namespace:
using namespace std;

// Prototypes:
int userInput(string&, const int, const int);

void init(void);
void printError(string&, const int);

// Problem1:
void executeP1(const int, const int);
void makeBinFileP1(const int);
void* threadStart(void*);

bool getNewValue(const int, const int, Bitset*);
bool checkProb1(void);

// Problem2:
void runProblem2(const int, const int);
void* threadStart2(void*);
void p2txtGen(const int, double *);
void generateRandomDoublesInRange(const double, const double, double*, const int);
void readArrayFromFile(double *);

bool checkProb2(double *);


// Global constants:
const string s_FILENAME  = "outputProblem1.bin";
const string s_FILENAME2 = "outputProblem2.txt";
const double d_RANDMAX   =  1000.0;
const double d_RANDMIN   = -1000.0;

// Global variables:
mutex mtx;
int i_N;

// Constants:
const int maxMatrix       = 10000;
const int mxThreads = 100;
const int mxChoice  = 3;
const int mChoice  = 1;
const int mThreads = 1;
const int minMatrix       = 1;

string positiveMatrix  = "Enter a positive integer for the size of matrix to use \n"
                         "Has to be 1 <= n <= 10000: \n";
string threads         = "Enter a positive integer for the number of threads to use\n"
                         "Has to be 1 <= m <= 100: \n";
string inputChoice     = "Enter your choice:\n";
string errorMessage    = "You must chose either 1, 2, or 3. \n";

void executeP1(const int i_N, const int i_M)
{
    // Variables:
    makeBinFileP1(i_N);
    Bitset* set = new Bitset(s_FILENAME, i_N*i_N);
    do
    {
        pthread_t threads[i_M];

        for (int i = 0; i < i_M; i++)
        {
            pthread_create(&threads[i], NULL, threadStart, (void*)set);
        } // end for
        for(int i = 0; i < i_M; i++)
        {
            pthread_join(threads[i], NULL);
        } // end for

        threadStart((void*)set);

        cout << set << endl;
    } while(!checkProb1());

    delete set;
} // end method executeP1

void* threadStart(void* args)
{
    Bitset * set = (Bitset*)args;

    int i = rand() % i_N,
            j = rand() % i_N;

    try
    {
        bool newValue = getNewValue(i, j, set);

        mtx.lock();
        set->setBit(i, j, newValue);
        set->writeToFile(s_FILENAME);
        mtx.unlock();
    } // end try
    catch (exception)
    {
        exit(EXIT_FAILURE);
    } // end catch

    return NULL;
} // end method threadStart


bool getNewValue(const int i, const int j, Bitset * set)
{
    int zeroes = 0,
            ones   = 0;

    if (i >= i_N - 1) {}
    else {
        if ((*set)(i + 1, j)) {
            ones++;
        } // end if
        else {
            zeroes++;
        } // end else
    } // end if

    if (j >= i_N - 1) {}
    else {
        if ((*set)(i, j + 1)) {
            ones++;
        } // end if
        else {
            zeroes++;
        } // end else
    }

    if (i > 0)
    {
        if ((*set)(i - 1, j))
        {
            ones++;
        } // end if
        else
        {
            zeroes++;
        } // end else
    }

    if (j > 0)
    {
        if ((*set)(i, j - 1))
        {
            ones++;
        } // end if
        else
        {
            zeroes++;
        } // end else
    }

    if (i >= (i_N - 1) || j >= (i_N - 1)) {}
    else {
        if ((*set)(i + 1, j + 1)) {
            ones++;
        } // end if
        else {
            zeroes++;
        } // end else
    }

    if (i <= 0 || j <= 0) {}
    else {
        if (!(*set)(i - 1, j - 1)) {
            zeroes++;
        } // end if
        else {
            ones++;
        } // end else
    }

    if (i <= 0 || j >= (i_N - 1)) {}
    else {
        if ((*set)(i - 1, j + 1)) {
            ones++;
        } // end if
        else {
            zeroes++;
        } // end else
    }

    if (i >= (i_N - 1) || j <= 0)
        return zeroes < ones;
    if (!(*set)(i + 1, j - 1)) {
        zeroes++;
    } // end if
    else {
        ones++;
    } // end else

    return zeroes < ones;

}


void makeBinFileP1(const int i_N)
{
    remove(s_FILENAME.c_str());
    fstream file(s_FILENAME.c_str(), ios::binary | ios::in | ios::app);

    int stop = static_cast<int>(ceil((i_N * i_N) / 8.0));

    if(file.is_open() && !file.bad())
    {
        for(int i = 0; i < stop; i++)
        {
            char temp = rand() % 256;
            file << temp;
        }
    }
}


void p2txtGen(const int i_N, double *da_arr)
{
    remove(s_FILENAME2.c_str());
    fstream file(s_FILENAME2.c_str(), ios::out | ios::app);

    if(file.is_open() && !file.bad())
    {
        for(int i = 0; i < i_N*i_N; i++)
        {
            file << std::fixed << std::setprecision(8) << da_arr[i];
            file << '\t';
        }
    }
}


void runProblem2(const int i_N, const int i_M)
{
    double* da_arr = new double[i_N*i_N];

    generateRandomDoublesInRange(d_RANDMIN, d_RANDMAX, da_arr, i_N*i_N);
    p2txtGen(i_N, da_arr);

    do
    {
        pthread_t threads[i_M];
        readArrayFromFile(da_arr);

        for(int i = 0; i < i_M; i++)
        {
            pthread_create(&threads[i], NULL, threadStart2, (void*)da_arr);
        }
        for(int i = 0; i < i_M; i++)
        {
            pthread_join(threads[i], NULL);
        }

        cout << "Array: " << endl << "[";
        for (int i = 0; i < (i_N*i_N); i++)
        {
            cout << da_arr[i] << " ";
        }
        cout << "]" << endl;

        p2txtGen(i_N, da_arr);
    } while(!checkProb2(da_arr));

    delete[] da_arr;
}


void readArrayFromFile(double * da_arr)
{
    ifstream file(s_FILENAME2.c_str(), ios::in);

    double temp = 0;
    int i = 0;

    while (file >> temp)
    {
        da_arr[i] = temp;
        i++;
    }
}


void* threadStart2(void* args)
{
    int i   = rand() % (i_N*i_N),
            j   = rand() % (i_N*i_N),
            run = rand() % 3,
            temp = _MAX(i, j);

    i = _MIN(i, j);
    j = temp;

    double * arr = (double*)args;

    try
    {
        mtx.lock();
        switch(run)
        {
            case 0:
                cout << "Quick Sort "
                        "Running on the interval [" << i << ", " << j << "]" << endl;
                quicksort(arr, i, j);
                break;

            case 1:
                cout << "Bubble Sort"
                        "Running on the interval [" << i << ", " << j << "]" << endl;
                bubbleSort(arr, i, j);
                break;

            case 2:
                cout << "Insertion Sort"
                        "Running on the interval [" << i << ", " << j << "]" << endl;
                insertionSort(arr, i, j);
                break;
        }
        mtx.unlock();

    }
    catch (exception)
    {
        exit(EXIT_FAILURE);
    }

    return NULL;
}


void generateRandomDoublesInRange(const double d_MIN, const double d_MAX, double* da_arr, const int i_COUNT)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(d_MIN, d_MAX);

    for(int i = 0; i < i_COUNT; i++)
    {
        da_arr[i] = dis(gen);
    }
}


void printError(string& s_msg, const int i_choice)
{
    cout << "Error. Your input of \"" << i_choice << "\" did not work." << endl;
    cout << s_msg << endl << endl;
} // end method printError


void init(void)
{
    cout << endl;
    cout << "*******************" << endl;
    cout << "*[1] Run problem 1*" << endl;
    cout << "*[2] Run problem 2*" << endl;
    cout << "*[3] Exit         *" << endl;
    cout << "*******************" << endl;
    cout << endl;
}


bool checkProb1(void)
{
    ifstream file(s_FILENAME.c_str(), ios::binary);

    Bitset* a = new Bitset(s_FILENAME, i_N*i_N);

    bool done = a->allSame();

    delete a;

    if (done)
    {
        cout << "Problem 1 finished." << endl;
        file.close();
        return true;
    } // end if

    return false;
}


bool checkProb2(double *da_arr)
{
    int i;
    for (i = 1; i < i_N * i_N; i++)
    {
        if (da_arr[i - 1] > da_arr[i])
        {
            return false;
        }
    }

    return true;
}


int userInput(string& s_MSG, const int i_MIN, const int i_MAX)
{
    // Variables:
    int i_value = 0;
    string c;

    for(;;)
    {
        cout << s_MSG;

        getline(cin, c);

        i_value = atoi(c.c_str());

        // ensure valid input
        if (i_value < i_MIN || i_value > i_MAX) {
            cout << endl << "Invalid input. Try again." << endl;
            cout << "Input must be an integer in the range [" << i_MIN << "," << i_MAX << "]." << endl << endl;
            cin.clear();
        }
        else {
            return i_value;
        }
    }
}

#endif //LAB3_1_HELPERFUNCTIONS_H
