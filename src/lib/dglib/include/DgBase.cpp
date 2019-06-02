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
// DgBase.cpp: DgBase class implementation
//
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>

#include "DgBase.h"

////////////////////////////////////////////////////////////////////////////////

const string DgBase::defaultName = "UNDEFNAME";
DgBase::DgReportLevel DgBase::minReportLevel_ = DgBase::Info;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void report (const string& message, DgBase::DgReportLevel level)
//
// Global report function accessible to all objects, even if they are not
// derived from DgBase. If level is Info, the message is printed to stdout
// followed by a newline and flush. If level is Warning, "WARNING" is
// printed to stderr followed by the message, newline, and flush. If level
// is Fatal, "FATAL ERROR" is printed to stderr, followed by the message,
// newline, and flush, and then the program is exited. 
//
////////////////////////////////////////////////////////////////////////////////
{
   if (level < DgBase::minReportLevel()) return;

   switch (level)
   {
      case DgBase::Debug0:
	 cout << "DEBUG0: " << message << endl;
	 break;

      case DgBase::Debug1:
	 cout << "DEBUG1: " << message << endl;
	 break;

      case DgBase::Info:

         cout << message << endl;
         break;

      case DgBase::Warning:

         cout.flush();  // in case stdout and stderr go to the same place
         cerr << "WARNING: " << message << endl;
         break;

      case DgBase::Fatal:

         cout.flush();  // in case stdout and stderr go to the same place
         cerr << "FATAL ERROR: " << message << endl;
         exit(1);

      case DgBase::Silent:

         break;
   }

} // void report

////////////////////////////////////////////////////////////////////////////////
DgBase::~DgBase (void)
{ }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool
DgBase::testArgEqual (int argc, int expected, const string& message,
                      DgReportLevel level)
{
   if ((argc - 1) != expected)
   {
      ::report(message, level);
      return false;
   }
   else 
   {
      return true;
   }

} // bool DgBase::testArgEqual

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool
DgBase::testArgEqual (int argc, char* argv[], int expected, 
                      const string& message)
{
   if ((argc - 1) != expected)
   {
      string mess(string("usage: ") + string(argv[0]));

      if ((message.c_str())[0] != ' ') mess += " ";

      ::report(mess + message, DgBase::Fatal);

      return false;
   }
   else 
   {
      return true;
   }

} // bool DgBase::testArgEqual

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool
DgBase::testArgMin (int argc, int minExpected, const string& message,
                      DgReportLevel level)
{
   if ((argc - 1) < minExpected)
   {
      ::report(message, level);
      return false;
   }
   else 
   {
      return true;
   }

} // bool DgBase::testArgMin

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool
DgBase::testArgMin (int argc, char* argv[], int minExpected, 
                     const string& message)
{
   if ((argc - 1) < minExpected)
   {
      string mess(string("usage: ") + string(argv[0]));

      if ((message.c_str())[0] != ' ') mess += " ";

      ::report(mess + message, DgBase::Fatal);

      return false;
   }
   else 
   {
      return true;
   }

} // bool DgBase::testArgMin

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DgBase::DgBase (const string& instanceName)

   : instanceName_ (instanceName)

{
   debug("DgBase::constructor()");

} // DgBase::DgBase

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DgBase::DgBase (const string* instanceName)
{
   debug("DgBase::constructor()");

   if (instanceName)
      instanceName_ = *instanceName;
   else
      instanceName_ = defaultName;

} // DgBase::DgBase

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void
DgBase::report (const string& message, DgReportLevel level) const
//
// Call the global report function preceded with my instanceName.
//
////////////////////////////////////////////////////////////////////////////////
{
   ::report(string("[") + instanceName_ + string("] ") + message, level);

} // void DgBase::report

////////////////////////////////////////////////////////////////////////////////
