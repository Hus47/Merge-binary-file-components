#ifndef FUNKCIJAS_H
#define FUNKCIJAS_H

#include <string>

using namespace std;

/**
 * void createFile(const string &fileName);
 * Funkcija createFile(fileName) -
 * izveido failu fileName.bin un pieprasa ierakstīt failā ierakstus.
*/
void createFile(const string &fileName);
/**
 * void printFile(const string &fileName);
 * Funkcija printFile(fileName) -
 * izdrukā faila fileName.bin saturu.
*/
void printFile(const string &fileName);
/**
 * bool mergeFiles(const string &f1Name, const string &f2Name, const string &f3Name);
 * Funkcija mergeFiles(f1Name, f2Name, f3Name) -
 * apvieno failus f1 un f2 failā f3 tā, lai arī f3 komponentes būtu sakārtotas.
*/
bool mergeFiles(const string &f1Name, const string &f2Name, const string &f3Name);

#endif // FUNKCIJASS_H
