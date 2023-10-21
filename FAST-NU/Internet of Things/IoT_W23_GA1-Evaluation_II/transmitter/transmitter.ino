int button1=13, button2=12, b1,b2;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop() {
  b1=digitalRead(button1);
  b2=digitalRead(button2);
  if((b1==LOW)&&(b2==HIGH))
  {
    Serial.print('a');
    delay(10);
  }
  if((b1==HIGH)&&(b2==LOW))
  {
    Serial.print('b');
    delay(10);
  }
  if((b1==LOW)&&(b2==LOW))
  {
    Serial.print('c');
    delay(10);
  }
  if((b1==HIGH)&&(b2==HIGH))
  {
    Serial.print('d');
    delay(10);
  }

}
