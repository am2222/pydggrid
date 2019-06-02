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
// table.cpp: creates tables of grid statistics
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

#include <sstream>
#include "dggrid.h"
#include "../dglib/include/DgIDGGS.h"
#include "../dglib/include/DgString.h"

////////////////////////////////////////////////////////////////////////////////
void doTable (MainParam& dp, DgGridPList& plist)
{
   orientGrid(dp, plist);

   DgRFNetwork net0;
   DgGeoSphRF geoRF(net0, "GS0", dp.earthRadius);
   int numRes = dp.actualRes + 1;
   const DgIDGGS *idggs = DgIDGGS::makeRF(net0, geoRF, dp.vert0, 
          dp.azimuthDegs, dp.aperture, numRes, dp.gridTopo, "IDGGS", 
          dp.projType, dp.isMixed43, dp.numAp4, dp.isSuperfund);

   cout << "Earth Radius: " 
        << dgg::util::addCommas(geoRF.earthRadiusKM(), dp.precision)
        << "\n" << endl;

   string resS = "Res";
   string nCellsS = "# Cells";
   string areaS = "Area (km^2)";
   string spcS = "Spacing (km)";
   string clsS = "CLS (km)";

   const DgGridStats& gs0 = idggs->idgg(0).gridStats();
   const DgGridStats& gsR = idggs->idgg(numRes - 1).gridStats();
   int resWidth = resS.length();
   int nCellsWidth = max(dgg::util::addCommas(gsR.nCells()).length(), 
                         nCellsS.length()) + 1;
   int areaWidth = max(dgg::util::addCommas(gs0.cellAreaKM(), 
                         dp.precision).length(), areaS.length()) + 1;
   int spcWidth = max(dgg::util::addCommas(gs0.cellDistKM(), 
                         dp.precision).length(), spcS.length()) + 1;
   int clsWidth = max(dgg::util::addCommas(gs0.cls(), 
                         dp.precision).length(), clsS.length()) + 1;

   cout << setw(resWidth) << "Res" 
        << setw(nCellsWidth) << "# Cells" 
        << setw(areaWidth) << "Area (km^2)" 
        << setw(spcWidth) << "Spacing (km)" 
        << setw(clsWidth) << "CLS (km)" << endl;

   for (int r = 0; r < numRes; r++)
   {
      if (idggs->idgg(r).outputRes() >= 0) // in case invalid sf res
      {
         const DgGridStats& gs = idggs->idgg(r).gridStats();
         cout << setw(resWidth)  << idggs->idgg(r).outputRes()
           << setw(nCellsWidth) << dgg::util::addCommas(gs.nCells()) 
           << setw(areaWidth) << dgg::util::addCommas(gs.cellAreaKM(), 
                                                dp.precision) 
           << setw(spcWidth) << dgg::util::addCommas(gs.cellDistKM(), 
                                                dp.precision) 
           << setw(clsWidth) << dgg::util::addCommas(gs.cls(), 
                                                dp.precision) << endl;
      }
   }

   delete idggs;
}

