#include "Position.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846  
#endif

Position::Position(double lat, double lon) : latitude(lat), longitude(lon) {}

double Position::getLatitude() const {
    return latitude;
}

double Position::getLongitude() const {
    return longitude;
}

// Calculate the distance to another position 

double Position::distanceTo(const Position& other) const {
    const double earthRadiusKm = 6371.0;
    double dLat = (other.latitude - latitude) * M_PI / 180.0;
    double dLon = (other.longitude - longitude) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(latitude * M_PI / 180.0) * cos(other.latitude * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRadiusKm * c;
}
