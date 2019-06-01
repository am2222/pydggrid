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
// DgBoundedIDGG.h: DgBoundedIDGG class definitions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGBOUNDEDIDGG_H 
#define DGBOUNDEDIDGG_H

#include "DgIDGG.h"
#include "DgGeoSphRF.h"
#include "DgBoundedRF.h"

using namespace std;

class DgBoundedRF2D;

////////////////////////////////////////////////////////////////////////////////
class DgBoundedIDGG : public DgBoundedRF<DgQ2DICoord, DgGeoCoord, long double> {

   public:

      DgBoundedIDGG (const DgIDGG& IDGGin);

      virtual DgQ2DICoord& incrementAddress (DgQ2DICoord& add) const;
      virtual DgQ2DICoord& decrementAddress (DgQ2DICoord& add) const;

      virtual bool validAddress (const DgQ2DICoord& add) const;

      const DgQ2DICoord& invalidAdd (void) const
                         { return idgg().undefAddress(); }

      const DgIDGG& idgg (void) const { return IDGG_; }

      unsigned long long int offsetPerQuad (void) const { return offsetPerQuad_; }

      virtual unsigned long long int seqNumAddress (const DgQ2DICoord& add) const;

      virtual DgQ2DICoord addFromSeqNum (unsigned long long int sNum) const;

   protected:

      const DgBoundedRF2D& bnd2D (void) const { return *bnd2D_; }

   private:

      const DgIDGG& IDGG_;
      DgBoundedRF2D* bnd2D_;
      unsigned long long int offsetPerQuad_;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
