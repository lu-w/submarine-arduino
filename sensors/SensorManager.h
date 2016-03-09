/**
 * Handles the sensor of the submarine. It contains a list of valid sensor types
 * which you need to edit for every new sensor you put into the submarine.
 * Other than that, you also need to adapt the number of sensors.
 * In the beginning, just add sensors with their corresponding callback methods
 * and after calling update(), you will find the sensor information in the
 * returned Datum struct.
 */
#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "Arduino.h"
#include "Time.h"
#include "../defines.h"
#include "../libraries/protocol/submarine.pb.h"

namespace sensors {
   // The type a sensor can have. Adapt this if needed.
   enum Type {TEMPERATURE, PRESSURE, DEPTH};

   namespace sensormanager {
      // Pointer to a setup handler function.
      typedef void (*SetupHandler)();

      // Pointer to an update handler function.
      typedef float (*UpdateHandler)();

      /**
       * Adds the sensor of the given type to the sensor list.
       * @param type The type of the sensor to add.
       * @param setupHandler The handler which is called during the intial setup.
       * @param updateHandler The handler which is called to retrieve the sensor's
       *                      data.
       */
      void add(Type type, SetupHandler const setup, UpdateHandler const update);

      /**
       * Sets the sensor up, i.e. calls their setup routine.
       */
      void setup();

      /**
       * Updates all the sensors and retrieves their current values. After that,
       * it returns the datum struct filled with the retrieved information.
       * @return The data of all sensors.
       */
      Datum update();

      // Stores the information for one sensor.
      struct Sensor {
         Type type;
         SetupHandler setup;
         UpdateHandler update;
      };
   };
}

#endif
