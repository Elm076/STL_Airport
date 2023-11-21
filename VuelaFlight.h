//
// Created by fotop on 24/10/2023.
//

#ifndef PR1_CD_VUELAFLIGHT_H
#define PR1_CD_VUELAFLIGHT_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include "Airport.h"
#include "Route.h"
#include "Airline.h"
#include <set>

class VuelaFlight {
private:
    std::vector<Airport> airports;
    std::list<Route> routes;
    std::map<std::string,Airline> work;
public:
    VuelaFlight() = default;

    VuelaFlight(std::string airports_file, std::string routes_file, std::string airlines_file);

    const std::vector<Airport> &getAirports() const;

    const std::list<Route> &getRoutes() const;

    Route& origDestRoutesSearch(const std::string& airportIataOrig, const std::string& airportIataDest);

    std::vector<Route> origRoutesSearch(std::string airportIataOrig);

    std::vector<Airport> countryAirportSearch(std::string country);

    void addNewRoute(std::string origAirportIata, std::string destAirportIata, std::string airline);

    Airline& searchAirline(std::string airlineIcao);

    std::vector<Airline> searchActiveAirline();

    bool flightRegister(std::string fNmber, std::string origAirpIata, std::string destAirpIata, std::string plane, std::string weatherData, Date f);

    void loadFlights(std::string file);

    std::vector<Flight> searchFlights(std::string fNumber);

    std::vector<Flight> flightsOperatedBy(std::string icaoAirline, Date dat);

    std::set<std::string> searchFlightsDestAirp(std::string origCountry, std::string iataDestAirp);
};



#endif //PR1_CD_VUELAFLIGHT_H
