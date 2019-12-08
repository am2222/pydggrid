//
// Created by Majid on 12/7/2019.
//

#include "GridThing.h"

GridThing::GridThing(long double pole_lon_deg, long double pole_lat_deg, long double azimuth_deg, unsigned int aperture,
                     int res, std::string topology, std::string projection) : DgGrid(pole_lon_deg, pole_lat_deg,
                             azimuth_deg, aperture,res, topology, projection),dgg(idggs->idggBase(res)){ }

GridThing::GridThing(const DgParams &dp) :DgGrid(dp),dgg(idggs->idggBase(dp.res)){ }


long double GridThing::cellAreaKM() const {
    return cellAreaKM(res);
}

double GridThing::nCells() const {
    return nCells(res);
}

double GridThing::cellDistKM() const {
    return cellAreaKM(res);
}

double GridThing::cls() const {
    return cls(res);
}

double GridThing::nCells(int res) const {
    const DgGridStats& gs = dgg.gridStats();
    return gs.nCells();
}

long double GridThing::cellAreaKM(int res) const {
    const DgGridStats& gs = dgg.gridStats();
    return gs.cellAreaKM();
}

double GridThing::cellDistKM(int res) const {
    const DgGridStats& gs = dgg.gridStats();
    return gs.cellDistKM();
}

double GridThing::cls(int res) const {
    const DgGridStats& gs = dgg.gridStats();
    return gs.cls();
}
