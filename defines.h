#pragma once

#ifndef DEFINES_H
#define DEFINES_H

// When set to != 0, debug output is printed to serial connection.
#define DEBUG 1

// Bluetooth pins.
#define BT_RX_PIN 11
#define BT_TX_PIN 10

// Motor pins.
#define STEPPER_ACTIVE 49
#define STEPPER_DIR 51
#define STEPPER_STEP 53

// Number of states of the submarine automaton.
#define NUMBER_OF_STATES 3

// Sensor settings.
#define NUMBER_OF_SENSORS 3

// Temperature sensor pin.
#define TEMPERATURE_ONE_WIRE_BUS 2

// Pressure sensor pin.
#define PRESSURE_PIN A0
// Max values for the pressure pin.
#define MAX_PRESSURE_BAR 12
#define MAX_SENSOR_VALUE 1023

// Number of steps the motor is allowed to do.
#define MAX_NUMBER_OF_STEPS 160000

// How many data items can be collected (Be careful, memory is limited).
#define DATA_BUFFER_SIZE 8

// The intervall in which the depth may deviate.
#define DEPTH_TOLERANCE 0.1

#endif
