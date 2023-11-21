

#include <iostream>
#include <string>
#include <ctime>
#include "Dynamic_container.h"
#include "Airport.h"
#include "Linked_list.h"
#include "Iterator.h"
#include "AVL.h"
#include "VuelaFlight.h"

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

int main() {

    std::cout << std::endl << ".....Start of the program ....." << std::endl << std::endl;

    VuelaFlight dataBase("..\\aeropuertos_v2.csv", "..\\rutas_v1.csv", "..\\aerolineas_v1.csv");
    std::cout << std::endl;

    /*----EXERCISE 2----*/

    auto resultAEA = dataBase.searchFlights("AEA5201");
    auto resultVLG = dataBase.searchFlights("VLG2021");
    std::set<std::string> weathers;
    std::set<Date> dates;

    std::cout   << "Data of flight AEA5201:"<< std::endl
                << "Name of the Airline " << resultAEA[0].getAirline()->getName() << std::endl
                << "Country of the Airline " << resultAEA[0].getAirline()->getCountry() << std::endl
                << "Orig Airport " << resultAEA[0].getAirpOrig()->getIata() << std::endl
                << "Destiny Airport " << resultAEA[0].getAirpDest()->getIata() << std::endl;

    for(unsigned int i = 0; i < resultAEA.size(); i++){
            dates.insert(resultAEA[i].getDate());
            weathers.insert(resultAEA[i].getWeatherData());
    }

    std::cout   << "The flights were done during these flight conditions: " << std::endl;
    for (auto it = weathers.begin(); it != weathers.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    std::cout   << "The flights were done in these dates: " << std::endl;
    for (auto it = dates.begin(); it != dates.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;



    std::cout   << "Data of flight VLG2021:"<< std::endl
                << "Name of the Airline " << resultVLG[0].getAirline()->getName() << std::endl
                << "Country of the Airline " << resultVLG[0].getAirline()->getCountry() << std::endl
                << "Orig Airport " << resultVLG[0].getAirpOrig()->getIata() << std::endl
                << "Destiny Airport " << resultVLG[0].getAirpDest()->getIata() << std::endl;

    std::set<std::string> weathers2;
    std::set<Date> dates2;

    for(unsigned int i = 0; i < resultAEA.size(); i++){
        dates2.insert(resultAEA[i].getDate());
        weathers2.insert(resultAEA[i].getWeatherData());
    }

    std::cout   << "The flights were done during these flight conditions: " << std::endl;
    for (auto it = weathers2.begin(); it != weathers2.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    std::cout   << "The flights were done in these dates: " << std::endl;
    for (auto it = dates2.begin(); it != dates2.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

/*----EXERCISE 3----*/
    Airline airportVLG = dataBase.searchAirline("VLG");
    std::vector<Flight> flightsDateVLG = airportVLG.getFlights(Date(12,4,18),Date(14,4,18));

    std::set<std::string> planes;
    for(auto it = flightsDateVLG.begin(); it != flightsDateVLG.end(); it++){
        planes.insert(it.operator*().getPlane());
    }

    std::cout << "The planes used during the flights of VLG at 13/04/2018 are:" << std::endl;
    for (auto it = planes.begin(); it != planes.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;


/*----EXERCISE 4----
 * I tried to do it but it didn't work as spected.
 * The ERROR might be inside of VuelaFlight
    auto espLHR = dataBase.searchFlightsDestAirp("ES","LHR");
    auto espSTN = dataBase.searchFlightsDestAirp("ES","STN");
    auto espLTN = dataBase.searchFlightsDestAirp("ES","LTN");
    auto espLGW = dataBase.searchFlightsDestAirp("ES","LGW");

    for (auto it = espLHR.begin(); it != espLHR.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    for (auto it = espSTN.begin(); it != espSTN.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    for (auto it = espLTN.begin(); it != espLTN.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    for (auto it = espLGW.begin(); it != espLGW.end(); it++){
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
*/
    std::cout << "----- End of the program -----" << std::endl;
}