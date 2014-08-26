// COPYRIGHT:     University of California, San Francisco, 2014,
//                All Rights reserved
//
// LICENSE:       This file is distributed under the "Lesser GPL" (LGPL) license.
//                License text is included with the source distribution.
//
//                This file is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty
//                of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//                IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//                INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES.
//
// AUTHOR:        Mark Tsuchida

#pragma once


namespace mm
{
namespace logging
{

namespace internal
{

template <
   typename TLoggerData,
   typename UEntryData,
   typename VStampData
>
struct GenericMetadata
{
   typedef TLoggerData LoggerDataType;
   typedef UEntryData EntryDataType;
   typedef VStampData StampDataType;

   LoggerDataType loggerData_;
   EntryDataType entryData_;
   StampDataType stampData_;

   GenericMetadata(LoggerDataType loggerData, EntryDataType entryData,
         StampDataType stampData) :
      loggerData_(loggerData),
      entryData_(entryData),
      stampData_(stampData)
   {}
};

} // namespace internal
} // namespace logging
} // namespace mm
