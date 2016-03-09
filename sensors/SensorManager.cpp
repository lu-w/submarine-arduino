#include "SensorManager.h"

// Stores the list of all sensors.
sensors::sensormanager::Sensor sensorList[NUMBER_OF_SENSORS];

// Stores the number of added sensors.
size_t numberOfAddedSensors = 0;

void sensors::sensormanager::add(Type type, SetupHandler const setup, UpdateHandler const update) {
   sensors::sensormanager::Sensor sensor;
   sensor.type = type;
   sensor.setup = setup;
   sensor.update = update;
   sensorList[numberOfAddedSensors] = sensor;
   numberOfAddedSensors++;
}

void sensors::sensormanager::setup() {
   for(size_t i = 0; i < numberOfAddedSensors; i++) {
      sensorList[i].setup();
   }
}

Datum sensors::sensormanager::update() {
   Datum datum;
   datum.timestamp = now();
   for(size_t i = 0; i < numberOfAddedSensors; i++) {
      switch(sensorList[i].type) {
         case TEMPERATURE:
            datum.temperature = sensorList[i].update();
            break;
         case PRESSURE:
            datum.pressure = sensorList[i].update();
            break;
         case DEPTH:
            datum.depth = sensorList[i].update();
            break;
      }
   }
   #if DEBUG
      const String dataMessage PROGMEM = "Assembled data point as follows: ";
      const String tMessage PROGMEM = " deg. C, ";
      const String pMessage PROGMEM = " bar, ";
      const String dMessage PROGMEM = " meters.";
      Serial.print(dataMessage);
      Serial.print(datum.temperature);
      Serial.print(tMessage);
      Serial.print(datum.pressure);
      Serial.print(pMessage);
      Serial.print(datum.depth);
      Serial.println(dMessage);
   #endif
   return datum;
}
