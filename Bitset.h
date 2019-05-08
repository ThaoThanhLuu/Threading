//
// Created by Development Environment on 4/29/19.
//
#ifndef NULL
#define NULL 0
#endif // !NULL

// offset for byte
#ifndef __BYTEOFFSET
#define __BYTEOFFSET 8
#endif // !__BYTEOFFSET

// masks to extract bit k
#ifndef __BITMASKS
#define __BITMASKS

#define __SETBIT0MASK 0x01
#define __SETBIT1MASK 0x02
#define __SETBIT2MASK 0x04
#define __SETBIT3MASK 0x08
#define __SETBIT4MASK 0x10
#define __SETBIT5MASK 0x20
#define __SETBIT6MASK 0x40
#define __SETBIT7MASK 0x80

#define __RESETBIT0MASK ~__SETBIT0MASK
#define __RESETBIT1MASK ~__SETBIT1MASK
#define __RESETBIT2MASK ~__SETBIT2MASK
#define __RESETBIT3MASK ~__SETBIT3MASK
#define __RESETBIT4MASK ~__SETBIT4MASK
#define __RESETBIT5MASK ~__SETBIT5MASK
#define __RESETBIT6MASK ~__SETBIT6MASK
#define __RESETBIT7MASK ~__SETBIT7MASK

#endif // !__BITMASKS


#ifndef __BITSET_T

#define __BITSET_T

#include <string>

using namespace std;

class Bitset
{
private:
    int capacity;
    int size;
    int bitsPerRow;
    char * set;
    bool testBit(int i, int j);
    int countChars(string s_fileName);
    void setBit(int i, int j, int val);
public:
    Bitset(string s_fileName, int size); //
    Bitset(Bitset &other);
    ~Bitset();
    bool allSame();
    void setBit(int i, int j, bool b_val);
    void writeToFile(string s_fileName);
    friend ostream& operator<<(ostream&, Bitset*);
    int operator()(int i, int j);
    int operator[](int i);
};
#endif

