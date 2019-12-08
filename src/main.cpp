#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
//#include <pybind11/complex.h>,
//#include <pybind11/functional.h>
//#include  <pybind11/chrono.h>
#include <iostream>

#include "DgParams.h"
#include "Transformer.h"


/*
 * parameters to save dggs structure
 */
DgParams dp;


/*
 * Construct a DGGS
 */
void dgconstruct(string projection = "ISEA", int aperture = 3,
                 string topology = "HEXAGON",
                 double azimuth_deg = 0,
                 double res = 10,
                 double pole_lon_deg = 11.25, double pole_lat_deg = 58.28252559) {

    std::cout << "** executing DGGRID version " << DGGRID_VERSION << " **\n";
    std::cout << "type sizes: big int: " << sizeof(long long int) * 8 << " bits / ";
    std::cout << "big double: " << sizeof(long double) * 8 << " bits\n";

    dp.aperture = aperture;
    dp.azimuth_deg = azimuth_deg;
    dp.pole_lat_deg = pole_lat_deg;
    dp.pole_lon_deg = pole_lon_deg;
    dp.projection = projection;
    dp.topology = topology;
    dp.res = res;


}

/*
 * Helper function to check if an item is in a vector or not
 */
bool in_array(const std::string &value, const std::vector<string> &array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}


/*
 * checks if DgParams are valid or not
 * FIXME: only topology is checked here
 */
bool isvalid() {
    std::vector<std::string> topologies{"HEXAGON", "DIAMOND", "TRIANGLE"};

    if (in_array(dp.topology, topologies)) {
        return true;
    } else {
        throw std::invalid_argument(
                "dgconstruct(): Topology must be set! call dgconstruct() first and configure DGGS parametes.");
    }
    return false;
}

/*
 * Convert a lat/long point into a sequence number
 */
uint64_t geo_to_seq(double in_lon_deg, double in_lat_deg) {

    if (!isvalid()) {
        dgconstruct();
    }

    Transformer dgt(dp);

    auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
    uint64_t out_seqnum;

    dgt.outSEQNUM(in, out_seqnum);
    return out_seqnum;

}

std::vector<long double> geo_to_projtri(double in_lon_deg,double in_lat_deg) {

    if(!isvalid()){
        dgconstruct();
    }


    Transformer dgt(dp);
    auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
    uint64_t tnum;
    long double  tx;
    long double  ty;

    dgt.outPROJTRI(in,tnum,tx,ty);

    std::vector<long double> values;
    values.push_back(tnum);
    values.push_back(tx);
    values.push_back(ty);
    return values;

}

std::vector<uint64_t> geo_to_q2di(double in_lon_deg,double in_lat_deg) {

    if(!isvalid()){
        dgconstruct();
    }


    Transformer dgt(dp);
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


    Transformer dgt(dp);
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

std::vector<long double> geo_to_geo(double in_lon_deg,double in_lat_deg) {

    if(!isvalid()){
        dgconstruct();
    }


    Transformer dgt(dp);
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


    if(!isvalid()){
        dgconstruct();
    }


    Transformer dgt(dp);
    auto in = dgt.inGEO(in_lon_deg, in_lat_deg);
    long double  px;
    long double  py;

    dgt.outGEO(in,px,py);
    std::vector<long double> values;
    values.push_back(py);
    values.push_back(py);
    return values;//py::cast(values);

}






namespace py = pybind11;

PYBIND11_MODULE(pydggrid, m) {
    m.doc() = R"pbdoc(
        DGGRID Python wrapper

        .. currentmodule:: pydggrid
        .. autosummary::
           :toctree: _generate
           dgconstruct
           geo_to_seq
           geo_to_q2di
           geo_to_q2dd
           geo_to_projtri
           geo_to_plane
           geo_to_geo

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