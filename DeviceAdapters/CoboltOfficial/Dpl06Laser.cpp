///////////////////////////////////////////////////////////////////////////////
// FILE:       Dpl06Laser.cpp
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
// AUTHORS:       Lukas Kalinski / lukas.kalinski@coboltlasers.com (2025)
//

#include <assert.h>
#include "Dpl06Laser.h"
#include "Logger.h"

#include "LaserDriver.h"
#include "LaserStateProperty.h"
#include "EnumerationProperty.h"
#include "NoShutterCommandLegacyFix.h"

using namespace std;
using namespace cobolt;

Dpl06Laser::Dpl06Laser( const std::string& wavelength, LaserDriver* driver ) :
    Laser( "06-DPL (12V)", driver )
{
    currentUnit_ = Milliamperes;
    powerUnit_ = Milliwatts;

    CreateNameProperty();
    CreateModelProperty();
    CreateSerialNumberProperty();
    CreateFirmwareVersionProperty();
    CreateAdapterVersionProperty();
    CreateOperatingHoursProperty();
    CreateWavelengthProperty( wavelength );

    CreateKeyswitchProperty();
    CreateLaserStateProperty();
    //CreateLaserOnOffProperty();
    CreateShutterProperty();
    CreateRunModeProperty();
    CreatePowerSetpointProperty();
    CreatePowerReadingProperty();
    CreateCurrentSetpointProperty();
    CreateCurrentReadingProperty();
    CreateDigitalModulationProperty();
    CreateAnalogModulationFlagProperty();

    CreateModulationCurrentHighSetpointProperty();
    CreateModulationCurrentLowSetpointProperty();
}

void Dpl06Laser::CreateLaserStateProperty()
{
    if ( IsInCdrhMode() ) {

        laserStateProperty_ = new LaserStateProperty( Property::String, "Dpl06Laser State", laserDriver_, "gom?");

        laserStateProperty_->RegisterState("0", "Off", false);
        laserStateProperty_->RegisterState("1", "Waiting for TEC", false);
        laserStateProperty_->RegisterState("2", "Waiting for Key", false);
        laserStateProperty_->RegisterState("3", "Warming Up", false);
        laserStateProperty_->RegisterState("4", "Completed", true);
        laserStateProperty_->RegisterState("5", "Fault", false);
        laserStateProperty_->RegisterState("6", "Aborted", false);
        laserStateProperty_->RegisterState("7", "Modulation", false);

    } else {
        
        laserStateProperty_ = new LaserStateProperty( Property::String, "Dpl06Laser State", laserDriver_, "l?" );
        
        laserStateProperty_->RegisterState( "0", "Off", true );
        laserStateProperty_->RegisterState( "1", "On", true );
    }
    
    RegisterPublicProperty( laserStateProperty_ );
}

void Dpl06Laser::CreateRunModeProperty()
{
    EnumerationProperty* property;
    
    property = new EnumerationProperty( "Run Mode", laserDriver_, "gam?" );
    
    property->SetCaching( false );

    property->RegisterEnumerationItem( "0", "ecc", EnumerationItem_RunMode_ConstantCurrent );
    property->RegisterEnumerationItem( "1", "ecp", EnumerationItem_RunMode_ConstantPower );
    property->RegisterEnumerationItem( "2", "em", EnumerationItem_RunMode_Modulation );
    
    RegisterPublicProperty( property );
}
