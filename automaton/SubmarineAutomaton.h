/**
 * Handles the state management of the submarine. For every state which is
 * defined in Status_StatusType, the user can add one handler function which is
 * -- If the automaton is in the given state -- called every time the run()
 * method of the automaton is called.
 * The user needs to adapt the number of states if necessary.
 */
#pragma once
#ifndef SUBMARINE_AUTOMATON_H
#define SUBMARINE_ATUOMATON_H

#include <Time.h>
#include "Arduino.h"
#include "../defines.h"
#include "../connection/ConnectionManager.h"
#include "../libraries/protocol/submarine.pb.h"

namespace automaton {
   class SubmarineAutomaton {
   public:
      typedef void (*StateHandler)();
      typedef void (*SetupHandler)();

      /**
       * Sets the automaton to the default state.
       */
      static void setup();

      /**
       * Sets the handler which is run when the automaton is in the given state.
       * This handler is run every time the run() method is called.
       * @param state The state for which to set the handler.
       * @param handler The function which is called on run().
       */
      static void setStateHandler(Status_StatusType state, StateHandler const handler, SetupHandler const setup);

      /**
       * Changes the state of the submarine. Runs the setup method of the new
       * state.
       * @param newState The new state of the submarine.
       */
      static void changeState(Status_StatusType newState);

      /**
       * Runs the automaton, i.e. does one execution of the handler function of the
       * current state.
       */
      static void run();

      /**
       * Returns the current state of the submarine.
       * @return The current state.
       */
      static Status_StatusType getState();

      /**
       * Returns the time spent in the previous state in seconds.
       */
      static unsigned long getTimeSpentInPreviousStateS();

       /**
        * Returns the starting time of the current state in ms.
        */
       static unsigned long getStartingTimeOfCurrentStateMs();
   private:
      // A struct used to identify the correct handler for each state.
      struct StateAndHandler {
         Status_StatusType state;
         StateHandler handler;
         SetupHandler setup;
      };
      // Stores the current state of the submarine.
      static Status_StatusType state;
      // How long the submarine spent in the previous state in seconds.
      static unsigned long timeSpentInPreviousStateS;
      // The starting time of the current state (output of millis()).
      static unsigned long startingTimeOfCurrentStateMs;
      // The number of state handlers added.
      static size_t numberOfStateHandlers;
      // The index of the state handler of the current state.
      static size_t indexOfCurrentStateHandler;
      // Stores the handlers for the states.
      static StateAndHandler stateHandlers[NUMBER_OF_STATES];
   };
}

#endif
