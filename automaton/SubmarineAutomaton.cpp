#include "SubmarineAutomaton.h"

Status_StatusType automaton::SubmarineAutomaton::state = Status_StatusType_AVAILABLE;
unsigned long automaton::SubmarineAutomaton::timeSpentInPreviousStateS = 0;
unsigned long automaton::SubmarineAutomaton::startingTimeOfCurrentStateMs = millis();
size_t automaton::SubmarineAutomaton::numberOfStateHandlers = 0;
size_t automaton::SubmarineAutomaton::indexOfCurrentStateHandler = 0;
automaton::SubmarineAutomaton::StateAndHandler automaton::SubmarineAutomaton::stateHandlers[NUMBER_OF_STATES];

void automaton::SubmarineAutomaton::setup() {
   automaton::SubmarineAutomaton::state = Status_StatusType_AVAILABLE;
   automaton::SubmarineAutomaton::timeSpentInPreviousStateS = 0;
   automaton::SubmarineAutomaton::startingTimeOfCurrentStateMs = millis();
}

void automaton::SubmarineAutomaton::setStateHandler(Status_StatusType state, StateHandler const handler, SetupHandler const setup) {
   StateAndHandler stateAndHandler;
   stateAndHandler.state   = state;
   stateAndHandler.handler = handler;
   stateAndHandler.setup   = setup;
   automaton::SubmarineAutomaton::stateHandlers[numberOfStateHandlers] = stateAndHandler;
   automaton::SubmarineAutomaton::numberOfStateHandlers++;
}

void automaton::SubmarineAutomaton::changeState(Status_StatusType newState) {
   if(state != newState) {
      automaton::SubmarineAutomaton::state = newState;
      // Searches for correct handler for the current state and executes it.
      for(size_t i = 0; i < automaton::SubmarineAutomaton::numberOfStateHandlers; i++) {
         if(automaton::SubmarineAutomaton::stateHandlers[i].state == newState) {
            automaton::SubmarineAutomaton::indexOfCurrentStateHandler = i;
            automaton::SubmarineAutomaton::stateHandlers[i].setup();
            break;
         }
      }
      automaton::SubmarineAutomaton::timeSpentInPreviousStateS = (automaton::SubmarineAutomaton::startingTimeOfCurrentStateMs - millis()) / 1000;
      automaton::SubmarineAutomaton::startingTimeOfCurrentStateMs = millis();
      connection::ConnectionManager::sendMessage(SubmarineMessage_MessageType_STATUS);
      #if DEBUG
         const String stateMessage PROGMEM = "Changed state to ";
         Serial.print(stateMessage);
         Serial.println(newState);
      #endif
   }
}

void automaton::SubmarineAutomaton::run() {
   automaton::SubmarineAutomaton::stateHandlers[automaton::SubmarineAutomaton::indexOfCurrentStateHandler].handler();
}

Status_StatusType automaton::SubmarineAutomaton::getState() {
   return automaton::SubmarineAutomaton::state;
}

unsigned long automaton::SubmarineAutomaton::getTimeSpentInPreviousStateS() {
   return automaton::SubmarineAutomaton::timeSpentInPreviousStateS;
}

unsigned long automaton::SubmarineAutomaton::getStartingTimeOfCurrentStateMs() {
   return automaton::SubmarineAutomaton::startingTimeOfCurrentStateMs;
}
