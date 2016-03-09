#include "Available.h"

void automaton::Available::setup() {

}

void automaton::Available::handler() {
   // Retrieve the message from the connection, otherwise skip everything.
   if(connection::ConnectionManager::hasMessage()) {
      // We handle the message content accordingly.
      ControlMessage* const message = connection::ConnectionManager::getMessage();
      if(message != NULL) {
         switch(message->type) {
            case ControlMessage_MessageType_DIVE:
            {
               #if DEBUG
                  const String diveMessage1 PROGMEM = "Got: DIVE - Offset = ";
                  const String diveMessage2 PROGMEM = " - Depth = ";
                  Serial.print(diveMessage1);
                  Serial.print(message->dive.offset_s);
                  Serial.print(diveMessage2);
                  Serial.println(message->dive.depth_m);
               #endif
               DiveScheduled::setOffsetS(message->dive.offset_s);
               Diving::setDepthM(message->dive.depth_m);
               SubmarineAutomaton::changeState(Status_StatusType_DIVE_SCHEDULED);
               break;
            }
            case ControlMessage_MessageType_CANCEL_DIVE:
            {
               // Ignore since we are in the wrong state to cancel a dive.
               #if DEBUG
                  const String cancelMessage PROGMEM = "Got: CANCEL_DIVE in state AVAILABLE - doing nothing";
                  Serial.println(cancelMessage);
               #endif
               break;
            }
            case ControlMessage_MessageType_STATUS_REQUEST:
            {
               #if DEBUG
                  const String dataRequestMessage PROGMEM = "Got: STATUS_REQUEST";
                  Serial.println(dataRequestMessage);
               #endif
               connection::ConnectionManager::sendMessage(SubmarineMessage_MessageType_STATUS);
               break;
            }
            case ControlMessage_MessageType_DATA_REQUEST:
            {
               #if DEBUG
                  const String dataRequestMessage PROGMEM = "Got: DATA_REQUEST";
                  Serial.println(dataRequestMessage);
               #endif
               connection::ConnectionManager::sendMessage(SubmarineMessage_MessageType_DATA);
               break;
               break;
            }
         }
      }
      free(message);
   }
}
