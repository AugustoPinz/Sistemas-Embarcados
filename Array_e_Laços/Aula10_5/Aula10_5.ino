int leds[3] = {11,10,9}; 
const int tempos[3] = {5000, 2000, 5000};

void setup() {
 
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
 }
}

void loop() {
  for (int i = 0; i < 3; i++) {
  digitalWrite(leds[i], HIGH); 
  delay(tempos[i]);            
  digitalWrite(leds[i], LOW);  
  }
   
}
