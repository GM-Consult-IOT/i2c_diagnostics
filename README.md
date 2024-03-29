# Two-wire (I2C) Diagnostics Library

Provides utilities for diagnosing the I2C bus and devices on it.

Currently provides only the `devices` function:

```C++
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h> 
// include the library
#include <i2c_diagnostics.h>

// run the diagnostics once on start
void setup() {

  // start serial port
  Serial.begin(115200); 

  // start the i2c comms  
  Wire.begin(); 

  // wait for serial port monitor to connect, needed for some processors
  // you can comment this out if your serial port monitor connects fast enough
  delay(2500); 

 // instantiate a new [TwoWireDiagnostics], passing the [TwoWire] you are diagnosing
 TwoWireDiagnostics i2cdiags = TwoWireDiagnostics(Wire);

  // The array that will be populated with the I2C addresses on the bus
  String devices[9];

  // handshake with the serial port
  Serial.println("Starting scan of I2C bus"); 

  // scan for all the i2c devices on the bus
  i2cdiags.devices(devices); 

  // loop through the devices
  for (byte i = 0; i<devices->length(); i++){
    String device = devices[i];
    if (device!=""){
      // display the address for each I2C device found
      Serial.println("I2C Device at: " + devices[i]);
    }
  }
}

void loop() {
  // do nothing, then do it again
  delay(2000); // wait a bit
}

```

This library is open-source under the [BSD 3-Clause license](https://github.com/GM-Consult-IOT/QMC6310_Unified/blob/master/LICENSE) and redistribution and use in source and binary forms, with or without modification, are permitted, provided that the license conditions are met. The I2C scan function was adapted from a sketch by [Rui Santos](https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#2). 