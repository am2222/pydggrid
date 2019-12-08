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
// DgIDGG.cpp: DgIDGG class implementation
//
// Version 7.0 - Kevin Sahr, 11/15/14
// Version 6.1 - Kevin Sahr, 5/23/13
//
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <climits>
#include <cfloat>

#include "DgIDGG.h"
#include "DgDmdD4Grid2DS.h"
#include "DgHexGrid2DS.h"
#include "DgTriGrid2DS.h"
//#include "DgSeriesConverter.h"
#include "DgRadixString.h"
#include "DgBoundedIDGG.h"
//#include "DgProjISEA.h"
//#include "DgProjFuller.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DgIDGG::DgIDGG (const DgIDGGSBase* dggs, const DgGeoSphRF& geoRF, const DgGeoCoord& vert0, 
       long double azDegs, unsigned int aperture, int res, const string& name,
       const string& gridTopo, const string& projType, bool isMixed43, 
       int numAp4, bool isSuperfund, int sfRes, bool isApSeq, const DgApSeq& apSeq,
       unsigned int precision)
   : DgIDGGBase (dggs, geoRF, aperture, res, name, precision),
     geoRF_(geoRF), vert0_(vert0), azDegs_(azDegs), gridTopo_(gridTopo), 
     projType_(projType), isApSeq_ (isApSeq), apSeq_ (apSeq), isMixed43_(isMixed43), 
     numAp4_(numAp4), isSuperfund_(isSuperfund), sfRes_ (sfRes)
{ 
   initialize();

} // DgIDGG::DgIDGG

////////////////////////////////////////////////////////////////////////////////
DgIDGG::DgIDGG (const DgIDGG& rfIn)
   : DgIDGGBase (NULL, rfIn.geoRF(), rfIn.aperture(), 
                 rfIn.res(), rfIn.name(), rfIn.precision()),
        geoRF_(rfIn.geoRF()), vert0_(rfIn.vert0()), 
        azDegs_(rfIn.azDegs()), gridTopo_(rfIn.gridTopo()), 
        projType_ (rfIn.projType()), isApSeq_ (rfIn.isApSeq()),
        apSeq_ (rfIn.apSeq()),
        isMixed43_(rfIn.isMixed43()), numAp4_(rfIn.numAp4()), 
        isSuperfund_(rfIn.isSuperfund()), sfRes_(rfIn.sfRes())
{ 
   initialize();

} // DgIDGG::DgIDGG

