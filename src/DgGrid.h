//
// Created by Majid on 12/7/2019.
//

#ifndef UNTITLED1_DGGRID_H
#define UNTITLED1_DGGRID_H


#include "lib/DgRFNetwork.h"
#include "lib/DgGeoSphRF.h"
#include "lib/DgIDGGSBase.h"
#include "DgParams.h"

class DgGrid {
private:

protected:
    DgRFNetwork   net0;
    DgGeoSphRF    geoRF;
    DgGeoSphDegRF deg;
public:
    int res;
    const DgIDGGSBase* idggs;
    DgGrid (const DgParams &dp);
    DgGrid (
            long double  pole_lon_deg,
            long double  pole_lat_deg,
            long double  azimuth_deg,
            unsigned int aperture,
            int          res,
            std::string  topology,   //"HEXAGON", "DIAMOND", "TRIANGLE"
            std::string  projection  //ISEA/FULLER
    );
    void init (
            long double  pole_lon_deg,
            long double  pole_lat_deg,
            long double  azimuth_deg,
            unsigned int aperture,
            int          res,
            std::string  topology,   //"HEXAGON", "DIAMOND", "TRIANGLE"
            std::string  projection  //ISEA/FULLER
    );
};


#endif //UNTITLED1_DGGRID_H
