#ifndef Quirkbot_h_
#define Quirkbot_h_

#include "Arduino.h"

// Keyboard & Mouse
#include "KeyPress.h"
#include "KeySequence.h"

// Signal
#include "Wave.h"
#include "Randomizer.h"

// Sensors
#include "AnalogSensor.h"
#include "DigitalSensor.h"
#include "CircuitTouch.h"
#include "SqueezeSensor.h"
#include "IRProximity.h"
#include "LightSensor.h"
#include "Sonar.h"

// Light
#include "Led.h"
#include "DualColorLed.h"
#include "RGBLed.h"

// Movement
#include "ServoMotor.h"
#include "ContinuousServo.h"

// Sound
#include "Buzzer.h"

// General
#include "VoltageOutput.h"

// Logic
#include "Mathematics.h"
#include "Converter.h"
#include "List.h"
#include "Sequence.h"
#include "Gate.h"

// Debug
#include "SystemMemory.h"
#include "SerialMonitor.h"
#include "Time.h"

class Quirkbot_{
	public:
	void setup(void);
	void loop(void);
	void delay(unsigned long ms);
	void delayMicroseconds(unsigned int us);
	void disableSerialReport(void);
	void enableSerialReport(void);
};
extern Quirkbot_ Quirkbot;

#endif
