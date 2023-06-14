/***********************************************************************
 * Izveidot programmu valodā C++.
 * Ar faila komponenti tiek saprasts fiksēta garuma ieraksts.
 * Sīkākās prasības sk. Laboratorijas darbu noteikumos.
 * H9.
 * Doti divi faili bināri f1 un f2,
 * kuru komponentes ir patvaļīgas simbolu virknes (komponentes sakārtotas alfabētiski).
 * Uzrakstīt programmu,
 * kas apvieno failus f1 un f2 failā f3 tā, lai arī f3 komponentes būtu sakārtotas
 * (failā f3 nedrīkst parādīties divas komponentes ar vienādu vērtību).
 * Programmu veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā.
 * *Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
 *
 * Autors: Markuss Birznieks, mb20075
 * Programma izveidota: 26.04.2023 18:25
 * Pēdejās izmaiņas: 06.05.2023
 *
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "Komp.h"

using namespace std;

/**
void createFile(int n);
funkcija createFile(n) -
izveido failu f1.bin vai f2.bin, atkarībā no n vērtības un pieprasa ierakstīt failā ierakstus.
*/
void createFile(int n);
/**
void printFile(int n);
funkcija printFile(n) -
izdrukā faila f1.bin vai f2.bin saturu, atkarībā no n vērtības.
*/
void printFile(int n);

int main()
{
    int izvele;
    do {
        cout << "Izvēlieties darbību (1 - izveidot failu, 2 - izdruktāt faila saturu, 0 - beigt darbu): ";
        cin >> izvele;

        switch (izvele)
        {
            case 1:
                cout << "Izvēlēties failu (f1 - 1, f2 - 2): ";
                cin >> izvele;
                createFile(izvele);
                printFile(izvele);
                break;
            case 2:
                cout << "Izvēlēties failu (f1 - 1, f2 - 2): ";
                cin >> izvele;
                printFile(izvele);
                break;
            case 0:
                cout << "Darbs pabeigts!" << endl;
                break;
            default:
                cout << "Nepareiza ievade!" << endl;
                break;
        }

        cin.clear();
    } while (izvele);

    return 0;
}

void createFile(int n)
{
    ofstream f;
    switch (n)
    {
        case 1:
            f.open("f1.bin", ios::out | ios::binary);
            break;
        case 2:
            f.open("f2.bin", ios::out | ios::binary);
            break;
        default:
            cout << "Nepareiza ievade!" << endl;
            return;
    }

    if (!f) {
        cout << "Neizdevās atvērt failu!" << endl;
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

void printFile(int n)
{
    ifstream f;
    switch (n)
    {
        case 1:
            f.open("f1.bin", ios::in | ios::binary);
            cout << "Faila f1.bin saturs:" << endl;
            break;
        case 2:
            f.open("f2.bin", ios::in | ios::binary);
            cout << "Faila f2.bin saturs:" << endl;
            break;
        default:
            cout << "Nepareiza ievade!" << endl;
            return;
    }

    cout << "---------------------" << endl;
    Komp k;
    while (k.readFromFile(f))
    {
        k.print();
    }
    cout << "---------------------" << endl;
    f.close();
}
