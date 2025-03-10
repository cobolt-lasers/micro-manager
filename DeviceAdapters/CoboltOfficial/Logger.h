///////////////////////////////////////////////////////////////////////////////
// FILE:       Logger.h
// PROJECT:    MicroManager
// SUBSYSTEM:  DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:
// Cobolt Lasers Controller Adapter
//
// COPYRIGHT:     Cobolt AB, Stockholm, 2020
//                All rights reserved
//
// LICENSE:       MIT
//                Permission is hereby granted, free of charge, to any person obtaining a
//                copy of this software and associated documentation files( the "Software" ),
//                to deal in the Software without restriction, including without limitation the
//                rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//                sell copies of the Software, and to permit persons to whom the Software is
//                furnished to do so, subject to the following conditions:
//                
//                The above copyright notice and this permission notice shall be included in all
//                copies or substantial portions of the Software.
//
//                THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//                INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//                PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//                HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//                OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//                SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// CAUTION:       Use of controls or adjustments or performance of any procedures other than those
//                specified in owner's manual may result in exposure to hazardous radiation and
//                violation of the CE / CDRH laser safety compliance.
//
// AUTHORS:       Lukas Kalinski / lukas.kalinski@coboltlasers.com (2020)
//

#ifndef __COBOLT__LOGGER
#define __COBOLT__LOGGER

#include <string>

NAMESPACE_COBOLT_BEGIN

class Logger
{
public:

    class Gateway
    {
    public:

        virtual void SendLogMessage( const char* message, bool debug ) const = 0;
    };

    static Logger* Instance()
    {
        static Logger instance;
        return &instance;
    }

    void SetupWithGateway( const Gateway* gateway )
    {
        gateway_ = gateway;
    }
    
    virtual void LogMessage( const std::string& message, bool debug ) const
    {
        if ( gateway_ == NULL ) {
            return;
        }
        
        gateway_->SendLogMessage( message.c_str(), debug );
    }

    virtual void LogError( const std::string& message ) const
    {
        if ( gateway_ == NULL ) {
            return;
        }
        
        std::string taggedMessage = std::string( "ERROR: " );
        taggedMessage.append( message );

        gateway_->SendLogMessage( taggedMessage.c_str(), false );
    }

private:

    Logger() : gateway_( NULL ) {}

    const Gateway* gateway_;
};

NAMESPACE_COBOLT_END

#endif // #ifndef __COBOLT__LOGGER