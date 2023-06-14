#include <string>
#include <fstream>
using namespace std;

const int KOMPGAR = 10;

class Komp
{
public:
    /**
     * void setVal(string val);
     * Funkcija setVal(string val) -
     * iestata komponentes vērtību.
    */
    void setVal(string val);
    /**
     * void print();
     * Funkcija print() -
     * izdrukā komponentes vērtību.
    */
    void print();
    /**
     * bool readFromFile(ifstream &f);
     * Funkcija readFromFile(ifstream &f) -
     * nolasa komponenti no faila.
    */
    bool readFromFile(ifstream &f);
    /**
     * bool readUniqueFromFile(ifstream &f);
     * Funkcija readUniqueFromFile(ifstream &f) -
     * nolasa komponenti, kas nav vienāda ar iepriekšējo komponenti.
    */
    bool readUniqueFromFile(ifstream &f);
    /**
     * void writeToFile(ofstream &f);
     * Funkcija writeToFile(ofstream &f) -
     * ieraksta komponenti failā.
    */
    void writeToFile(ofstream &f);
    /**
     * bool compare(Komp &k);
     * Funkcija compare(Komp &k) -
     * salīdzina komponentes vērtības.
    */
    int compare(Komp &k);
    /**
     * void copy(Komp &k);
     * Funkcija copy(Komp &k) -
     * kopē komponentes vērtību.
    */
    void copy(Komp &k);
private:
    char val[KOMPGAR+1];
};
