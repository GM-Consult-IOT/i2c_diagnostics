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
  byte devices[9];

  // handshake with the serial port
  Serial.println("Starting scan of I2C bus"); 

  // scan for all the i2c devices on the bus, and echo the results to the serial port
  i2cdiags.devices(devices, true); 

}

void loop() {
  // do nothing, then do it again
  delay(2000); // wait a bit
}