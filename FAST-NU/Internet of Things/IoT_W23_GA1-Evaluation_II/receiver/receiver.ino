int bulb1=8, bulb2=9;
char data;

void setup() {
  Serial.begin(9600);
  pinMode(bulb1,OUTPUT);
  pinMode(bulb2,OUTPUT);
}

void loop() {
  data=Serial.read();
  if(data=='a')
  {
    digitalWrite(bulb1,HIGH);
    digitalWrite(bulb2,LOW);
    delay(10);
  }
  if(data=='b')
  {
    digitalWrite(bulb1,LOW);
    digitalWrite(bulb2,HIGH);
    delay(10);
  }
  if(data=='c')
  {
    digitalWrite(bulb1,HIGH);
    digitalWrite(bulb2,HIGH);
    delay(10);
  }
  if(data=='d')
  {
    digitalWrite(bulb1,LOW);
    digitalWrite(bulb2,LOW);
    delay(10);
  }
}
