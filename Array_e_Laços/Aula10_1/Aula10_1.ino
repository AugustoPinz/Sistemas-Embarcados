int led = 9;
void setup()
{
  pinMode(led, OUTPUT);
  for(int i=0;i<20;i++){
    digitalWrite(led, HIGH);
  	delay(500);
      digitalWrite(led,LOW);
  	delay(500);
  }
}

void loop()
{
}
