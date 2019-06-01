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
// DgIDGGS3H.cpp: DgIDGGS3H class implementation
//
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "DgContCartRF.h"
#include "DgDiscRF.h"
#include "DgHexC1Grid2D.h"
#include "DgHexC2Grid2D.h"
#include "DgIDGGS3H.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DgIDGGS3H::DgIDGGS3H (const DgIDGGS3H& rf) 
  : DgIDGGS (rf)
{
   report("DgIDGGS3H::operator=() not implemented yet", DgBase::Fatal);

} // DgIDGGS3H::DgIDGGS3H

////////////////////////////////////////////////////////////////////////////////
DgIDGGS3H::~DgIDGGS3H (void)
{
   for (unsigned long i = 0; i < grids().size(); i++) 
    delete (*grids_)[i]; 

   delete grids_;

} // DgIDGGS3H::~DgIDGGS3H

////////////////////////////////////////////////////////////////////////////////
DgIDGGS3H&
DgIDGGS3H::operator= (const DgIDGGS3H& rf)
{
   report("DgIDGGS3H::operator=() not implemented", DgBase::Fatal);

   return *this;

} // DgIDGGS3H& DgIDGGS3H::operator=

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS3H::setAddParents (const DgResAdd<DgQ2DICoord>& add, 
                             DgLocVector& vec) const
{
   DgPolygon verts;
   DgLocation* tmpLoc = grids()[add.res()]->makeLocation(add.address());
   grids()[add.res()]->setVertices(*tmpLoc, verts);
   delete tmpLoc;

   // vertices lie in parents

   grids()[add.res() - 1]->convert(verts);

   for (int i = 0; i < verts.size(); i++)
   {
      // check if already present

      bool found = false;
      for (int j = 0; j < vec.size(); j++)
      {
         if (vec[j] == verts[i])
         {
            found = true;
            break;
         }
      }

      if (!found) vec.push_back(verts[i]);
   }

} // void DgIDGGS3H::setAddParents

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS3H::setAddInteriorChildren (const DgResAdd<DgQ2DICoord>& add, 
                                        DgLocVector& vec) const
{
   DgLocVector verts;
   DgLocation* tmpLoc = grids()[add.res()]->makeLocation(add.address());
   grids()[add.res() + 1]->convert(tmpLoc);
   vec.push_back(*tmpLoc);

   delete tmpLoc;

} // void DgIDGGS3H::setAddInteriorChildren

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS3H::setAddBoundaryChildren (const DgResAdd<DgQ2DICoord>& add, 
                                        DgLocVector& vec) const
{
   DgPolygon verts;
   DgLocation* tmpLoc = grids()[add.res()]->makeLocation(add.address());
   grids()[add.res()]->setVertices(*tmpLoc, verts);
   delete tmpLoc;

   // vertices lie in children

   grids()[add.res() + 1]->convert(verts);

   for (int i = 0; i < verts.size(); i++)
   {
      // check if already present

      bool found = false;
      for (int j = 0; j < vec.size(); j++)
      {
         if (vec[j] == verts[i])
         {
            found = true;
            break;
         }
      }

      if (!found) vec.push_back(verts[i]);
   }

} // void DgIDGGS3H::setAddBoundaryChildren

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS3H::setAddAllChildren (const DgResAdd<DgQ2DICoord>& add, 
                                   DgLocVector& vec) const
{
   setAddInteriorChildren(add, vec);

   DgLocVector bndVec(vec.rf());
   setAddBoundaryChildren(add, bndVec);

   for (int i = 0; i < bndVec.size(); i++) vec.push_back(bndVec[i]);

} // void DgIDGGS3H::setAddAllChildren

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
