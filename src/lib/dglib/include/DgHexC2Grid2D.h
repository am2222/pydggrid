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
// DgHexC2Grid2D.h: DgHexC2Grid2D class definitions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGHEXC2GRID2D_H 
#define DGHEXC2GRID2D_H

#include <cmath>

#include "DgDiscRF2D.h"
#include "DgDVec2D.h"
#include "DgIVec2D.h"

class DgHexC1Grid2D;
class DgPolygon;

////////////////////////////////////////////////////////////////////////////////
class DgHexC2Grid2D : public DgDiscRF2D {

   public:

      DgHexC2Grid2D (DgRFNetwork& networkIn, 
                     const DgRF<DgDVec2D, long double>& ccFrameIn,
                     const string& nameIn = "HexC12D");

      DgHexC2Grid2D (const DgHexC2Grid2D& grd) : DgDiscRF2D (grd) {}

      DgHexC2Grid2D& operator= (const DgHexC2Grid2D& grd)
           { DgDiscRF2D::operator=(grd); return *this; }

      virtual long long int dist (const DgIVec2D& add1, const DgIVec2D& add2) const;

      const DgHexC1Grid2D& surrogate (void) const { return *surrogate_; }
      const DgHexC1Grid2D& substrate (void) const { return *substrate_; }

   protected:

      static const long double sin60_;

      DgHexC1Grid2D* surrogate_;
      DgHexC1Grid2D* substrate_;

      virtual void setAddVertices (const DgIVec2D& add, DgPolygon& vec) const;

      virtual void setAddNeighbors 
                                  (const DgIVec2D& add, DgLocVector& vec) const;

      virtual DgIVec2D quantify (const DgDVec2D& point) const;

      virtual DgDVec2D invQuantify (const DgIVec2D& add) const;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif
