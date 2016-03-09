#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "../defines.h"
#include "../automaton/SubmarineAutomaton.h"
#include "../automaton/Available.h"
#include "../automaton/Diving.h"
#include "../sensors/SensorManager.h"
#include "../libraries/nanopb/pb_encode.h"
#include "../libraries/nanopb/pb_decode.h"
#include "../libraries/protocol/submarine.pb.h"

namespace connection {
   class ConnectionManager {
   public:
      /**
       * Initializes the connection and does basic setup steps. Call this method
       * before you call everything else.
       */
      static void setup();

      /**
       * Returns true if a message is in the buffer.
       * @return True if a message is present.
       */
      static bool hasMessage();

      /**
       * Returns a reference to the message if a message is available.
       * WARNING: This method _blocks_ until a message is present. So, if you
       * want nonblocking communication in your code, check message availability
       * with hasMessage() beforehand.
       * The user needs to free the memory after he processed the message!
       * @return A pointer to the read message from the control station.
       */
      static ControlMessage* const getMessage();

      /**
       * Sends the given message to the control station. It assembles the
       * content of the message automatically, i.e. fetches data from the
       * diving process / submarine state from the corresponding functions.
       * @param type The type of the message which is to send.
       */
      static void sendMessage(SubmarineMessage_MessageType type);
   private:
      /**
       * Assembles a data message which sends the array of collected data to the
       * control station. Warning: It allocates memory for the message which needs
       * to be free'd by the callee after the message was sent.
       * @param[out] buffer The message which was assembled.
       * @param[out] length The length of the message which was assembled.
       */
      static void const assembleDataMessage(byte* const buffer, size_t* const length);

      /**
       * Assembles a status update message which sends the array of collected data
       * to the control station. Warning: It allocates memory for the message which
       * needs to be free'd by the callee after the message was sent.
       * @param[out] buffer The message which was assembled.
       * @param[out] length The length of the message which was assembled.
       */
      static void const assembleStatusUpdateMessage(byte* const buffer, size_t* const length);

      // Used for the serial communication over bluetooth.
      static SoftwareSerial bluetoothSerial;
   };
}

#endif
