
/*
LCD:

https://www.arduino.cc/en/Reference/LiquidCrystal
https://www.youtube.com/watch?v=dZZynJLmTn8
https://www.youtube.com/watch?v=R-CRIthB7ZY
http://howtomechatronics.com/tutorials/arduino/lcd-tutorial/


DHT (temp & hum)

https://github.com/adafruit/DHT-sensor-library/blob/master/examples/DHTtester/DHTtester.ino
*/

#include <DHT.h>
#include <LiquidCrystal.h>

#define LED_Pin 13 // Pin del led de la placa
#define DHT_APin A0 // Pin Análogico al que he conectado el sensor de temperatura
#define DHT_Type DHT22 // mi sensor es el DHT11
//#define PHOTORES_APin 3 // Pin Análogico al que he conectado el sensor de luz

// init
DHT dht(DHT_APin, DHT_Type);
LiquidCrystal lcd(9, 10, 4, 5, 6, 7); // syntax: LiquidCrystal(rs, enable, d4, d5, d6, d7)

int timer = 0;
int interval = 60;
//int luz;

void setup() { // put your setup code here, to run once:
	Serial.begin(9600);
	dht.begin();
	lcd.begin(16, 2);

	pinMode(LED_Pin, OUTPUT);
	//pinMode(PHOTORES_APin, INPUT);

	lcd.print("  hue hue hue");

}

void loop() { // put your main code here, to run repeatedly:
	timer--;

	if (timer <= 0) {
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

		//luz = digitalRead(PHOTORES_APin);

		// D = DHT, para el script en python que leerá esto
		Serial.print("D h:");
		Serial.print(h);
		Serial.print(" t:");
		Serial.print(t);
		Serial.print(" i:");
		Serial.print(hic);
		//Serial.print(" l:");
		//Serial.print(luz);
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
		//delay(60000); // 1 minuto

		timer = interval;
	}

	lcd.setCursor(14, 2);
	if (timer < 10)
		lcd.print(0);
	lcd.print(timer);
	delay(1000);
}
