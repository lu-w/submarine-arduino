#ifndef DIVINGCELLMANAGER_H
#define DIVINGCELLMANAGER_H

#include "Arduino.h"
#include "../defines.h"

namespace divingcell {
	enum DivingCellStatus {FULLY_CLOSED, IN_BETWEEN, FULLY_OPENED};
	enum Direction {OPEN, CLOSE};

	class DivingCellManager {
	public:
		/**
		 * Sets the motor control up, sets pin modes etc. Assumes that the tank
		 * is fully closed and wants to open somewhen after startup.
		 */
		static void setup();

		/**
		 * Sets whether the diving cell motor is in sleep mode or not.
		 * @param sleep The mode.
		 */
		static void setSleep(bool sleep);

		/**
		 * Sets the direction in which to move the tank.
		 * @param direction The direction in which to move the tank.
		 */
		static void setDirection(Direction direction);

		/**
		 * Moves the the tank by one step in the specified direction.
		 */
		static void move();

		/**
		 * Returns the status of the diving cell.
		 * @return The status of the cell.
		 */
		static DivingCellStatus getStatus();

		/**
		 *
		 */
		static unsigned long getCurrentNumberOfSteps();
	private:
		// The current number of steps of the stepper motor.
		static unsigned long currentNumberOfSteps;
		// The current status of the cell.
		static DivingCellStatus status;
		// The current direction in which to move the stepper motor.
		static Direction direction;
	};
}

#endif
