#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
#include "TinyWireM.h"
#define Wire TinyWireM
#else
#include <Wire.h>
#endif

#ifndef TWO_WIRE_DIAGNOSTICS_H_
#define TWO_WIRE_DIAGNOSTICS_H_
class TwoWireDiagnostics {
  public:

    /// @param i2c_wire the [TwoWire] instance to diagnose.      
    TwoWireDiagnostics(TwoWire &i2c_wire);

    /// @brief Poll all addresses on [i2c_wire] and populate a list of the addresses that respond.
    /// @param devices Array that will be populated with the addresses of the attached I2C devices.
    /// @param echo Prints the results of the device poll to the serial port if echo is true. Defaults to false.
    void devices(byte  devices[], bool echo = false); 

    /*! @brief Abstract away platform differences in Arduino wire library*/
    void write8(byte address, byte reg, byte value); 
     
    /*! @brief Abstract away platform differences in Arduino wire library*/
    byte read8(byte address, byte reg); 

    /// @brief Returns an address string from the [address].
    /// @param address The I2C address to stringify.
    /// @return An address string from the [address].
    String getAddressString(byte address);

  private:
    /// @brief The [TwoWire] instance to diagnose.    
    TwoWire &_i2c_wire;

  };

#endif // TWO_WIRE_DIAGNOSTICS_H_