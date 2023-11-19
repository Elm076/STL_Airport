

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

    dataBase.searchAirline("RYR");

    //Tried to do exercise 4
    // dataBase.searchAirline("IBE");

    std::cout << "----- End of the program -----" << std::endl;
}