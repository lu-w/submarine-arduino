#include "DivingCellManager.h"

unsigned long divingcell::DivingCellManager::currentNumberOfSteps = 0;
divingcell::DivingCellStatus divingcell::DivingCellManager::status = FULLY_CLOSED;
divingcell::Direction divingcell::DivingCellManager::direction = OPEN;

void divingcell::DivingCellManager::setup() {
   pinMode(STEPPER_DIR, OUTPUT);
   pinMode(STEPPER_STEP, OUTPUT);
	pinMode(STEPPER_ACTIVE, OUTPUT);
   digitalWrite(STEPPER_STEP, LOW);
   divingcell::DivingCellManager::setDirection(OPEN);
   divingcell::DivingCellManager::setSleep(true);
}

void divingcell::DivingCellManager::setSleep(bool sleep) {
   if(sleep) {
	     digitalWrite(STEPPER_ACTIVE, LOW);
   } else {
	     digitalWrite(STEPPER_ACTIVE, HIGH);
   }
   #if DEBUG
      if(sleep) Serial.println("Motor put to sleep mode.");
      else Serial.println("Motor was awaken.");
   #endif
}

void divingcell::DivingCellManager::setDirection(divingcell::Direction direction) {
	switch(direction) {
		case OPEN:
			digitalWrite(STEPPER_DIR, LOW);
         #if DEBUG
            Serial.println("Direction of syringe: Open");
         #endif
			break;
		case CLOSE:
			digitalWrite(STEPPER_DIR, HIGH);
         #if DEBUG
            Serial.println("Direction of syringe: Close");
         #endif
			break;
	}
	divingcell::DivingCellManager::direction = direction;
}

void divingcell::DivingCellManager::move() {
	// Asserts that we don't do too much steps in one direction and destroy the cell.
	if(!(divingcell::DivingCellManager::direction == OPEN && divingcell::DivingCellManager::status == FULLY_OPENED)
		&& !(divingcell::DivingCellManager::direction == CLOSE && divingcell::DivingCellManager::status == FULLY_CLOSED)) {
		// Does on step.
		digitalWrite(STEPPER_STEP, HIGH);
      #if !DEBUG
		    delay(1);
      #endif
		digitalWrite(STEPPER_STEP, LOW);
      #if !DEBUG
		    delay(1);
      #endif
		divingcell::DivingCellManager::currentNumberOfSteps++;
      #if DEBUG
         if(divingcell::DivingCellManager::currentNumberOfSteps % 10000 == 0) Serial.println(divingcell::DivingCellManager::currentNumberOfSteps);
      #endif
      // Checks if we need to reverse directions after the current step.
		if(divingcell::DivingCellManager::currentNumberOfSteps == MAX_NUMBER_OF_STEPS) {
			divingcell::DivingCellManager::currentNumberOfSteps = 0;
			if(divingcell::DivingCellManager::direction == OPEN) {
				divingcell::DivingCellManager::status = FULLY_OPENED;
			} else {
				divingcell::DivingCellManager::status = FULLY_CLOSED;
			}
		} else if(divingcell::DivingCellManager::status == FULLY_CLOSED || divingcell::DivingCellManager::status == FULLY_OPENED) {
			divingcell::DivingCellManager::status = IN_BETWEEN;
		}
	}
}

divingcell::DivingCellStatus divingcell::DivingCellManager::getStatus() {
	return divingcell::DivingCellManager::status;
}

unsigned long divingcell::DivingCellManager::getCurrentNumberOfSteps() {
   return divingcell::DivingCellManager::currentNumberOfSteps;
}
