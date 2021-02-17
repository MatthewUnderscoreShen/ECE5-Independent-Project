int x = 0;
int y = 0;
int z = 0;

void setup() {
  pinMode(A8,INPUT); // VRx
  pinMode(A9,INPUT); // VRy
  pinMode(26,INPUT_PULLUP); // SW
  Serial.begin(9600);

}

void loop() {
  x = analogRead(A8);
  Serial.print("X:");
  Serial.print(x,DEC);

  y = analogRead(A9);
  Serial.print(" | Y:");
  Serial.print(y, DEC);

  z = digitalRead(26);
  Serial.print(" | Button:");
  Serial.println(z, DEC);

  if (z==0) {
    Serial.print("PRESSED");
  }

  delay(100);

}
