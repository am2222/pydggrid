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
// DgHexGrid2DS.h: DgHexGrid2DS class definitions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGHEXGRID2DS_H 
#define DGHEXGRID2DS_H 

#include "DgRF.h"
#include "DgLocVector.h"
#include "DgDiscRFS2D.h"
#include "DgIVec2D.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class DgHexGrid2DS : public DgDiscRFS2D {

   public:

      DgHexGrid2DS (DgRFNetwork& network, 
                 const DgRF<DgDVec2D, long double>& backFrame,
                 int nRes = 1, unsigned int aperture = 4, 
                 bool isCongruent = true, bool isAligned = false,
                 const string& name = "6H4", bool isMixed43 = false,
                 int numAp4 = 0, bool isSuperfund = false);

      DgHexGrid2DS (const DgHexGrid2DS& rf);

     ~DgHexGrid2DS (void);

      DgHexGrid2DS& operator= (const DgHexGrid2DS& rf);

      long double frequency     (void) const { return frequency_; }
      bool     isMixed43     (void) const { return isMixed43_; }
      int      numAp4        (void) const { return numAp4_; }
      bool     isSuperfund   (void) const { return isSuperfund_; }

   protected:

      long double frequency_;

      // pure virtual functions from DgDiscRFS

      virtual void setAddParents (const DgResAdd<DgIVec2D>& add,
                                  DgLocVector& vec) const;

      virtual void setAddInteriorChildren (const DgResAdd<DgIVec2D>& add,
                                           DgLocVector& vec) const;

      virtual void setAddBoundaryChildren (const DgResAdd<DgIVec2D>& add,
                                           DgLocVector& vec) const;

      virtual void setAddAllChildren (const DgResAdd<DgIVec2D>& add,
                                      DgLocVector& vec) const;

   private:

      bool isMixed43_;
      int  numAp4_;
      bool isSuperfund_;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif
