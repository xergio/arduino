
/*
LCD:

https://www.arduino.cc/en/Reference/LiquidCrystal
https://www.youtube.com/watch?v=dZZynJLmTn8
https://www.youtube.com/watch?v=R-CRIthB7ZY
http://howtomechatronics.com/tutorials/arduino/lcd-tutorial/


DHT (temp & hum)

https://github.com/adafruit/DHT-sensor-library/blob/master/examples/DHTtester/DHTtester.ino

Photoresistor
https://learn.adafruit.com/photocells/using-a-photocell
https://arduinodiy.wordpress.com/2013/11/03/measuring-light-with-an-arduino/
*/

#include <DHT.h>
#include <LiquidCrystal.h>

#define DHT_APin A0 // Pin Análogico al que he conectado el sensor de temperatura
#define DHT_Type DHT22 // mi sensor es el DHT11
#define PHOTORES_APin A2 // Pin Análogico al que he conectado el sensor de luz

// init
DHT dht(DHT_APin, DHT_Type);
LiquidCrystal lcd(9, 10, 4, 5, 6, 7); // syntax: LiquidCrystal(rs, enable, d4, d5, d6, d7)

int timer = 0;
int milis = 0;
int ticks = 0;
int tmp = 0;
int loops = 0;
int luzMin = 1024; // máximo de lectura para el sensor
int luzMax = 0;
long luzSum = 0; // value use to exceed INT


void setup() { // put your setup code here, to run once:
	Serial.begin(9600);
	dht.begin();
	lcd.begin(16, 2);

	lcd.print("  hue hue hue   ");
}


void loop() { // put your main code here, to run repeatedly:
	timer = 59 - ((millis() / 1000) % 60);
	if (timer == ticks) {
		return;
	}

	ticks = timer;
	loops++;

	tmp = analogRead(PHOTORES_APin);
	luzMin = min(luzMin, tmp);
	luzMax = max(luzMax, tmp);
	luzSum += tmp;

	if (timer == 59) {
		// Reading temperature or humidity takes about 250 milliseconds!
		// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
		float h = dht.readHumidity();
		float t = dht.readTemperature(); // lectura en Celsius, readTemperature(true) para Fahrenheit

		if (isnan(h) || isnan(t)) {
			Serial.println("E"); // E = error, para el script en python que lee
			return;
		}

		// Compute heat index in Celsius (isFahreheit = false)
		float hic = dht.computeHeatIndex(t, h, false); // sensación térmica


		// D = DHT, para el script en python que leerá esto
		Serial.print("D h:");
		Serial.print(h);
		Serial.print(" t:");
		Serial.print(t);
		Serial.print(" i:");
		Serial.print(hic);
		Serial.print(" la:");
		Serial.print(luzSum/loops);
		Serial.print(" ln:");
		Serial.print(luzMin);
		Serial.print(" lx:");
		Serial.print(luzMax);
		Serial.println("");

		lcd.clear();
		lcd.print(t);
		lcd.print("C    ");
		lcd.print(h);
		lcd.print("%");
		lcd.setCursor(0, 2);
		lcd.print(hic);
		lcd.print("C");

		digitalWrite(13, HIGH);
		delay(100);
		digitalWrite(13, LOW);

		// reset counters
		loops = 0;
		luzMin = 1024;
		luzMax = 0;
		luzSum = 0;
	}

	lcd.setCursor(10, 2);
	lcd.print(tmp);

	lcd.setCursor(14, 2);
	if (timer < 10)
		lcd.print(0);
	lcd.print(timer);

	delay(100);
}


/* Not used now
double Lux(int RawADC0) {
	double Vout = RawADC0 * 0.0048828125;
	//int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
	int lux = (2500 / Vout-500) / 10;
	return lux;
}
*/

/* GRAFANA: 
SELECT (2500 / (mean("avg") * 0.0048828125) - 500) / 10, 
       (2500 / (min("min") * 0.0048828125) - 500) / 10, 
       (2500 / (max("max") * 0.0048828125) - 500) / 10 
FROM "luminosidad" 
WHERE $timeFilter 
GROUP BY time(2m)
*/