//
// Created by Majid on 12/7/2019.
//

#ifndef UNTITLED1_DGPARAMS_H
#define UNTITLED1_DGPARAMS_H


#include <string>

class DgParams {
public:
    long double  pole_lon_deg;
    long double  pole_lat_deg;
    long double  azimuth_deg;
    unsigned int aperture;
    int          res;
    std::string  topology = "cheese";    //"HEXAGON", "DIAMOND", "TRIANGLE"
    std::string  projection;  //ISEA/FULLER
};


#endif //UNTITLED1_DGPARAMS_H
