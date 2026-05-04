int leds[5] = {5,6,7,8,9};
void setup() {
 
  for(int i=0;i<5;i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
    delay(500);
  }
  
}
void loop() {   
}
