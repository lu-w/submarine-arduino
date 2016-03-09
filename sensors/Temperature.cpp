#include "Temperature.h"

void sensors::temperature::setup() {

}

float sensors::temperature::update() {
   // The temperature sensor handler.
   OneWire temperatureOneWire(TEMPERATURE_ONE_WIRE_BUS);
   // The sensor collection handler.
   DallasTemperature temperatureSensors(&temperatureOneWire);
   temperatureSensors.begin();
   temperatureSensors.requestTemperatures();
   return temperatureSensors.getTempCByIndex(0);
}
