const int led1 = 9;  
int pin_sensor = A0;
int valor_sensor = 0;
void setup() {
  pinMode(led1,OUTPUT);
}
void loop() {
  valor_sensor = analogRead(pin_sensor) / 4;
  analogWrite(led1, valor_sensor);
  delay(10);
}