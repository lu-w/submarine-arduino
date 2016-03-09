#ifndef AVAILABLE_H
#define AVAILABLE_H

#include <SoftwareSerial.h>
#include "Arduino.h"
#include "SubmarineAutomaton.h"
#include "DiveScheduled.h"
#include "Diving.h"
#include "../defines.h"
#include "../connection/ConnectionManager.h"
#include "../libraries/nanopb/pb_encode.h"
#include "../libraries/nanopb/pb_decode.h"
#include "../libraries/protocol/submarine.pb.h"

namespace automaton {
   class Available {
   public:
      /**
       * Sets up the bluetooth communication.
       */
      static void setup();

      /**
       * Handles the message receiving part. It checks if characters are in the
       * bluetooth serial buffer and reads them if so. It then passes the parsed
       * message to the message handler which implements the interpretation.
       */
      static void handler();
   };
}

#endif
