////////////////////////////////////////////////////////////////////////////////
//
// DgConverterBase.cpp: DgConverterBase class implementation
//
// Version 6.1 - Kevin Sahr, 5/23/13
//
////////////////////////////////////////////////////////////////////////////////

#include "DgBase.h"
#include "DgString.h"
#include "DgConverterBase.h"

bool DgConverterBase::isTraceOn_ = false;
//ostream* DgConverterBase::traceStream_ = &cout;

////////////////////////////////////////////////////////////////////////////////
DgConverterBase::~DgConverterBase (void)
{ 
   // virtual destructor 

} // DgConverterBase::~DgConverterBase

////////////////////////////////////////////////////////////////////////////////
DgConverterBase::DgConverterBase (const DgRFBase& fromFrame, 
                                  const DgRFBase& toFrame,
                                  bool userGeneratedIn)
    : fromFrame_ (const_cast<DgRFBase*>(&fromFrame)), 
      toFrame_ (const_cast<DgRFBase*>(&toFrame)),
      userGenerated_ (userGeneratedIn)
{
   // check for network match

   if (fromFrame.network() != toFrame.network())
   {
      report("DgConverterBase::DgConverterBase() from/to network mismatch",
             DgBase::Fatal);
      return;
   }

   if (userGenerated())
   {
      // override any existing converter

      if (fromFrame.network_->existsConverter(fromFrame, toFrame))
      {
         delete const_cast<DgRFNetwork*>(fromFrame.network_)
                           ->matrix_[fromFrame.id()][toFrame.id()];
      }

      // if we're here we're neither a passthrough nor an identity converter
      
      const_cast<DgRFNetwork*>(fromFrame.network_)
                           ->matrix_[fromFrame.id()][toFrame.id()] = this;

      // make any connections this gives us; note we are indirectly changing
      // the const frames here
      
      if (fromFrame_->id() != 0 && fromFrame_->connectTo() == 0 &&
          toFrame_->connectTo()) 
      {
         fromFrame_->connectTo_ = toFrame_; 
      }

      if (toFrame_->id() != 0 && toFrame_->connectFrom() == 0 &&
          fromFrame_->connectFrom()) 
      {
         toFrame_->connectFrom_ = fromFrame_;
      }
   }

} // DgConverterBase::DgConverterBase

////////////////////////////////////////////////////////////////////////////////
DgConverterBase&
DgConverterBase::operator= (const DgConverterBase& con)
{
   fromFrame_ = &const_cast<DgRFBase&>(con.fromFrame());
   toFrame_ = &const_cast<DgRFBase&>(con.toFrame());
   userGenerated_ = con.userGenerated();

   return *this;

} // DgConverterBase& DgConverterBase::operator=

////////////////////////////////////////////////////////////////////////////////
void
DgConverterBase::forceConnectFrom (bool verify) const
{
   if (verify && !fromFrame_->connectFrom())
   {
      report("DgConverter::forceConnectFrom() dangling connection",
              DgBase::Fatal);
   }

   toFrame_->connectFrom_ = fromFrame_;

   const_cast<DgRFNetwork&>(fromFrame_->network()).matrix_
                                    [fromFrame_->id()][toFrame_->id()] 
                                          = const_cast<DgConverterBase*>(this);

} // void DgConverterBase::forceConnectFrom

////////////////////////////////////////////////////////////////////////////////
void
DgConverterBase::forceConnectTo (bool verify) const
{
   if (!toFrame_->connectTo())
   {
      report("DgConverter::forceConnectTo() dangling connection",
              DgBase::Fatal);
   }

   fromFrame_->connectTo_ = toFrame_;

   const_cast<DgRFNetwork&>(fromFrame_->network()).matrix_
                                    [fromFrame_->id()][toFrame_->id()] 
                                          = const_cast<DgConverterBase*>(this);

} // void DgConverterBase::forceConnectTo

////////////////////////////////////////////////////////////////////////////////
DgLocation* 
DgConverterBase::convert (DgLocation* loc) const
{
   // verify grid

   if (loc->rf() != fromFrame())
   {
      report("DgConverter::convert(" + loc->asString() + ") frame " + 
             loc->rf().name() + " does not match fromFrame " + 
             fromFrame().name(), DgBase::Fatal);

      return loc;
   }

   //if (isTraceOn()) traceStream() << *loc;
   
   loc->rf_ = &toFrame();

   DgAddressBase* tmpAdd = createConvertedAddress(*loc->address());
   delete loc->address_;
   loc->address_ = tmpAdd;

   //if (isTraceOn()) traceStream() << "->" << *loc << endl;
  
   return loc;

} // DgLocation* DgConverterBase::convert

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

