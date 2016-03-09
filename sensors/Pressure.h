#ifndef PRESSURE_H
#define PRESSURE_H

#include "../defines.h"
#include "Arduino.h"

namespace sensors {
   namespace pressure {
      void setup();
      /**
       * Returns the pressure in bar.
       * @param The current pressure in bar.
       */
      float update();
   }
}

#endif