////////////////////////////////////////////////////////////////////////////////
void
DgIDGG::initialize (void)
{
   if (isApSeq())
      report("DgIDGG::initialize(): isApSeq must be false", DgBase::Fatal);

   // verify parameter validity

   string apErrStr = string("DgIDGG::initialize(): invalid aperture " + 
                         dgg::util::to_string(aperture()) + 
                         string(" for grid topo ") + gridTopo());

   if (gridTopo() == "HEXAGON")
   {
      if (aperture() != 3 && aperture() != 4 && aperture() != 7) 
         report(apErrStr, DgBase::Fatal);
   }
   else if (gridTopo() == "TRIANGLE" || gridTopo() == "DIAMOND")
   {
      if (aperture() != 4) report(apErrStr, DgBase::Fatal);
   }
   else
      report("DgIDGG::initialize(): invalid grid topo " + gridTopo(), 
             DgBase::Fatal);

   if (isMixed43())
      aperture_ = (res() > numAp4()) ? 3 : 4;

   // create some internal data structures

   undefLoc_ = makeLocation(undefAddress());
   sphIcosa_ = new DgSphIcosa(vert0(), azDegs());

   // setup some parameters

   isClassI_ = true; // default
   radix_ = (int) sqrtl((long double) aperture());
   allocRes_ = res();

   if (gridTopo() == "HEXAGON")
   {
      isAligned_ = true;
      isCongruent_ = false;

      if (!isMixed43())
      {
         if (aperture() == 4)
         {
            isClassI_ = true;
            maxD_ = (long long int) pow(2.0L, res()) - 1;
         }
         else if (aperture() == 3)
         {
            isClassI_ = !(res() % 2);
            if (!isClassI()) allocRes_ = res() + 1;
            maxD_ = (long long int) pow(3.0L, (allocRes() / 2)) - 1;
         }
         else // aperture 7
         {
            isClassI_ = true;
            //if (!isClassI()) allocRes_ = res() + 1;
            //maxD_ = (long long int) pow(3.0L, (allocRes() / 2)) - 1;
         }
      }
      else // mixed43
      {
         if (res() <= numAp4())
         {
            isClassI_ = true;
            maxD_ = (long long int) pow(2.0L, res()) - 1;
         }
         else
         {
            isClassI_ = !((res() - numAp4()) % 2);
            if (!isClassI()) allocRes_ = res() + 1;

            maxD_ = (long long int) (pow(2.0L, numAp4()) *
                      pow(3.0L, ((allocRes() - numAp4()) / 2))) - 1;
         }
         // cout << "MAXD: " << maxD_ << endl;
      }
      maxI_ = maxD();
      maxJ_ = maxD();
      mag_ = maxD() + 1;
      firstAdd_ = DgQ2DICoord(0, DgIVec2D(0, 0));
      lastAdd_ = DgQ2DICoord(11, DgIVec2D(0, 0));
   }
   else
   {
      maxD_ = (long long int) pow((long double) radix(), res()) - 1;
      maxI_ = maxD();
      maxJ_ = maxD();
      mag_ = maxD() + 1;
      if (gridTopo() == "TRIANGLE") 
      {
         isAligned_ = true; // only for aperture 4
         isCongruent_ = true;
         maxJ_ = (mag() * 2) - 1;
      }
      else // topo is DIAMOND
      {
         isAligned_ = false;
         isCongruent_ = true;
      }
      firstAdd_ = DgQ2DICoord(1, DgIVec2D(0, 0));
      lastAdd_ = DgQ2DICoord(10, DgIVec2D(maxI(), maxJ()));
   }

   // set-up local network to scale so that quad (and consequently tri) edge 
   // length is 1.0

   ccFrame_ = new DgContCartRF(locNet_, name() + "CC1");

   if (gridTopo() == "DIAMOND")
   {
      grid2DS_ = new DgDmdD4Grid2DS(locNet_, ccFrame(), res() + 1, aperture(), 
                                    isCongruent(), isAligned());
   }
   else if (gridTopo() == "HEXAGON")
   {
      grid2DS_ = new DgHexGrid2DS(locNet_, ccFrame(), allocRes() + 1, aperture(), 
        isCongruent(), isAligned(), "H2DS", isMixed43(), numAp4(), isSuperfund());
   }
   else if (gridTopo() == "TRIANGLE")
   {
      grid2DS_ = new DgTriGrid2DS(locNet_, ccFrame(), res() + 1, aperture(), 
                                  isCongruent(), isAligned());
   }

   createConverters();

   ///// calculate the statistics /////

   gridStats_.setPrecision(precision());
   gridStats_.setNCells(bndRF().size());

   long double tmpLen = DgGeoSphRF::icosaEdgeKM();
   if (gridTopo() == "TRIANGLE") tmpLen /= M_SQRT3;
   if (!isMixed43())
      gridStats_.setCellDistKM(tmpLen / pow(sqrtl((long double) aperture()), res()));
   else // mixed43
   {
      if (res() < numAp4())
      {
         tmpLen = tmpLen / pow((long double) 2.0, (long double) res());
      }
      else
      {
         tmpLen = tmpLen / pow((long double) 2.0, (long double) numAp4());
         if (res() > numAp4())
            tmpLen = tmpLen / pow(M_SQRT3, (long double) (res() - numAp4()));
      }
      gridStats_.setCellDistKM(tmpLen);
   }

   if (gridTopo() == "HEXAGON")
   {
      // a = globeArea / ((#cells - 12) + (12 * 5/6))
      //   = globeArea / (#cells - 2);
      gridStats_.setCellAreaKM(DgGeoSphRF::totalAreaKM() / 
                       (gridStats_.nCells() - 2));
   }
   else if (gridTopo() == "DIAMOND")
      gridStats_.setCellAreaKM(DgGeoSphRF::totalAreaKM() / gridStats_.nCells());
   else if (gridTopo() == "TRIANGLE")
      gridStats_.setCellAreaKM(DgGeoSphRF::totalAreaKM() / gridStats_.nCells());

   gridStats_.setCLS(2.0L * 2.0L * DgGeoSphRF::earthRadiusKM() * 
                     asinl(sqrtl(gridStats_.cellAreaKM() / M_PI) / 
                     (2.0L * DgGeoSphRF::earthRadiusKM())));

} // DgIDGG::initialize

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
