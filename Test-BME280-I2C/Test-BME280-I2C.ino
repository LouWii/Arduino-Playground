// Example based on BlueDot_BME280 example
// You will need the BlueDot_BME280 library to run this demo

#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme;
int bmeDetected = 0;

void setup() {
  Serial.begin(9600);

  // I2C communication
  bme.parameter.communication = 0;

  // I2C Address for Sensor
  bme.parameter.I2CAddress = 0x76;

  // Choose on which mode your device will run
  // Normal mode is the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  bme.parameter.sensorMode = 0b11;

  // Set up the internal IIR Filter
  // The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  // In short, a high factor value means less noise, but measurements are also less responsive
  // You can play with these values and check the results!
  // In doubt just leave on default

  //0b000:      factor 0 (filter off)
  //0b001:      factor 2
  //0b010:      factor 4
  //0b011:      factor 8
  //0b100:      factor 16 (default value)

  bme.parameter.IIRfilter = 0b100;

  // Define the oversampling factor for the humidity measurements
  // Again, higher values mean less noise, but slower responses
  // If you don't want to measure humidity, set the oversampling to zero

  //0b000:      factor 0 (Disable humidity measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)
  
  bme.parameter.humidOversampling = 0b101;

  // Define the oversampling factor for the temperature measurements
  // You know now, higher values lead to less noise but slower measurements
  
  //0b000:      factor 0 (Disable temperature measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

  bme.parameter.tempOversampling = 0b101;

  // Define the oversampling factor for the pressure measurements
  // For altitude measurements a higher factor provides more stable values
  // On doubt, just leave it on default
  
  //0b000:      factor 0 (Disable pressure measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

  bme.parameter.pressOversampling = 0b101;

  // For precise altitude measurements please put in the current pressure corrected for the sea level
  // On doubt, just leave the standard pressure as default (1013.25 hPa);
  
  bme.parameter.pressureSeaLevel = 1013.25;

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C and 59°F);
  
  bme.parameter.tempOutsideCelsius = 15;
  // bme.parameter.tempOutsideFahrenheit = 59;

  if (bme.init() != 0x60) {
    Serial.println(F("BME not detected"));
    bmeDetected = 0;
  } else {
    Serial.println(F("BME detected"));
    bmeDetected = 1;
  }
}

void loop() {
  if (bmeDetected) {
    Serial.print(F("Temperature Sensor [°C]:\t\t"));
    Serial.println(bme.readTempC());
    //Serial.print(F("Temperature Sensor [°F]:\t\t"));
    //Serial.println(bme.readTempF());
    Serial.print(F("Humidity Sensor [%]:\t\t\t"));
    Serial.println(bme.readHumidity());
    Serial.print(F("Pressure Sensor [hPa]:\t\t\t"));
    Serial.println(bme.readPressure());
    Serial.print(F("Altitude Sensor [m]:\t\t\t"));
    Serial.println(bme.readAltitudeMeter());
    //Serial.print(F("Altitude Sensor [ft]:\t\t\t"));
    //Serial.println(bme.readAltitudeFeet());

    Serial.println();
    Serial.println();

    delay(1000);
  }
}
