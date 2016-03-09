#include "connection/ConnectionManager.h"
#include "divingcell/DivingCellManager.h"
#include "sensors/SensorManager.h"
#include "sensors/Temperature.h"
#include "sensors/Pressure.h"
#include "sensors/Depth.h"
#include "automaton/SubmarineAutomaton.h"
#include "automaton/Available.h"
#include "automaton/DiveScheduled.h"
#include "automaton/Diving.h"
#include "libraries/protocol/submarine.pb.h"
#if DEBUG
  #include "libraries/MemoryFree/MemoryFree.h"
#endif

#if DEBUG
  size_t prevFreeMemory = 0;
#endif

/**
 * Sets up the serial connection as well as the sensors and state machine.
 */
void setup () {
  // Serial port for debugging purposes.
  #if DEBUG
    Serial.begin(9600);
  #endif

  // Sets up the motor control for the diving cell.
  divingcell::DivingCellManager::setup();

  // Starts the connection over which we communicate.
  connection::ConnectionManager::setup();

  // Creates sensor handler and announce sensors and their handler functions.
  sensors::sensormanager::add(sensors::Type::TEMPERATURE, &(sensors::temperature::setup), &(sensors::temperature::update));
  sensors::sensormanager::add(sensors::Type::PRESSURE,    &(sensors::pressure::setup),    &(sensors::pressure::update));
  sensors::sensormanager::add(sensors::Type::DEPTH,       &(sensors::depth::setup),       &(sensors::depth::update));
  sensors::sensormanager::setup();

  // Sets up the state machine.
  automaton::SubmarineAutomaton::setStateHandler(Status_StatusType_AVAILABLE,      &(automaton::Available::handler),     &(automaton::Available::setup));
  automaton::SubmarineAutomaton::setStateHandler(Status_StatusType_DIVE_SCHEDULED, &(automaton::DiveScheduled::handler), &(automaton::DiveScheduled::setup));
  automaton::SubmarineAutomaton::setStateHandler(Status_StatusType_DIVING,         &(automaton::Diving::handler),        &(automaton::Diving::setup));
  automaton::SubmarineAutomaton::setup();
}

/**
 * Depending on the status of the submarine, we run a proper handler each loop
 * iteration.
 */
void loop () {
  #if DEBUG
    if(millis() % 5000 == 0 && prevFreeMemory != freeMemory()) {
      prevFreeMemory = freeMemory();
      Serial.print("Free memory: ");
      Serial.print(prevFreeMemory);
      Serial.println(" bytes.");
    }
  #endif
  automaton::SubmarineAutomaton::run();
}
