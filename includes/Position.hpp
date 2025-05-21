#ifndef POSITION_HPP
#define POSITION_HPP

class Position {

public:
double latitude;
double longitude;
    Position(double lat = 0.0, double lon = 0.0);
    double getLatitude() const;
    double getLongitude() const;
    double distanceTo(const Position& other) const;
};

#endif
