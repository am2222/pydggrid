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
// DgIDGGS43H.cpp: DgIDGGS43H class implementation
//
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "DgContCartRF.h"
#include "DgDiscRF.h"
#include "DgHexC1Grid2D.h"
#include "DgHexC2Grid2D.h"
#include "DgIDGGS43H.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DgIDGGS43H::DgIDGGS43H (const DgIDGGS43H& rf) 
  : DgIDGGS (rf)
{
   report("DgIDGGS43H::operator=() not implemented yet", DgBase::Fatal);

} // DgIDGGS43H::DgIDGGS43H

////////////////////////////////////////////////////////////////////////////////
DgIDGGS43H::~DgIDGGS43H (void)
{
   for (unsigned int i = 0; i < grids().size(); i++) 
    delete (*grids_)[i]; 

   delete grids_;

} // DgIDGGS43H::~DgIDGGS43H

////////////////////////////////////////////////////////////////////////////////
DgIDGGS43H&
DgIDGGS43H::operator= (const DgIDGGS43H& rf)
{
   report("DgIDGGS43H::operator=() not implemented", DgBase::Fatal);

   return *this;

} // DgIDGGS43H& DgIDGGS43H::operator=

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS43H::setAddParents (const DgResAdd<DgQ2DICoord>& add, 
                             DgLocVector& vec) const
{
   report("DgIDGGS43H::setAddParents()  not implemented yet", DgBase::Fatal);

} // void DgIDGGS43H::setAddParents

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS43H::setAddInteriorChildren (const DgResAdd<DgQ2DICoord>& add, 
                                        DgLocVector& vec) const
{
   report("DgIDGGS43H::setAddInteriorChildren() not implemented yet", 
          DgBase::Fatal);

} // void DgIDGGS43H::setAddInteriorChildren

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS43H::setAddBoundaryChildren (const DgResAdd<DgQ2DICoord>& add, 
                                        DgLocVector& vec) const
{
   report("DgIDGGS43H::setAddBoundaryChildren() not implemented yet", 
          DgBase::Fatal);

} // void DgIDGGS43H::setAddBoundaryChildren

////////////////////////////////////////////////////////////////////////////////
void 
DgIDGGS43H::setAddAllChildren (const DgResAdd<DgQ2DICoord>& add, 
                                   DgLocVector& vec) const
{
   report("DgIDGGS43H::setAddAllChildren() not implemented yet", DgBase::Fatal);

} // void DgIDGGS43H::setAddAllChildren

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
