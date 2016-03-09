#ifndef DIVESCHEDULED_H
#define DIVESCHEDULED_H

#include <Time.h>
#include "Arduino.h"
#include "SubmarineAutomaton.h"
#include "Available.h"
#include "../connection/ConnectionManager.h"

namespace automaton {
   class DiveScheduled {
   public:
      static void setup();

      /**
       * Checks if the current time exceeds the given offset of the currently
       * scheduled dive. If so, we change the status of the submarine to diving and
       * perform the initial setup for the dive.
       */
      static void handler();

      /**
       * Sets the dive offset in seconds.
       * @param offset The offset in seconds.
       */
      static void setOffsetS(size_t offsetS);
   private:
      static size_t offsetS;
   };
}

#endif
