//
// Created by Majid on 12/7/2019.
//

#ifndef UNTITLED1_TRANSFORMER_H
#define UNTITLED1_TRANSFORMER_H

#include <iostream>
#include <memory>
#include "DgParams.h"
#include "lib/DgLocation.h"
#include "GridThing.h"

class Transformer: public GridThing {
public:
    Transformer (const DgParams &dp);

    Transformer (
            long double  pole_lon_deg,
            long double  pole_lat_deg,
            long double  azimuth_deg,
            unsigned int aperture,
            int          res,
            std::string  topology,   //"HEXAGON", "DIAMOND", "TRIANGLE"
            std::string  projection  //ISEA/FULLER
    );

    std::shared_ptr<DgLocation> inGEO    (long double lon_deg, long double lat_deg);
    std::shared_ptr<DgLocation> inPROJTRI(uint64_t tnum, long double x, long double y);
    std::shared_ptr<DgLocation> inQ2DD   (uint64_t quad, long double x, long double y);
    std::shared_ptr<DgLocation> inQ2DI   (uint64_t quad, long double i, long double j);
    std::shared_ptr<DgLocation> inSEQNUM (uint64_t seqnum);

    void outGEO    (std::shared_ptr<DgLocation> loc, long double &lon_deg, long double &lat_deg);
    void outPROJTRI(std::shared_ptr<DgLocation> loc, uint64_t &tnum, long double &x, long double &y);
    void outQ2DD   (std::shared_ptr<DgLocation> loc, uint64_t &quad, long double &x, long double &y);
    void outQ2DI   (std::shared_ptr<DgLocation> loc, uint64_t &quad, long double &i, long double &j);
    void outSEQNUM (std::shared_ptr<DgLocation> loc, uint64_t &seqnum);
    void outPLANE  (std::shared_ptr<DgLocation> loc, long double &x, long double &y);
};


#endif //UNTITLED1_TRANSFORMER_H
