#ifndef DIVING_H
#define DIVING_H

#include "Arduino.h"
#include "SubmarineAutomaton.h"
#include "../defines.h"
#include "../connection/ConnectionManager.h"
#include "../divingcell/DivingCellManager.h"
#include "../sensors/SensorManager.h"
#include "../sensors/Depth.h"

namespace automaton {
   class Diving {
   public:
      /**
       * Refreshs data structure and diving state.
       */
      static void setup();

      /**
       * Implements the functionality that takes place during the dive. Collects
       * data points every now and then. Additionally checks if the dive is over,
       * i.e. if the depth has reached ca. 0 again. Also controls the motor.
       */
      static void handler();

      /**
       * Sets the dive offset in seconds.
       * @param offset The offset in seconds.
       */
      static void setDepthM(size_t offsetS);

      /**
       * Gets the latest diving data, an array of size DATA_BUFFER_SIZE.
       * @return The latest diving data.
       */
      static Datum* getData();
   private:
      enum DivingStatus {SUBMERGING, EMERGING};
      static DivingStatus divingStatus;
      static size_t depthM;
      static size_t dataIndex;
      static Datum* data;

      /**
       * Fills the data set with empty stubs if we did not collect the maximum
       * amount of data.
       */
      static void fillData();

      /**
       * Returns true if we are done submerging (This is either calculated or
       * just simply done when the diving cell is fully opened).
       * @return True if the submarine has finished its submerging task.
       */
      static bool submergingDone();

      /**
       * Returns true if we are done emerging (This is either calculated or just
       * simply done when the diving cell is fully closed).
       * @return True if the submarine has finished its emerging task.
       */
      static bool emergingDone();

      /**
       * Returns true if a new data measurement intervall is reached dependent
       * on the depth of the submarine.
       */
      static bool newDataIntervalReached();
   };
}

#endif
