// Wiring with ProMicro
// MISO -> 14
// MOSI -> 16
// SCK -> 15
// SS or CS -> 3 (you can change that, but you'll need to change it line 26 as well)
// Leonardo Pinout
// Use ICSP pins for MOSI, MISO and SCK
// SS or CS -> 3 (you can change that, but you'll need to change it line 26 as well)


#include <SPI.h>
#include <SD.h>

File myFile;
int fileDetected = 0;

#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme;
int bmeDetected = 0;

#define csvFileName "temps.csv"

// Timings
unsigned long currentMillis; // store current timer value
unsigned long tempFetchPeriod = 10000UL; // 10 seconds
unsigned long ledUpPeriod = 1000UL; // 1sec
unsigned long lastTempFetched;
unsigned long lastLedUpped;

// States
boolean ledUp = false;

void bmeSetup() {
  Serial.print("Initializing BME...");

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
  bme.parameter.pressureSeaLevel = 1015;

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

void sdSetup() {
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) { // change SS pin here in begin call
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // re-open the file for reading:
//  myFile = SD.open(csvFileName);
//  if (myFile) {
//    Serial.println(csvFileName);
//
//    // read from the file until there's nothing else in it:
//    // while (myFile.available()) {
//    //   Serial.write(myFile.read());
//    // }
//
//    Serial.println("File opened correctly");
//
    fileDetected = 1;
//
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.print("error opening");
//    Serial.println(csvFileName);
//  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  //}

  bmeSetup();
  sdSetup();

  Serial.println();
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  currentMillis = millis();

  if (ledUp && currentMillis - lastLedUpped >= ledUpPeriod) {
    digitalWrite(LED_BUILTIN, LOW);
    ledUp = false;
  }

  if (currentMillis - lastTempFetched >= tempFetchPeriod) {
    lastTempFetched = millis();
    if (bmeDetected && fileDetected) {
      digitalWrite(LED_BUILTIN, HIGH);
      ledUp = true;
      lastLedUpped = millis();

      Serial.print(F("Timer [ms]:\t\t\t\t"));
      Serial.println(lastTempFetched);
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

      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      myFile = SD.open(csvFileName, FILE_WRITE);

      // if the file opened okay, write to it:
      if (myFile) {
        Serial.print("Writing to CSV file...");
        myFile.print(lastTempFetched);
        myFile.print(",");
        myFile.print(bme.readTempC());
        myFile.print(",");
        myFile.print(bme.readHumidity());
        myFile.print(",");
        myFile.print(bme.readPressure());
        myFile.print(",");
        myFile.print(bme.readAltitudeMeter());
        myFile.println(",");

        // close the file:
        myFile.close();
        Serial.println("done.");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening CSV file");
      }

      Serial.println();
      Serial.println();
    }
  }
}
