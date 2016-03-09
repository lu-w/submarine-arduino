#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "../defines.h"
#include <OneWire.h>
#include <DallasTemperature.h>

namespace sensors {
   namespace temperature {
      void setup();
      /**
       * Returns the temperature in degree Celcius.
       * @return The temperature in °C.
       */
      float update();
   }
}

#endif
