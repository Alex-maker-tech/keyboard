String str = "";
int a = 0;
int timer = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (millis() - timer >= 250) {
    ledState = !ledState;
    digitalWrite(13, ledState);
    Serial.print(0);
    Serial.print(',');
    Serial.print(analogRead(A0));
    Serial.print(',');
    Serial.print(analogRead(A0));
    Serial.print(',');
    Serial.println(analogRead(A0));
  }
}
