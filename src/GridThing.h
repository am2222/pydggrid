//
// Created by Majid on 12/7/2019.
//

#ifndef UNTITLED1_GRIDTHING_H
#define UNTITLED1_GRIDTHING_H


#include "lib/DgGeoSphRF.h"
#include "lib/DgIDGGSBase.h"
#include "DgParams.h"
#include "DgGrid.h"

class GridThing : public DgGrid  {
private:

protected:

public:

    GridThing (const DgParams &dp);
    GridThing (
            long double  pole_lon_deg,
            long double  pole_lat_deg,
            long double  azimuth_deg,
            unsigned int aperture,
            int          res,
            std::string  topology,   //"HEXAGON", "DIAMOND", "TRIANGLE"
            std::string  projection  //ISEA/FULLER
    );

    double nCells() const;
    long double cellAreaKM() const;
    double cellDistKM() const;
    double cls() const;
    double nCells(int res) const;
    long double cellAreaKM(int res) const;
    double cellDistKM(int res) const;
    double cls(int res) const;

    const DgIDGGBase &dgg;
};


#endif //UNTITLED1_GRIDTHING_H
