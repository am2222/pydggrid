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
// DgOutChildrenFile.h: DgOutChildrenFile class definitions
//
// Version 7.0 - Kevin Sahr, 12/14/14
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DGOUTCHILDREN_H
#define DGOUTCHILDREN_H

#include <string>
#include <fstream>

#include "DgUtil.h"
#include "DgOutputStream.h"
#include "DgOutLocFile.h"

using namespace std;

class DgIDGGBase;

////////////////////////////////////////////////////////////////////////////////
class DgOutChildrenFile : public DgOutputStream {

   public:

      DgOutChildrenFile (const string& fileName, 
                        const string& suffix = string("chd"), 
                        DgReportLevel failLevel = DgBase::Fatal);

      virtual DgOutChildrenFile& insert (const DgIDGGBase& dgg, 
                   const DgLocation& center, DgLocVector& vec);
};

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, const char* str)
              { ostream& o = file; o << str; return file; }

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, const string& str)
              { ostream& o = file; o << str; return file; }

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, long double val)
              { ostream& o = file; o << val; return file; }

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, float val)
              { ostream& o = file; o << val; return file; }

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, int val)
              { ostream& o = file; o << val; return file; }

inline DgOutChildrenFile& operator<< (DgOutChildrenFile& file, unsigned long long val)
              { ostream& o = file; o << val; return file; }

#endif
