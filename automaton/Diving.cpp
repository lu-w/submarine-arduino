#include "DiveScheduled.h"

automaton::Diving::DivingStatus automaton::Diving::divingStatus = SUBMERGING;
size_t automaton::Diving::depthM = 0;
size_t automaton::Diving::dataIndex = 0;
Datum* automaton::Diving::data = (Datum*)malloc(sizeof(Datum) * DATA_BUFFER_SIZE);

void automaton::Diving::setup() {
   free(data);
   automaton::Diving::divingStatus = SUBMERGING;
   automaton::Diving::dataIndex = 0;
   automaton::Diving::data = (Datum*)malloc(sizeof(Datum) * DATA_BUFFER_SIZE);
   divingcell::DivingCellManager::setSleep(false);
   divingcell::DivingCellManager::setDirection(divingcell::OPEN);
}

void automaton::Diving::handler() {
   // Moves the syringe one step.
   divingcell::DivingCellManager::move();

  // Retrieves data if this is possible.
   if(automaton::Diving::dataIndex < DATA_BUFFER_SIZE && newDataIntervalReached()) {
      automaton::Diving::data[automaton::Diving::dataIndex] = sensors::sensormanager::update();
      automaton::Diving::dataIndex++;
   }

   // Checks if we need to emerge or end the dive.
   if(submergingDone()) {
      divingcell::DivingCellManager::setDirection(divingcell::CLOSE);
      automaton::Diving::divingStatus = EMERGING;
      #if DEBUG
         const String emergingMessage PROGMEM = "Done. Emerging... ";
         Serial.println(emergingMessage);
      #endif
   } else if(emergingDone()) {
      automaton::Diving::fillData();
      divingcell::DivingCellManager::setDirection(divingcell::OPEN);
      divingcell::DivingCellManager::setSleep(true);
      SubmarineAutomaton::changeState(Status_StatusType_AVAILABLE);
      #if DEBUG
         const String doneMessage PROGMEM = "Done.";
         Serial.println(doneMessage);
      #endif
   }
}

void automaton::Diving::setDepthM(size_t depthM) {
   automaton::Diving::depthM = depthM;
}

Datum* automaton::Diving::getData() {
   return automaton::Diving::data;
}

void automaton::Diving::fillData() {
   for(size_t i = automaton::Diving::dataIndex; i < DATA_BUFFER_SIZE; i++) {
      Datum emptyDatum = {now(), 0, 0, 0};
      automaton::Diving::data[i] = emptyDatum;
   }
}

bool automaton::Diving::submergingDone() {
   if(automaton::Diving::divingStatus != SUBMERGING) {
      return false;
   } else {
      // depth == 0 means that we just discard depth.
      if(automaton::Diving::depthM == 0) {
         return divingcell::DivingCellManager::getStatus() == divingcell::FULLY_OPENED;
      } else {
         return (sensors::depth::update() * (1 + DEPTH_TOLERANCE)) >= automaton::Diving::depthM;
      }
   }
}

bool automaton::Diving::emergingDone() {
   if(automaton::Diving::divingStatus != EMERGING) {
      return false;
   } else {
      // depth == 0 means that we just discard depth.
      if(automaton::Diving::depthM == 0) {
         return divingcell::DivingCellManager::getStatus() == divingcell::FULLY_CLOSED;
      } else {
         return sensors::depth::update() <= DEPTH_TOLERANCE;
      }
   }
}

bool automaton::Diving::newDataIntervalReached() {
   if(automaton::Diving::depthM > 0) {
      float measurementIntervalM = (float)automaton::Diving::depthM / DATA_BUFFER_SIZE;
      return (((measurementIntervalM * automaton::Diving::dataIndex) <= sensors::depth::update() && automaton::Diving::divingStatus == SUBMERGING));
   } else {
      return ((divingcell::DivingCellManager::getCurrentNumberOfSteps() >= ((float)automaton::Diving::dataIndex / DATA_BUFFER_SIZE) * MAX_NUMBER_OF_STEPS) && automaton::Diving::divingStatus == SUBMERGING);
   }
}
