#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
//#include <pybind11/complex.h>,
//#include <pybind11/functional.h>
//#include  <pybind11/chrono.h>
#include <iostream>
#include "lib/dglib.h"
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>


#include "boost/geometry/extensions/gis/io/wkb/read_wkb.hpp"
#include "boost/geometry/extensions/gis/io/wkb/utility.hpp"
#include "boost/geometry/extensions/gis/io/wkb/write_wkb.hpp"



//parameters to save dggs structure
dglib::DgParams params;

namespace bg = boost::geometry;
BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
bool in_array(const std::string &value, const std::vector<string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

//checks if params are valid or not
//FIXME: only topology is checked here
bool isvalid(){
    std::vector<std::string> topologies {"HEXAGON", "DIAMOND","TRIANGLE"};

    if (in_array(params.topology, topologies)) {
        return true;
    }
   else{
        throw std::invalid_argument("dgconstruct(): Topology must be set! call dgconstruct() first and configure DGGS parametes.");
    }
    return false;
}

void dgconstruct(string projection= "ISEA",int aperture=3,
                 string topology= "HEXAGON",
                 double azimuth_deg=0,
                 double res=10,
                 double pole_lon_deg=11.25,double pole_lat_deg=58.28252559){
//    dgt.~Transformer(); // destruct

    params.aperture=aperture;
    params.azimuth_deg=azimuth_deg;
    params.pole_lat_deg=pole_lat_deg;
    params.pole_lon_deg=pole_lon_deg;
    params.projection=projection;
    params.topology=topology;
    params.res=res;
    //new(&dgt) dglib::Transformer(pole_lon_deg, pole_lat_deg, azimuth_deg, aperture, res, topology, projection); // reconstruct

}

uint64_t geo_to_seq(double in_lon_deg,double in_lat_deg) {

//    double in_lon_deg=35.36;
//    double in_lat_deg=40.36;


//    dglib::Transformer dgt(pole_lon_deg, pole_lat_deg, azimuth_deg, aperture, res, topology, projection);
    if(!isvalid()){
        dgconstruct();
    }

    dglib::Transformer dgt(params);
    auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
    uint64_t tout_seqnum;
    dgt.outSEQNUM(in, tout_seqnum);
    return tout_seqnum;

}

std::vector<uint64_t> geo_to_q2di(double in_lon_deg,double in_lat_deg) {

if(!isvalid()){
        dgconstruct();
    }


        dglib::Transformer dgt(params);
        auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
        uint64_t quad;
        long double  i;
        long double  j;

        dgt.outQ2DI(in,quad,i,j);

        std::vector<uint64_t> values;
        values.push_back(quad);
        values.push_back(i);
        values.push_back(j);
        return values;//py::cast(values);

}


std::vector<long double> geo_to_q2dd(double in_lon_deg,double in_lat_deg) {

        if(!isvalid()){
            dgconstruct();
        }


        dglib::Transformer dgt(params);
        auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
        uint64_t quad;
        long double  qx;
        long double  qy;

        dgt.outQ2DD(in,quad,qx,qy);

        std::vector<long double> values;
        values.push_back(quad);
        values.push_back(qx);
        values.push_back(qy);
        return values;//py::cast(values);



}


std::vector<long double> geo_to_projtri(double in_lon_deg,double in_lat_deg) {

        if(!isvalid()){
            dgconstruct();
        }


        dglib::Transformer dgt(params);
        auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
        uint64_t tnum;
        long double  tx;
        long double  ty;

        dgt.outPROJTRI(in,tnum,tx,ty);

        std::vector<long double> values;
        values.push_back(tnum);
        values.push_back(tx);
        values.push_back(ty);
        return values;//py::cast(values);

}

std::vector<long double> geo_to_geo(double in_lon_deg,double in_lat_deg) {

        if(!isvalid()){
            dgconstruct();
        }


        dglib::Transformer dgt(params);
        auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
        long double  lon_deg;
        long double  let_deg;

        dgt.outGEO(in,lon_deg,let_deg);

        std::vector<long double> values;
        values.push_back(lon_deg);
        values.push_back(let_deg);
        return values;//py::cast(values);

}




std::vector<long double> geo_to_plane(double in_lon_deg,double in_lat_deg) {



    typedef bg::model::point<float, 2,bg::cs::cartesian> point;
    typedef bg::model::polygon<point, false,false> polygon;

    polygon p;
    p.outer().push_back(point(1,1));
    p.outer().push_back(point(1,2));
    p.outer().push_back(point(2,2));

    std::cout<< bg::wkt<polygon>(p)<<std::endl;


    std::string wkb_out;
    bg::write_wkb(p, std::back_inserter(wkb_out));

    std::cout<<wkb_out;
    std::string hex_out;
    bg::wkb2hex(wkb_out.begin(), wkb_out.end(), hex_out) ;

    boost::algorithm::to_lower(hex_out);
    std::cout<<hex_out;


        if(!isvalid()){
            dgconstruct();
        }


        dglib::Transformer dgt(params);
        auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
        long double  px;
        long double  py;

        dgt.outGEO(in,px,py);
        std::vector<long double> values;
        values.push_back(py);
        values.push_back(py);
        return values;//py::cast(values);

}


//
//
//#' @name dgconstruct
//#'
//#' @title      Construct a discrete global grid system (dggs) object
//#'
//#' @description
//#'             Construct a discrete global grid system (dggs) object
//#'
//#' @param projection Type of grid to use. Options are: ISEA and FULLER.
//#'                   Default: ISEA3H
//#'
//#' @param topology   Shape of cell. Options are: HEXAGON, DIAMOND, TRIANGLE.
//#'                   Default: HEXAGON
//#'
//#' @param aperture   How finely subsequent resolution levels divide the grid.
//#'                   Options are: 3, 4. Not all options work with all
//#'                   projections and topologies.
//#'                   Default: 3
//#'
//#' @param res  Resolution. Must be in the range [0,30]. Larger values represent
//#'             finer resolutions. Appropriate resolutions can be found with
//#'             dg_closest_res_to_area(), dg_closest_res_to_spacing(), and
//#'             dg_closest_res_to_cls(). Default is 9, which corresponds to a
//#'             cell area of ~2600 sq km and a cell spacing of ~50 km.
//#'             Only one of res, area, length, or cls should be used.
//#'
//#' @param precision Round output to this number of decimal places. Must be in
//#'                  the range [0,30]. Default: 7.
//#'
//#' @param area      The desired area of the grid's cells.
//#'                  Only one of res, area, length, or cls should be used.
//#'
//#' @param spacing   The desired spacing between the center of adjacent cells.
//#'                  Only one of res, area, length, or cls should be used.
//#'
//#' @param cls       The desired CLS of the cells.
//#'                  Only one of res, area, length, or cls should be used.
//#'
//#' @param resround  What direction to search in. Must be nearest, up, or down.
//#'
//#' @param show_info Print the area, spacing, and CLS of the chosen resolution.
//#'
//#' @param metric    Whether input and output should be in metric (TRUE) or
//#'                  imperial (FALSE)
//#'
//#' @param azimuth_deg   Rotation in degrees of grid about its pole, value in [0,360].
//#'                      Default=0.
//#'
//#' @param pole_lat_deg  Latitude in degrees of the pole, value in [-90,90].
//#'                      Default=58.28252559.
//#'
//#' @param pole_lon_deg  Longitude in degrees of the pole, value in [-180,180].
//#'                      Default=11.25.
//#'
//#' @return          Returns a dggs object which can be passed to other dggridR
//#'                  functions
//#'
//#' @examples
//#' \dontrun{
//#' library(dggridR)
//#' dggs <- dgconstruct(res=20)
//#'
//#' dggs <- dgconstruct(area=5,metric=FALSE)
//#' }
//#' @export
//
//bool dgconstruct(string projection,int aperture,String topology,int precision,double area,
//                    double spacing,double cls,string resround,bool metric,bool show_info,double azimuth_deg,
//                    double pole_lon_deg,double pole_lat_deg){
//
//
//}
//
//dgconstruct <- function(
//  projection   = 'ISEA',
//  aperture     = 3,
//  topology     = 'HEXAGON',
//  res          = NA,
//  precision    = 7,
//  area         = NA,
//  spacing      = NA,
//  cls          = NA,
//  resround     = 'nearest',
//  metric       = TRUE,
//  show_info    = TRUE,
//  azimuth_deg  = 0,
//  pole_lat_deg = 58.28252559,
//  pole_lon_deg = 11.25
//){
//  if(sum(!is.na(c(res,area,spacing,cls)))!=1)
//    stop('dgconstruct(): Only one of res, area, length, or cls can have a value!')
//
//  #Use a dummy resolution, we'll fix it in a moment
//  dggs <- list(
//    pole_lon_deg = pole_lon_deg,
//    pole_lat_deg = pole_lat_deg,
//    azimuth_deg  = azimuth_deg,
//    aperture     = aperture,
//    res          = 1,
//    topology     = topology,
//    projection   = projection,
//    precision    = precision
//  )
//
//  if(!is.na(res))
//    dggs[['res']] = res
//  else if(!is.na(area))
//    dggs[['res']] = dg_closest_res_to_area   (dggs,area=area,      round=resround,metric=metric,show_info=TRUE)
//  else if(!is.na(spacing))
//    dggs[['res']] = dg_closest_res_to_spacing(dggs,spacing=spacing,round=resround,metric=metric,show_info=TRUE)
//  else if(!is.na(cls))
//    dggs[['res']] = dg_closest_res_to_cls    (dggs,cls=cls,        round=resround,metric=metric,show_info=TRUE)
//  else
//    stop('dgconstruct(): Logic itself has failed us.')
//
//  dgverify(dggs)
//
//  dggs
//}







namespace py = pybind11;

PYBIND11_MODULE(pydggrid, m) {
    m.doc() = R"pbdoc(
        DGGRID Python3 wrapper

        .. currentmodule:: pydggrid
        .. autosummary::
           :toctree: _generate
           dgconstruct
           geo_to_q2di
           geo_to_q2dd
           geo_to_projtri
    )pbdoc";

    m.def("geo_to_seq", &geo_to_seq, R"pbdoc(
        convert a lat lon point into seqnum
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));
    m.def("geo_to_q2di", &geo_to_q2di, R"pbdoc(
        convert a lat lon point into q2di; returns an array with following structure quad,i,j
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));

    m.def("geo_to_q2dd", &geo_to_q2dd, R"pbdoc(
        convert a lat lon point into q2dd; returns an array with following structure [quad,qx,qy]
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));


    m.def("geo_to_projtri", &geo_to_projtri, R"pbdoc(
        convert a lat lon point into projtri; returns an array with following structure [qnum,tx,ty]
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));

    m.def("geo_to_geo", &geo_to_geo, R"pbdoc(
        convert a lat lon point into GEO; returns an array with following structure [lon_deg,lat_deg]
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));

    m.def("geo_to_plane", &geo_to_plane, R"pbdoc(
        convert a lat lon point into PLANE; returns an array with following structure [px,py]
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"));


    m.def("dgconstruct", &dgconstruct, R"pbdoc(
        reinitialize gdds object
    )pbdoc",
     py::arg("projection")="ISEA", py::arg("aperture")=3,
     py::arg("topology")= "HEXAGON", py::arg("azimuth_deg")=0,py::arg("res")=10, py::arg("pole_lon_deg")=11.25,
     py::arg("pole_lat_deg")=58.28252559
    );


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
