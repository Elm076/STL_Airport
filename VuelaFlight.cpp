//
// Created by fotop on 24/10/2023.
//


#include "VuelaFlight.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>

VuelaFlight::VuelaFlight(const std::string airports_file, const std::string routes_file, const std::string airlines_file) {

    std::ifstream airports_stream;

    airports_stream.open(airports_file); //project folder
    if (airports_stream.good()) {
        std::string id;
        std::string iata;
        std::string type;
        std::string name;
        std::string strLatitude;
        std::string strLongitude;
        std::string continent;
        std::string country_iso;
        std::stringstream columns_airports;
        std::string line;

        clock_t t_ini = clock();

        while (getline(airports_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_airports.str(line);

                //Line format: id;iata;type;size;fecha;country_iso

                getline(columns_airports, id, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_airports, iata, ';');
                getline(columns_airports, type, ';');
                getline(columns_airports, name, ';');
                getline(columns_airports, strLatitude, ';');
                getline(columns_airports, strLongitude, ';');
                getline(columns_airports, continent, ';');
                getline(columns_airports, country_iso, ';');

                line = "";
                columns_airports.clear();
                UTM location = UTM(strLatitude, strLongitude);
                airports.push_back(Airport(std::stoi(id), iata, type, name, location, continent, country_iso));
            }
        }


        airports_stream.close();
        std::sort(airports.begin(), airports.end());

        std::cout << " Vector with airports initialized." << std::endl << " Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }

    std::ifstream airlines_stream;
    airlines_stream.open(airlines_file); //project folder
    if (airlines_stream.good()) {
        std::string id;
        std::string icao;
        std::string name;
        std::string country;
        std::string active;
        bool real_active;
        std::stringstream columns_airlines;
        std::string line;

        clock_t t_ini = clock();

        while (getline(airlines_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_airlines.str(line);


                getline(columns_airlines, id, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_airlines, icao, ';');
                getline(columns_airlines, name, ';');
                getline(columns_airlines, country, ';');
                getline(columns_airlines, active, ';');

                if (active == "Y")
                    real_active = true;
                else
                    real_active = false;

                line = "";
                columns_airlines.clear();

                Airline line_airline(std::stoul(id),icao,name,country,real_active);
                work.insert(std::pair<std::string,Airline>(icao,line_airline));

            }
        }

        airports_stream.close();

        std::cout << " Map with airports initialized." << std::endl << " Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }



    std::ifstream routes_stream;
    routes_stream.open(routes_file); //project folder
    if (routes_stream.good()) {
        std::string airline;
        std::string orig_airport;
        std::string dest_airport;
        std::stringstream columns_routes;
        std::string line;
        unsigned int counter = 0;


        clock_t t_ini = clock();

        while (getline(routes_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_routes.str(line);


                getline(columns_routes, airline, ';'); //we read till ';' and omit the caracter
                getline(columns_routes, orig_airport, ';');
                getline(columns_routes, dest_airport, ';');

                line = "";
                columns_routes.clear();

                //build the "key" objects to find them
                Airport orig = Airport(orig_airport);
                Airport dest = Airport(dest_airport);

                //search the airline needed to build the route
                Airline* realAirline = &work.find(airline)->second;

                //search the airports in the data base and build the route to push it after.
                auto real_orig = std::lower_bound(airports.begin(), airports.end(),orig);
                auto real_dest = std::lower_bound(airports.begin(), airports.end(), dest);
                //build the new route
                Route line_route(realAirline,&*real_orig,&*real_dest);
                //push the new route on the linkedList
                routes.push_back(line_route);
                //link recent route to his airline.
                realAirline->linkAirRoute(&routes.back());
                /*
                std::cout << counter << std::endl;
                counter++;
                 */
            }
        }

        airports_stream.close();

        std::cout << " List with airports initialized." << std::endl << " Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }

    loadFlights("..\\infovuelos_v1.csv");

}

Route& VuelaFlight::origDestRoutesSearch(const std::string& airportIataOrig, const std::string& airportIataDest) {
    std::list<Route>::iterator iterator = routes.begin();
    unsigned int count = 0;

    while(count < routes.size() and iterator != routes.end()){
        if (iterator->getOrigin()->getIata() == airportIataOrig and iterator->getDestination()->getIata() == airportIataDest){
            return *iterator;
        }
        iterator++;
        count++;
    }
    throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the airports given");
}

std::vector<Route> VuelaFlight::origRoutesSearch(std::string airportIataOrig) {
    std::list<Route>::iterator iterator = routes.begin();
    unsigned int count = 0;
    unsigned int found_count = 0;
    std::vector<Route> found_routes;
    while(count < routes.size() and iterator != routes.end()){
        if (iterator->getOrigin()->getIata() == airportIataOrig){
            found_routes.push_back(*iterator);
            found_count++;
        }
        iterator++;
        count++;
    }
    if(found_count == 0){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport given");
    }
    return found_routes;
}

std::vector<Airport> VuelaFlight::countryAirportSearch(std::string country) {
    std::list<Route>::iterator iterator = routes.begin();
    unsigned int count = 0;
    unsigned int found_count = 0;
    std::vector<Airport> found_airports;
    while(count < routes.size() and iterator != routes.end()){
        if (iterator->getOrigin()->getCountryIso() == country or iterator->getDestination()->getCountryIso() == country){
            Airport* airport_to_push = iterator->getOrigin();
            found_airports.push_back(*airport_to_push);
            found_count++;
        }
        iterator++;
        count++;
    }
    if(found_count == 0){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport given");
    }
    return found_airports;
}

void VuelaFlight::addNewRoute(std::string origAirportIata, std::string destAirportIata, std::string airline) {
    Airport orig_to_search(origAirportIata);
    Airport* orig = &*std::find(airports.begin(), airports.end(),orig_to_search);
    if (orig == nullptr){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport IATA given");
    }
    Airport dest_to_search(destAirportIata);
    Airport* dest = &*std::find(airports.begin(), airports.end(),dest_to_search);
    if (dest == nullptr){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the destination airport IATA given");
    }
    Airline auxAirline(airline);
    Route new_route(&work.find(auxAirline.getIcao())->second,orig,dest);
    routes.push_back(new_route);

}

const std::vector<Airport> &VuelaFlight::getAirports() const {
    return airports;
}

const std::list<Route> &VuelaFlight::getRoutes() const {
    return routes;
}

Airline& VuelaFlight::searchAirline(std::string airlineIcao) {
    Airline *result = &work.find(airlineIcao)->second;

    return *result;
}


std::vector<Airline> VuelaFlight::searchActiveAirline() {
    std::vector<Airline*> data;
    std::map<std::string,Airline>::iterator it;
    for (it = work.begin(); it != work.end(); it++){
        data.push_back(&it->second);
    }
    std::vector<Airline> result;
    for (unsigned int i=0; i < data.size();i++){
        if(data[i]->isActive())
            result.push_back(*data[i]);
    }
    return result;
}

bool VuelaFlight::flightRegister(std::string fNmber, std::string origAirpIata, std::string destAirpIata,
                                 std::string plane, std::string weatherData, Date f) {

    Airport orig(origAirpIata);
    Airport dest(destAirpIata);

    std::string fliIcao(fNmber.substr(0,3));

    Airline *company = &work[fliIcao];
    if (*company != Airline()){
        Flight flight(fNmber,
                      company,
                      &*std::lower_bound(airports.begin(), airports.end(),orig),
                      &*std::lower_bound(airports.begin(), airports.end(),dest),
                      plane,
                      weatherData,
                      f);

        if (&flight != company->addFlight(flight))
            return true;
        return false;
    }
    std::cout << "---ERROR--- in flightRegister(); The Airline: " << fliIcao << " found in flight " << fNmber << " does not exist." << std::endl;
    return false;
}

void VuelaFlight::loadFlights(std::string file) {
    std::ifstream flights_stream;

    flights_stream.open(file); //project folder
    if (flights_stream.good()) {
        std::string flightNumb;
        std::string orig_airport;
        std::string dest_airport;
        std::string plane;
        std::string weatherData;
        std::string day;
        std::string month;
        std::string year;
        std::stringstream columns_flights;
        std::string line;

        clock_t t_ini = clock();

        while (getline(flights_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_flights.str(line);

                //Line format: id;iata;type;size;fecha;country_iso

                getline(columns_flights, flightNumb, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_flights, orig_airport, ';');
                getline(columns_flights, dest_airport, ';');
                getline(columns_flights, plane, ';');
                getline(columns_flights, weatherData, ';');
                getline(columns_flights, day, '/');
                getline(columns_flights, month, '/');
                getline(columns_flights, year, ' ');

                line = "";
                columns_flights.clear();

                Date real_date(stoul(day),stoul(month),stoul(year));
                flightRegister(flightNumb,orig_airport,dest_airport,plane,weatherData,real_date);
                }

            }

        flights_stream.close();

        std::cout << " List with flights initialized." << std::endl << " Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }
}

std::vector<Flight> VuelaFlight::searchFlights(std::string fNumber) {
    std::string icao(fNumber.substr(0,3));
    return work.find(icao)->second.getFlights(fNumber);
}

std::vector<Flight> VuelaFlight::flightsOperatedBy(std::string icaoAirline, Date dat) {
    std::vector<Flight> result;
    Airline targetAirline = work.find(icaoAirline)->second;
    Date begin = dat, end = dat;
    begin.asignarDia(dat.verDia()-1,dat.verMes(),dat.verAnio());
    end.anadirDias(1);

    return targetAirline.getFlights(begin, end);
}

std::set<std::string> VuelaFlight::searchFlightsDestAirp(std::string origCountry, std::string iataDestAirp) {
    std::set<std::string> result;
    auto allAirpCountry = countryAirportSearch(origCountry);
    std::vector<Route> routesFound;

    for (unsigned int i = 0; i < allAirpCountry.size(); i++){
        routesFound.push_back(origDestRoutesSearch(allAirpCountry[i].getIata(),iataDestAirp));
    }
    for (unsigned int i = 0; i < routesFound.size(); i++){
        for(auto it = routesFound[i].getFlights().begin(); i < routesFound[i].getFlightsNum(); i++)
        result.insert(it.operator*()->getFlightNumb());
    }
}
