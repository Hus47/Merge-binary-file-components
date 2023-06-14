#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "Komp.h"
#include "funkcijas.h"

using namespace std;

void createFile(const string &fileName)
{
    ofstream f;
    f.open(fileName, ios::binary | ios::out);

    if (!f) {
        cout << "Neizdevās atvērt failu " << fileName << endl;
        return;
    }

    // Pieprasam ievadīt ierakstus un saglabājam tos listā
    list<string> ieraksti;
    string ieraksts;
    cout << "(CTRL+Z lai pabeigtu ierakstīšanu)" << endl;
    cout << "Ierakstiet ierakstu: ";
    cin.ignore();
    while (getline(cin, ieraksts))
    {
        ieraksti.push_back(ieraksts);
        cout << "(CTRL+Z lai pabeigtu ierakstīšanu)" << endl;
        cout << "Ierakstiet ierakstu: ";
    }
    cin.clear();

    // Sakārtojam ierakstus alfabētiski
    // Vispirms saliekam tos mapē, kur atslēga ir pirmā burts un vērtība ir list ar visiem ierakstiem, kuri sākas ar šo burtu
    map<char, list<string>> ierakstiMap;
    for (auto s : ieraksti)
    {
        char c = s[0];
        if (ierakstiMap.find(c) == ierakstiMap.end()) {
            ierakstiMap[c] = list<string>();
        }
        ierakstiMap[c].push_back(s);
    }

    // Ierakstam ierakstus failā
    Komp k;
    for (auto i : ierakstiMap)
    {
        i.second.sort();
        //cout << i.first << ": ";
        for (auto s : i.second)
        {
            //cout << s << ", ";
            k.setVal(s);
            k.writeToFile(f);
        }
    }

    f.close();
}

void printFile(const string &fileName)
{
    ifstream f;
    f.open(fileName, ios::binary | ios::in);

    if (!f) {
        cout << "Neizdevās atvērt failu " << fileName << endl;
        return;
    }

    Komp k;
    cout << fileName << " saturs" << endl;
    cout << "---------------------" << endl;
    while (k.readFromFile(f))
    {
        k.print();
    }
    cout << "---------------------" << endl;
    f.close();
}

bool mergeFiles(const string &f1Name, const string &f2Name, const string &f3Name)
{
    ifstream f1(f1Name, ios::in | ios::binary);
    if (!f1) {
        cout << "Neizdevās atvērt failu " << f1Name << endl;
        return false;
    }
    ifstream f2(f2Name, ios::in | ios::binary);
    if (!f2) {
        cout << "Neizdevās atvērt failu " << f2Name << endl;
        return false;
    }
    ofstream f3(f3Name, ios::out | ios::binary);
    if (!f3) {
        cout << "Neizdevās atvērt failu " << f3Name << endl;
        return false;
    }

    Komp f1Komp;
    Komp f2Komp;

    f1Komp.readUniqueFromFile(f1);
    f2Komp.readUniqueFromFile(f2);

    // Lasa failu f1 un f2 komponentes un liek failā f3 alfabētiskā secībā neatkārtojot vārdus
    // Tas ir liek failā f3 mazāko komponenti vai ja vienādas tad vienu no tām
    while (f1.good() && f2.good()) {
        if (f1Komp.compare(f2Komp) < 0) {
            f1Komp.writeToFile(f3);
            f1Komp.readUniqueFromFile(f1);
        } else if (f1Komp.compare(f2Komp) > 0){
            f2Komp.writeToFile(f3);
            f2Komp.readUniqueFromFile(f2);
        }
        else if (f1Komp.compare(f2Komp) == 0) {
            f1Komp.writeToFile(f3);
            f1Komp.readUniqueFromFile(f1);
            f2Komp.readUniqueFromFile(f2);
        }
    }

    // Ja viens no failiem ir beidzies, tad ieraksta otrā faila komponentes
    while (f1.good()) {
        f1Komp.writeToFile(f3);
        f1Komp.readUniqueFromFile(f1);
    }
    while (f2.good()) {
        f2Komp.writeToFile(f3);
        f2Komp.readUniqueFromFile(f2);
    }

    return true;
}
