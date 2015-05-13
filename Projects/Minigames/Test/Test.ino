const int buttonPin = 8;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  Serial.print(!digitalRead(buttonPin));
  delay(25);
}
