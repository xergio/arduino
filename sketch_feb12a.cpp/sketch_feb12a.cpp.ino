int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("led 13!");
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(5000);
}
