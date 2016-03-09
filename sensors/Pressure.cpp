#include "Pressure.h"

void sensors::pressure::setup() {

}

float sensors::pressure::update() {
   int sensorValue = analogRead(PRESSURE_PIN);
   return ((float)sensorValue / MAX_SENSOR_VALUE) * MAX_PRESSURE_BAR;
}
