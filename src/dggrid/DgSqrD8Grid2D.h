////////////////////////////////////////////////////////////////////////////////
//
// DgSqrD8Grid2D.h: DgSqrD8Grid2D class definitions
//
// Version 6.1 - Kevin Sahr, 5/23/13
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGSQRGRIDD82D_H 
#define DGSQRGRIDD82D_H

#include <cstdint>

#include "DgSqrD4Grid2D.h"

////////////////////////////////////////////////////////////////////////////////
class DgSqrD8Grid2D : public DgSqrD4Grid2D {

   public:

      DgSqrD8Grid2D (DgRFNetwork& networkIn, 
                     const DgRF<DgDVec2D, long double>& contCartFrameIn,
                     const string& nameIn = "Sqr2D")
         : DgSqrD4Grid2D (networkIn, contCartFrameIn, nameIn) { }

      DgSqrD8Grid2D (const DgSqrD8Grid2D& grd) 
         : DgSqrD4Grid2D (grd) {}

      virtual std::int64_t dist (const DgIVec2D& add1, const DgIVec2D& add2) const
           { std::int64_t diffi = abs(add2.i() - add1.i());
             std::int64_t diffj = abs(add2.j() - add1.j());
             return (diffi >= diffj) ? diffi : diffj; }

   protected:

      virtual void setAddNeighbors (const DgIVec2D& add, DgLocVector& vec) 
                                                                        const;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif
