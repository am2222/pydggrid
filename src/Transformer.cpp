//
// Created by Majid on 12/7/2019.
//

#include "Transformer.h"
//#include "lib/DgIDGGBase.h"
//#include "lib/DgIDGGSBase.h"
//#include "lib/DgIDGG.h"
#include "lib/DgBoundedIDGG.h"
#include "lib/DgIDGG.h"

//#include "lib/DgInputStream.h"
//#include "lib/DgOutputStream.h"
//#include "lib/DgCell.h"
//#include "lib/DgOutAIGenFile.h"
Transformer::Transformer (const DgParams &dp) : GridThing(dp)  {}

Transformer::Transformer (
        long double  pole_lon_deg,
        long double  pole_lat_deg,
        long double  azimuth_deg,
        unsigned int aperture,
        int          res,
        std::string  topology,   //"HEXAGON", "DIAMOND", "TRIANGLE"
        std::string  projection  //ISEA/FULLER
) : GridThing(pole_lon_deg,pole_lat_deg,azimuth_deg,aperture,res,topology,projection) {}

std::shared_ptr<DgLocation> Transformer::inGEO    (long double lon_deg, long double lat_deg){
    const DgGeoCoord dgc(lon_deg,lat_deg);
    DgLocation *tloc = geoRF.makeLocation(dgc);
    return std::make_shared<DgLocation>(const_cast<const DgLocation &>(*tloc));
}

std::shared_ptr<DgLocation> Transformer::inPROJTRI(uint64_t tnum, long double x, long double y){
    const DgProjTriCoord dptc(tnum, DgDVec2D(x,y));
//    DgAddressBase *dab = new DgAddress<DgProjTriCoord>(dptc);
    return std::make_shared<DgLocation>(dgg.projTriRF());
}

std::shared_ptr<DgLocation> Transformer::inQ2DD   (uint64_t quad, long double x, long double y){
    const DgQ2DDCoord dgq(quad, DgDVec2D(x,y));
//    DgAddressBase *dab = new DgAddress<DgQ2DDCoord>(dgq);
    return std::make_shared<DgLocation>(dgg.q2ddRF());
//    delete dab;
}

std::shared_ptr<DgLocation> Transformer::inQ2DI   (uint64_t quad, long double i, long double j){
    const DgQ2DICoord dgq(quad, DgDVec2D(i,j));
//    DgAddressBase *dab = new DgAddress<DgQ2DICoord>(dgq);
    return std::make_shared<DgLocation>(dgg);
//    delete dab;
}

std::shared_ptr<DgLocation> Transformer::inSEQNUM (uint64_t seqnum){
    DgLocation *loc = static_cast<const DgIDGG&>(dgg).bndRF().locFromSeqNum(seqnum);
    return std::shared_ptr<DgLocation>(loc);
}

void Transformer::outGEO    (std::shared_ptr<DgLocation> loc, long double &lon_deg, long double &lat_deg){
    geoRF.convert(loc.get());
    const DgGeoCoord *add = geoRF.getAddress(*loc);
    lon_deg = add->lonDegs();
    lat_deg = add->latDegs();
}

void Transformer::outPROJTRI(std::shared_ptr<DgLocation> loc, uint64_t &tnum, long double &x, long double &y){
    dgg.projTriRF().convert(loc.get());
    const DgRFBase* pOutRF = &dgg.projTriRF();
    const DgProjTriCoord *add = static_cast<const DgRF<DgProjTriCoord, long double>*>(pOutRF)->getAddress(*loc);
    tnum = add->triNum();
    x    = add->coord().x();
    y    = add->coord().y();
}

void Transformer::outQ2DD   (std::shared_ptr<DgLocation> loc, uint64_t &quad, long double &x, long double &y){
    dgg.q2ddRF().convert(loc.get());
    const DgRFBase* pOutRF = &dgg.q2ddRF();
    const DgQ2DDCoord *add = static_cast<const DgRF<DgQ2DDCoord, long double>*>(pOutRF)->getAddress(*loc);
    quad = add->quadNum();
    x    = add->coord().x();
    y    = add->coord().y();
}

void Transformer::outPLANE  (std::shared_ptr<DgLocation> loc, long double &x, long double &y){
    dgg.planeRF().convert(loc.get());
    const DgRFBase* pOutRF = &dgg.planeRF();
    const DgDVec2D *add = static_cast<const DgRF<DgDVec2D, long double>*>(pOutRF)->getAddress(*loc);
    x = add->x();
    y = add->y();
}

void Transformer::outQ2DI   (std::shared_ptr<DgLocation> loc, uint64_t &quad, long double &i, long double &j){
    dgg.convert(loc.get());
    const DgRFBase* pOutRF = &dgg;
    const DgQ2DICoord *add = static_cast<const DgRF<DgQ2DICoord, long double>*>(pOutRF)->getAddress(*loc);
    quad = add->quadNum();
    i    = add->coord().i();
    j    = add->coord().j();
}

void Transformer::outSEQNUM (std::shared_ptr<DgLocation> loc, uint64_t &seqnum){
    dgg.convert(loc.get());
//    const_cast<DgRFBase&>(outRF).setPrecision(dp.precision);
    seqnum = dgg.bndRF().seqNum(*loc);
}
