ARDUINO_DIR       = /usr/share/arduino
ARDMK_DIR         = /usr/share/arduino
AVR_TOOLS_DIR     = /usr
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/arduino/avr/cores/arduino
BOARDS_TXT        = /usr/share/arduino/hardware/arduino/avr/boards.txt
ARDUINO_VAR_PATH  = /usr/share/arduino/hardware/arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/arduino/avr/bootloaders
BOARD_TAG         = uno
ARDUINO_PORT      = /dev/ttyACM0
ARDUINO_LIBS      = Time SoftwareSerial OneWire DallasTemperature
CXXFLAGS         += -std=c++11

include /usr/share/arduino/Arduino.mk

