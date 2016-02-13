#include <DHT.h>

#define DHT_APin A0 // Pin Análogico al que he conectado el sensor
#define DHT_Type DHT11 // mi sensor es el DHT11

DHT dht(DHT_APin, DHT_Type);

int ledPin = 13;

void setup() { // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() { // put your main code here, to run repeatedly:
  delay(60000); // 1 minuto

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
  
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}
