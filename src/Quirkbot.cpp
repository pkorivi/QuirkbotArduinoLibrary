#include "Quirkbot.h"

Quirkbot_::Quirkbot_(){
	inited = false;
}
void Quirkbot_::setup(void){
	inited = true;
	Bot::start();
	// Setup the timer interrupt
	TCCR4B = 7;
	TCCR4A = 0;
	TCCR4C = 0;
	TCCR4D = 0;
	TCCR4E = 0;
	TIFR4 = (1<<TOV4);
	TCNT4 = 0;
	TIMSK4 = (1<<TOIE4);
	PLLFRQ = 0b01011010;
}
void Quirkbot_::loop(void){
	if(!inited) {
		return;
	}
	Bot::update();
}
void Quirkbot_::delay_(unsigned long ms){
	if(!inited) {
		return (delay)(ms);
	}
	unsigned long deadline = Bot::millis + ms;
	while(Bot::millis < deadline){
		Bot::update();
	}
}
void Quirkbot_::delayMicroseconds_(unsigned long us){
	if(!inited) {
		return (delayMicroseconds)(us);
	}
	if(us > 1000){
		return delay_((float)us / 1000.0);
	}
	unsigned int deadline = Bot::micros + us;
	while(Bot::micros < deadline){
		Bot::update();
	}
}
void Quirkbot_::disableSerialReport(void){
	Bot::serialReportEnabled = false;
}
void Quirkbot_::enableSerialReport(void){
	Bot::serialReportEnabled = true;
}
ISR(TIMER4_OVF_vect) {
	Bot::interruptUpdate();
}

Quirkbot_ Quirkbot;