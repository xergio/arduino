
// https://www.arduino.cc/en/Reference/LiquidCrystal
// https://www.youtube.com/watch?v=dZZynJLmTn8
// http://howtomechatronics.com/tutorials/arduino/lcd-tutorial/

#include <DHT.h>
#include <LiquidCrystal.h>

#define DHT_APin A0 // Pin Análogico al que he conectado el sensor
#define DHT_Type DHT11 // mi sensor es el DHT11

// init
DHT dht(DHT_APin, DHT_Type);
LiquidCrystal lcd(9, 10, 4, 5, 6, 7); // syntax: LiquidCrystal(rs, enable, d4, d5, d6, d7) 

// defs
int ledPin = 13;

void setup() { // put your setup code here, to run once:
	Serial.begin(9600);
	dht.begin();
	lcd.begin(16, 2);
	pinMode(ledPin, OUTPUT);

	lcd.print("    hue hue");
	lcd.setCursor(0, 2);
	lcd.print("    boot");
	delay(500);
	lcd.print(".");
	delay(500);
	lcd.print(".");
	delay(500);
	lcd.print(".");
	delay(1000);

}

void loop() { // put your main code here, to run repeatedly:

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
	Serial.println("");

	lcd.clear();
	lcd.print(t);
	lcd.print("C    ");
	lcd.print(h);
	lcd.print("%");
	lcd.setCursor(0, 2);
	lcd.print(hic);
	lcd.print("C");

	digitalWrite(ledPin, HIGH);
	delay(100);
	digitalWrite(ledPin, LOW);
	delay(60000); // 1 minuto
}
