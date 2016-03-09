#include "Depth.h"

void sensors::depth::setup() {
   sensors::pressure::setup();
}

/**
 * Retrieves the current depth in meters from the pressure sensor.
 * @return The current depth, always positive, in meters.
 */
float sensors::depth::update() {
   // depth = (pressure - airpressure) / (fluid_density * gravity)
   return (sensors::pressure::update() - 1.13) * 9.95520159283225485316; // = pressure * 100000 / (1025 * 9.8)
}
