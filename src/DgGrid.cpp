//
// Created by Majid on 12/7/2019.
//

#include "DgGrid.h"

DgGrid::DgGrid(const DgParams &dp)  : geoRF(DgGeoSphRF(net0)),
                                      deg(geoRF, geoRF.name() + "Deg"){

    init(dp.pole_lon_deg,dp.pole_lat_deg,dp.azimuth_deg,dp.aperture,dp.res,dp.topology,dp.projection);
}

DgGrid::DgGrid(long double pole_lon_deg, long double pole_lat_deg, long double azimuth_deg, unsigned int aperture,
               int res, std::string topology, std::string projection) :
        geoRF(DgGeoSphRF(net0)),
        deg(geoRF, geoRF.name() + "Deg"){

    init(pole_lon_deg,pole_lat_deg,azimuth_deg,aperture,res,topology,projection);

}

void DgGrid::init(long double pole_lon_deg, long double pole_lat_deg, long double azimuth_deg, unsigned int aperture,
                  int res, std::string topology, std::string projection) {
    idggs = DgIDGGSBase::makeRF(net0, geoRF,
                                DgGeoCoord(pole_lon_deg, pole_lat_deg),
                                azimuth_deg, aperture, res+2, topology, "IDGGS",
                                projection, false, 0, false, false);
}
