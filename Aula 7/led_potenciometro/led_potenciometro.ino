int pin_sensor = A0;
int valor_sensor = 0;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
void setup() {
  pinMode(pin_sensor,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
 Serial.begin(115200);
}

void loop() {
  valor_sensor = analogRead(pin_sensor);
  Serial.print("Valor analogico =");
  Serial.println(valor_sensor);
  delay(200);
if (valor_sensor < 205) {
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
}
else if ((valor_sensor >= 205) && (valor_sensor < 409 )) {
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
}
else if ((valor_sensor >= 409) && (valor_sensor < 614 )) {
digitalWrite(led1,LOW);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
}
else if ((valor_sensor >= 614) && (valor_sensor < 818)) {
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);
}
else {
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,HIGH);
}

}