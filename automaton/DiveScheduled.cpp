#include "DiveScheduled.h"

size_t automaton::DiveScheduled::offsetS = 0;

void automaton::DiveScheduled::setup() {

}

void automaton::DiveScheduled::handler() {
   // Runs the connection handler to fetch any requests for canceling the dive.
   if(connection::ConnectionManager::hasMessage()) {
      ControlMessage* message = connection::ConnectionManager::getMessage();
      if(message != NULL && message->type == ControlMessage_MessageType_CANCEL_DIVE) {
         #if DEBUG
            const String cancelMessage PROGMEM = "Dive canceled.";
            Serial.println(cancelMessage);
         #endif
         SubmarineAutomaton::changeState(Status_StatusType_AVAILABLE);
         free(message);
         return;
      }
   }
   // If offset is over and the state was not changed, we are going to dive!
   if(millis() >= (SubmarineAutomaton::getStartingTimeOfCurrentStateMs() + (automaton::DiveScheduled::offsetS * 1000))) {
      SubmarineAutomaton::changeState(Status_StatusType_DIVING);
      #if DEBUG
         const String submeringMessage PROGMEM = "Going to dive now! Bye.";
         Serial.println(submeringMessage);
      #endif
   }
}

void automaton::DiveScheduled::setOffsetS(size_t offsetS) {
   automaton::DiveScheduled::offsetS = offsetS;
}
