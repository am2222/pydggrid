/*******************************************************************************
    Copyright (C) 2018 Kevin Sahr

    This file is part of DGGRID.

    DGGRID is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DGGRID is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
//
// DgGeoSphRF.h: DgGeoSphRF class definitions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGGEOSPHRF_H 
#define DGGEOSPHRF_H

#include "DgEllipsoidRF.h"
#include "DgContCartRF.h"
#if _MSC_VER 
#define _USE_MATH_DEFINES
#include <math.h>
#endif
////////////////////////////////////////////////////////////////////////////////
class DgGeoSphRF : public DgEllipsoidRF {

   public:

      DgGeoSphRF (DgRFNetwork& networkIn, const string& nameIn = "GeodeticSph",
                  long double earthRadiusKMin = DEFAULT_RADIUS_KM)
         : DgEllipsoidRF (networkIn, nameIn, earthRadiusKMin * 1000L,
                earthRadiusKMin * 1000L) 
           { 
              earthRadiusKM_ = earthRadiusKMin; 
              icosaEdgeRads_ = M_ATAN2;
              icosaEdgeDegs_ = icosaEdgeRads_ * M_180_PI;
              icosaEdgeKM_ = icosaEdgeRads_ * earthRadiusKM_;
              totalAreaKM_ = 4.0L * M_PI * earthRadiusKM_ * earthRadiusKM_;
           }

      DgGeoSphRF (const DgGeoSphRF& rf) 
         : DgEllipsoidRF(rf) { /* earthRadius_ = rf.earthRadius(); */ }

      DgGeoSphRF& operator= (const DgGeoSphRF& rf)
         { DgEllipsoidRF::operator=(rf); 
           return *this; }

      // distance in km
      virtual long double dist (const DgGeoCoord& add1, const DgGeoCoord& add2) const
         { return earthRadiusKM() * DgGeoCoord::gcDist(add1, add2); }

      static long double earthRadiusKM (void) { return earthRadiusKM_; } 
      static long double icosaEdgeKM   (void) { return icosaEdgeKM_; } 
      static long double icosaEdgeDegs (void) { return icosaEdgeDegs_; } 
      static long double icosaEdgeRads (void) { return icosaEdgeRads_; } 
      static long double totalAreaKM   (void) { return totalAreaKM_; } 

      // midpoint of great circle connecting two points
      static DgGeoCoord midPoint(const DgGeoCoord& p1, const DgGeoCoord& p2);

      // azimuth from pt1 to pt2
      static long double azimuth(const DgGeoCoord& p1, const DgGeoCoord& p2,
                            bool returnRads = true);

      // point that is distance (rads) from p0 along azimuth (rads)
      static DgGeoCoord travelGC (const DgGeoCoord& p0, long double distance,
                                  long double azimuth, bool inputRads = true);

      // densify polygon in geodetic coordinates
      static void densify (DgPolygon& p, long double maxDist, bool rads = true);

   private:

      static long double earthRadiusKM_;  // earth radius in km
      static long double icosaEdgeKM_;    // spherical icosahedron edge length
      static long double icosaEdgeDegs_;  // spherical icosahedron edge length
      static long double icosaEdgeRads_;  // spherical icosahedron edge length
      static long double totalAreaKM_;    // spherical icosahedron edge length
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class DgGeoSphDegRF : public DgContCartRF {

   public:

      DgGeoSphDegRF (const DgGeoSphRF& geoRFin, 
                     const string& nameIn = "GeodeticSphDeg");

      const DgGeoSphRF& geoRF (void) const { return geoRF_; }

   protected:

      const DgGeoSphRF& geoRF_;
};

#endif
