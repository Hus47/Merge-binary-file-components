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
 * Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
 *
 * Autors: Markuss Birznieks, mb20075
 * Sākts: 24.04.2023 18:35
 * Sesija1: 24.04.2023 18:35 - 20:37 Sapratu ka nepazīstu pietiekami labi bināros failus. Pamācijos par bināriem failiem. Izgāju cauri nodaļai par bināriem failiem.
 * Sesija2: 26.04.2023 17:48 - 20:35 Izveidoju palīgprogrammu, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
 * Sesija3: 27.04.2023 8:40 - 8:57 Papildināju palīgprogrammu ar kārtošanu
 * Sesija4: 27.04.2023 9:00 - 12:30 Rakstu galveno programmu, sarkastīju testa plānus
 * Sesija5: 03.05.2023 22:00 - 22:30 -
 * Mainu pieeju, izmantoju klasi Komp, kas ļauj izveidot komponenti, kā arī salīdzināt komponentes.
 * Sesija6: 06.05.2023 15:40 - 17:05 - Izveidoju klasi Komp, kas ļauj izveidot komponenti, kā arī salīdzināt komponentes.
 * Sesija7: 07.05.2023 10:00 - 10:45 - Izveidoju metodi readUniqueFromFile, kas ļauj nolasīt nākamo komponenti, kas neatkārtojas. Izveidoju funkciju, kas apvieno failus f1 un f2 failā f3 tā, lai arī f3 komponentes būtu sakārtotas.
 * Sesija8: 07.05.2023 10:55 - 12:12 - Atsevišķu programmu vietā izviedoju funkcijas.h un funkcijas.cpp un pārrakstiju funkcijas printFile un createFile lai strādā ar klasi Komp un citi uzlabojumi. Veicu uzlabojumus klasei Komp un funkcijām. Izveidoju main kur var izvelēties darbību un kas izsauc funkcijas.
 * Līdz šim pavadītais laiks: ~12h
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Komp.h"
#include "funkcijas.h"

using namespace std;

int main()
{
    cout << "Programma izveido un apvieno failus f1 un f2 failā f3 tā, lai arī f3 komponentes būtu sakārtotas" << endl;
    int izvele;
    int apaksIzvele;
    do {
        cout << "Izvēlieties darbību (1 - izveidot failu, 2 - izdruktāt faila saturu, 3 - apvienot failus, 0 - beigt darbu): ";
        cin >> izvele;

        switch (izvele)
        {
            case 1:
                cout << "Faila izveidošana" << endl;

                cout << "Izvēlēties failu (f1 - 1, f2 - 2): ";
                cin >> apaksIzvele;

                switch (apaksIzvele)
                {
                    case 1:
                        createFile("f1.bin");
                        break;
                    case 2:
                        createFile("f2.bin");
                        break;
                    default:
                        cout << "Nepareiza izvēle" << endl;
                        break;
                }

                break;
            case 2:
                cout << "Faila izdruka" << endl;

                cout << "Izvēlēties failu (f1 - 1, f2 - 2, f3 - 3): ";
                cin >> apaksIzvele;

                switch (apaksIzvele)
                {
                    case 1:
                        printFile("f1.bin");
                        break;
                    case 2:
                        printFile("f2.bin");
                        break;
                    case 3:
                        printFile("f3.bin");
                        break;
                    default:
                        cout << "Nepareiza izvēle" << endl;
                        break;
                }

                break;
            case 3:
                cout << "Failu apvienošana" << endl;

                if(mergeFiles("f1.bin", "f2.bin", "f3.bin")) {
                    cout << "Failu apvienošana veiksmīga" << endl;

                    printFile("f3.bin");
                } else {
                    cout << "Failu apvienošana neveiksmīga" << endl;
                }

                break;
            case 0:
                cout << "Darbs pabeigts" << endl;
                break;
            default:
                cout << "Nepareiza izvēle" << endl;
                break;
        }

    } while (izvele);

    return 0;
}
/*****************************************************
 * Testa plāns failu apvienošanai
 * komats ',' atdala komponentes
 * f1 saturs                                f2 saturs                                   f3 saturs                                               Programma rezultāts     Apraksts
 * daba, ddba, lauks, maja, miza, saaule,   daaba, lats, maize, saule, zars, zirgs      daaba, daba, ddba, laats, lauks, maize, maja, miza,     +                       Atšķirīgas un kopīgas komponentes
 * saule, zale, zirgs                                                                   saaule, saule, zale, zars, zirgs
 *
 * daba, lauks, maja, saule, zirgs          daba, lauks, maja, saule, zirgs             daba, lauks, maja, saule, zirgs                         +                       Vienādas komponentes
 *
 * <nav>                                    daba, lauks, maja, saule, zirgs             daba, lauks, maja, saule, zirgs                         +
 *
 * daba, lauks, maja, saule, zirgs          <nav>                                       daba, lauks, maja, saule, zirgs                         +
 *
 * <nav>                                    <nav>                                       <nav>                                                   +
 *
 * daaba, lats, maize, saule, zirgs         sa ule, saaule, zars, zirgs zars            daaba, lats, maize, sa ule, saaule, saule, zars,        +                       Atšķirīgas komponentes un atstarpes komponentēs
 *                                                                                      zirgs, zirgs zars
 *
 * abols, daba, daba, lauks, lauks, lauks   abols, daaba, lats, saule, zars, zirgs      abols, daaba, daba, lats, lauks, saule, zars, zirgs     +                       Failos atkārtojošas komponentes
*/
/**************************************************
 * Testa Plāns failu izveidei
 * komats ',' atdala ierakstus
 * Ievadītie ieraksti(ievade)                No faila nolasītie ieraksti(izvade)        Rezultāts
 * zirgs, saule, lauks, maja, daba           daba, lauks, maja, saule, zirgs            +
 *
 * svaigs, sartums, zelts, sviests, burkans  burkans, sartums, svaigs, sviests, zelts   +
 *
 * zirgs, zale, saule, saaule, lauks, maja,  daba, ddba, lauks, maja, miza, saaule,     +
 * miza, ddba, daba                          saule, zale, zirgs
 *
 * zirgs, zars, saule, lats, maize, daaba    daaba, lats, maize, saule, zars, zirgs     +
 *
 * zirgs zars, sa ule, saaule, zars          sa ule, saaule, zars, zirgs zars           +               Atstarpes komponentēs
 *
 * <nav>                                     <nav>                                      +
 *
 * daba, lauks, daba, lauks, lauks, abols    abols, daba, daba, lauks, lauks, lauks     +               Atkārtojošas komponentes
 *
****************************************************/
