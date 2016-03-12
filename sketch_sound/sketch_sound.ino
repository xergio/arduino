
/*
http://www.princetronics.com/sound-sensitive-lights-w-sound-sensor-arduino/
*/

#include <LiquidCrystal.h>

#define SOUND_APin A1 // Pin Análogico al que he conectado el sensor de sonido

LiquidCrystal lcd(9, 10, 4, 5, 6, 7); // syntax: LiquidCrystal(rs, enable, d4, d5, d6, d7)

int timer = 0;
int milis = 0;
int sound = 0;


void setup() { // put your setup code here, to run once:
	Serial.begin(9600);
	lcd.begin(16, 2);

	lcd.print("  hue hue hue   ");
}


void loop() { // put your main code here, to run repeatedly:

	sound = analogRead(SOUND_APin);

	lcd.clear();
	lcd.setCursor(10, 2);
	lcd.print(sound);
	Serial.println(sound);

	delay(200);
}
