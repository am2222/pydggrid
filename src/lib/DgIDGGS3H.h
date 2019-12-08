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
// DgIDGGS3H.h: DgIDGGS3H class definitions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGIDGGS3H_H 
#define DGIDGGS3H_H

#include "DgRF.h"
#include "DgLocVector.h"
#include "DgIDGGS.h"
#include "DgIVec2D.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class DgIDGGS3H : public DgIDGGS {

   public:

      DgIDGGS3H (DgRFNetwork& networkIn, const DgGeoSphRF& backFrameIn,
               const DgGeoCoord& vert0, long double azDegs, int nResIn = 1,
               const string& nameIn = "ISEA3H", const string& projType = "ISEA")
         : DgIDGGS (networkIn, backFrameIn, vert0, azDegs, 3, nResIn,
                "HEXAGON", nameIn, projType, false, 0, false) 
           { frequency_ = sqrtl(aperture()); }

      DgIDGGS3H (const DgIDGGS3H& rf);

     ~DgIDGGS3H (void);

      DgIDGGS3H& operator= (const DgIDGGS3H& rf);

      long double frequency (void) const { return frequency_; }

   protected:

      long double frequency_;

      // pure virtual functions from DgDiscRFS

      virtual void setAddParents (const DgResAdd<DgQ2DICoord>& add,
                                  DgLocVector& vec) const;

      virtual void setAddInteriorChildren (const DgResAdd<DgQ2DICoord>& add,
                                           DgLocVector& vec) const;

      virtual void setAddBoundaryChildren (const DgResAdd<DgQ2DICoord>& add,
                                           DgLocVector& vec) const;

      virtual void setAddAllChildren (const DgResAdd<DgQ2DICoord>& add,
                                      DgLocVector& vec) const;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif
