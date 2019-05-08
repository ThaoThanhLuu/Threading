//
// Created by Development Environment on 5/7/19.
//

#include "Bitset.h"
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;


Bitset::Bitset(std::string s_fileName, int size)
{
    int temp = countChars(s_fileName);

    if (temp > 0) {

        ifstream file(s_fileName.c_str());

        capacity = temp;
        set = new char[capacity];
        this->size = size;
        bitsPerRow = static_cast<int>(sqrt(size));

        if (file.is_open() && !file.bad()) {
            char c;
            int counter = 0;

            while (file >> c && counter < capacity) {
                set[counter] = c;
                counter++;
            } // end while
        } // end if

        file.close();
    } else {
        throw new invalid_argument("Size must be greater than 0.");
    }
}


Bitset::Bitset(Bitset &other)
{
    size = other.size;
    capacity = other.capacity;
    set = new char[capacity];
    bitsPerRow = other.bitsPerRow;

    int i;
    for(i = 0; i < capacity; i++)
    {
        set[i] = other.set[i];
    }
}


Bitset::~Bitset(void)
{
    delete[] set;
}


int Bitset::operator()(int i, int j)
{
    int _byte    = (i * bitsPerRow) / __BYTEOFFSET;
    int rowStart = (i * bitsPerRow) % __BYTEOFFSET;
    int _bit = rowStart + j;

    while (_bit > 7)
    {
        _byte++;
        _bit -= 8;
    } // end

    if (testBit(_byte, _bit))
    {
        return 1;
    } // end if

    return 0;
}


int Bitset::operator[](int i)
{
    int byte = i / __BYTEOFFSET;
    int bit  = i % __BYTEOFFSET;

    if (testBit(byte, bit))
    {
        return 1;
    } // end if

    return 0;
} // end operator[]


void Bitset::setBit(int i, int j, bool b_val)
{
    int _byte = (i * bitsPerRow) / __BYTEOFFSET;
    int rowStart = (i * bitsPerRow) % __BYTEOFFSET;
    int _bit = rowStart + j;


    while (_bit > 7)
    {
        _byte++;
        _bit -= 8;
    } // end

    setBit(_byte, _bit, (b_val ? 1 : 0));
}


bool Bitset::allSame()
{
    int temp = (testBit(0, 0) ? 1 : 0);

    for(int i = 0; i < size; i++)
    {
        if (this->operator[](i) != temp)
        {
            return false;
        } // end if
    } // end for

    return true;
}

void Bitset::setBit(int i, int j, int i_val)
{
    if (i >= capacity)
    {
        string error = "Not a valid byte. Received: " + i;
        error += " Expected: 0-" + size;
        throw new invalid_argument(error);
    } // end if

    char temp = set[i];
    char* bit = &set[i];

    if (i_val && !testBit(i,j))
    {
        switch (j)
        {
            case 0:
                *(bit) |= __SETBIT0MASK;
                break;
            case 1:
                *(bit) |= __SETBIT1MASK;
                break;
            case 2:
                *(bit) |= __SETBIT2MASK;
                break;
            case 3:
                *(bit) |= __SETBIT3MASK;
                break;
            case 4:
                *(bit) |= __SETBIT4MASK;
                break;
            case 5:
                *(bit) |= __SETBIT5MASK;
                break;
            case 6:
                *(bit) |= __SETBIT6MASK;
                break;
            case 7:
                *(bit) |= __SETBIT7MASK;
                break;
            default:
                string error = "Not a valid bit. Received: " + j;
                error += " Expected: 0-7";
                throw new invalid_argument(error);
        }
    }
    else if(!i_val && testBit(i,j))
    {
        switch (j)
        {
            case 0:
                *(bit) &= __RESETBIT0MASK;
                break;
            case 1:
                *(bit) &= __RESETBIT1MASK;
                break;
            case 2:
                *(bit) &= __RESETBIT2MASK;
                break;
            case 3:
                *(bit) &= __RESETBIT3MASK;
                break;
            case 4:
                *(bit) &= __RESETBIT4MASK;
                break;
            case 5:
                *(bit) &= __RESETBIT5MASK;
                break;
            case 6:
                *(bit) &= __RESETBIT6MASK;
                break;
            case 7:
                *(bit) &= __RESETBIT7MASK;
                break;
            default:
                string error = "Not a valid bit. Received: " + j;
                error += " Expected: 0-7";
                throw new invalid_argument(error);
        } // end switch
    } // end else
} // end method setBit(int,int,int)

void Bitset::writeToFile(string s_fileName)
{
    remove(s_fileName.c_str());
    ofstream file(s_fileName.c_str(), ios::app | ios::binary);

    if (file.is_open() && !file.bad())
    {
        for (int i = 0; i < capacity; i++)
        {
            char temp = set[i];

            file << temp;
        }
    }
}


bool Bitset::testBit(int i, int j)
{
    if (i >= capacity)
    {
        string error = "Not a valid byte. Received: " + i;
        error += " Expected: 0-" + (capacity-1);
        throw new invalid_argument(error);
    } // end if
    if ((i*__BYTEOFFSET + j >= size))
    {
        string error = "Not a valid bit. Received: " + (i*__BYTEOFFSET + j);
        error += " Expected: 0-" + (size-1);
        throw new invalid_argument(error);
    } // end if

    char temp = set[i];

    switch (j)
    {
        case 0:
            return temp & __SETBIT0MASK;
        case 1:
            return temp & __SETBIT1MASK;
        case 2:
            return temp & __SETBIT2MASK;
        case 3:
            return temp & __SETBIT3MASK;
        case 4:
            return temp & __SETBIT4MASK;
        case 5:
            return temp & __SETBIT5MASK;
        case 6:
            return temp & __SETBIT6MASK;
        case 7:
            return temp & __SETBIT7MASK;
        default:
            string error = "Not valid bit. Received: " + j;
            error += " Expected: 0-7";
            throw new invalid_argument(error);
    }
}


int Bitset::countChars(string s_fileName)
{
    ifstream file(s_fileName, ios::binary | ios::ate);
    return static_cast<int>(file.tellg());
} // end method countChars


ostream& operator<<(ostream& stream, Bitset* set)
{
    for (int i = 0; i < set->bitsPerRow; i++)
    {
        for (int j = 0; j < set->bitsPerRow; j++)
        {
            stream << (*set)(i, j) << " " ;
        }

        stream << endl;
    }

    return stream;
}