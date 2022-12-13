/*!
 * @file i2c_diagnostics.cpp
 *
 * @mainpage Two-wire (I2C) Diagnostics Library
 *
 * @section intro_sec Introduction
 *
 * Provides utilities for diagnosing the I2C bus and devices on it.
 *
 * @section author Author
 *
 * Gerhard Malan, adapted from a sketch by Rui Santos on 
 * https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#2 
 *
 * @section license License
 *
 * This library is open-source under the BSD 3-Clause license and 
 * redistribution and use in source and binary forms, with or without 
 * modification, are permitted, provided that the license conditions are 
 * met.
 */

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

#include "i2c_diagnostics.h"


 /// @brief Poll all addresses on [i2c_wire] and populate a list of the addresses that respond.
 /// @param devices Array that will be populated with the addresses of the attached I2C devices.
 /// @param echo Prints the results of the device poll to the serial port if echo is true.
void TwoWireDiagnostics::devices(byte devices[], bool echo){
  // devices->clear();
  byte error, address;
  int nDevices;
  Serial.println("Scanning I2C bus");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    _i2c_wire.beginTransmission(address);
    error = _i2c_wire.endTransmission();
    String addressStr = getAddressString(address);  
    if (error == 0) {
      if (echo){
        Serial.println("Found I2C device at address " + addressStr);
      }
      devices[nDevices]=address;
      nDevices++;
    }
    else if (error==4) {
      if (echo){
        Serial.println("Unknow error at address " + addressStr);
      }
    }    
  }
  if (nDevices == 0) {
    if (echo){
      Serial.println("No I2C devices found\n");
    }
  }
  if (nDevices == 0) {
    Serial.println("No devices found on I2C bus");
  }
  if (nDevices == 1){ 
    Serial.println("Found one device on the I2C bus");
  }  
  if (nDevices > 1){ 
    Serial.println("Found " + String(nDevices) + " devices on the I2C bus");
  }
  
}

/// @brief  Abstract away platform differences in Arduino wire library
void TwoWireDiagnostics::write8(byte address, byte reg, byte value) {
  _i2c_wire.beginTransmission(address);
#if ARDUINO >= 100
  _i2c_wire.write((uint8_t)reg);
  _i2c_wire.write((uint8_t)value);
#else
  _i2c_wire.send(reg);
  _i2c_wire.send(value);
#endif
  _i2c_wire.endTransmission();
}

/// @brief  Abstract away platform differences in Arduino wire library
byte TwoWireDiagnostics::read8(byte address, byte reg) {
  byte value;

  _i2c_wire.beginTransmission(address);
#if ARDUINO >= 100
  _i2c_wire.write((uint8_t)reg);
#else
  _i2c_wire.send(reg);
#endif
  _i2c_wire.endTransmission();
  _i2c_wire.requestFrom(address, (byte)1);
#if ARDUINO >= 100
  value = _i2c_wire.read();
#else
  value = _i2c_wire.receive();
#endif
  _i2c_wire.endTransmission();

  return value;
}

// Returns an address string from the [address].
String TwoWireDiagnostics::getAddressString(byte address){
  // prefix with "0x"
  String addressStr = "0x";
      if (address<16) {
        // add "0" if less than 16
        addressStr = addressStr + "0";
      }
      // add the address and return the string
      return addressStr+String(address, HEX);
}

TwoWireDiagnostics::TwoWireDiagnostics(TwoWire &i2c_wire):_i2c_wire(i2c_wire){};