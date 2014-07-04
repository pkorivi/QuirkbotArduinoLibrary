#ifndef SonarSensor_h_
#define SonarSensor_h_

#include "Sensor.h"

class SonarSensor :
public Sensor
{
	public:
	
	SonarSensor(){
		registerInput(pin);

		centimetersConversion = 27.0;
		inchesConversion = 146.0;
		normalizingFactor = 5000.0;
	};

	void onInterval();

	Input<int> pin;

	Output<float> micros;
	Output<float> centimeters;
	Output<float> inches;

	float centimetersConversion;
	float inchesConversion;
	
	protected:
	void onInternalInputChange(BaseInput &input);
};
typedef SonarSensor Sonar;

void SonarSensor::onInternalInputChange(BaseInput &input){
	if(&input == &interval){
		if(interval < 0.05) interval = 0.05;
	}
};
void SonarSensor::onInterval(){
	if(pin == -1) return;


	pinMode(pin, OUTPUT);

	digitalWrite(pin, LOW);
	delayMicroseconds(2);
	digitalWrite(pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pin, LOW);

	pinMode(pin, INPUT);

	float reading = pulseIn(pin, HIGH, 5000);

	if(reading == 0) return;

	processReading(reading);

	micros = value;
	centimeters = value / centimetersConversion;
	inches = value / inchesConversion;
};


#endif
