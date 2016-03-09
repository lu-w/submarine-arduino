#ifndef DEPTH_H
#define DEPTH_H

#include "Pressure.h"

namespace sensors {
   namespace depth {
      void setup();
      /**
       * Returns the depth in meters.
       * @param The current depth in meters.
       */
      float update();
   }
}

#endif
