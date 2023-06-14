#include <iostream>
#include <string>
#include <cstring>
#include "Komp.h"

using namespace std;

void Komp::setVal(string val)
{
    strncpy(this->val, val.c_str(), KOMPGAR);
    this->val[KOMPGAR] = '\0';
}

void Komp::print()
{
    cout << this->val << endl;
}

bool Komp::readFromFile(ifstream &f)
{
    f.read(reinterpret_cast<char*>(this->val), sizeof(Komp));
    this->val[KOMPGAR] = '\0';
    return f.good();
}

bool Komp::readUniqueFromFile(ifstream &f)
{
    Komp temp;
    while(temp.readFromFile(f)) {
        if (this->compare(temp) != 0) {
            this->copy(temp);
            break;
        }
    }
    return f.good();
}

void Komp::writeToFile(ofstream &f)
{
    f.write(reinterpret_cast<char*>(this->val), sizeof(Komp));
}

int Komp::compare(Komp &k)
{
    return strcmp(this->val, k.val);
}

void Komp::copy(Komp &k)
{
    strcpy(this->val, k.val);
}
