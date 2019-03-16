#include <pybind11/pybind11.h>
#include <iostream>
#include "dggrid/dglib.h"
int geo_to_seq(double in_lon_deg,double in_lat_deg,
                 string projection= "ISEA",int aperture=3,
                 string topology= "HEXAGON",
                 double azimuth_deg=0,
                 double res=10,
                 double pole_lon_deg=11.25,double pole_lat_deg=58.28252559) {

//    double in_lon_deg=35.36;
//    double in_lat_deg=40.36;


    dglib::Transformer dgt(pole_lon_deg, pole_lat_deg, azimuth_deg, aperture, res, topology, projection);
    auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
    uint64_t tout_seqnum;
    dgt.outSEQNUM(in, tout_seqnum);
    return tout_seqnum;

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
        -----------------------

        .. currentmodule:: pydggrid

        .. autosummary::
           :toctree: _generate

           geo_to_seq

    )pbdoc";

    m.def("geo_to_seq", &geo_to_seq, R"pbdoc(
        convert a lat lon point into seqnum
    )pbdoc",
     py::arg("in_lon_deg"), py::arg("in_lat_deg"),py::arg("projection")="ISEA", py::arg("aperture")=3,
     py::arg("topology")= "HEXAGON", py::arg("azimuth_deg")=0,py::arg("res")=10, py::arg("pole_lon_deg")=11.25,
     py::arg("pole_lat_deg")=58.28252559
    );

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
